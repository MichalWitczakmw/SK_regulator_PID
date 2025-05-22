#include "mainwindow.h"
#include <QFile>
#include <QFileDialog>
#include <QTimer>
#include <QInputDialog>
#include <QMessageBox>
#include "./ui_mainwindow.h"
#include "networkdialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , simulation(Simulation::get_instance())
    , chart(new ChartWidget(this)) // Inicjalizacja chart
    , client(new MyTCPClient(this)) // Inicjalizacja client
    , server(nullptr) // Serwer ustawiony na nullptr
    , networkdialog(nullptr) // Dialog sieciowy również ustawiony na nullptr
{
    ui->setupUi(this);
    init();

    // Połączenia sygnałów symulacji z MainWindow
    connect(&simulation, &Simulation::simulation_start, this, &MainWindow::simulation_start);
    connect(&simulation, &Simulation::simulation_stop, this, &MainWindow::simulation_stop);

    // Łączenie sygnałów klienta z funkcjami symulacji i wykresu
    connect(client, &MyTCPClient::newFrameReceived, this, &MainWindow::addSeriesFromFrame);

    // Połączenia sygnałów UI z funkcjami MainWindow
    connect(ui->action_save_as, &QAction::triggered, this, &MainWindow::action_save_as);
    connect(ui->action_open, &QAction::triggered, this, &MainWindow::action_open);
    connect(ui->action_export, &QAction::triggered, this, &MainWindow::action_simulation_export);
    connect(ui->action_simulation_open, &QAction::triggered, this, &MainWindow::action_simulation_open);
    connect(ui->Network, &QPushButton::clicked, this, &MainWindow::on_Network_clicked);
    connect(ui->chackNetwork, &QPushButton::clicked, this, &MainWindow::on_chackNetwork_clicked);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete server;
    delete client;
    delete networkdialog;
}

void MainWindow::init()
{
    // Inicjalizacja symulacji i elementów UI
    simulation.stop();
    ui->simulation_interval_input->setValue(simulation.get_interval());
    ui->simulation_duration_input->setValue(simulation.durration);

    ui->pid_kp_input->setValue(simulation.pid->get_kp());
    ui->pid_ti_input->setValue(simulation.pid->get_ti());
    ui->pid_td_input->setValue(simulation.pid->get_td());

    ui->generator_amplitude_input->setValue(simulation.generator->get_amplitude());
    ui->generator_frequency_input->setValue(simulation.generator->get_frequency());
    ui->generator_generatortype_input->setCurrentIndex(static_cast<int>(simulation.generator->get_type()));
    ui->generator_infill_input->setValue(simulation.generator->get_infill());

    ui->arx_noise_input->setValue(simulation.arx->get_noise());
    ui->arx_noisetype_input->setCurrentIndex(static_cast<int>(simulation.arx->get_noise_type()));
    ui->arx_delay_input->setValue(simulation.arx->get_delay());
}

void MainWindow::simulation_start()
{
    ui->simulation_start_button->setEnabled(false);
    ui->simulation_stop_button->setEnabled(true);
}

void MainWindow::simulation_stop()
{
    ui->simulation_start_button->setEnabled(true);
    ui->simulation_stop_button->setEnabled(false);
}

void MainWindow::on_simulation_start_button_clicked()
{
    simulation.start();
}

void MainWindow::on_simulation_stop_button_clicked()
{
    simulation.stop();
}

void MainWindow::on_simulation_duration_input_editingFinished()
{
    simulation.set_duration(ui->simulation_duration_input->value());
}

void MainWindow::on_simulation_interval_input_editingFinished()
{
    simulation.set_interval(ui->simulation_interval_input->value());
}

void MainWindow::on_simulation_reset_button_clicked()
{
    simulation.reset();
}

void MainWindow::on_Network_clicked()
{
    if (ui->Network->text() == "Network") {
        if (!networkdialog) {
            networkdialog = new NetworkDialog(this);

            connect(networkdialog, &NetworkDialog::dialogClosed, [this]() {
                networkdialog = nullptr;
            });

            connect(networkdialog, &NetworkDialog::sendData, this, &MainWindow::handleNetworkInstance);
        }
        networkdialog->show();
    } else if (ui->Network->text() == "Disconnect") {
        QMessageBox::StandardButton reply = QMessageBox::question(
            this, "Disconnect", "Are you sure you want to disconnect?", QMessageBox::Yes | QMessageBox::No);

        if (reply == QMessageBox::Yes) {
            if (server) {
                server->disconnectClients();
                delete server;
                server = nullptr;
            } else if (client) {
                client->notifyDisconnection();
                delete client;
                client = nullptr;
            }

            ui->Network->setText("Network");
            ui->labelConnected->setText("Disconnected");
        }
    }
}

void MainWindow::handleNetworkInstance(QObject *networkInstance)
{
    if (auto *serverInstance = qobject_cast<MyTCPServer *>(networkInstance)) {
        server = serverInstance;
        Simulation::get_instance().set_mode(SimulationMode::Server);

        connect(&simulation, &Simulation::frameReadyToSendToClient, server, &MyTCPServer::sendFrame);

        connect(server, &MyTCPServer::clientConnected, this, [this](QString clientAddress, quint16 clientPort) {
            ui->labelConnected->setText("Client Connected");
            ui->Network->setText("Disconnect");
            QMessageBox::information(this, "New Connection",
                                     QString("New client (ARX) from: ::ffff:%1").arg(clientAddress));
        });

        connect(server, &MyTCPServer::clientDisconnected, this, [this]() {
            QMessageBox::information(this, "Disconnected", "Client has disconnected.");
            ui->labelConnected->setText("No clients connected");
            delete server;
            server = nullptr;
        });

        updateControlsBasedOnRole(true);
    } else if (auto *clientInstance = qobject_cast<MyTCPClient *>(networkInstance)) {
        client = clientInstance;
        Simulation::get_instance().set_mode(SimulationMode::Client);

        connect(client, &MyTCPClient::serverDisconnected, this, [this]() {
            QMessageBox::warning(this, "Connection Lost", "Server is not available.");
            delete client;
            client = nullptr;
        });

        ui->labelConnected->setText("Connecting...");
        updateControlsBasedOnRole(false);
    }
}

void MainWindow::updateControlsBasedOnRole(bool isServer)
{
    ui->simulation_start_button->setEnabled(isServer);
    ui->simulation_stop_button->setEnabled(isServer);
    ui->simulation_reset_button->setEnabled(isServer);
    ui->simulation_interval_input->setEnabled(isServer);
    ui->simulation_duration_input->setEnabled(isServer);

    ui->pid_kp_input->setEnabled(isServer);
    ui->pid_ti_input->setEnabled(isServer);
    ui->pid_td_input->setEnabled(isServer);
    ui->generator_amplitude_input->setEnabled(isServer);
    ui->generator_frequency_input->setEnabled(isServer);
    ui->generator_generatortype_input->setEnabled(isServer);
    ui->generator_infill_input->setEnabled(isServer);

    ui->arx_noise_input->setEnabled(!isServer);
    ui->arx_noisetype_input->setEnabled(!isServer);
    ui->arx_delay_input->setEnabled(!isServer);
    ui->arx_a_input->setEnabled(!isServer);
    ui->arx_b_input->setEnabled(!isServer);
}

void MainWindow::on_chackNetwork_clicked()
{
    if (server && server->isListening()) {
        ui->labelChacConnected->setText("All Right");
    } else if (client && client->isConnected()) {
        ui->labelChacConnected->setText("All Right");
    } else {
        ui->labelChacConnected->setText("Offline");
    }
}

void MainWindow::addSeriesFromFrame(const SimulationFrame &frame)
{
    chart->add_series("PID Output", frame.pid_output, ChartPosition::top);
    chart->add_series("ARX Output", frame.arx_output, ChartPosition::bottom);
    chart->add_series("Noise", frame.noise, ChartPosition::middle);
}
void MainWindow::on_pid_td_input_editingFinished()
{
    simulation.pid->set_td(ui->pid_td_input->value());
}

void MainWindow::on_pid_kp_input_editingFinished()
{
    simulation.pid->set_kp(ui->pid_kp_input->value());
}

void MainWindow::on_generator_amplitude_input_editingFinished()
{
    simulation.generator->set_amplitude(ui->generator_amplitude_input->value());
}

void MainWindow::on_generator_frequency_input_editingFinished()
{
    simulation.generator->set_frequency(ui->generator_frequency_input->value());
}

void MainWindow::on_arx_noise_input_editingFinished()
{
    simulation.arx->set_noise(ui->arx_noise_input->value());
}

void MainWindow::on_arx_noisetype_input_currentIndexChanged(int index)
{
    simulation.arx->set_noise_type(static_cast<NoiseType>(index));
}

void MainWindow::on_arx_delay_input_editingFinished()
{
    simulation.arx->set_delay(ui->arx_delay_input->value());
}

void MainWindow::on_arx_b_input_editingFinished()
{
    QString input = ui->arx_b_input->text();
    QStringList b_values = input.split(",");
    std::vector<float> b;

    for (const QString& value : b_values) {
        if (!value.isEmpty()) {
            b.push_back(value.toFloat());
        }
    }

    simulation.arx->set_b(b);
}

void MainWindow::on_arx_a_input_editingFinished()
{
    QString input = ui->arx_a_input->text();
    QStringList a_values = input.split(",");
    std::vector<float> a;

    for (const QString& value : a_values) {
        if (!value.isEmpty()) {
            a.push_back(value.toFloat());
        }
    }

    simulation.arx->set_a(a);
}

void MainWindow::action_simulation_export()
{
    // Implementacja eksportu symulacji
    qDebug() << "Eksportowanie symulacji...";
}

void MainWindow::action_save_as()
{
    // Implementacja zapisu symulacji
    qDebug() << "Zapisywanie symulacji...";
}

void MainWindow::action_open()
{
    // Implementacja otwierania symulacji
    qDebug() << "Otwieranie symulacji...";
}
void MainWindow::on_pid_ti_input_editingFinished()
{
    simulation.pid->set_ti(ui->pid_ti_input->value());
}

void MainWindow::on_generator_generatortype_input_currentIndexChanged(int index)
{
    simulation.generator->set_type(static_cast<GeneratorType>(index));
}

void MainWindow::on_generator_infill_input_editingFinished()
{
    simulation.generator->set_infill(ui->generator_infill_input->value());
}

void MainWindow::on_outside_sum_radio_clicked()
{
    if (!simulation.get_outside_sum()) {
        simulation.set_outside_sum(true);
        ui->inside_sum_radio->setChecked(false);
    }
}

void MainWindow::on_inside_sum_radio_clicked()
{
    if (simulation.get_outside_sum()) {
        simulation.set_outside_sum(false);
        ui->outside_sum_radio->setChecked(false);
    }
}

void MainWindow::action_simulation_open()
{
    QString file_name = QFileDialog::getOpenFileName(this, "Open Simulation", "", "Simulation Files (*.sim)");
    if (file_name.isEmpty()) return;

    QFile file(file_name);
    if (file.open(QIODevice::ReadOnly)) {
        std::vector<std::byte> data(file.size());
        file.read(reinterpret_cast<char *>(data.data()), data.size());
        simulation.deserialize(data);
        file.close();
    }

    init(); // Odśwież wartości w UI po otwarciu
}

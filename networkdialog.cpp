#include "networkdialog.h"
#include "ui_networkdialog.h"
#include "networkclient.h"
#include "networkserver.h"
#include <QMessageBox>

NetworkDialog::NetworkDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::NetworkDialog)
{
    ui->setupUi(this);

    // Podłącz przycisk zamknięcia do slotu
    connect(ui->pushConnect, &QPushButton::clicked, this, &NetworkDialog::on_pushConnect_clicked);

    // Domyślne zaznaczenie opcji "Server (PID)" i dezaktywacja pola IP
    ui->radioServerPID->setChecked(true);
    ui->textIP->setEnabled(false);

    // Podłącz zmiany stanu radiobuttonów do odpowiednich funkcji
    connect(ui->radioServerPID, &QRadioButton::toggled, this, [this](bool checked) {
        if (checked) {
            ui->textIP->setEnabled(false); // Dezaktywuj pole IP
        }
    });

    connect(ui->radioClientARX, &QRadioButton::toggled, this, [this](bool checked) {
        if (checked) {
            ui->textIP->setEnabled(true); // Aktywuj pole IP
        }
    });

    // Domyślne wartości pola PORT
    ui->textPORT->setPlainText("8080");

}

NetworkDialog::~NetworkDialog()
{
    delete ui;
}

void NetworkDialog::on_pushConnect_clicked()
{
    QString ip = ui->textIP->toPlainText();
    int port = ui->textPORT->toPlainText().toInt();

    if (ui->radioServerPID->isChecked()) {
        // Tworzenie instancji serwera
        server = new MyTCPServer(this);
        if (server->startListening(port)) {
            emit sendData(server); // Wyślij wskaźnik do serwera
            QMessageBox::information(this, "Serwer", "Serwer został uruchomiony. Oczekiwanie na klienta...");
        } else {
            // Obsługa błędu
            QMessageBox::warning(this, "Serwer", "Nie udało się uruchomić serwera.");
            delete server;
            server = nullptr;
        }
    } else if (ui->radioClientARX->isChecked()) {
        // Tworzenie instancji klienta
        client = new MyTCPClient(this);
        client->connectTo(ip, port);
        emit sendData(client); // Wyślij wskaźnik do klienta
    }

    this->accept(); // Zamykamy okno dialogowe po akceptacji
}
void NetworkDialog::closeEvent(QCloseEvent *event)
{
    emit dialogClosed();  // Emitujemy sygnał o zamknięciu
    QDialog::closeEvent(event);  // Wywołujemy metodę bazową
}


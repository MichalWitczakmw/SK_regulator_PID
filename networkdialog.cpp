#include "networkdialog.h"
#include "ui_networkdialog.h"
#include "networkclient.h"
#include "networkserver.h"

NetworkDialog::NetworkDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::NetworkDialog)
{
    ui->setupUi(this);

    // Podłącz przycisk zamknięcia do slotu
    connect(ui->pushConnect, &QPushButton::clicked, this, &NetworkDialog::on_pushConnect_clicked);

    ui->radioClientARX->setChecked(true);
    ui->textIP->setPlainText("127.0.0.1");
    ui->textPORT->setPlainText("123456");

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
        } else {
            // Obsługa błędu
            delete server;
            server = nullptr;
        }
    } else {
        // Tworzenie instancji klienta
        client = new MyTCPClient(this);
        client->connectTo(ip, port);
        emit sendData(client); // Wyślij wskaźnik do klienta
    }

    // Zamykamy okno dialogowe po akceptacji
    this->close();

}


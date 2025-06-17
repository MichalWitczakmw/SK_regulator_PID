#include "serverdialog.h"
#include "ui_serverdialog.h"
#include <QMessageBox>

ServerDialog::ServerDialog(MyServer* server, QWidget *parent)
    : QDialog(parent)
    , server(server)
    , ui(new Ui::ServerDialog)
{
    ui->setupUi(this);
}

ServerDialog::~ServerDialog()
{
    delete ui;
}

void ServerDialog::on_connect_button_clicked()
{
    QHostAddress ip = QHostAddress(ui->ip_text->text());
    int port = ui->port_spin->value();


    if (ui->server_radio->isChecked()){
        server->startServer(ip, port);
    } else if (ui->client_radio->isChecked()) {
        server->connectToServer(ip, port);
    }

    if (server->server->isListening() || server->clientSocket) {
        accept();
    } else {
        QMessageBox::critical(this, "Connection Error", "Failed to connect to server.");
    }
}

void ServerDialog::on_server_radio_clicked()
{
    if (ui->client_radio->isChecked()) {
        ui->client_radio->setChecked(false);
    }
}


void ServerDialog::on_client_radio_clicked()
{
    if (ui->server_radio->isChecked()) {
        ui->server_radio->setChecked(false);
    }
}


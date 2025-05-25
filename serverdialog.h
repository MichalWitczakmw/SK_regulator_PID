#ifndef SERVERDIALOG_H
#define SERVERDIALOG_H

#include <QDialog>
#include "myserver.h"

namespace Ui {
class ServerDialog;
}

class ServerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ServerDialog(MyServer* server, QWidget *parent = nullptr);
    ~ServerDialog();

private slots:
    void on_connect_button_clicked();

    void on_server_radio_clicked();

    void on_client_radio_clicked();

private:
    MyServer* server;
    Ui::ServerDialog *ui;
};

#endif // SERVERDIALOG_H

#ifndef NETWORKDIALOG_H
#define NETWORKDIALOG_H

#include <QDialog>
#include <QTcpServer>
#include <QTcpSocket>
#include "networkclient.h"
#include "networkserver.h"


namespace Ui {
class NetworkDialog;
}

class NetworkDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NetworkDialog(QWidget *parent = nullptr);
    ~NetworkDialog();

private slots:
    void on_pushConnect_clicked();

signals:
    void sendData(QObject *networkInstance);

private:
    Ui::NetworkDialog *ui;
    MyTCPServer *server = nullptr;
    MyTCPClient *client = nullptr;
};

#endif // NETWORKDIALOG_H

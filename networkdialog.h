#ifndef NETWORKDIALOG_H
#define NETWORKDIALOG_H

#include <QDialog>
#include <QTcpServer>
#include <QTcpSocket>
#include "networkclient.h"
#include "networkserver.h"
#include <QCloseEvent>


namespace Ui {
class NetworkDialog;
}

class NetworkDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NetworkDialog(QWidget *parent = nullptr);
    ~NetworkDialog();

protected:
    void closeEvent(QCloseEvent *event) override; // Pamiętaj o `override`

private slots:
    void on_pushConnect_clicked();

signals:
    void sendData(QObject *networkInstance);
    void dialogClosed();

private:
    Ui::NetworkDialog *ui;
    MyTCPServer *server = nullptr;
    MyTCPClient *client = nullptr;
};

#endif // NETWORKDIALOG_H

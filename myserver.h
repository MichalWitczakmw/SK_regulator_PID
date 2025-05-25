#ifndef MYSERVER_H
#define MYSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include "simulation.h"

class MyServer : public QObject
{
    Q_OBJECT
public:
    static MyServer * instance;

    static MyServer * getInstance()
    {
        if (!instance) {
            instance = new MyServer();
        }
        return instance;
    }

    explicit MyServer(QObject *parent = nullptr);
    void startServer(QHostAddress ip, quint16 port);
    void sendData(SimulationFrame frame);

    void connectToServer(QHostAddress ip, quint16 port);

    void disconnectFromServer()
    {
        if (clientSocket) {
            clientSocket->disconnectFromHost();
            clientSocket = nullptr;
        }
    }

    void closeServer()
    {
        if (server->isListening()) {
            server->close();
            emit serverDisconnected();
        }
    }

    QTcpServer *server;
    QTcpSocket *clientSocket;

signals:
    void clientConnected();
    void clientDisconnected();

    void serverStarted();
    void serverDisconnected();

    void dataReceived(const QByteArray &data);

private slots:
    void onNewConnection();
    void onClientDisconnected();
    void onReadyRead();
    void ServerDisconnected();
};


#endif // MYSERVER_H

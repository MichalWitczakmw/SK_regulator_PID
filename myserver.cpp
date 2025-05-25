#include "myserver.h"
#include <QDebug>

MyServer * MyServer::instance = nullptr;


MyServer::MyServer(QObject *parent)
    : QObject{parent}, server(new QTcpServer(this)), clientSocket(nullptr)
{
    instance = this;
    connect(server, &QTcpServer::newConnection, this, &MyServer::onNewConnection);
}

void MyServer::startServer(QHostAddress ip, quint16 port)
{
    if (!server->listen(ip, port)) {
        qCritical() << "Server could not start:" << server->errorString();
    } else {
        qDebug() << "Server started on port" << port;
    }

    emit serverStarted();
}

void MyServer::onNewConnection()
{
    if (clientSocket) {
        QTcpSocket *newClient = server->nextPendingConnection();
        newClient->disconnectFromHost();
        newClient->deleteLater();
        qDebug() << "Rejected new client: already connected.";
        return;
    }

    clientSocket = server->nextPendingConnection();
    connect(clientSocket, &QTcpSocket::disconnected, this, &MyServer::onClientDisconnected);
    connect(clientSocket, &QTcpSocket::readyRead, this, &MyServer::onReadyRead);

    qDebug() << "Client connected from" << clientSocket->peerAddress().toString();
    emit clientConnected();
}

void MyServer::onClientDisconnected()
{
    qDebug() << "Client disconnected";
    clientSocket->deleteLater();
    clientSocket = nullptr;
    emit clientDisconnected();
}

void MyServer::onReadyRead()
{
    if (!clientSocket)
        return;

    QByteArray data = clientSocket->readAll();
    emit dataReceived(data);
}

void MyServer::sendData(SimulationFrame frame)
{
    if (clientSocket && clientSocket->state() == QAbstractSocket::ConnectedState) {
        QByteArray data;
        data.append(reinterpret_cast<const char*>(&frame), sizeof(frame));

        clientSocket->write(data);
        clientSocket->flush();
        qDebug() << "Sent data:" << data;
    } else {
        qWarning() << "No client connected to send data.";
    }
}

void MyServer::ServerDisconnected()
{
    qDebug() << "Server disconnected";
    if (clientSocket) {
        clientSocket->deleteLater();
        clientSocket = nullptr;
    }
    emit serverDisconnected();
}

void MyServer::connectToServer(QHostAddress ip, quint16 port)
{
    if (clientSocket) {
        qWarning() << "Already connected to a server.";
        return;
    }

    clientSocket = new QTcpSocket(this);
    connect(clientSocket, &QTcpSocket::disconnected, this, &MyServer::ServerDisconnected);
    connect(clientSocket, &QTcpSocket::readyRead, this, &MyServer::onReadyRead);
    clientSocket->connectToHost(ip, port);
    if (!clientSocket->waitForConnected(5000)) {
        qCritical() << "Could not connect to server:" << clientSocket->errorString();
        delete clientSocket;
        clientSocket = nullptr;
        return;
    }

    qDebug() << "Connected to server at" << ip.toString() << ":" << port;


    emit clientConnected();
}

#include "networkclient.h"

MyTCPClient::MyTCPClient(QObject *parent)
    : QObject{parent}, m_socket(this)
{
    connect(&m_socket,SIGNAL(connected()),this,SLOT(slot_connected()));
    connect(&m_socket, SIGNAL(disconnected()), this, SLOT(slot_socket_disconnected()));
    connect(&m_socket,SIGNAL(readyRead()),this,SLOT(slot_readyRead()));

    connect(&m_socket,SIGNAL(disconnected()),this,SIGNAL(disconnected()));


}

void MyTCPClient::connectTo(QString address, int port)
{
    m_ipAddress = address;
    m_port = port;
    m_socket.connectToHost(m_ipAddress,port);
}

void MyTCPClient::disconnectFrom()
{
    m_socket.close();
}

void MyTCPClient::sendMsg(QString msg)
{
    QByteArray data = msg.toUtf8();
    m_socket.write(data);
}

void MyTCPClient::slot_connected()
{
    if (m_socket.state() == QAbstractSocket::ConnectedState) {
        m_socket.write("connected");
        emit connected(getServerAddress(), getServerPort());
    }
}

void MyTCPClient::slot_socket_disconnected()
{
    // Tylko jeśli to serwer zamknął połączenie (a nie klient sam się odłączył)
    if (m_socket.state() == QAbstractSocket::UnconnectedState) {
        emit serverDisconnected();
    }
}


void MyTCPClient::slot_readyRead()
{
    auto message = m_socket.readAll();
    emit messageRecived(message);
}

// Poprawiona funkcja sprawdzająca faktyczne połączenie
bool MyTCPClient::isConnected() const
{
    return m_socket.state() == QAbstractSocket::ConnectedState;
}

void MyTCPClient::notifyDisconnection()
{
    if (m_socket.isOpen()) {
        m_socket.write("Client disconnected");
        m_socket.disconnectFromHost();
        emit serverDisconnected(); // Emituj sygnał o rozłączeniu serwera
    }
}

QString MyTCPClient::getServerAddress() const
{
    // Zwraca adres IP serwera, z którym klient jest połączony
    return m_socket.peerAddress().toString();
}

int MyTCPClient::getServerPort() const
{
    // Zwraca port serwera, z którym klient jest połączony
    return m_socket.peerPort();
}

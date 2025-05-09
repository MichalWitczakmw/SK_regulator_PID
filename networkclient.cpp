#include "networkclient.h"

MyTCPClient::MyTCPClient(QObject *parent)
    : QObject{parent}, m_socket(this)
{
    connect(&m_socket,SIGNAL(connected()),this,SLOT(slot_connected()));
    connect(&m_socket, SIGNAL(disconnected()), this, SLOT(slot_socket_disconnected()));
    connect(&m_socket,SIGNAL(readyRead()),this,SLOT(slot_readyRead()));

    connect(&m_socket,SIGNAL(disconnected()),this,SIGNAL(disconnected()));


}

void MyTCPClient::sendFrame(const SimulationFrame &frame)
{
    QByteArray data(reinterpret_cast<const char*>(&frame), sizeof(SimulationFrame));
    m_socket.write(data);
    qDebug() << "Frame sent to server:" << frame.tick;
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
    m_ipAddress.clear();
    m_port = 0;
    emit serverDisconnected();
}


void MyTCPClient::slot_readyRead()
{
    QByteArray message = m_socket.readAll();
    qDebug() << "Message received from server:" << message;

    // Handle commands from server
    if (message == "CMD_START") {
        qDebug() << "Command received: CMD_START";
        Simulation::get_instance().start();
    } else if (message == "CMD_STOP") {
        qDebug() << "Command received: CMD_STOP";
        Simulation::get_instance().stop();
    } else if (message == "CMD_RESET") {
        qDebug() << "Command received: CMD_RESET";
        Simulation::get_instance().reset();
    }

    // Handle frames from server
    while (m_socket.bytesAvailable() >= static_cast<qint64>(sizeof(SimulationFrame))) {
        SimulationFrame frame;
        m_socket.read(reinterpret_cast<char*>(&frame), sizeof(SimulationFrame));
        qDebug() << "Simulation frame received:" << frame.tick;
        Simulation::get_instance().receiveFrameFromServer(frame);
    }

    // Handle server disconnection message
    if (message == "Server disconnected") {
        qDebug() << "Server disconnected";
        emit serverDisconnected();
        return;
    }

    if (!message.isEmpty()) {
        emit messageRecived(message);
    }
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

#include "networkserver.h"

MyTCPServer::MyTCPServer(QObject *parent)
    : QObject{parent},
    m_server(this)
{
    connect(&m_server,SIGNAL(newConnection()),this,SLOT(slot_new_client()));

}

void MyTCPServer::sendFrame(const SimulationFrame &frame)
{
    QByteArray data(reinterpret_cast<const char*>(&frame), sizeof(SimulationFrame));
    for (QTcpSocket* client : m_clients) {
        if (client && client->state() == QAbstractSocket::ConnectedState)
            client->write(data);
    }
}

bool MyTCPServer::startListening(int port)
{
    m_port = port;
    m_isListening = m_server.listen(QHostAddress::Any, port);
    return m_isListening;
}

void MyTCPServer::stopListening()
{
    m_server.close();
    m_isListening = false;
}

int MyTCPServer::getNumClients()
{
    return m_clients.length();
}

void MyTCPServer::sendMsg(QString msg, int numCli)
{
    if(numCli < m_clients.length())
        m_clients.at(numCli)->write(msg.toUtf8());
}

void MyTCPServer::slot_new_client()
{
    QTcpSocket *client = m_server.nextPendingConnection();
    m_clients.push_back(client);
    auto clientAddress = client->peerAddress().toString();
    auto clientPort = client->peerPort();

    // Połącz sygnały zdarzeń klienta
    connect(client, &QTcpSocket::disconnected, this, &MyTCPServer::slot_client_disconnetcted);
    connect(client, &QTcpSocket::readyRead, this, &MyTCPServer::slot_newMsg);

    // Wyślij sygnał do GUI o nowym kliencie
    emit clientConnected(clientAddress, clientPort);
}
void MyTCPServer::slot_client_disconnetcted()
{
    int idx = getClinetID();
    if (idx >= 0 && idx < m_clients.size()) {
        QTcpSocket *client = m_clients.at(idx);
        m_clients.removeAt(idx);
        client->deleteLater(); // Zwalnia pamięć po gnieździe
    }
    emit clientDisconnected();
}

void MyTCPServer::slot_newMsg()
{
    QTcpSocket *client = qobject_cast<QTcpSocket *>(sender());
    if (!client) return;

    // Odbiór ramek SimulationFrame
    while (client->bytesAvailable() >= static_cast<qint64>(sizeof(SimulationFrame))) {
        SimulationFrame frame;
        client->read(reinterpret_cast<char*>(&frame), sizeof(SimulationFrame));
        Simulation::get_instance().receiveFrameFromClient(frame);
    }

    // Obsługa ewentualnych tekstowych wiadomości (np. handshake)
    QByteArray remainingData = client->readAll();
    if (!remainingData.isEmpty()) {
        QString message = QString::fromUtf8(remainingData);
        if (message == "connected") {
            emit clientConfirmedConnection();
        } else {
            qDebug() << "Received message from client:" << message;
        }
    }
}

bool MyTCPServer::getClinetID()
{
    QTcpSocket *client = static_cast<QTcpSocket*> (QObject::sender());
    return m_clients.indexOf(client);
}

// Dodanie funkcji sprawdzającej faktyczne połączenie klienta
bool MyTCPServer::isClientConnected(int clientIndex) const
{
    if (clientIndex < 0 || clientIndex >= m_clients.size())
        return false;

    return m_clients[clientIndex]->state() == QAbstractSocket::ConnectedState;
}

void MyTCPServer::disconnectClients()
{
    for (QTcpSocket *client : m_clients) {
        if (client->isOpen()) {
            client->write("Server disconnected");
            client->flush(); // Dodaj to!
            client->disconnectFromHost();
        }
    }
    m_clients.clear();
    emit clientDisconnected();
    stopListening();
}

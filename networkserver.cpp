#include "networkserver.h"

MyTCPServer::MyTCPServer(QObject *parent)
    : QObject{parent},
    m_server(this)
{
    connect(&m_server,SIGNAL(newConnection()),this,SLOT(slot_new_client()));

}

void MyTCPServer::broadcastStart() {
    for (QTcpSocket* client : m_clients)
        if (client->isOpen()) client->write("CMD_START");
}
void MyTCPServer::broadcastStop() {
    for (QTcpSocket* client : m_clients)
        if (client->isOpen()) client->write("CMD_STOP");
}
void MyTCPServer::broadcastReset() {
    for (QTcpSocket* client : m_clients)
        if (client->isOpen()) client->write("CMD_RESET");
}

void MyTCPServer::sendFrame(const SimulationFrame &frame)
{
    QByteArray payload;
    QDataStream out(&payload, QIODevice::WriteOnly);

    out << frame;

    QByteArray packet;
    QDataStream packetStream(&packet, QIODevice::WriteOnly);

    packetStream.writeRawData("FRAM", 4); // typ wiadomości
    packetStream << quint32(payload.size()); // długość danych
    packetStream.writeRawData(payload.constData(), payload.size());

    for (QTcpSocket* client : m_clients) {
        if (client && client->isOpen()) {
            client->write(packet);
        }
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
    if (numCli < m_clients.length()) {
        QByteArray payload = msg.toUtf8();

        QByteArray packet;
        QDataStream out(&packet, QIODevice::WriteOnly);
        out.writeRawData("CMD_", 4);
        out << quint32(payload.size());
        out.writeRawData(payload.constData(), payload.size());

        m_clients.at(numCli)->write(packet);
    }
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
    QTcpSocket *client = qobject_cast<QTcpSocket *>(sender());
    int idx = m_clients.indexOf(client);
    if (idx != -1) {
        m_clients.removeAt(idx);
        client->deleteLater();
    }
    emit clientDisconnected();
}

void MyTCPServer::slot_newMsg()
{
    QTcpSocket *client = qobject_cast<QTcpSocket *>(sender());
    if (!client) return;

    static QMap<QTcpSocket*, QByteArray> buffers;

    QByteArray &buffer = buffers[client];
    buffer.append(client->readAll());

    while (buffer.size() >= 8) {
        QByteArray typeBytes = buffer.mid(0, 4);
        QString type(typeBytes);

        QDataStream lengthStream(buffer.mid(4, 4));
        quint32 payloadSize;
        lengthStream >> payloadSize;

        if (buffer.size() < 8 + payloadSize)
            return; // Poczekaj na więcej danych

        QByteArray payload = buffer.mid(8, payloadSize);
        buffer.remove(0, 8 + payloadSize);

        if (type == "FRAM") {
            QDataStream in(&payload, QIODevice::ReadOnly);
            SimulationFrame frame;
            in >> frame;
            Simulation::get_instance().receiveFrameFromClient(frame);
            qDebug() << "SERVER OTRZYMAŁ RAMKĘ Z TICKIEM:" << frame.tick;
        } else if (type == "CMD_") {
            QString cmd = QString::fromUtf8(payload);
            if (cmd == "connected") {
                emit clientConfirmedConnection();
            } else {
                qDebug() << "SERVER RECEIVED CMD:" << cmd;
            }
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

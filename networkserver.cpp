#include "networkserver.h"

MyTCPServer::MyTCPServer(QObject *parent)
    : QObject{parent},
    m_server(this)
{
    connect(&m_server, SIGNAL(newConnection()), this, SLOT(slot_new_client()));
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
            qDebug() << "SERVER sent frame to client (tick):" << frame.tick;
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

    connect(client, &QTcpSocket::disconnected, this, &MyTCPServer::slot_client_disconnetcted);
    connect(client, &QTcpSocket::readyRead, this, &MyTCPServer::slot_newMsg);

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
    buffers[client].append(client->readAll());

    while (buffers[client].size() >= 8) {
        QByteArray typeBytes = buffers[client].mid(0, 4); // Typ wiadomości (np. "FRAM")
        QString type(typeBytes);

        QDataStream lengthStream(buffers[client].mid(4, 4)); // Rozmiar danych
        quint32 payloadSize;
        lengthStream >> payloadSize;

        if (buffers[client].size() < 8 + payloadSize)
            return; // Poczekaj na więcej danych

        QByteArray payload = buffers[client].mid(8, payloadSize);
        buffers[client].remove(0, 8 + payloadSize);

        if (type == "FRAM") {
            QDataStream in(&payload, QIODevice::ReadOnly);
            SimulationFrame frame;
            in >> frame; // Deserializacja ramki

            // Aktualizacja wykresu na serwerze
            emit Simulation::get_instance().add_series("ARX", frame.arx_output, ChartPosition::bottom);
        }
    }
}
void MyTCPServer::disconnectClients()
{
    for (QTcpSocket *client : std::as_const(m_clients)) {
        if (client->isOpen()) {
            client->write("Server disconnected");
            client->flush();
            client->disconnectFromHost();
        }
    }
    m_clients.clear();
    emit clientDisconnected();
    stopListening();
}

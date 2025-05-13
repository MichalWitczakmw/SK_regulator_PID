#include "networkclient.h"

MyTCPClient::MyTCPClient(QObject *parent)
    : QObject{parent}, m_socket(this)
{
    connect(&m_socket, SIGNAL(connected()), this, SLOT(slot_connected()));
    connect(&m_socket, SIGNAL(disconnected()), this, SLOT(slot_socket_disconnected()));
    connect(&m_socket, SIGNAL(readyRead()), this, SLOT(slot_readyRead()));

    connect(&m_socket, SIGNAL(disconnected()), this, SIGNAL(disconnected()));
}

void MyTCPClient::slot_readyRead()
{
    m_buffer.append(m_socket.readAll());

    while (m_buffer.size() >= 8) {
        QByteArray typeBytes = m_buffer.mid(0, 4); // Typ wiadomości (np. "FRAM")
        QString type(typeBytes);

        QDataStream lengthStream(m_buffer.mid(4, 4)); // Rozmiar danych
        quint32 payloadSize;
        lengthStream >> payloadSize;

        if (m_buffer.size() < 8 + payloadSize)
            return; // Poczekaj na więcej danych

        QByteArray payload = m_buffer.mid(8, payloadSize);
        m_buffer.remove(0, 8 + payloadSize);

        if (type == "FRAM") {
            QDataStream in(&payload, QIODevice::ReadOnly);
            SimulationFrame frame;
            in >> frame; // Deserializacja ramki

            // Emituj sygnał o nowej ramce
            emit newFrameReceived(frame);
        } else {
            qDebug() << "Unknown message type:" << type;
        }
    }
}
void MyTCPClient::connectTo(QString address, int port)
{
    m_ipAddress = address;
    m_port = port;
    m_socket.connectToHost(m_ipAddress, port);
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

void MyTCPClient::slot_socket_disconnected()
{
    m_ipAddress.clear();
    m_port = 0;
    emit serverDisconnected();
}

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
    return m_socket.peerAddress().toString();
}

int MyTCPClient::getServerPort() const
{
    return m_socket.peerPort();
}
void MyTCPClient::slot_connected()
{
    if (m_socket.state() == QAbstractSocket::ConnectedState) {
        m_socket.write("connected");
        emit connected(getServerAddress(), getServerPort());

        // Inicjalizacja wykresu po połączeniu
        emit initializeChart();
    }
}
void MyTCPClient::processFrameForChart(const SimulationFrame &frame)
{
    // Rysowanie wykresów na podstawie danych PID i ARX
    emit add_series("PID", frame.pid_output, ChartPosition::top);
    emit add_series("ARX", frame.arx_output, ChartPosition::bottom);

    // Oblicz dane ARX i odsyłaj do serwera
    SimulationFrame newFrame = frame;
    newFrame.arx_output = Simulation::get_instance().arx->run(frame.pid_output);
    newFrame.noise = Simulation::get_instance().arx->noise_part;

    sendFrame(newFrame);
}
void MyTCPClient::sendFrame(const SimulationFrame &frame)
{
    QByteArray buffer;
    QDataStream out(&buffer, QIODevice::WriteOnly);
    out << frame; // Serializacja ramki
    m_socket.write(buffer);

    qDebug() << "CLIENT sent frame to server (tick):" << frame.tick;
}

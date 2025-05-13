#include "networkclient.h"

MyTCPClient::MyTCPClient(QObject *parent)
    : QObject{parent}, m_socket(this)
{
    connect(&m_socket,SIGNAL(connected()),this,SLOT(slot_connected()));
    connect(&m_socket, SIGNAL(disconnected()), this, SLOT(slot_socket_disconnected()));
    connect(&m_socket,SIGNAL(readyRead()),this,SLOT(slot_readyRead()));

    connect(&m_socket,SIGNAL(disconnected()),this,SIGNAL(disconnected()));

    connect(&m_socket, &QTcpSocket::readyRead, this, &MyTCPClient::slot_gotData);
}

void MyTCPClient::slot_gotData()
{
    QDataStream in(&m_socket);
    in.setVersion(QDataStream::Qt_5_15);  // lub inna wersja zgodna z Twoją aplikacją

    while (true)
    {
        if (m_socket.bytesAvailable() < 8)
            return; // za mało danych, czekaj dalej

        char type[4];
        in.readRawData(type, 4);

        quint32 size;
        in >> size;

        if (m_socket.bytesAvailable() < size)
        {
            // czekaj aż cały payload dotrze
            m_socket.seek(m_socket.pos() - 8); // cofnij, bo niepełne dane
            return;
        }

        QByteArray payload;
        payload.resize(size);
        in.readRawData(payload.data(), size);

        QString typ(QString::fromLatin1(type, 4));

        qDebug() << "Odebrano typ:" << typ << " payload:" << payload;

        if (typ == "CMD_") {
            QString komenda = QString::fromUtf8(payload);
            if (komenda == "START") {
                qDebug() << "Klient: odebrano START";
                emit startReceived();
            }
        }
        else if (typ == "FRAM") {
            qDebug() << "Klient: odebrano rameczkę ->" << payload.toHex();
            emit newFrameReceived(payload);
        }
    }
}

void MyTCPClient::sendFrame(const SimulationFrame &frame)
{
    QByteArray buffer;
    QDataStream out(&buffer, QIODevice::WriteOnly);
    //out.setVersion(QDataStream::Qt_6_2);  // lub inna wersja zgodna z Twoim Qt

    out << frame;
    m_socket.write(buffer);

    qDebug() << "Frame sent to server (tick):" << frame.tick;
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
    m_buffer.append(m_socket.readAll());

    while (m_buffer.size() >= 8) {
        QByteArray typeBytes = m_buffer.mid(0, 4);
        QString type(typeBytes);

        QDataStream lengthStream(m_buffer.mid(4, 4));

        quint32 payloadSize;
        lengthStream >> payloadSize;

        if (m_buffer.size() < 8 + payloadSize)
            return; // Poczekaj na więcej danych

        QByteArray payload = m_buffer.mid(8, payloadSize);
        m_buffer.remove(0, 8 + payloadSize);

        if (type == "CMD_") {
            QString command = QString::fromUtf8(payload);
            qDebug() << "Command received:" << command;
            if (command == "START") Simulation::get_instance().start();
            else if (command == "STOP") Simulation::get_instance().stop();
            else if (command == "RESET") Simulation::get_instance().reset();
        } else if (type == "FRAM") {
            QDataStream in(&payload, QIODevice::ReadOnly);

            SimulationFrame frame;
            in >> frame;
            qDebug() << "Simulation frame received - Tick:" << frame.tick;
            Simulation::get_instance().receiveFrameFromServer(frame);
        }
    }

    // // Obsługa rozłączenia
    // if (message == "Server disconnected") {
    //     qDebug() << "Server disconnected";
    //     emit serverDisconnected();
    //     return;
    // }
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

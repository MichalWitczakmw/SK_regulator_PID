#ifndef NETWORKCLIENT_H
#define NETWORKCLIENT_H
#include <QObject>
#include <QTcpSocket>
#include "simulation.h"

class MyTCPClient : public QObject
{
    Q_OBJECT
public:
    explicit MyTCPClient(QObject *parent = nullptr);
    void connectTo(QString address, int port);
    void disconnectFrom();
    bool isConnected() const;
    void sendMsg(QString msg);
    void notifyDisconnection(); // Funkcja do powiadamiania serwera o rozłączeniu
    QString getServerAddress() const;
    int getServerPort() const;

signals:
    void connected(QString adr, int port);
    void disconnected();
    void messageRecived(QString msg);
    void serverDisconnected(); // Sygnał rozłączenia serwera
    void newFrameReceived(const SimulationFrame &frame);// Sygnał do aktualizacji wykresu

public slots:
    void sendFrame(const SimulationFrame &frame);
private slots:
    void slot_connected();
    void slot_socket_disconnected();
    void slot_readyRead();

private:
    QTcpSocket m_socket;
    QString m_ipAddress = "127.0.0.1";
    int m_port = 8080;
    QByteArray m_buffer;
};

#endif // NETWORKCLIENT_H

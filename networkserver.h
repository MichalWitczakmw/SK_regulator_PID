#ifndef NETWORKSERVER_H
#define NETWORKSERVER_H
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include "simulation.h"

class MyTCPServer : public QObject
{
    Q_OBJECT
public:
    explicit MyTCPServer(QObject *parent = nullptr);
    bool startListening(int port);
    bool isListening() {return m_isListening;}
    void stopListening();
    int getNumClients();
    void sendMsg(QString msg, int numCli);
    bool isClientConnected(int clientIndex) const;
    void disconnectClients(); // Funkcja do rozłączania klientów

signals:
    void newClientConnected(QString adr);
    void clientDisconnected(); // Sygnał rozłączenia klienta
    void newMsgFrom(QString, int num);
    void clientConnected(QString clientAddress, quint16 clientPort); // Sygnał o nowym połączeniu klienta
    void clientConfirmedConnection(); // Sygnał o potwierdzeniu połączenia przez klienta

public slots:
    void sendFrame(const SimulationFrame &frame); // slot do wysyłania ramek do klienta
private slots:
    void slot_new_client();
    void slot_client_disconnetcted();
    void slot_newMsg();

private:
    bool getClinetID();

    bool m_isListening = false;
    int m_port = 8080;
    QTcpServer m_server;
    QVector<QTcpSocket*> m_clients;
};
#endif // NETWORKSERVER_H

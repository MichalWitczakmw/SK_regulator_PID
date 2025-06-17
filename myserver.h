#ifndef MYSERVER_H
#define MYSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include "simulation.h"
#include <vector>
#include <QDataStream>
#include <QVector>
struct SimulationConfig {
    // PID
    float kp;
    float ti;
    float td;

    // Generator
    float amplitude;
    float frequency;
    int generator_type;
    float infill;

    // ARX
    float noise;
    int noise_type;
    int delay;
    std::vector<float> a;
    std::vector<float> b;

    bool is_outside_sum;
    int interval;

    // operator ==
    bool operator==(const SimulationConfig &other) const {
        return kp == other.kp &&
               ti == other.ti &&
               td == other.td &&
               amplitude == other.amplitude &&
               frequency == other.frequency &&
               generator_type == other.generator_type &&
               infill == other.infill &&
               noise == other.noise &&
               noise_type == other.noise_type &&
               delay == other.delay &&
               a == other.a &&
               b == other.b;
    }

    bool is_ok(){
        // check if it is logically good
        bool result = kp >= 0 && ti >= 0 && td >= 0 &&
                      amplitude >= 0 && frequency >= 0 && generator_type >= 0 && infill >= 0 &&
                      noise >= 0 && noise_type >= 0 && delay >= 0;

        // check if something isnt to big
        result = result && (kp <= 1000 && ti <= 1000 && td <= 1000 &&
                            amplitude <= 1000 && frequency <= 1000 && generator_type <= 10 && infill <= 100 &&
                            noise <= 1000 && noise_type <= 10 && delay <= 1000);

        // check if something is inf
        result = result && (a.size() > 0 || b.size() > 0);

        return result;
    }
};



inline QByteArray serialize_config(const SimulationConfig &config) {
    QByteArray data;
    QDataStream out(&data, QIODevice::WriteOnly);

    // PID
    out << config.kp << config.ti << config.td;

    // Generator
    out << config.amplitude << config.frequency << config.generator_type << config.infill;

    // ARX
    out << config.noise << config.noise_type << config.delay;
    QVector<float> aVec(config.a.begin(), config.a.end());
    QVector<float> bVec(config.b.begin(), config.b.end());

    out << aVec << bVec;
    out << config.is_outside_sum;
    out << config.interval;

    return data;
}

inline SimulationConfig deserialize_config(const QByteArray &data) {
    QDataStream in(data);
    SimulationConfig config;

    QVector<float> aVec, bVec;

    in >> config.kp >> config.ti >> config.td;
    in >> config.amplitude >> config.frequency >> config.generator_type >> config.infill;
    in >> config.noise >> config.noise_type >> config.delay;
    in >> aVec >> bVec;

    config.a = std::vector<float>(aVec.begin(), aVec.end());
    config.b = std::vector<float>(bVec.begin(), bVec.end());

    in >> config.is_outside_sum;
    in >> config.interval;

    return config;
}

class MyServer : public QObject
{
    Q_OBJECT
public:
    static MyServer * instance;

    static MyServer * getInstance()
    {
        if (!instance) {
            instance = new MyServer();
        }
        return instance;
    }

    explicit MyServer(QObject *parent = nullptr);
    void startServer(QHostAddress ip, quint16 port);
    void sendData(SimulationFrame frame);
    void sendRawData(QByteArray data)
    {

        if (clientSocket && clientSocket->state() == QAbstractSocket::ConnectedState) {
            clientSocket->write(data);
            clientSocket->flush();
        }
    }

    void connectToServer(QHostAddress ip, quint16 port);

    void disconnectFromServer()
    {
        if (clientSocket) {
            clientSocket->disconnectFromHost();
            clientSocket = nullptr;
        }
    }

    void closeServer()
    {
        if (server->isListening()) {
            server->close();
            emit serverDisconnected();
        }
    }


    QTcpServer *server;
    QTcpSocket *clientSocket;

signals:
    void clientConnected();
    void clientDisconnected();

    void serverStarted();
    void serverDisconnected();

    void dataReceived(const QByteArray &data);
    void send_config();

private slots:
    void onNewConnection();
    void onClientDisconnected();
    void onReadyRead();
    void ServerDisconnected();
};


#endif // MYSERVER_H

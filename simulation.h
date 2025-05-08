#ifndef SIMULATION_H
#define SIMULATION_H

#include <QMainWindow>
#include <QObject>

#include "arx.h"
#include "generator.h"
#include "pid.h"

enum class SimulationMode {
    Offline,
    Server,
    Client
};

enum class ChartPosition {
    top,
    middle,
    bottom,
};

struct Point
{
    float x;
    float y;
};

struct SimulationFrame
{
    size_t tick;
    float geneartor_output;

    float p;
    float i;
    float d;
    float pid_output;

    float error;

    float arx_output;
    float noise;
};

class Simulation : public QObject
{
    Q_OBJECT
public:
    static Simulation &get_instance();

    void set_mode(SimulationMode mode);
    SimulationMode get_mode() const;

    void start();
    void stop();

    void set_ticks_per_second(float ticks_per_second);
    void set_duration(float duration);

    void set_outside_sum(bool is_outside_sum);
    bool get_outside_sum() const;

    size_t get_tick() const;
    float get_current_time() const;
    float get_ticks_per_second() const;

    void increment_tick();

    float durration{0};

    bool is_running{false};


    size_t duration_timer_id{0};

    void reset();

    void set_interval(int interval);
    int get_interval() const;

    std::unique_ptr<PID> pid;
    std::unique_ptr<Generator> generator;
    std::unique_ptr<ARX> arx;

    std::list<SimulationFrame> frames{};

    std::vector<std::byte> serialize();
    void deserialize(std::vector<std::byte> data);

    // Nowe metody do komunikacji
    void sendFrameToClient(const SimulationFrame &frame); // serwer -> klient
    void sendFrameToServer(const SimulationFrame &frame); // klient -> serwer
    void receiveFrameFromClient(const SimulationFrame &frame);
    void receiveFrameFromServer(const SimulationFrame &frame);

signals:
    void simulation_start();
    void simulation_stop();

    void reset_chart();
    void update_chart();
    void add_series(QString series_name, float y, ChartPosition position);

    // Sygnały do integracji z warstwą sieciową
    void frameReadyToSendToClient(const SimulationFrame &frame); // serwer -> klient
    void frameReadyToSendToServer(const SimulationFrame &frame); // klient -> serwer

protected:
    void timerEvent(QTimerEvent *event) override;

private:

    SimulationMode mode{SimulationMode::Offline};
    std::optional<SimulationFrame> pendingFrameFromServer;

    void simulate();

    bool is_outside_sum{true};
    float ticks_per_second{60};
    size_t tick{0};
    float current_time{0};
    size_t timer_id{0};
    int interval{100};

    explicit Simulation(QObject *parent = nullptr);
    ~Simulation();

signals:
};

#endif // SIMULATION_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QAction>
#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>
#include "networkclient.h"
#include "networkserver.h"
#include "simulation.h"
#include "networkdialog.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void updateControlsBasedOnRole(bool isServer);
    bool isConnectionValid() const;


private slots:
    void simulation_start();
    void simulation_stop();

    //void receiveData(const QString &IP,const QString &PORT, bool isServer);
    void handleNetworkInstance(QObject *networkInstance); // Slot do odbioru wskaźnika instancji

    // simulation

    void on_simulation_start_button_clicked();
    void on_simulation_stop_button_clicked();
    void on_simulation_duration_input_editingFinished();

    // pid

    void on_pid_ti_input_editingFinished();
    void on_pid_td_input_editingFinished();
    void on_pid_kp_input_editingFinished();

    // generator

    void on_generator_amplitude_input_editingFinished();
    void on_generator_frequency_input_editingFinished();
    void on_generator_generatortype_input_currentIndexChanged(int index);

    // arx

    void on_arx_noise_input_editingFinished();
    void on_arx_noisetype_input_currentIndexChanged(int index);
    void on_arx_delay_input_editingFinished();
    void on_arx_b_input_editingFinished();
    void on_arx_a_input_editingFinished();

    void on_simulation_reset_button_clicked();

    void on_simulation_interval_input_editingFinished();

    void action_save_as();
    void action_open();
    void action_simulation_export();
    void action_simulation_open();

    void on_generator_infill_input_editingFinished();

    void on_outside_sum_radio_clicked();

    void on_inside_sum_radio_clicked();

    void on_Network_clicked();

    void on_chackNetwork_clicked();



private:
    void init();

    Simulation &simulation;
    MyTCPServer *server = nullptr;
    MyTCPClient *client = nullptr;
    QString ip;
    QString port;
    NetworkDialog * networkdialog = nullptr;
    bool isServerW = 0;
    Ui::MainWindow *ui;

    SimulationMode selected_network_mode = SimulationMode::Offline;
};
#endif // MAINWINDOW_H

#include "chartwidget.h"
#include "mainwindow.h"
#include "networkclient.h"
#include "networkserver.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    MyTCPClient client;
    MyTCPServer server;
    ChartWidget chart;

    // Połącz sygnały klienta z wykresem
    QObject::connect(&client, &MyTCPClient::add_series, &chart, &ChartWidget::add_series);

    // Połącz sygnały serwera z wykresem
    QObject::connect(&Simulation::get_instance(), &Simulation::add_series, &chart, &ChartWidget::add_series);

    QObject::connect(&client, &MyTCPClient::newFrameReceived, &client, &MyTCPClient::processFrameForChart);
    QObject::connect(&client, &MyTCPClient::add_series, &chart, &ChartWidget::add_series);
    return a.exec();
}

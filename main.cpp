#include "chartwidget.h"
#include "mainwindow.h"
#include "networkclient.h"
#include "networkserver.h"

#include <QApplication>
QString chartPositionToString(ChartPosition position) {
    switch (position) {
    case ChartPosition::top:
        return "top";
    case ChartPosition::middle:
        return "middle";
    case ChartPosition::bottom:
        return "bottom";
    }
    return "unknown";
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.show();

    MyTCPClient client;
    MyTCPServer server;
    ChartWidget chart;

    // Połącz sygnały klienta z widgetem wykresów
    QObject::connect(&client, &MyTCPClient::add_series, &chart, &ChartWidget::add_series);

    // Połącz sygnały serwera z widgetem wykresów
    QObject::connect(&Simulation::get_instance(), &Simulation::add_series, &chart, &ChartWidget::add_series);

    // Uproszczone debugowanie
    Simulation &simulation = Simulation::get_instance();
    QObject::connect(&simulation, &Simulation::add_series, &w, [](QString series_name, float y, ChartPosition position) {
        qDebug() << "Updating series" << series_name << "with value" << y << "at position" << chartPositionToString(position);
    });

    return a.exec();
}

/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../mainwindow.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
struct qt_meta_tag_ZN10MainWindowE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN10MainWindowE = QtMocHelpers::stringData(
    "MainWindow",
    "simulation_start",
    "",
    "simulation_stop",
    "on_simulation_start_button_clicked",
    "on_simulation_stop_button_clicked",
    "on_simulation_duration_input_editingFinished",
    "on_pid_ti_input_editingFinished",
    "on_pid_td_input_editingFinished",
    "on_pid_kp_input_editingFinished",
    "on_generator_amplitude_input_editingFinished",
    "on_generator_frequency_input_editingFinished",
    "on_generator_generatortype_input_currentIndexChanged",
    "index",
    "on_arx_noise_input_editingFinished",
    "on_arx_noisetype_input_currentIndexChanged",
    "on_arx_delay_input_editingFinished",
    "on_arx_b_input_editingFinished",
    "on_arx_a_input_editingFinished",
    "on_simulation_reset_button_clicked",
    "on_simulation_interval_input_editingFinished",
    "action_save_as",
    "action_open",
    "action_simulation_export",
    "action_simulation_open",
    "on_generator_infill_input_editingFinished",
    "on_outside_sum_radio_clicked",
    "on_inside_sum_radio_clicked",
    "on_network_button_clicked",
    "on_disconnect_button_clicked",
    "set_server_gui",
    "state",
    "set_client_gui",
    "set_gui_enabled"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN10MainWindowE[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      30,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,  194,    2, 0x08,    1 /* Private */,
       3,    0,  195,    2, 0x08,    2 /* Private */,
       4,    0,  196,    2, 0x08,    3 /* Private */,
       5,    0,  197,    2, 0x08,    4 /* Private */,
       6,    0,  198,    2, 0x08,    5 /* Private */,
       7,    0,  199,    2, 0x08,    6 /* Private */,
       8,    0,  200,    2, 0x08,    7 /* Private */,
       9,    0,  201,    2, 0x08,    8 /* Private */,
      10,    0,  202,    2, 0x08,    9 /* Private */,
      11,    0,  203,    2, 0x08,   10 /* Private */,
      12,    1,  204,    2, 0x08,   11 /* Private */,
      14,    0,  207,    2, 0x08,   13 /* Private */,
      15,    1,  208,    2, 0x08,   14 /* Private */,
      16,    0,  211,    2, 0x08,   16 /* Private */,
      17,    0,  212,    2, 0x08,   17 /* Private */,
      18,    0,  213,    2, 0x08,   18 /* Private */,
      19,    0,  214,    2, 0x08,   19 /* Private */,
      20,    0,  215,    2, 0x08,   20 /* Private */,
      21,    0,  216,    2, 0x08,   21 /* Private */,
      22,    0,  217,    2, 0x08,   22 /* Private */,
      23,    0,  218,    2, 0x08,   23 /* Private */,
      24,    0,  219,    2, 0x08,   24 /* Private */,
      25,    0,  220,    2, 0x08,   25 /* Private */,
      26,    0,  221,    2, 0x08,   26 /* Private */,
      27,    0,  222,    2, 0x08,   27 /* Private */,
      28,    0,  223,    2, 0x08,   28 /* Private */,
      29,    0,  224,    2, 0x08,   29 /* Private */,
      30,    1,  225,    2, 0x08,   30 /* Private */,
      32,    1,  228,    2, 0x08,   32 /* Private */,
      33,    0,  231,    2, 0x08,   34 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   13,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   13,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   31,
    QMetaType::Void, QMetaType::Bool,   31,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_ZN10MainWindowE.offsetsAndSizes,
    qt_meta_data_ZN10MainWindowE,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_tag_ZN10MainWindowE_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<MainWindow, std::true_type>,
        // method 'simulation_start'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'simulation_stop'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_simulation_start_button_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_simulation_stop_button_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_simulation_duration_input_editingFinished'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_pid_ti_input_editingFinished'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_pid_td_input_editingFinished'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_pid_kp_input_editingFinished'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_generator_amplitude_input_editingFinished'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_generator_frequency_input_editingFinished'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_generator_generatortype_input_currentIndexChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'on_arx_noise_input_editingFinished'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_arx_noisetype_input_currentIndexChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'on_arx_delay_input_editingFinished'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_arx_b_input_editingFinished'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_arx_a_input_editingFinished'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_simulation_reset_button_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_simulation_interval_input_editingFinished'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'action_save_as'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'action_open'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'action_simulation_export'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'action_simulation_open'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_generator_infill_input_editingFinished'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_outside_sum_radio_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_inside_sum_radio_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_network_button_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_disconnect_button_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'set_server_gui'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'set_client_gui'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'set_gui_enabled'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<MainWindow *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->simulation_start(); break;
        case 1: _t->simulation_stop(); break;
        case 2: _t->on_simulation_start_button_clicked(); break;
        case 3: _t->on_simulation_stop_button_clicked(); break;
        case 4: _t->on_simulation_duration_input_editingFinished(); break;
        case 5: _t->on_pid_ti_input_editingFinished(); break;
        case 6: _t->on_pid_td_input_editingFinished(); break;
        case 7: _t->on_pid_kp_input_editingFinished(); break;
        case 8: _t->on_generator_amplitude_input_editingFinished(); break;
        case 9: _t->on_generator_frequency_input_editingFinished(); break;
        case 10: _t->on_generator_generatortype_input_currentIndexChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 11: _t->on_arx_noise_input_editingFinished(); break;
        case 12: _t->on_arx_noisetype_input_currentIndexChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 13: _t->on_arx_delay_input_editingFinished(); break;
        case 14: _t->on_arx_b_input_editingFinished(); break;
        case 15: _t->on_arx_a_input_editingFinished(); break;
        case 16: _t->on_simulation_reset_button_clicked(); break;
        case 17: _t->on_simulation_interval_input_editingFinished(); break;
        case 18: _t->action_save_as(); break;
        case 19: _t->action_open(); break;
        case 20: _t->action_simulation_export(); break;
        case 21: _t->action_simulation_open(); break;
        case 22: _t->on_generator_infill_input_editingFinished(); break;
        case 23: _t->on_outside_sum_radio_clicked(); break;
        case 24: _t->on_inside_sum_radio_clicked(); break;
        case 25: _t->on_network_button_clicked(); break;
        case 26: _t->on_disconnect_button_clicked(); break;
        case 27: _t->set_server_gui((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 28: _t->set_client_gui((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 29: _t->set_gui_enabled(); break;
        default: ;
        }
    }
}

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZN10MainWindowE.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 30)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 30;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 30)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 30;
    }
    return _id;
}
QT_WARNING_POP

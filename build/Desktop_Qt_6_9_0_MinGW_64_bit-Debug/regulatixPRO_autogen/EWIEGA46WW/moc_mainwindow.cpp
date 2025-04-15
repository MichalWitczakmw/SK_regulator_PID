/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.0)
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
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.9.0. It"
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

template <> constexpr inline auto MainWindow::qt_create_metaobjectdata<qt_meta_tag_ZN10MainWindowE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "MainWindow",
        "simulation_start",
        "",
        "simulation_stop",
        "handleNetworkInstance",
        "networkInstance",
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
        "on_Network_clicked",
        "on_chackNetwork_clicked"
    };

    QtMocHelpers::UintData qt_methods {
        // Slot 'simulation_start'
        QtMocHelpers::SlotData<void()>(1, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'simulation_stop'
        QtMocHelpers::SlotData<void()>(3, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'handleNetworkInstance'
        QtMocHelpers::SlotData<void(QObject *)>(4, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::QObjectStar, 5 },
        }}),
        // Slot 'on_simulation_start_button_clicked'
        QtMocHelpers::SlotData<void()>(6, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_simulation_stop_button_clicked'
        QtMocHelpers::SlotData<void()>(7, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_simulation_duration_input_editingFinished'
        QtMocHelpers::SlotData<void()>(8, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_pid_ti_input_editingFinished'
        QtMocHelpers::SlotData<void()>(9, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_pid_td_input_editingFinished'
        QtMocHelpers::SlotData<void()>(10, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_pid_kp_input_editingFinished'
        QtMocHelpers::SlotData<void()>(11, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_generator_amplitude_input_editingFinished'
        QtMocHelpers::SlotData<void()>(12, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_generator_frequency_input_editingFinished'
        QtMocHelpers::SlotData<void()>(13, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_generator_generatortype_input_currentIndexChanged'
        QtMocHelpers::SlotData<void(int)>(14, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Int, 15 },
        }}),
        // Slot 'on_arx_noise_input_editingFinished'
        QtMocHelpers::SlotData<void()>(16, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_arx_noisetype_input_currentIndexChanged'
        QtMocHelpers::SlotData<void(int)>(17, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Int, 15 },
        }}),
        // Slot 'on_arx_delay_input_editingFinished'
        QtMocHelpers::SlotData<void()>(18, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_arx_b_input_editingFinished'
        QtMocHelpers::SlotData<void()>(19, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_arx_a_input_editingFinished'
        QtMocHelpers::SlotData<void()>(20, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_simulation_reset_button_clicked'
        QtMocHelpers::SlotData<void()>(21, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_simulation_interval_input_editingFinished'
        QtMocHelpers::SlotData<void()>(22, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'action_save_as'
        QtMocHelpers::SlotData<void()>(23, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'action_open'
        QtMocHelpers::SlotData<void()>(24, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'action_simulation_export'
        QtMocHelpers::SlotData<void()>(25, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'action_simulation_open'
        QtMocHelpers::SlotData<void()>(26, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_generator_infill_input_editingFinished'
        QtMocHelpers::SlotData<void()>(27, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_outside_sum_radio_clicked'
        QtMocHelpers::SlotData<void()>(28, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_inside_sum_radio_clicked'
        QtMocHelpers::SlotData<void()>(29, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_Network_clicked'
        QtMocHelpers::SlotData<void()>(30, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_chackNetwork_clicked'
        QtMocHelpers::SlotData<void()>(31, 2, QMC::AccessPrivate, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<MainWindow, qt_meta_tag_ZN10MainWindowE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10MainWindowE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10MainWindowE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN10MainWindowE_t>.metaTypes,
    nullptr
} };

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<MainWindow *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->simulation_start(); break;
        case 1: _t->simulation_stop(); break;
        case 2: _t->handleNetworkInstance((*reinterpret_cast< std::add_pointer_t<QObject*>>(_a[1]))); break;
        case 3: _t->on_simulation_start_button_clicked(); break;
        case 4: _t->on_simulation_stop_button_clicked(); break;
        case 5: _t->on_simulation_duration_input_editingFinished(); break;
        case 6: _t->on_pid_ti_input_editingFinished(); break;
        case 7: _t->on_pid_td_input_editingFinished(); break;
        case 8: _t->on_pid_kp_input_editingFinished(); break;
        case 9: _t->on_generator_amplitude_input_editingFinished(); break;
        case 10: _t->on_generator_frequency_input_editingFinished(); break;
        case 11: _t->on_generator_generatortype_input_currentIndexChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 12: _t->on_arx_noise_input_editingFinished(); break;
        case 13: _t->on_arx_noisetype_input_currentIndexChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 14: _t->on_arx_delay_input_editingFinished(); break;
        case 15: _t->on_arx_b_input_editingFinished(); break;
        case 16: _t->on_arx_a_input_editingFinished(); break;
        case 17: _t->on_simulation_reset_button_clicked(); break;
        case 18: _t->on_simulation_interval_input_editingFinished(); break;
        case 19: _t->action_save_as(); break;
        case 20: _t->action_open(); break;
        case 21: _t->action_simulation_export(); break;
        case 22: _t->action_simulation_open(); break;
        case 23: _t->on_generator_infill_input_editingFinished(); break;
        case 24: _t->on_outside_sum_radio_clicked(); break;
        case 25: _t->on_inside_sum_radio_clicked(); break;
        case 26: _t->on_Network_clicked(); break;
        case 27: _t->on_chackNetwork_clicked(); break;
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
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10MainWindowE_t>.strings))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 28)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 28;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 28)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 28;
    }
    return _id;
}
QT_WARNING_POP

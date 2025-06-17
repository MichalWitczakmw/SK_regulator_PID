/********************************************************************************
** Form generated from reading UI file 'serverdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SERVERDIALOG_H
#define UI_SERVERDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_ServerDialog
{
public:
    QFormLayout *formLayout;
    QLabel *label;
    QLineEdit *ip_text;
    QLabel *label_2;
    QPushButton *connect_button;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QRadioButton *server_radio;
    QRadioButton *client_radio;
    QSpacerItem *horizontalSpacer_2;
    QSpinBox *port_spin;

    void setupUi(QDialog *ServerDialog)
    {
        if (ServerDialog->objectName().isEmpty())
            ServerDialog->setObjectName("ServerDialog");
        ServerDialog->resize(403, 217);
        formLayout = new QFormLayout(ServerDialog);
        formLayout->setObjectName("formLayout");
        label = new QLabel(ServerDialog);
        label->setObjectName("label");

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        ip_text = new QLineEdit(ServerDialog);
        ip_text->setObjectName("ip_text");

        formLayout->setWidget(0, QFormLayout::FieldRole, ip_text);

        label_2 = new QLabel(ServerDialog);
        label_2->setObjectName("label_2");

        formLayout->setWidget(2, QFormLayout::LabelRole, label_2);

        connect_button = new QPushButton(ServerDialog);
        connect_button->setObjectName("connect_button");

        formLayout->setWidget(6, QFormLayout::SpanningRole, connect_button);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        server_radio = new QRadioButton(ServerDialog);
        server_radio->setObjectName("server_radio");
        server_radio->setChecked(true);

        horizontalLayout->addWidget(server_radio);

        client_radio = new QRadioButton(ServerDialog);
        client_radio->setObjectName("client_radio");

        horizontalLayout->addWidget(client_radio);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        formLayout->setLayout(4, QFormLayout::SpanningRole, horizontalLayout);

        port_spin = new QSpinBox(ServerDialog);
        port_spin->setObjectName("port_spin");
        port_spin->setMaximum(65535);
        port_spin->setValue(1234);

        formLayout->setWidget(2, QFormLayout::FieldRole, port_spin);


        retranslateUi(ServerDialog);

        QMetaObject::connectSlotsByName(ServerDialog);
    } // setupUi

    void retranslateUi(QDialog *ServerDialog)
    {
        ServerDialog->setWindowTitle(QCoreApplication::translate("ServerDialog", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("ServerDialog", "IP", nullptr));
        ip_text->setText(QCoreApplication::translate("ServerDialog", "127.0.0.1", nullptr));
        label_2->setText(QCoreApplication::translate("ServerDialog", "PORT", nullptr));
        connect_button->setText(QCoreApplication::translate("ServerDialog", "CONNECT", nullptr));
        server_radio->setText(QCoreApplication::translate("ServerDialog", "PID(SERVER)", nullptr));
        client_radio->setText(QCoreApplication::translate("ServerDialog", "ARX(CLIENT)", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ServerDialog: public Ui_ServerDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SERVERDIALOG_H

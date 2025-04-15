/********************************************************************************
** Form generated from reading UI file 'networkdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NETWORKDIALOG_H
#define UI_NETWORKDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_NetworkDialog
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label;
    QTextEdit *textIP;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_2;
    QTextEdit *textPORT;
    QHBoxLayout *horizontalLayout;
    QRadioButton *radioServerPID;
    QRadioButton *radioClientARX;
    QPushButton *pushConnect;
    QLabel *labelNotConnected;

    void setupUi(QDialog *NetworkDialog)
    {
        if (NetworkDialog->objectName().isEmpty())
            NetworkDialog->setObjectName("NetworkDialog");
        NetworkDialog->resize(274, 216);
        gridLayout = new QGridLayout(NetworkDialog);
        gridLayout->setObjectName("gridLayout");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        label = new QLabel(NetworkDialog);
        label->setObjectName("label");
        label->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);

        horizontalLayout_3->addWidget(label);

        textIP = new QTextEdit(NetworkDialog);
        textIP->setObjectName("textIP");
        textIP->setLineWrapMode(QTextEdit::LineWrapMode::FixedPixelWidth);

        horizontalLayout_3->addWidget(textIP);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        label_2 = new QLabel(NetworkDialog);
        label_2->setObjectName("label_2");
        label_2->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);

        horizontalLayout_4->addWidget(label_2);

        textPORT = new QTextEdit(NetworkDialog);
        textPORT->setObjectName("textPORT");
        textPORT->setLineWrapMode(QTextEdit::LineWrapMode::FixedPixelWidth);

        horizontalLayout_4->addWidget(textPORT);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        radioServerPID = new QRadioButton(NetworkDialog);
        radioServerPID->setObjectName("radioServerPID");

        horizontalLayout->addWidget(radioServerPID);

        radioClientARX = new QRadioButton(NetworkDialog);
        radioClientARX->setObjectName("radioClientARX");

        horizontalLayout->addWidget(radioClientARX);


        verticalLayout->addLayout(horizontalLayout);

        pushConnect = new QPushButton(NetworkDialog);
        pushConnect->setObjectName("pushConnect");

        verticalLayout->addWidget(pushConnect);

        labelNotConnected = new QLabel(NetworkDialog);
        labelNotConnected->setObjectName("labelNotConnected");

        verticalLayout->addWidget(labelNotConnected);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);


        retranslateUi(NetworkDialog);

        QMetaObject::connectSlotsByName(NetworkDialog);
    } // setupUi

    void retranslateUi(QDialog *NetworkDialog)
    {
        NetworkDialog->setWindowTitle(QCoreApplication::translate("NetworkDialog", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("NetworkDialog", "IP:", nullptr));
        label_2->setText(QCoreApplication::translate("NetworkDialog", "Port:", nullptr));
        radioServerPID->setText(QCoreApplication::translate("NetworkDialog", "Server (PID)", nullptr));
        radioClientARX->setText(QCoreApplication::translate("NetworkDialog", "Client (ARX)", nullptr));
        pushConnect->setText(QCoreApplication::translate("NetworkDialog", "Connect", nullptr));
        labelNotConnected->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class NetworkDialog: public Ui_NetworkDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NETWORKDIALOG_H

/********************************************************************************
** Form generated from reading UI file 'arxdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ARXDIALOG_H
#define UI_ARXDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_ArxDialog
{
public:
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout_2;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *ArxDialog)
    {
        if (ArxDialog->objectName().isEmpty())
            ArxDialog->setObjectName("ArxDialog");
        ArxDialog->resize(400, 300);
        verticalLayout = new QVBoxLayout(ArxDialog);
        verticalLayout->setObjectName("verticalLayout");
        formLayout_2 = new QFormLayout();
        formLayout_2->setObjectName("formLayout_2");
        label = new QLabel(ArxDialog);
        label->setObjectName("label");

        formLayout_2->setWidget(0, QFormLayout::ItemRole::LabelRole, label);

        label_2 = new QLabel(ArxDialog);
        label_2->setObjectName("label_2");

        formLayout_2->setWidget(1, QFormLayout::ItemRole::LabelRole, label_2);

        label_3 = new QLabel(ArxDialog);
        label_3->setObjectName("label_3");

        formLayout_2->setWidget(2, QFormLayout::ItemRole::LabelRole, label_3);


        verticalLayout->addLayout(formLayout_2);

        buttonBox = new QDialogButtonBox(ArxDialog);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setOrientation(Qt::Orientation::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::StandardButton::Cancel|QDialogButtonBox::StandardButton::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(ArxDialog);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, ArxDialog, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, ArxDialog, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(ArxDialog);
    } // setupUi

    void retranslateUi(QDialog *ArxDialog)
    {
        ArxDialog->setWindowTitle(QCoreApplication::translate("ArxDialog", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("ArxDialog", "TextLabel", nullptr));
        label_2->setText(QCoreApplication::translate("ArxDialog", "TextLabel", nullptr));
        label_3->setText(QCoreApplication::translate("ArxDialog", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ArxDialog: public Ui_ArxDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ARXDIALOG_H

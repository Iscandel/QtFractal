/********************************************************************************
** Form generated from reading UI file 'BoxFilterConfigurationDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BOXFILTERCONFIGURATIONDIALOG_H
#define UI_BOXFILTERCONFIGURATIONDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BoxFilterConfigurationDialog
{
public:
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *myButtonOk;
    QPushButton *myButtonCancel;
    QDoubleSpinBox *mySpinRadiusX;
    QDoubleSpinBox *mySpinRadiusY;
    QLabel *label;
    QLabel *label_2;

    void setupUi(QDialog *BoxFilterConfigurationDialog)
    {
        if (BoxFilterConfigurationDialog->objectName().isEmpty())
            BoxFilterConfigurationDialog->setObjectName(QStringLiteral("BoxFilterConfigurationDialog"));
        BoxFilterConfigurationDialog->resize(242, 104);
        horizontalLayoutWidget = new QWidget(BoxFilterConfigurationDialog);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(20, 60, 195, 31));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        myButtonOk = new QPushButton(horizontalLayoutWidget);
        myButtonOk->setObjectName(QStringLiteral("myButtonOk"));

        horizontalLayout->addWidget(myButtonOk);

        myButtonCancel = new QPushButton(horizontalLayoutWidget);
        myButtonCancel->setObjectName(QStringLiteral("myButtonCancel"));

        horizontalLayout->addWidget(myButtonCancel);

        mySpinRadiusX = new QDoubleSpinBox(BoxFilterConfigurationDialog);
        mySpinRadiusX->setObjectName(QStringLiteral("mySpinRadiusX"));
        mySpinRadiusX->setGeometry(QRect(30, 30, 81, 22));
        mySpinRadiusX->setValue(2);
        mySpinRadiusY = new QDoubleSpinBox(BoxFilterConfigurationDialog);
        mySpinRadiusY->setObjectName(QStringLiteral("mySpinRadiusY"));
        mySpinRadiusY->setGeometry(QRect(130, 30, 81, 22));
        mySpinRadiusY->setValue(2);
        label = new QLabel(BoxFilterConfigurationDialog);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(30, 10, 55, 16));
        label_2 = new QLabel(BoxFilterConfigurationDialog);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(130, 10, 55, 16));

        retranslateUi(BoxFilterConfigurationDialog);

        QMetaObject::connectSlotsByName(BoxFilterConfigurationDialog);
    } // setupUi

    void retranslateUi(QDialog *BoxFilterConfigurationDialog)
    {
        BoxFilterConfigurationDialog->setWindowTitle(QApplication::translate("BoxFilterConfigurationDialog", "BoxFilterConfigurationDialog", Q_NULLPTR));
        myButtonOk->setText(QApplication::translate("BoxFilterConfigurationDialog", "OK", Q_NULLPTR));
        myButtonCancel->setText(QApplication::translate("BoxFilterConfigurationDialog", "Cancel", Q_NULLPTR));
        label->setText(QApplication::translate("BoxFilterConfigurationDialog", "Radius X", Q_NULLPTR));
        label_2->setText(QApplication::translate("BoxFilterConfigurationDialog", "Radius Y", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class BoxFilterConfigurationDialog: public Ui_BoxFilterConfigurationDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BOXFILTERCONFIGURATIONDIALOG_H

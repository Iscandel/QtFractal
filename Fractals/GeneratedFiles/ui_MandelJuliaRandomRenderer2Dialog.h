/********************************************************************************
** Form generated from reading UI file 'MandelJuliaRandomRenderer2Dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MANDELJULIARANDOMRENDERER2DIALOG_H
#define UI_MANDELJULIARANDOMRENDERER2DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MandelJuliaRandomRenderer2Dialog
{
public:
    QGroupBox *groupBox_2;
    QPushButton *myButtonRandom;
    QSpinBox *mySpinRandom;
    QGroupBox *groupBox;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QListWidget *myListColors;
    QVBoxLayout *verticalLayout_2;
    QPushButton *myButtonAddColor;
    QPushButton *myButtonRemoveColor;
    QPushButton *myButtonMoveColorUp;
    QPushButton *myButtonMoveColorDown;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *myButtonOk;
    QPushButton *myButtonCancel;
    QGroupBox *groupBox_3;
    QLabel *myLabelColorPreview;
    QPushButton *myButtonChangeFractalColor;

    void setupUi(QDialog *MandelJuliaRandomRenderer2Dialog)
    {
        if (MandelJuliaRandomRenderer2Dialog->objectName().isEmpty())
            MandelJuliaRandomRenderer2Dialog->setObjectName(QStringLiteral("MandelJuliaRandomRenderer2Dialog"));
        MandelJuliaRandomRenderer2Dialog->resize(293, 605);
        groupBox_2 = new QGroupBox(MandelJuliaRandomRenderer2Dialog);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(20, 310, 261, 71));
        myButtonRandom = new QPushButton(groupBox_2);
        myButtonRandom->setObjectName(QStringLiteral("myButtonRandom"));
        myButtonRandom->setGeometry(QRect(10, 30, 93, 28));
        mySpinRandom = new QSpinBox(groupBox_2);
        mySpinRandom->setObjectName(QStringLiteral("mySpinRandom"));
        mySpinRandom->setGeometry(QRect(130, 30, 91, 22));
        mySpinRandom->setMinimum(1);
        mySpinRandom->setValue(3);
        groupBox = new QGroupBox(MandelJuliaRandomRenderer2Dialog);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(20, 10, 261, 271));
        horizontalLayoutWidget = new QWidget(groupBox);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(10, 30, 241, 231));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        myListColors = new QListWidget(horizontalLayoutWidget);
        myListColors->setObjectName(QStringLiteral("myListColors"));

        verticalLayout->addWidget(myListColors);


        horizontalLayout->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        myButtonAddColor = new QPushButton(horizontalLayoutWidget);
        myButtonAddColor->setObjectName(QStringLiteral("myButtonAddColor"));

        verticalLayout_2->addWidget(myButtonAddColor);

        myButtonRemoveColor = new QPushButton(horizontalLayoutWidget);
        myButtonRemoveColor->setObjectName(QStringLiteral("myButtonRemoveColor"));

        verticalLayout_2->addWidget(myButtonRemoveColor);

        myButtonMoveColorUp = new QPushButton(horizontalLayoutWidget);
        myButtonMoveColorUp->setObjectName(QStringLiteral("myButtonMoveColorUp"));

        verticalLayout_2->addWidget(myButtonMoveColorUp);

        myButtonMoveColorDown = new QPushButton(horizontalLayoutWidget);
        myButtonMoveColorDown->setObjectName(QStringLiteral("myButtonMoveColorDown"));

        verticalLayout_2->addWidget(myButtonMoveColorDown);


        horizontalLayout->addLayout(verticalLayout_2);

        horizontalLayoutWidget_2 = new QWidget(MandelJuliaRandomRenderer2Dialog);
        horizontalLayoutWidget_2->setObjectName(QStringLiteral("horizontalLayoutWidget_2"));
        horizontalLayoutWidget_2->setGeometry(QRect(40, 560, 195, 31));
        horizontalLayout_2 = new QHBoxLayout(horizontalLayoutWidget_2);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        myButtonOk = new QPushButton(horizontalLayoutWidget_2);
        myButtonOk->setObjectName(QStringLiteral("myButtonOk"));

        horizontalLayout_2->addWidget(myButtonOk);

        myButtonCancel = new QPushButton(horizontalLayoutWidget_2);
        myButtonCancel->setObjectName(QStringLiteral("myButtonCancel"));

        horizontalLayout_2->addWidget(myButtonCancel);

        groupBox_3 = new QGroupBox(MandelJuliaRandomRenderer2Dialog);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setGeometry(QRect(20, 390, 261, 151));
        myLabelColorPreview = new QLabel(groupBox_3);
        myLabelColorPreview->setObjectName(QStringLiteral("myLabelColorPreview"));
        myLabelColorPreview->setGeometry(QRect(10, 30, 111, 111));
        myButtonChangeFractalColor = new QPushButton(groupBox_3);
        myButtonChangeFractalColor->setObjectName(QStringLiteral("myButtonChangeFractalColor"));
        myButtonChangeFractalColor->setGeometry(QRect(150, 70, 93, 28));

        retranslateUi(MandelJuliaRandomRenderer2Dialog);

        QMetaObject::connectSlotsByName(MandelJuliaRandomRenderer2Dialog);
    } // setupUi

    void retranslateUi(QDialog *MandelJuliaRandomRenderer2Dialog)
    {
        MandelJuliaRandomRenderer2Dialog->setWindowTitle(QApplication::translate("MandelJuliaRandomRenderer2Dialog", "MandelJuliaRandomRenderer2Dialog", Q_NULLPTR));
        groupBox_2->setTitle(QApplication::translate("MandelJuliaRandomRenderer2Dialog", "Create colors", Q_NULLPTR));
        myButtonRandom->setText(QApplication::translate("MandelJuliaRandomRenderer2Dialog", "Random", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("MandelJuliaRandomRenderer2Dialog", "Colors", Q_NULLPTR));
        myButtonAddColor->setText(QApplication::translate("MandelJuliaRandomRenderer2Dialog", "Add color", Q_NULLPTR));
        myButtonRemoveColor->setText(QApplication::translate("MandelJuliaRandomRenderer2Dialog", "Remove color", Q_NULLPTR));
        myButtonMoveColorUp->setText(QApplication::translate("MandelJuliaRandomRenderer2Dialog", "Move color up", Q_NULLPTR));
        myButtonMoveColorDown->setText(QApplication::translate("MandelJuliaRandomRenderer2Dialog", "Move color down", Q_NULLPTR));
        myButtonOk->setText(QApplication::translate("MandelJuliaRandomRenderer2Dialog", "OK", Q_NULLPTR));
        myButtonCancel->setText(QApplication::translate("MandelJuliaRandomRenderer2Dialog", "Cancel", Q_NULLPTR));
        groupBox_3->setTitle(QApplication::translate("MandelJuliaRandomRenderer2Dialog", "Fractal color", Q_NULLPTR));
        myLabelColorPreview->setText(QString());
        myButtonChangeFractalColor->setText(QApplication::translate("MandelJuliaRandomRenderer2Dialog", "Change color", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MandelJuliaRandomRenderer2Dialog: public Ui_MandelJuliaRandomRenderer2Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MANDELJULIARANDOMRENDERER2DIALOG_H

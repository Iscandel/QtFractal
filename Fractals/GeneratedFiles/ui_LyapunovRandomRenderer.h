/********************************************************************************
** Form generated from reading UI file 'LyapunovRandomRenderer.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LYAPUNOVRANDOMRENDERER_H
#define UI_LYAPUNOVRANDOMRENDERER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LyapunovRandomRendererDialog
{
public:
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *myButtonOk;
    QPushButton *myButtonCancel;
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
    QGroupBox *groupBox_2;
    QPushButton *myButtonRandom;
    QSpinBox *mySpinRandom;

    void setupUi(QDialog *LyapunovRandomRendererDialog)
    {
        if (LyapunovRandomRendererDialog->objectName().isEmpty())
            LyapunovRandomRendererDialog->setObjectName(QStringLiteral("LyapunovRandomRendererDialog"));
        LyapunovRandomRendererDialog->resize(294, 472);
        horizontalLayoutWidget_2 = new QWidget(LyapunovRandomRendererDialog);
        horizontalLayoutWidget_2->setObjectName(QStringLiteral("horizontalLayoutWidget_2"));
        horizontalLayoutWidget_2->setGeometry(QRect(40, 420, 195, 31));
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

        groupBox = new QGroupBox(LyapunovRandomRendererDialog);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(20, 20, 261, 271));
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

        groupBox_2 = new QGroupBox(LyapunovRandomRendererDialog);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(20, 320, 251, 71));
        myButtonRandom = new QPushButton(groupBox_2);
        myButtonRandom->setObjectName(QStringLiteral("myButtonRandom"));
        myButtonRandom->setGeometry(QRect(10, 30, 93, 28));
        mySpinRandom = new QSpinBox(groupBox_2);
        mySpinRandom->setObjectName(QStringLiteral("mySpinRandom"));
        mySpinRandom->setGeometry(QRect(130, 30, 91, 22));
        mySpinRandom->setMinimum(1);
        mySpinRandom->setValue(3);

        retranslateUi(LyapunovRandomRendererDialog);

        QMetaObject::connectSlotsByName(LyapunovRandomRendererDialog);
    } // setupUi

    void retranslateUi(QDialog *LyapunovRandomRendererDialog)
    {
        LyapunovRandomRendererDialog->setWindowTitle(QApplication::translate("LyapunovRandomRendererDialog", "LyapunovRandomRenderer", Q_NULLPTR));
        myButtonOk->setText(QApplication::translate("LyapunovRandomRendererDialog", "OK", Q_NULLPTR));
        myButtonCancel->setText(QApplication::translate("LyapunovRandomRendererDialog", "Cancel", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("LyapunovRandomRendererDialog", "Colors", Q_NULLPTR));
        myButtonAddColor->setText(QApplication::translate("LyapunovRandomRendererDialog", "Add color", Q_NULLPTR));
        myButtonRemoveColor->setText(QApplication::translate("LyapunovRandomRendererDialog", "Remove color", Q_NULLPTR));
        myButtonMoveColorUp->setText(QApplication::translate("LyapunovRandomRendererDialog", "Move color up", Q_NULLPTR));
        myButtonMoveColorDown->setText(QApplication::translate("LyapunovRandomRendererDialog", "Move color down", Q_NULLPTR));
        groupBox_2->setTitle(QApplication::translate("LyapunovRandomRendererDialog", "Create colors", Q_NULLPTR));
        myButtonRandom->setText(QApplication::translate("LyapunovRandomRendererDialog", "Random", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class LyapunovRandomRendererDialog: public Ui_LyapunovRandomRendererDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LYAPUNOVRANDOMRENDERER_H

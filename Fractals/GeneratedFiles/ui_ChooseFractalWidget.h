/********************************************************************************
** Form generated from reading UI file 'ChooseFractalWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHOOSEFRACTALWIDGET_H
#define UI_CHOOSEFRACTALWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ChooseFractalWidget
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QComboBox *myComboBoxFractal;
    QHBoxLayout *horizontalLayout;
    QPushButton *myOkButton;
    QPushButton *myCancelButton;

    void setupUi(QWidget *ChooseFractalWidget)
    {
        if (ChooseFractalWidget->objectName().isEmpty())
            ChooseFractalWidget->setObjectName(QStringLiteral("ChooseFractalWidget"));
        ChooseFractalWidget->resize(301, 91);
        verticalLayoutWidget = new QWidget(ChooseFractalWidget);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(9, 9, 281, 81));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        myComboBoxFractal = new QComboBox(verticalLayoutWidget);
        myComboBoxFractal->setObjectName(QStringLiteral("myComboBoxFractal"));

        verticalLayout->addWidget(myComboBoxFractal);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        myOkButton = new QPushButton(verticalLayoutWidget);
        myOkButton->setObjectName(QStringLiteral("myOkButton"));

        horizontalLayout->addWidget(myOkButton);

        myCancelButton = new QPushButton(verticalLayoutWidget);
        myCancelButton->setObjectName(QStringLiteral("myCancelButton"));

        horizontalLayout->addWidget(myCancelButton);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(ChooseFractalWidget);

        QMetaObject::connectSlotsByName(ChooseFractalWidget);
    } // setupUi

    void retranslateUi(QWidget *ChooseFractalWidget)
    {
        ChooseFractalWidget->setWindowTitle(QApplication::translate("ChooseFractalWidget", "ChooseFractalWidget", Q_NULLPTR));
        myOkButton->setText(QApplication::translate("ChooseFractalWidget", "OK", Q_NULLPTR));
        myCancelButton->setText(QApplication::translate("ChooseFractalWidget", "Cancel", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ChooseFractalWidget: public Ui_ChooseFractalWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHOOSEFRACTALWIDGET_H

/********************************************************************************
** Form generated from reading UI file 'WidgetFractal.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGETFRACTAL_H
#define UI_WIDGETFRACTAL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>

QT_BEGIN_NAMESPACE

class Ui_WidgetFractal
{
public:

    void setupUi(QLabel *WidgetFractal)
    {
        if (WidgetFractal->objectName().isEmpty())
            WidgetFractal->setObjectName(QStringLiteral("WidgetFractal"));
        WidgetFractal->resize(400, 300);

        retranslateUi(WidgetFractal);

        QMetaObject::connectSlotsByName(WidgetFractal);
    } // setupUi

    void retranslateUi(QLabel *WidgetFractal)
    {
        WidgetFractal->setWindowTitle(QApplication::translate("WidgetFractal", "WidgetFractal", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class WidgetFractal: public Ui_WidgetFractal {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGETFRACTAL_H

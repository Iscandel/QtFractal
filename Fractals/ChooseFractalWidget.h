#pragma once

#include <QWidget>
#include "ui_ChooseFractalWidget.h"

class ChooseFractalWidget : public QWidget
{
	Q_OBJECT

public:
	ChooseFractalWidget(QWidget *parent = Q_NULLPTR);
	~ChooseFractalWidget();

private:
	Ui::ChooseFractalWidget ui;
};

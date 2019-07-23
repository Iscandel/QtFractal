#pragma once

#include <QWidget>
#include "ui_ChooseFractalWidget.h"

class FractalWindow;

class ChooseFractalWidget : public QWidget
{
	Q_OBJECT

public:
	ChooseFractalWidget(QWidget *parent = Q_NULLPTR);
	~ChooseFractalWidget();

	void setFractalWindow(FractalWindow* window);

	void setFractalNames(const std::vector<std::string> names);

protected:
	void onOk();

private:
	Ui::ChooseFractalWidget ui;

	FractalWindow* myWindow;
};

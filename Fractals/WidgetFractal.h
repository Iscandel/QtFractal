#pragma once

#include <QLabel>
#include "ui_WidgetFractal.h"

class WidgetFractal : public QLabel
{
	Q_OBJECT

public:
	WidgetFractal(QWidget *parent = Q_NULLPTR);
	~WidgetFractal();

signals:
	void signalRightButtonDrawFractal(int startX, int startY, int endX, int endY);

protected:
	void paintEvent(QPaintEvent* event) override;
	void mousePressEvent(QMouseEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;

private:
	Ui::WidgetFractal ui;

	bool myIsPressed;
	int myStartX;
	int myStartY;
	int myEndX;
	int myEndY;
};

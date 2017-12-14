#include "WidgetFractal.h"

#include "qevent.h"
#include "qpainter.h"

#include <iostream>

WidgetFractal::WidgetFractal(QWidget *parent)
: QLabel(parent)
,myIsPressed(false)
,myStartX(0)
,myStartY(0)
,myEndX(0)
,myEndY(0)
{
	ui.setupUi(this);
}

WidgetFractal::~WidgetFractal()
{
}

void WidgetFractal::paintEvent(QPaintEvent* event)
{
	//QLabel::paintEvent(event);

	QPainter painter(this);
	if (pixmap())
	{
		painter.drawPixmap(0, 0, *pixmap());
		painter.setPen(QColor(128, 128, 128));
		painter.drawRect(myStartX, myStartY, myEndX - myStartX, myEndY - myStartY);
	}
}

void WidgetFractal::mousePressEvent(QMouseEvent* event)
{
	std::cout << event->x() << " " << event->y() << std::endl;
	if (!myIsPressed)
	{
		myStartX = myStartY = myEndX = myEndY = 0;
	}

	if (event->button() == Qt::LeftButton)
	{
		myIsPressed = true;
		myStartX = event->x();
		myStartY = event->y();
		myEndX = myStartX;
		myEndY = myStartY;
	}
	else
	{
		if (myStartX != myEndX && myStartY != myEndY)
		{
			emit signalRightButtonDrawFractal(myStartX, myStartY, myEndX, myEndY);
			myStartX = myStartY = myEndX = myEndY = 0;
		}
	}

	repaint();
}

void WidgetFractal::mouseMoveEvent(QMouseEvent* event)
{
	if (myIsPressed)
	{
		myEndX = event->x();
		myEndY = myStartY + (myEndX - myStartX);
		repaint();
	}
}
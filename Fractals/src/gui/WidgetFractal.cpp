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
,myIsDragMode(true)
{
	ui.setupUi(this);
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
WidgetFractal::~WidgetFractal()
{
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void WidgetFractal::paintEvent(QPaintEvent* event)
{
	//QLabel::paintEvent(event);

	QPainter painter(this);
	if (pixmap())
	{
		painter.drawPixmap(myPixmapOffset.x(), myPixmapOffset.y(), *pixmap());
		painter.setPen(QColor(128, 128, 128));
		painter.drawRect(myStartX, myStartY, myEndX - myStartX, myEndY - myStartY);
	}
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void WidgetFractal::mousePressEvent(QMouseEvent* event)
{
	if (myIsDragMode)
	{
		myLastMousePos = event->pos();
	}
	else
	{
		if (!myIsPressed)
		{
			myStartX = myStartY = myEndX = myEndY = 0;
		}

		if (event->button() == Qt::LeftButton)
		{
			//myIsPressed = true;
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
	}

	repaint();
}

void WidgetFractal::mouseReleaseEvent(QMouseEvent *event)
{
	if (myIsDragMode)
	{
		if (pixmap())
		{
			emit signalRightButtonDrawFractal(-myPixmapOffset.x(), 
											  -myPixmapOffset.y(), 
											   pixmap()->width() - myPixmapOffset.x(), 
											   pixmap()->height() - myPixmapOffset.y());
			myPixmapOffset = QPoint();
		}
	}
}

void WidgetFractal::mouseMoveEvent(QMouseEvent* event)
{
	//NB mouseMoveEvent is only called if a mouse button is pressed (see MouseTracking to change the behaviour)
	if (myIsDragMode)
	{
		myPixmapOffset += event->pos() - myLastMousePos;
		myLastMousePos = event->pos();
		repaint();
	}
	else
	{
		//if (myIsPressed)
		{
			myEndX = event->x();
			myEndY = myStartY + (myEndX - myStartX);
			repaint();
		}
	}
}
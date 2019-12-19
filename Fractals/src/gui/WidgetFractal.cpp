#include "WidgetFractal.h"

#include "qevent.h"
#include "qpainter.h"

#include "core/Types.h"

#include <iostream>

WidgetFractal::WidgetFractal(QWidget *parent)
: QLabel(parent)
,myIsPressed(false)
,myStartX(0)
,myStartY(0)
,myEndX(0)
,myEndY(0)
,myIsDragMode(false)
,myButtonPressed(Qt::NoButton)
,myAngle(0)
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
		painter.resetTransform();

		painter.translate(pixmap()->width() / 2., pixmap()->height() / 2.);//.setTransform(QTransform::fromTranslate(pixmap()->width() / 2., pixmap()->height() / 2.), true);
		painter.rotate(myAngle);//.setTransform(QTransform().rotate(myAngle), true);
		painter.translate(-pixmap()->width() / 2., -pixmap()->height() / 2.);//.setTransform(QTransform::fromTranslate(-pixmap()->width() / 2., -pixmap()->height() / 2.), true);

		painter.drawPixmap(myPixmapOffset.x(), myPixmapOffset.y(), *pixmap());
		painter.setPen(QColor(128, 128, 128));
		painter.drawRect(myStartX, myStartY, myEndX - myStartX, myEndY - myStartY);
	}
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void WidgetFractal::mousePressEvent(QMouseEvent* event)
{
	myButtonPressed = event->button();
	myFirstMousePos = event->pos();

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
				emit signalRightButtonDrawFractal(myStartX, myStartY, myEndX, myEndY, myAngle);
				myStartX = myStartY = myEndX = myEndY = 0;
			}
		}
	}

	repaint();
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void WidgetFractal::mouseReleaseEvent(QMouseEvent *event)
{
	if (myIsDragMode)
	{
		//if (event->button() == Qt::LeftButton)
		{
			if (pixmap())
			{
				if (myPixmapOffset.x() != 0 || myPixmapOffset.y() != 0 || myAngle != 0) {
					emit signalRightButtonDrawFractal(-myPixmapOffset.x(),
						-myPixmapOffset.y(),
						pixmap()->width() - myPixmapOffset.x(),
						pixmap()->height() - myPixmapOffset.y(), myAngle);
				}
				myPixmapOffset = QPoint();
			}
		}
		//else if (event->button() == Qt::RightButton)
		//{
		//	double theta = 
		//}
	}

	myAngle = 0.;
	myButtonPressed = Qt::NoButton;
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void WidgetFractal::mouseMoveEvent(QMouseEvent* event)
{
	//NB mouseMoveEvent is only called if a mouse button is pressed (see MouseTracking to change the behaviour)
	if (myIsDragMode)
	{
		if(myButtonPressed == Qt::LeftButton)
		{
			myPixmapOffset += event->pos() - myLastMousePos;				
		}
		else if (myButtonPressed == Qt::RightButton)
		{
			QPoint normalizedFirstPos = myFirstMousePos - QPoint(pixmap()->width() / 2., pixmap()->height() / 2.);
			QPoint normalizedCurrPos = event->pos() - QPoint(pixmap()->width() / 2., pixmap()->height() / 2.);
			double zAxis = normalizedFirstPos.x() * normalizedCurrPos.y() - normalizedFirstPos.y() * normalizedCurrPos.x();
			double norm1 = std::sqrt(normalizedCurrPos.x() * normalizedCurrPos.x() + normalizedCurrPos.y() * normalizedCurrPos.y());
			double norm2 = std::sqrt(normalizedFirstPos.x() * normalizedFirstPos.x() + normalizedFirstPos.y() * normalizedFirstPos.y());
			//normalizedCurrPos /= norm1; normalizedFirstPos /= norm2;
			double dotProduct = normalizedCurrPos.x() * normalizedFirstPos.x() + normalizedCurrPos.y() * normalizedFirstPos.y();
			double tmpAngle = std::acos(dotProduct / (norm1 * norm2)) * 180 / 3.1415;
			
			if(zAxis > 0 )
				myAngle = tmpAngle;
			else 
				myAngle = -tmpAngle;
			if(myAngle > 360) myAngle -= 360;
			if (myAngle < -360) myAngle += 360;
		}
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

void WidgetFractal::wheelEvent(QWheelEvent * event)
{
	if (myIsDragMode)
	{
		real normalizedValue = (event->delta() / 120.); //To get the minimal stepsize in [-1, 1]
		real ratio = 1.;
		real minRatio = 0.7;
		if (event->delta() > 0)
			ratio = minRatio / normalizedValue;
		else
			ratio = -1./minRatio * normalizedValue;
	
		real startX = ratio * (0 - event->x()) + event->x();
		real endX = ratio * (pixmap()->width() - event->x()) + event->x();
		real startY = ratio * (0 - event->y()) + event->y();
		real endY = ratio * (pixmap()->height() - event->y()) + event->y();

		emit signalRightButtonDrawFractal(startX, startY, endX, endY, myAngle);
	}
	//left'  = ratio*(left -clickx)+clickx
	//right' = ratio*(right-clickx)+clickx

	//newMapWidth = zoomFactor * mapArea.width;//lets say that zoomFactor = <1.0, maxZoomFactor>
	//newMapHeight = zoomFactor * mapArea.height;

	//mapArea.left = mapClickPoint.x - (windowClickPoint.x - windowArea.left) * (newMapWidth / windowArea.width());
	//mapArea.top = mapClickPoint.y - (windowArea.bottom - windowClickPoint.y) * (newMapHeight / windowArea.height());
	//mapArea.right = mapArea.left + newWidth;
	//mapArea.bottom = mapArea.top + newHeight;

	//scale += (event->delta() / 120); //or use any other step for zooming 
}
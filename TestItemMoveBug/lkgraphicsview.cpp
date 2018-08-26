#include "lkgraphicsview.h"
#include <QGraphicsOpacityEffect>
// 
LKGraphicsView::LKGraphicsView(QWidget *parent)
	: QGraphicsView(parent)
{
	setDragMode(RubberBandDrag);
	setRenderHints(QPainter::Antialiasing|
		QPainter::TextAntialiasing);
	//setBackgroundBrush(QPixmap("./images/IMG_0816.JPG"));//background.png
}


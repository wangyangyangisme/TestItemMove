#include "LKRectItem.h"
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QBrush>
#include <QCoreApplication>
#include <QGraphicsScene>

LKRectItem::LKRectItem(QGraphicsItem* parent)
	: LKAgentItem<QGraphicsRectItem>(parent)
{

}

LKRectItem::LKRectItem(const  LKRectItem &srcItem)
{
	setRect(srcItem.rect());
}

LKRectItem::~LKRectItem()
{

}

QRectF LKRectItem::itemRectF()const
{
	return rect();
}

void  LKRectItem::setItemRectF(QRectF rect)
{
	setRect(rect);
}


QRectF LKRectItem::boundingRect()const
{
	QRectF reBounding = rect();
	reBounding.adjust(-pen().width()/2,-pen().width()/2,
		              pen().width()/2,pen().width()/2);
	return reBounding;
}

void LKRectItem::paint(QPainter *painter, 
					   const QStyleOptionGraphicsItem *option, 
                       QWidget *widget /* = 0 */)
{
	Q_UNUSED(widget);
	painter->drawRect(rect());
	LKBaseItem::paint(painter,option,widget);
	
}
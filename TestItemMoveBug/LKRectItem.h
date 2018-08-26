#ifndef LKRECTITEM_H
#define LKRECTITEM_H

#include <QGraphicsRectItem>
#include <QMenu>
#include <QPen>
#include "LKBaseItem.h"
#include "ItemDefine.h"
#include "LKAgentItem.h"

class LKRectItem : public LKAgentItem<QGraphicsRectItem>
{

public:
	LKRectItem(QGraphicsItem* parent=NULL);
	LKRectItem(const  LKRectItem &srcItem);
	~LKRectItem();
	enum { Type = c_rect };
	int type() const{ return Type; }
	QString  typeName()const{return "Rect";}
	QRectF itemRectF()const;
	void   setItemRectF(QRectF rect);
	QRectF boundingRect()const;
public:
	virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = 0 */);
	
};

#endif // LKRECTITEM_H

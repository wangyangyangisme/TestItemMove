#ifndef LKGROUPITEM_H
#define LKGROUPITEM_H

#include <QGraphicsItemGroup>
#include <QObject>
#include "focusagentitem.h"
#include "LKAgentItem.h"
class LKGroupItem :public QObject,public LKAgentItem<QGraphicsItemGroup>
{
	Q_OBJECT
public:
	LKGroupItem(QGraphicsItem *parent = 0,QObject *obj=0);
	~LKGroupItem();
	QRectF  itemRectF()const;
	void    setItemRectF(QRectF rect);
	void    setItemPos(QPointF curPos);
	void    setEnableEdit(bool bOk=true);
protected:
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = 0 */);
	void contextMenuEvent(QGraphicsSceneContextMenuEvent* event);
Q_SIGNALS:
	void sgnl_createNewType(LKGroupItem *item);
	void sgnl_deleteThis(LKGroupItem *item);
};
#endif // LKGROUPITEM_H

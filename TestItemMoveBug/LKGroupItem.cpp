#include "LKGroupItem.h"
#include <QMenu>
#include <QGraphicsScene>
#include <QDebug>
LKGroupItem::LKGroupItem(QGraphicsItem *parent,QObject *obj)
	: LKAgentItem<QGraphicsItemGroup>(parent)
	,QObject(obj)
{
}

LKGroupItem::~LKGroupItem()
{
}

QRectF LKGroupItem::itemRectF()const
{
	return boundingRect();
}
void LKGroupItem::setItemRectF(QRectF rect)
{
	//QTransform curMatrix = QTransform().translate(xx,yy).scale(wS,hS).translate(-xx, -yy);
	//QTransform transForm;
	QRectF curRect = boundingRect();
	qreal wS = rect.width()/boundingRect().width();
	qreal hS = rect.height()/boundingRect().height();
	setMatrix(QMatrix().scale(wS,hS));
}

void LKGroupItem::setItemPos(QPointF curPos)
{

	QPointF origin = sceneBoundingRect().topLeft() - scenePos();
	QPointF delta = curPos - origin;
	setPos(delta);
}

void LKGroupItem::setEnableEdit(bool bOk)
{
	if(bOk)
	{
		setHandlesChildEvents(false);
		setFlags(QGraphicsItem::ItemIsMovable|QGraphicsItem::ItemIsSelectable);
	}
	else
	{
		setFiltersChildEvents(true);
		setHandlesChildEvents(false);
		setAcceptHoverEvents(false);
		setFlag(QGraphicsItem::ItemIsMovable,false);
		setFlag(QGraphicsItem::ItemIsSelectable,false);
	}
}

void LKGroupItem::contextMenuEvent(QGraphicsSceneContextMenuEvent* event)
{
	QMenu menu;
	QAction *resolveGroupAction = menu.addAction(QIcon(":/divide_group.png"),QObject::tr("divide group"));
	QAction *commandAction = 0;
	QAction *selectedAction = menu.exec(event->screenPos());
	if (selectedAction==resolveGroupAction)
	{
		foreach (QGraphicsItem *item,this->childItems())
		{
			if(item->type()<c_line || item->type()>=c_end)
				continue;//过滤agentItem
			
			QPointF itemPos = item->scenePos();
			item->setParentItem(0);
			this->removeFromGroup(item);//将item从group中移出
				QRectF curRect = dynamic_cast<LKBaseItem*>(item)->itemRectF();//
				dynamic_cast<LKBaseItem*>(item)->setItemRectF(curRect);//oldTransform.mapRect(curRect)
				if(item->type()==c_group)
					item->setPos(itemPos);
				else
					dynamic_cast<LKBaseItem*>(item)->setItemPos(itemPos);
				dynamic_cast<LKBaseItem*>(item)->setEnableEdit(true);
		}

		//setEnableEdit(false);//取消尺寸编辑并删除当前group的agentItem
		//发送信号到scene对象，通知删除自己
		connect(this,SIGNAL(sgnl_deleteThis(LKGroupItem*)),scene(),SLOT(deleteGroupItem(LKGroupItem*)));
		emit sgnl_deleteThis(this);
		
	}
}




void LKGroupItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = 0 */)
{
	QGraphicsItemGroup::paint(painter,option,widget);
}


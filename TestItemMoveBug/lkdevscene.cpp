#include "lkdevscene.h"
#include "LKBaseItem.h"
#include "LKGroupItem.h"
#include <QTextCursor>
#include <QDebug>
#include <QMenu>
#include "LKRectItem.h"
LKDevScene::LKDevScene(QObject *parent)
	: QGraphicsScene (-250,-250,500,500,parent)
	,curShap_(none)
	,selectItem_(0)
{
	LKRectItem *pRectItem0 = new LKRectItem();
	pRectItem0->setItemRectF(QRectF(80,80,200,200));
	addItem(pRectItem0);
	pRectItem0->setEnableEdit(true);

	LKRectItem *pRectItem1 = new LKRectItem();
	pRectItem1->setItemRectF(QRectF(150,80,200,200));
	addItem(pRectItem1);
	pRectItem1->setEnableEdit(true);
}

LKDevScene::~LKDevScene()
{

}

void LKDevScene::setCurShap(item_type curShap)
{
	curShap_=curShap;
}

void LKDevScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	QGraphicsScene::mousePressEvent(event); 
}

void LKDevScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
	QGraphicsScene::mouseMoveEvent(event); 
}

void LKDevScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
	QGraphicsScene::mouseReleaseEvent(event); 
}

void LKDevScene::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
	int count=0;
	foreach(QGraphicsItem *item,selectedItems())
	{
		if(item->type()>c_base && item->type()<c_end && item->type()!=c_background)
			++count;
	}
	if(count<=1)
		return QGraphicsScene::contextMenuEvent(event);
	QMenu menu;
	QAction *createGroupAction = menu.addAction(QIcon(":/create_group.png"),tr("create group"));
	QAction *selectedAction = menu.exec(event->screenPos());
	if (selectedAction==createGroupAction)
	{
		LKGroupItem *pGroup = new LKGroupItem;
		QList<QGraphicsItem *> validItems;//收集可用的items，即需要加入group的item
		int itemCount = this->selectedItems().count();
		foreach(QGraphicsItem *item,this->selectedItems())
		{  
			if(item->type()!=c_agent)
				validItems.append(item);
		}
		foreach(QGraphicsItem *curItem,validItems)
		{
			LKBaseItem *newItem = dynamic_cast<LKBaseItem*>(curItem);
			removeItem(newItem->focuseAgentPtr());
			newItem->setEnableEdit(false);
			pGroup->addToGroup(newItem->item());
		}
		addItem(pGroup);
		pGroup->setEnableEdit(true);
	}
}
#include "LKBaseItem.h"

#include<Quuid>
#include <QGraphicsScene>
#include <QStyleOptionGraphicsItem>

qint16 LKBaseItem::openFileEdition_= 0x01;

LKBaseItem::LKBaseItem(QGraphicsItem *parent)
:enableEdit_(false)
,pItem_(NULL)
,presizeAgent_(0)
,focuseType_(FocusAgentItem::SHAP_RECT)
,uuid_(QUuid::createUuid().toString())
,objName_(QString())
{

}

LKBaseItem::~LKBaseItem()
{
}

void LKBaseItem::setItem(QGraphicsItem *curItem)
{
	pItem_=curItem;
}

QGraphicsItem * LKBaseItem::item()const
{
	return pItem_;
}


void LKBaseItem::setEnableEdit(bool bAllow)
{
	if(bAllow)
	{
		if( presizeAgent_==0)
		{
			presizeAgent_ = new FocusAgentItem(this,FocusAgentItem::shap_type(focuseType_));
			pItem_->scene()->addItem(presizeAgent_);
			
		}
		presizeAgent_->hide();
		//pItem_->setFiltersChildEvents(true);
		pItem_->setAcceptHoverEvents(true);
		pItem_->setFlags(  QGraphicsItem::ItemIsMovable | 
			QGraphicsItem::ItemSendsGeometryChanges
			| QGraphicsItem::ItemIsSelectable);
		pItem_->setCursor(Qt::SizeAllCursor);
		enableEdit_ = true;
	}
	else
	{
		if( presizeAgent_!=0)
		{
			//pItem_->scene()->removeItem(presizeAgent_);
			delete presizeAgent_,presizeAgent_=0;
		}
		//pItem_->setFiltersChildEvents(false);
		pItem_->setAcceptHoverEvents(false);
		pItem_->setFlag(QGraphicsItem::ItemIsMovable,false);
		pItem_->setFlag(QGraphicsItem::ItemIsSelectable,false);
		pItem_->setFlag(QGraphicsItem::ItemSendsGeometryChanges,false);

		pItem_->setCursor(Qt::ArrowCursor);
		enableEdit_ = false;
	}
}
void LKBaseItem::paint(QPainter *painter, 
					   const QStyleOptionGraphicsItem *option, 
					   QWidget *widget /* = 0 */)
{
	Q_UNUSED(widget);
	if(!enableEdit())
		return;
	if(option->state & QStyle::State_Selected)
	{
		focuseAgentPtr()->show();
		focuseAgentPtr()->setSelected(true);
	}
	else
	{
		focuseAgentPtr()->hide();
	}
}

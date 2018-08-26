#ifndef LKBASEITEM_H
#define LKBASEITEM_H

#include <QGraphicsItem>
#include <QCursor>
#include <QString>
#include <QObject>
#include <QFont>
#include <QBrush>
#include <QPen>
#include <QPalette>
#include "FocusAgentItem.h"
#include "ItemDefine.h"
class LKBaseItem
{
public:
	LKBaseItem(QGraphicsItem *parent=NULL);
	virtual ~LKBaseItem();
	enum { Type = c_base };
	int      type() const{ return Type;}
	virtual QString  typeName()const{return QString();}
	void setItem(QGraphicsItem *curItem);//{pItem_=curItem;}
	QGraphicsItem * item()const;//{return pItem_;}
	QRectF  boundRect(){return pItem_->boundingRect();}
public:
	//*****************edit property******************//
	virtual  bool enableEdit(){return enableEdit_;}
	virtual  void setEnableEdit(bool bAllow=false);
	FocusAgentItem* focuseAgentPtr(){return presizeAgent_;}
	void setFocuseType(int ntype){focuseType_=ntype;}
	//base property
	int       itemType()const {return pItem_->type();}
	qreal   itemZValue()const{return pItem_->zValue();}
	virtual void    setItemPos(QPointF pos){pItem_->setPos(pos);pItem_->update();}
	virtual QPointF itemPos()const {return pItem_->pos();}
	void    setItemZValue(qreal zValue){pItem_->setZValue(zValue);}
	//------------------rect-------------------------//
	virtual bool   canSetItemRectF()const{return true;}
	virtual QRectF itemRectF()const{return pItem_->boundingRect();}
	virtual void   setItemRectF(QRectF rect){}	
protected:
	virtual void paint(QPainter *painter,const QStyleOptionGraphicsItem *option,QWidget *widget);
private:
	QGraphicsItem *pItem_;
	bool enableEdit_;
	FocusAgentItem *presizeAgent_;
	int  focuseType_;
	QString uuid_;
	QString objName_;
public:
	static qint16 openFileEdition_;
};

#endif // LKBASEITEM_H

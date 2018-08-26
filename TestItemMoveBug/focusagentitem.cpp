#include "focusagentitem.h"
#include "LKBaseItem.h"
#include <QCursor>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPainter>
#include <QGraphicsLineItem>
#include <QGraphicsEllipseItem>
#include <QDebug>

FocusAgentItem::FocusAgentItem(LKBaseItem *parent,shap_type shapType)
	: QGraphicsItem(0)
	,framRect_(0,0,0,0)
	,move_(false)
	,curPane_(NULL)
	,shapType_(shapType)
	,pCurrentItem_(parent)
	,pdashRectShap_(0)
{
	framRect_ = parent->item()->sceneBoundingRect();
	if(parent->item()->type()==c_rect)
		framRect_.adjust(-4,-4,4,4);
	setFlag(QGraphicsItem::ItemIsSelectable,true);
	setFlag(QGraphicsItem::ItemIsMovable,true);
	switch(shapType_)
	{
	case SHAP_RECT:
		{	
			pdashRectShap_ = new QGraphicsRectItem(this);
			pdashRectShap_->setPen(QPen(Qt::green,0,Qt::DashLine));
			pdashRectShap_->hide();
		}
		break;
	}
	

	if(shapType_==SHAP_RECT||shapType_==SHAP_ELLIPSE)
	{
		for(int i=0;i<8;++i)
		{
			QGraphicsRectItem *pPane = new QGraphicsRectItem(this);
			pPane->setCursor(Qt::SizeFDiagCursor);
			pPane->setPen(QPen(QColor(0,128,0)));
			pPane->setBrush(QBrush(QColor(173,235,173)));
			pPane->setRect(0,0,8,8);
			pPane->setData(0,10+i);
			panes_.insert(i,pPane);
			if(i==0 || i==7)
				pPane->setCursor(Qt::SizeFDiagCursor);
			else if(i==1 || i== 6)
				pPane->setCursor(Qt::SizeHorCursor);
			else if(i==2 || i==5)
				pPane->setCursor(Qt::SizeBDiagCursor);
			else if(i==3 || i==4)
				pPane->setCursor(Qt::SizeVerCursor);
		}
        adjustPanesPos(boundingRect());
	}
}

void FocusAgentItem::adjustPanesPos(QRectF re)
{
	const QRectF parentRect = re;
	qreal x = 0, y = 0;
	x = parentRect.width() / 2 - 4+re.left();
	y = 0+re.top();
	panes_[TOP]->setPos(x,y);


	x = parentRect.width() / 2 - 4+re.left();
	y = parentRect.height() - 8+re.top();
	panes_[BOTTOM]->setPos(x,y);

	x = parentRect.width() - 8+re.left();
	y = parentRect.height()/2 - 4+re.top();
	panes_[RIGHT]->setPos(x,y);

	x = 0+re.left();
	y = parentRect.height() / 2 - 4+re.top();
	panes_[LEFT]->setPos(x,y);

	x = 0+re.left();
	y = 0+re.top();
	panes_[LEFT_TOP]->setPos(x,y);

	x = parentRect.width()- 8+re.left();
	y = parentRect.height() - 8+re.top();
	panes_[RIGHT_BOTTOM]->setPos(x,y);

	x = parentRect.width() - 8+re.left();
	y = 0+re.top();
	panes_[RIGHT_TOP]->setPos(x,y);

	x = 0+re.left();
	y = parentRect.height()- 8+re.top();
	panes_[LEFT_BOTTOM]->setPos(x,y);

}
FocusAgentItem::~FocusAgentItem()
{

}

QRectF FocusAgentItem::boundingRect() const
{
	return framRect_;
}

void FocusAgentItem::updateFrameRect(QRectF re,qreal penWidth)
{
	framRect_ = pCurrentItem_->item()->boundingRect();
	setPos(pCurrentItem_->item()->scenePos());
	if(pCurrentItem_->item()->type()==c_rect)
		framRect_.adjust(1+penWidth,1+penWidth,-1-penWidth,-1-penWidth);
	else
		framRect_.adjust(-4,-4,4,4);
	adjustPanesPos(boundingRect());
	
}

void FocusAgentItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    curPane_ = qgraphicsitem_cast<QGraphicsItem*>(scene()->itemAt(event->scenePos(),QTransform()));
	int cellId = curPane_->data(0).toInt();
	if(curPane_ && cellId>=10)
	{
		move_=true;
		lastPoint_.setX(event->scenePos().x());
		lastPoint_.setY(event->scenePos().y());
		QRectF boundRect = boundingRect();
		switch(shapType_)
		{
		case SHAP_RECT:
			{
				pdashRectShap_->setRect(boundRect.left()+4,boundRect.top()+4,
					                    boundRect.width()-8,boundRect.height()-8);
				pdashRectShap_->show();
			}
			break;
		}

		
	}
	else
		return QGraphicsItem::mousePressEvent(event);
}

void FocusAgentItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
	if(!move_)
		return QGraphicsItem::mouseMoveEvent(event);
	QPointF curPoint(event->scenePos());
	QPointF interval = curPoint-lastPoint_;

	int nValue = curPane_->data(0).toInt();
	QRectF boundRect = boundingRect();
	qreal qleft = boundRect.left();
	qreal qtop = boundRect.top();
	QRectF re(0,0,1,1);
	switch(nValue-10)
	{
	case RIGHT_BOTTOM:
		re.setRect(4+qleft,4+qtop,boundRect.width()-8+interval.x(),boundRect.height()-8+interval.y());
		break;
	case RIGHT:
		re.setRect(4+qleft,4+qtop,boundRect.width()-8+interval.x(),boundRect.height()-8);
		break;
	case BOTTOM:
		re.setRect(4+qleft,4+qtop,boundRect.width()-8,boundRect.height()-8+interval.y());
		break;
	case LEFT_TOP:
		re.setRect(4+interval.x()+qleft,4+interval.y()+qtop,boundRect.width()-8-interval.x(),boundRect.height()-8-interval.y());
		if(re.top()>framRect_.bottom()-1-4)
			re.setTop(framRect_.bottom()-1-4);
		if(re.bottom()>framRect_.bottom()-4)
			re.setBottom(framRect_.bottom()-4);

		if(re.left()>framRect_.right()-1-4)
			re.setLeft(framRect_.right()-1-4);
		if(re.right()>framRect_.right()-4)
			re.setRight(framRect_.right()-4);
		break;
	case LEFT:
		re.setRect(4+interval.x()+qleft,4+qtop,boundRect.width()-8-interval.x(),boundRect.height()-8);
		if(re.left()>framRect_.right()-1-4)
			re.setLeft(framRect_.right()-1-4);
		if(re.right()>framRect_.right()-4)
			re.setRight(framRect_.right()-4);
		break;
	case TOP:
		re.setRect(4+qleft,4+interval.y()+qtop,boundRect.width()-8,boundRect.height()-8-interval.y());
		if(re.top()>framRect_.bottom()-1-4)
			re.setTop(framRect_.bottom()-1-4);
		if(re.bottom()>framRect_.bottom()-4)
			re.setBottom(framRect_.bottom()-4);
		break;
	case LEFT_BOTTOM:
		re.setRect(4+interval.x()+qleft,4+qtop,boundRect.width()-8-interval.x(),boundRect.height()-8+interval.y());
		if(re.left()>framRect_.right()-1-4)
			re.setLeft(framRect_.right()-1-4);
		if(re.right()>framRect_.right()-4)
			re.setRight(framRect_.right()-4);
		break;
	case RIGHT_TOP:
		re.setRect(4+qleft,4+interval.y()+qtop,boundRect.width()-8+interval.x(),boundRect.height()-8-interval.y());
		if(re.top()>framRect_.bottom()-1-4)
			re.setTop(framRect_.bottom()-1-4);
		if(re.bottom()>framRect_.bottom()-4)
			re.setBottom(framRect_.bottom()-4);
		break;
	}

	if(re.width()<1)
		re.setWidth(1);
	if(re.height()<1)
		re.setHeight(1);
	
	switch(shapType_)
	{
	case SHAP_RECT:
		pdashRectShap_->setRect(re);
		break;
	}
	
}

void FocusAgentItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
	if(!move_)
		return QGraphicsItem::mouseReleaseEvent(event);
	
	move_=false;

	

	switch(shapType_)
	{
	case SHAP_RECT:
		{
			pdashRectShap_->hide();
			framRect_.setWidth(pdashRectShap_->rect().width()+8);
			framRect_.setHeight(pdashRectShap_->rect().height()+8);
			framRect_ = pdashRectShap_->rect().adjusted(-4,-4,4,4);
 			adjustPanesPos(framRect_);
			pCurrentItem_->setItemRectF(QRectF(0,0,pdashRectShap_->rect().width(),pdashRectShap_->rect().height()));
			pCurrentItem_->setItemPos(mapToScene(pdashRectShap_->rect().topLeft()));

		}
		break;
	}
}

void FocusAgentItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = 0 */)
{
}


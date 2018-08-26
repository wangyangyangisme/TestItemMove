#ifndef FOCUSAGENTITEM_H
#define FOCUSAGENTITEM_H

#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QGraphicsSceneHoverEvent>
#include <QGraphicsEllipseItem>
#include "ItemDefine.h"
class LKBaseItem;
class FocusAgentItem : public QGraphicsItem
{
public:
	enum shap_type{SHAP_LINE,SHAP_ELLIPSE,SHAP_RECT,SHAP_POLYGON};
	enum pans_Pos{LEFT_TOP,LEFT,LEFT_BOTTOM,TOP,BOTTOM,RIGHT_TOP,RIGHT,RIGHT_BOTTOM};
	FocusAgentItem(LKBaseItem *parent,shap_type shapType=SHAP_RECT);
	~FocusAgentItem();
	virtual QRectF boundingRect() const;
    LKBaseItem * item(){return pCurrentItem_;}
	enum { Type = c_agent };
	int type() const{ return Type; }

    void       adjustPanesPos(QRectF re);

	void       updateFrameRect(QRectF re,qreal penWidth=0);

protected:
	void mousePressEvent(QGraphicsSceneMouseEvent *event);
	void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
	void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
	//void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
public:
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = 0 */);
private:
	QHash<int,QGraphicsItem*>    panes_;

	shap_type                    shapType_;
	QGraphicsRectItem            *pdashRectShap_;
	QPointF                      lastPoint_;
	QGraphicsItem                *curPane_;
	QRectF                       framRect_;
	bool                         move_;

	LKBaseItem                   *pCurrentItem_;

};

#endif // FOCUSAGENTITEM_H

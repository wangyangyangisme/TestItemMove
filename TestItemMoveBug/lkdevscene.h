#ifndef LKDEVSCENE_H
#define LKDEVSCENE_H

#include <QGraphicsScene >
#include <QVector>
#include "ItemDefine.h"
class LKGroupItem;
class LKBaseItem;
class LKDevScene : public QGraphicsScene 
{
	Q_OBJECT
public:
	LKDevScene(QObject *parent);
	~LKDevScene();

	void setCurShap(item_type curShap);
protected:
	void mousePressEvent(QGraphicsSceneMouseEvent *event);
	void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
	void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
	void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);
private:
	item_type               curShap_;
	LKBaseItem*             selectItem_;
};

#endif // LKDEVSCENE_H

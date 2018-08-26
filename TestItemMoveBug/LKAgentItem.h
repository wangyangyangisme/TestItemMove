#ifndef LKAGENTITEM_H
#define LKAGENTITEM_H

//#include <QObject>
#include "LKBaseItem.h"
//#include <QGraphicsItem>
template <class TItem>
class LKAgentItem : public LKBaseItem,public TItem
{
public:
	LKAgentItem(QGraphicsItem *parent=NULL);
	virtual ~LKAgentItem(){};

private:
	
};

template <class TItem>
LKAgentItem<TItem>::LKAgentItem(QGraphicsItem *parent)
:TItem(parent)
{
	setItem(this);
}

#endif // LKAGENTITEM_H

#ifndef __ITEM_DEFINE_H
#define __ITEM_DEFINE_H

#include <QGraphicsItem>

static const double Pi = 3.14159265358979323846264338327950288419717;
static double TwoPi = 2.0 * Pi;

enum item_type
{
	none       = -1,
	c_base     = QGraphicsItem::UserType,
	c_line     = QGraphicsItem::UserType+1,
	c_rect     = QGraphicsItem::UserType+2,
	c_ellipse  = QGraphicsItem::UserType+3,
	c_polyline = QGraphicsItem::UserType+4,
	c_polygon  = QGraphicsItem::UserType+5,
	c_pixmap   = QGraphicsItem::UserType+6,
	c_svg      = QGraphicsItem::UserType+7,
	c_text     = QGraphicsItem::UserType+8,
	c_button   = QGraphicsItem::UserType+9,
	c_led      = QGraphicsItem::UserType+10,
	c_gauge    = QGraphicsItem::UserType+11,
	c_lcd      = QGraphicsItem::UserType+12,
	c_joinline = QGraphicsItem::UserType+13,
	c_vumeter  = QGraphicsItem::UserType+14,
	c_curve    = QGraphicsItem::UserType+15,
	c_list     = QGraphicsItem::UserType+16,
	c_table    = QGraphicsItem::UserType+17,
	c_clock    = QGraphicsItem::UserType+18,
	c_edit     = QGraphicsItem::UserType+19,
	c_combox   = QGraphicsItem::UserType+20,
	c_group      = QGraphicsItem::UserType+21,
	c_background = QGraphicsItem::UserType+22,
	c_scroll_text= QGraphicsItem::UserType+23,
	c_end        = QGraphicsItem::UserType+100,
	c_agent      = QGraphicsItem::UserType+200,

};

enum endPtType
{
	C_TopRight=0,
	C_BottomLeft,
	C_BottomRight
};
#endif
#ifndef LKGRAPHICSVIEW_H
#define LKGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QWheelEvent>
#include <cmath>

class LKGraphicsView : public QGraphicsView
{
	Q_OBJECT

public:
	explicit LKGraphicsView(QWidget *parent=0);

	public slots:
		void zoomIn() { scaleBy(1.1); }
		void zoomOut() { scaleBy(1.0 / 1.1); }
		void zoomFit() { resetMatrix();}
protected:
	void wheelEvent(QWheelEvent *event)
	{ scaleBy(std::pow(4.0 / 3.0, (-event->delta() / 240.0))); }

private:
	void scaleBy(double factor) { scale(factor, factor); }
private:
	
};

#endif // LKGRAPHICSVIEW_H

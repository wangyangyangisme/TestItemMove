#include "testitemmovebug.h"
#include <QHBoxLayout>

TestItemMoveBug::TestItemMoveBug(QWidget *parent, Qt::WindowFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);

	scene = new LKDevScene(this);
	QHBoxLayout *layout = new QHBoxLayout();
	view = new LKGraphicsView(this);
	view->setScene(scene);
	layout->addWidget(view);
	QWidget *widget = new QWidget(this);
	widget->setLayout(layout);
	setCentralWidget(widget);

	showMaximized();
}

TestItemMoveBug::~TestItemMoveBug()
{

}

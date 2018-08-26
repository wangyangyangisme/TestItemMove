#ifndef TESTITEMMOVEBUG_H
#define TESTITEMMOVEBUG_H

#include <QMainWindow>
#include "ui_testitemmovebug.h"
#include "lkdevscene.h"
#include "lkgraphicsview.h"

class TestItemMoveBug : public QMainWindow
{
	Q_OBJECT

public:
    TestItemMoveBug(QWidget *parent = 0, Qt::WindowFlags flags = 0);
	~TestItemMoveBug();

private:
	Ui::TestItemMoveBugClass ui;
	LKDevScene                      *scene;      //场景
	LKGraphicsView                  *view;       //视图
};

#endif // TESTITEMMOVEBUG_H

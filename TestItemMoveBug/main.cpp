#include "testitemmovebug.h"
#include <QApplication>
#include <QTextCodec>
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
    //QTextCodec::setCodecForTr( QTextCodec::codecForName("GBK") );
    //QTextCodec::setCodecForCStrings(QTextCodec::codecForName("GBK"));
	QTextCodec::setCodecForLocale(QTextCodec::codecForName("GBK"));
	TestItemMoveBug w;
	w.show();
	return a.exec();
}

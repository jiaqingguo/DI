#include "widget.h"

#include <QApplication>
#include <qdebug.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();
//	Listen* l = new Listen;
	//HWND hwnd = GetForegroundWindow();
	////ShowWindow(hwnd, SW_MINIMIZE);
	//ShowWindow(hwnd, SW_HIDE); // вўВи
	if (argc > 1)
	{
		/*l->startProgram(argv[1]);
		l->hwndListen();*/
		QString input = argv[1];
		qDebug() << "argc:"<<argv[1];
		QStringList parts = input.split('|');
		qDebug() << parts.at(0);
		qDebug() << parts.at(1);
		if (parts.size() == 2)
		{
			w.InitResource(parts.at(1).toStdString());
			w.StartProgram(parts.at(0).toStdString());
			w.HwndListen();

		}
		
	}
    return a.exec();
}

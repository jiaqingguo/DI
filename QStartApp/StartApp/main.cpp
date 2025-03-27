#include "widget.h"

#include <QApplication>

#include <qdebug.h>

Widget* w = nullptr;

void success()
{
	w->closeGifDialog();
}

void cloae()
{
	w->showGifDialog();
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
	w = new Widget();

	w->show();
//	Listen* l = new Listen;
	//HWND hwnd = GetForegroundWindow();
	////ShowWindow(hwnd, SW_MINIMIZE);
	//ShowWindow(hwnd, SW_HIDE); // 隐藏
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
			w->showGifDialog();
			w->InitResource(parts.at(1).toStdString());
			w->StartProgram(parts.at(0).toStdString(), success);
			//w->setCloseCallBack(cloae);
		}
	}

	return a.exec();
}

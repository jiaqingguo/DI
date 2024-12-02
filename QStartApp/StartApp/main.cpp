#include "widget.h"

#include <QApplication>

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

		w.StartProgram(argv[1]);
		w.HwndListen();
	}
    return a.exec();
}

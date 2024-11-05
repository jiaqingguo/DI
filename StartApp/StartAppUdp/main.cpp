#include "pch.h"
#include "Listen.h"


int main(int argc, char* argv[])
{
	Listen* l = new Listen;
	HWND hwnd = GetForegroundWindow();
	//ShowWindow(hwnd, SW_MINIMIZE);
	ShowWindow(hwnd, SW_HIDE); // вўВи
	if (argc>1)
	{
		l->startProgram(argv[1]);
		
		l->hwndListen();
	}
	delete l;
	return 0;
}
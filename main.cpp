#include "CefBrowser.h"

#ifdef NDEBUG
#pragma comment(lib,"QCefBrowser")
#else
#pragma comment(lib,"QCefBrowser_d")
#endif

// Entry point function for all processes.
int main(int argc, char *argv[])
{
	//--- main process -----
	QApplication qapp(argc, argv);
	//
	QCefProcessStart();
	//
	//create window;
	QBrowserWindow* cefWebWindow = new QBrowserWindow(NULL);
	cefWebWindow->init();
	cefWebWindow->show();

	//
	QCefMessageLoop();
	//
	int qt_exit_code = qapp.exec();
	//
	QCefProcessExit();

	return qt_exit_code;
}

#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QTimer>
#ifdef Q_OS_WIN
#include <windows.h>
#endif
#include "CefAppImp.h"
#include "QBrowserWindow.h"

#pragma comment(lib,"libcef")
#ifdef NDEBUG
#pragma comment(lib,"libcef_dll_wrapper")
#else
#pragma comment(lib,"libcef_dll_wrapper_d")
#endif

int QCefProcessStart()
{
	// Provide CEF with command-line arguments.
	CefMainArgs main_args;

	void* sandbox_info = NULL;

	// CEF applications have multiple sub-processes (render, plugin, GPU, etc)
	// that share the same executable. This function checks the command-line and,
	// if this is a sub-process, executes the appropriate logic.
	int exit_code = CefExecuteProcess(main_args, NULL, sandbox_info);
	if (exit_code >= 0) {
	// The sub-process has completed so return here.
		return exit_code;
	}
	//
	// Specify CEF global settings here.
	CefSettings settings;
	settings.no_sandbox = true;
	//settings.multi_threaded_message_loop = true;

	// CefAppImp implements application-level callbacks for the browser process.
	// It will create the first browser instance in OnContextInitialized() after
	// CEF has initialized.
	CefRefPtr<CefAppImp> app(new CefAppImp);

	// Initialize CEF.
	CefInitialize(main_args, settings, app.get(), sandbox_info);
}


void QCefProcessExit()
{
	// Shut down CEF.
	CefShutdown();
}

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
	CefRunMessageLoop();
	//
	int qt_exit_code = qapp.exec();
	//
	QCefProcessExit();

	return qt_exit_code;
}

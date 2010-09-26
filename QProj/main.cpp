#include "qproj.h"
#include <QtGui/QApplication>

#import "Apogee.DLL" no_namespace

int main(int argc, char *argv[])
{
	// Start GUI application
	QApplication a(argc, argv);

	// Initialize COM library
	CoInitialize( NULL );

	// Create main window
	QProj w;
	w.show();

	// Display camera discover window
	w.discoverCamera();

	// Run GUI
	a.exec();

	// Uninitialize COM library
	CoUninitialize();

	return 0;
}

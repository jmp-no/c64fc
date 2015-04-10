#include <stdio.h>
#include <QDir>
#include <QStandardItem>
#include "GUI.h"
#include "ui_SIDPlay.h"

int main( int argc, char **argv ) {
	QApplication app( argc, argv );

	GUI *g = new GUI();
	g->show();
	
	return app.exec();
}





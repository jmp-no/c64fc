#include <stdio.h>
#include <QDir>
#include <QStandardItem>
#include "ui_Qt64GUI.h"
#include "qt64.h"

int main( int argc, char **argv ) {

	QApplication app( argc, argv );

	Qt64 t;
	t.IndexDirectory();
	t.show();
	
	return app.exec();
}





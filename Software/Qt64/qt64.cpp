#include <QDir>
#include <QListView>
#include <QModelIndexList>
#include <QMessageBox>
#include <QStandardItem>
#include <QProgressBar>
#include <QStatusBar>
#include <QHBoxLayout>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "qhexedit2/qhexedit.h"

#include "ui_Qt64GUI.h"
#include "qt64.h"


extern "C" {
        int OpenDevice();
        void CloseDevice();
        void Set8KMode();
        void Set16KMode();
        int Reset();
        int WriteData( unsigned short, unsigned char *, int );
        int SetAddress( unsigned short );
};


Qt64::Qt64( QMainWindow *parent ) : QMainWindow( parent ), ui(new Ui::Qt64 ) {
	ui->setupUi(this);
	im = new QStandardItemModel();

	statusBar = new QStatusBar();


/*
	QSize hint = ui->lovRightGroup->sizeHint();
	progressBar = new QProgressBar();
	progressBar->setAlignment( Qt::AlignRight );
	progressBar->setMaximumSize( hint.width(), 19 );
	statusBar->addPermanentWidget( progressBar );
	progressBar->setValue( 0 );
*/
	setStatusBar( statusBar );

	qhe = new QHexEdit();

	QWidget *wgt = ui->tabWidget->widget(1);	// Content tab
	QVBoxLayout *vBox = new QVBoxLayout;
	vBox->addWidget( qhe );
	wgt->setLayout( vBox );
	

}

void Qt64::IndexDirectory( char *dirname ) {
	QDir dir;
	if( dirname != NULL )
		dir = QDir( dirname );
	else
		dir = QDir( "ROMs" );

	if( ! dir.exists() ) {
		return;
	}

	foreach( QFileInfo item, dir.entryInfoList() ) {
		if( item.isFile() ) {
			QString s = item.fileName();
			ui->listWidget->addItem( s );
/*

			QStandardItem *i = new QStandardItem( s );
			im->appendRow( i );
			ui->listWidget->setModel( im );
*/
		}
	}
}

void Qt64::IndexDirectory() {
	IndexDirectory( NULL );
}

void Qt64::SetInfoTabData( QString title ) {
	ui->gameTitle->setText( title );
}

void Qt64::on_btnPatch_clicked() {
}

void Qt64::on_listWidget_doubleClicked( const QModelIndex &index ) {
	if( ! OpenDevice() ) {
		QString qs = index.data().toString();
		QString fullPath = "ROMs/" + qs;

		QFile file(fullPath);
		if( ! file.open( QIODevice::ReadOnly )) {
			QMessageBox::critical( this, "File open error",
				"Unable to open file for reading", QMessageBox::Ok );
		}

		QApplication::setOverrideCursor( Qt::WaitCursor );
		QByteArray blob = file.readAll();
		bool result = WriteData( 0, (unsigned char *) blob.data()+80, blob.length()-80 );
		qhe->setData(blob);
		QApplication::restoreOverrideCursor();

		if( ! result ) {
			if( blob.length()-80 > 8192 ) {
				Set16KMode();
			} else {
				Set8KMode();
			}
			Reset();
		}
		CloseDevice();

		SetInfoTabData( fullPath );

	} else {
		QMessageBox::critical( this, "USB error",
			"USB device not found", QMessageBox::Ok );
	}

}

void Qt64::on_btnRun_clicked() {
/*
	QModelIndexList sel = ui->listView->selectionModel()->selectedIndexes();
	QModelIndex index;

	char *fileName = NULL;

	foreach( index, sel ) {
		QString qs = index.data().toString();
		fileName = (char *) qs.toUtf8().constData();
	}
*/

	QString fileName = ui->listWidget->currentItem()->text();

	if( fileName.isEmpty() ) {
		QMessageBox::warning( this, "Index error",
			"Unable to determine filename selection. Please try again.", QMessageBox::Ok );
		return;
	}

	if( ! OpenDevice() ) {

		QString fullPath = "ROMs/" + QString( fileName );

		QFile file(fullPath);
		if( ! file.open( QIODevice::ReadOnly )) {
			QMessageBox::critical( this, "File open error",
				"Unable to open file for reading", QMessageBox::Ok );
		}

		QApplication::setOverrideCursor( Qt::WaitCursor );
		QByteArray blob = file.readAll();
		bool result = WriteData( 0, (unsigned char *) blob.data(), blob.length() );
		qhe->setData(blob);
		QApplication::restoreOverrideCursor();

		if( result ) Reset();
		CloseDevice();

	} else {
		QMessageBox::critical( this, "USB error",
			"USB device not found", QMessageBox::Ok );
	}

}

void Qt64::on_btnErase_clicked() {
	if( ! OpenDevice() ) {
		QApplication::setOverrideCursor( Qt::WaitCursor );
		QByteArray blob( 8192, 0 );
		WriteData( 0, (unsigned char *)blob.data(), blob.length() );
		qhe->setData(blob);
		QApplication::restoreOverrideCursor();

		//h->Reset();
		CloseDevice();

	} else {
		QMessageBox::critical( this, "USB error",
			"USB device not found", QMessageBox::Ok );
	}
}

void Qt64::on_btnReset_clicked() {
	printf( "Reset..\n" );
	if( ! OpenDevice() ) {
		printf( "Opendevice OK\n" );
		printf( "Issuing a RESET command..\n" );
		Reset();
	} else {
		printf( "Unable to open device\n" );
		QMessageBox::critical( this, "USB error",
			"USB device not found", QMessageBox::Ok );
	}
	printf( "Done.\n" );
	CloseDevice();
	progressBar->setValue( 0 );
}


#include <QFileSystemModel>
#include <QFileInfo>
#include <unistd.h>
#include "GUI.h"
#include "PSID.h"

extern "C" {
        int OpenDevice();
        void CloseDevice();
        int Reset();
        int WriteData( unsigned short, unsigned char *, int );
        int SetAddress( unsigned short );
        void Set8KMode();
        void Set16KMode();

};

GUI::GUI( QMainWindow *parent ) : QMainWindow( parent ) {
	ui = new Ui::SIDPlay();

	ui->setupUi( this );	

	InitializeDirectory( "C64Music" );

	ui->treeView->setAnimated( false );
	ui->treeView->setIndentation( 20 );
	ui->treeView->header()->setResizeMode( 0, QHeaderView::ResizeToContents );
	ui->treeView->setSortingEnabled( true );
}


void GUI::InitializeDirectory( QString path ) {
	model = new QFileSystemModel();
	model->setRootPath( path );
	model->setReadOnly( true );
	ui->treeView->setModel( model );
	ui->treeView->setRootIndex( model->index(path) );
}

void GUI::on_actionExit_activated() {
	QCoreApplication::instance()->exit();
}

void GUI::on_actionReset_activated() {
	if( ! OpenDevice() )
		Reset();
	else
		printf( "open dev err\n" );
}

void GUI::on_actionAbout_activated() {
	printf( "TODO: Add <on_actionAbout_activated>\n" );
}

void GUI::UpdateStatusBar( QString text ) {
	ui->statusbar->showMessage( text, 5000 );
}

void GUI::on_treeView_doubleClicked(const QModelIndex &index ) {
	// Check if the doubled-clicked item is a directory or a file
	//printf( "Test 1: '%s'\n", index.data().toString().toAscii().constData() );
	//printf( "Test 2: '%s'\n", model->filePath(index).toAscii().constData() );
	//printf( "TODO: Add <on_treeView_doubleClicked>\n" );
	QFileInfo fi( model->filePath(index) );
	if( fi.isDir() )
		return;
	else {
		PSID *p = new PSID();
		bool result = p->Validate( fi.absoluteFilePath() );
		if( result ) {
			printf( "PSID version %d\n", p->Version() );
			printf( "Name: %s\n", p->Name() );
			printf( "Load address $%04x\n", p->LoadAddress() );
			printf( "Init address $%04x\n", p->InitAddress() );
			printf( "Play address $%04x\n", p->PlayAddress() );
			UpdateStatusBar( QString( "Uploading \""+(QString)p->Name()+"\" to C64FC") );

			if( OpenDevice() == false ) {

				QFile file( fi.absoluteFilePath() );
				if( ! file.open( QIODevice::ReadOnly )) {
					printf( "file open err\n" );
					return;
				}
				QByteArray blob = file.readAll();
				WriteData( 0, (unsigned char *) blob.data(), blob.length() );

				unsigned char array[] = { 0xff };
				WriteData( 0x1eff, array, 1 );
				usleep( 50000 );
				array[0] = 0x64;
				WriteData( 0x1eff, array, 1 );
				CloseDevice();
			} else {
				// Unable to open device
				printf( "open dev err\n" );
			}
		} else {
			UpdateStatusBar( tr( "Not a PSID tune" ));
		}
	}
}


void GUI::on_actionRelaunch_player_activated() {
	if( OpenDevice() == false ) {
		QFile file( "c64/copyplayer.crt" );
		if( ! file.open( QIODevice::ReadOnly )) {
			printf( "blah blah file not found\n" );
			return;
		}
		QByteArray blob = file.readAll();
		WriteData( 0, (unsigned char *) blob.data(), blob.length() );
		Set8KMode();
		Reset();
		CloseDevice();
	} else {
		printf( "device not found\n" );
	}
}


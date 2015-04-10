#include <QWidget>
#include <QStandardItemModel>
#include <QFileSystemModel>
#include "ui_SIDPlay.h"

class GUI : public QMainWindow { Q_OBJECT
	public:
		GUI( QMainWindow *parent = 0 );
		virtual ~GUI() {};
	private slots:
		void on_actionExit_activated();
		void on_actionAbout_activated();
		void on_actionRelaunch_player_activated();
		void on_treeView_doubleClicked(const QModelIndex &);
	protected:
		void UpdateStatusBar( QString );
		void InitializeDirectory( QString );
		bool ValidatePSID( QString );
	private:
		QFileSystemModel *model;
		Ui::SIDPlay *ui;
};



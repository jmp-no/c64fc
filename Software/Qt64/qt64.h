#include <QWidget>
#include <QProgressBar>
#include <QStandardItemModel>
#include <QStatusBar>
#include "qhexedit2/qhexedit.h"
#include "ui_Qt64GUI.h"

namespace Ui {
	class Qt64;
}

class Qt64: public QMainWindow { Q_OBJECT
	public:
		Qt64 ( QMainWindow *parent = 0 );
		virtual ~Qt64() {};
		void IndexDirectory( char * );
		void IndexDirectory();

		QHexEdit *qhe;
	private slots:
		void on_btnRun_clicked();
		void on_btnReset_clicked();
		void on_btnPatch_clicked();
		void on_btnErase_clicked();
		void on_listWidget_doubleClicked( const QModelIndex & );
	private:
		Ui::Qt64 *ui;
		void SetInfoTabData( QString );
		QStandardItemModel *im;
		QProgressBar *progressBar;
		QStatusBar *statusBar;
};


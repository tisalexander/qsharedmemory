#ifndef MAINDIALOG_H
#define MAINDIALOG_H

#include "../sharedmemorylog/sharedmemorylog.h"
#include <QtCore/QSharedMemory>
#include <QtGui/QDialog>

namespace Ui {
	class MainDialog;
}

class MainDialog : public QDialog
{
	Q_OBJECT

public:
	explicit MainDialog(QWidget *parent = 0);
	~MainDialog();

private slots:
	void appendToSharedMemory();

private:
	Ui::MainDialog *ui;
	SharedMemoryLog m_log;
};

#endif // MAINDIALOG_H

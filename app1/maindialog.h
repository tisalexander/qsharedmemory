#ifndef MAINDIALOG_H
#define MAINDIALOG_H

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
	void saveToSharedMemory();

private:
	Ui::MainDialog *ui;
	QSharedMemory m_memory;
};

#endif // MAINDIALOG_H

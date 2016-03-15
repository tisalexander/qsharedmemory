#include "maindialog.h"
#include "ui_maindialog.h"
#include <QtCore/QBuffer>
#include <QtCore/QDebug>

MainDialog::MainDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::MainDialog),
	m_log(10, "qsharedmemory")
{
	ui->setupUi(this);

	if (!m_log.start()) {
		qDebug() << "Shared Memory Log is not started !";
	}

	connect(ui->pushButton, SIGNAL(clicked(bool)),
			qApp, SLOT(quit()));

	connect(ui->pushButtonAppend, SIGNAL(clicked(bool)),
			SLOT(appendToSharedMemory()));
}

MainDialog::~MainDialog()
{
	delete ui;
}

void MainDialog::appendToSharedMemory()
{
	m_log.append(ui->textEdit->toPlainText());
}

#include "maindialog.h"
#include "ui_maindialog.h"
#include <QtCore/QBuffer>
#include <QtCore/QDebug>

MainDialog::MainDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::MainDialog)
{
	ui->setupUi(this);

	m_log.setKey("qsharedmemory");

	connect(ui->pushButton, SIGNAL(clicked(bool)),
			qApp, SLOT(quit()));

	connect(ui->pushButton_2, SIGNAL(clicked(bool)),
			SLOT(readFromSharedMemory()));
}

MainDialog::~MainDialog()
{
	delete ui;
}

void MainDialog::readFromSharedMemory()
{
	ui->plainTextEdit->setPlainText(m_log.content());
}

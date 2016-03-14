#include "maindialog.h"
#include "ui_maindialog.h"
#include <QtCore/QBuffer>
#include <QtCore/QDebug>

MainDialog::MainDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::MainDialog)
{
	ui->setupUi(this);

	m_memory.setKey("qsharedmemory");

	if (!m_memory.attach(QSharedMemory::ReadOnly)) {
		qDebug() << "Reader. Can not attach shared memory.";
	}

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
	QBuffer buffer;
	const int size = m_memory.size();

	if (!m_memory.lock()) {
		qDebug() << "Can't lock shared memory.";
		return;
	}

	buffer.setData((const char *)m_memory.constData(), size);
	if (!buffer.open(QIODevice::ReadWrite)) {
		qDebug() << "Buffer is not opened.";
		return;
	}

	if (!m_memory.unlock()) {
		qDebug() << "Can't unlock shared memory.";
		return;
	}

	QString text = QString::fromAscii(buffer.buffer().data());
	ui->plainTextEdit->setPlainText(text);
}

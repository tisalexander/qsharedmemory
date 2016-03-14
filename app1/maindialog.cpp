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
	m_memory.create(1000000, QSharedMemory::ReadWrite);

	connect(ui->pushButton, SIGNAL(clicked(bool)),
			qApp, SLOT(quit()));

	connect(ui->pushButton_2, SIGNAL(clicked(bool)),
			SLOT(saveToSharedMemory()));
}

MainDialog::~MainDialog()
{
	delete ui;
}

void MainDialog::saveToSharedMemory()
{
	QBuffer buffer;
	if (!buffer.open(QIODevice::ReadWrite)) {
		qDebug() << "Buffer is not opened.";
	}

	QTextStream out(&buffer);
	out << ui->textEdit->toPlainText();
	out.flush();

	const int size = buffer.size();

	if (!m_memory.lock()) {
		qDebug() << "Can't lock shared memory.";
	}

	memcpy((char *)m_memory.data(), (const char *)buffer.buffer().data(), qMin(size, m_memory.size()));

	if (!m_memory.unlock()) {
		qDebug() << "Can't unlock shared memory.";
	}
}

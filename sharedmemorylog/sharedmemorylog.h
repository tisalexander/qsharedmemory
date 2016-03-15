#ifndef SHARED_MEMORY_LOG_H
#define SHARED_MEMORY_LOG_H

#include <QtCore/QBuffer>
#include <QtCore/QSharedMemory>
#include <QtCore/QString>
#include <QtCore/QTextStream>

/*------- SharedMemoryLog ---------------------------------------------------*/
class SharedMemoryLog
{
public:
	SharedMemoryLog(int size = 0, const QString &key = QString());
	~SharedMemoryLog();

	void setSize(int size);
	int size() const;

	void setKey(const QString &key);
	QString key() const;

	bool start();
	void stop();

	void append(const QString &text);

	QString content() const;

private:
	int m_size;
	QString m_key;
	mutable QSharedMemory m_memory;
	QBuffer m_buffer;
	QTextStream m_out;
};

#endif // SHARED_MEMORY_LOG_H

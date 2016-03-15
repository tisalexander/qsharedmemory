#include "sharedmemorylog.h"

/*------- SharedMemoryLog ---------------------------------------------------*/
SharedMemoryLog::SharedMemoryLog(int size, const QString &key)
{
	m_size = size;
	m_key = key;
}

SharedMemoryLog::~SharedMemoryLog()
{
}

void SharedMemoryLog::setSize(int size)
{
	m_size = size;
}

int SharedMemoryLog::size() const
{
	return m_size;
}

void SharedMemoryLog::setKey(const QString &key)
{
	m_key = key;
}

QString SharedMemoryLog::key() const
{
	return m_key;
}

bool SharedMemoryLog::start()
{
	if (m_memory.isAttached()) {
		m_memory.detach();
	}

	if (m_size <= 0 || m_key.isEmpty()) {
		return false;
	}

	m_memory.setKey(m_key);

	if (!m_memory.create(m_size)) {
		return false;
	}

	m_buffer.close();
	if (!m_buffer.open(QIODevice::ReadWrite)) {
		return false;
	}

	m_out.setDevice(&m_buffer);
	m_out.seek(0);
}

void SharedMemoryLog::stop()
{
	if (m_memory.isAttached()) {
		m_memory.detach();
	}
}

void SharedMemoryLog::append(const QString &text)
{
	if (m_out.pos() + text.size() >= m_size) {
		m_out.seek(0);
	}

	m_out << text;
	m_out.flush();

	const int bufferSize = m_buffer.size();
	const int memorySize = m_memory.size();

	const int size = qMin(m_buffer.size(), (qint64)m_memory.size());

	m_memory.lock();
	memcpy((char *)m_memory.data(), (const char *)m_buffer.buffer().data(), size);
	m_memory.unlock();
}

QString SharedMemoryLog::content() const
{
	if (!m_memory.isAttached()) {
		if (m_key.isEmpty()) {
			return "SharedMemoryLog error. Key is empty.";
		}

		m_memory.setKey(m_key);

		if (!m_memory.attach()) {
			return "SharedMemoryLog error. Can't attach.";;
		}
	}

	m_memory.lock();
	QString text = QString::fromAscii((const char *)m_memory.constData());
	m_memory.unlock();

	return text;
}

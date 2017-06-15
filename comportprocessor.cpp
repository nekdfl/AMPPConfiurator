#include "comportprocessor.h"

ComPortProcessor::ComPortProcessor()
{
    m_serialport = new QSerialPort();
    m_serialport->setBaudRate(QSerialPort::Baud9600);
}

ComPortProcessor::~ComPortProcessor()
{
    close();
}

ComPortProcessor::ComPortProcessor(QString a_comportname)
{
    m_comportname = a_comportname;
    m_serialport = new QSerialPort(m_comportname);
    m_serialport->setBaudRate(QSerialPort::Baud9600);
}

void ComPortProcessor::setComportName(QString a_comportname)
{
    m_comportname = a_comportname;
}

void ComPortProcessor::open()
{
    if (m_serialport->isOpen())
     {
         m_serialport->close();
     }
     m_serialport->open(QIODevice::ReadWrite);
}

void ComPortProcessor::close()
{
    if (m_serialport->isOpen())
        m_serialport->close();
}

void ComPortProcessor::handleBytesWritten(qint64 bytes)
{

}

void ComPortProcessor::handleBytesRead(qint64 bytes)
{

}

void ComPortProcessor::handleError(QSerialPort::SerialPortError error)
{

}

void ComPortProcessor::handleTimeout()
{

}

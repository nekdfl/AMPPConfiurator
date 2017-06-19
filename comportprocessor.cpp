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

ComPortProcessor::ComPortProcessor(const QString &a_comportname)
{

    m_serialport = new QSerialPort(a_comportname);
    m_serialport->setBaudRate(QSerialPort::Baud9600);
}

void ComPortProcessor::setComportName(const QString &a_comportname)
{

    m_serialport->setPortName(a_comportname);
}

void ComPortProcessor::open()
{
    if (m_serialport->isOpen())
        m_serialport->close();

    if (!m_serialport->open(QIODevice::ReadWrite))
        qDebug() << "Failed to open port" << m_serialport->portName() << "error: " << m_serialport->error() << endl;
    requestPresetValue();
}

void ComPortProcessor::close()
{
    if (m_serialport->isOpen())
        m_serialport->close();
}

void ComPortProcessor::requestPresetValue()
{
    QByteArray request_qbarr("r\r\n");
    write(request_qbarr);
    auto response = read();
    //    QByteArray response(Constants::getInstance().debug_fromdevice);
    parseResponse(response);
}

void ComPortProcessor::sendPresetValue(QList<QPair<QString, int>> a_vallist)
{

    auto listsize = a_vallist.size();
    qDebug() << "list size " << listsize;
    int count = 0;
    while (!a_vallist.empty())
    {
        auto val = a_vallist.front().second;
        a_vallist.pop_front();
        QByteArray data;
        QString num;
        write("w\r\n");
        read();

        data.clear();
        num = QString::number(count);
        data.append(num).append("\r\n");
        write(data);
        read();

        data.clear();
        num = QString::number(val);
        data.append(num).append("\r\n");
        write(data);
        read();

        qDebug() << "count: " << count;
        count++;
    }
}

QString ComPortProcessor::getStatus()
{
    QString message;
    Constants &constants = Constants::getInstance();
    if (m_serialport->isOpen())
    {
        message.append(constants.connected_port_msg).append(m_serialport->portName());

        message.append(constants.connected_speed_msg).append(QString::number(m_serialport->baudRate()));
    }
    else
        message.append(constants.disconnected_msg);

    return message;
}

void ComPortProcessor::write(const QByteArray &writeData)
{
    qint64 bytesWritten = m_serialport->write(writeData);

    if (bytesWritten == -1)
    {
        qDebug() << "Failed to write the data to port" << m_serialport->portName() << "error: " << m_serialport->error() << endl;
    }
    else if (bytesWritten != writeData.size())
    {
        qDebug() << "Failed to write the all data to port" << m_serialport->portName() << "error: " << m_serialport->error() << endl;
        ;
    }
    else if (!m_serialport->waitForBytesWritten(500))
    {
        qDebug() << "Operation timed out or an error occurred for port " << m_serialport->portName() << "error: " << m_serialport->error() << endl;
    }
    else
        emit dataTransfered(writeData);
}

QByteArray ComPortProcessor::read()
{
    QByteArray readData = m_serialport->readAll();
    while (m_serialport->waitForReadyRead(500))
        readData.append(m_serialport->readAll());

    if (m_serialport->error() == QSerialPort::ReadError)
    {
        qDebug() << "Failed to read from port" << m_serialport->portName() << "error: " << m_serialport->errorString() << endl;
    }
    else if (m_serialport->error() == QSerialPort::TimeoutError && readData.isEmpty())
    {
        qDebug() << "No data was currently available for reading from port " << m_serialport->portName() << endl;
    }
    else
        emit dataRecived(readData);

    return readData;
}

void ComPortProcessor::parseResponse(const QByteArray &a_recievbuff)
{
    Constants &constants = Constants::getInstance();
    QList<QPair<QString, int>> vallist;

    auto stringlist = a_recievbuff.split('\r').toVector();
    //read only 3d string with values(start from 0)
    auto str = stringlist[2];
    QVector<QByteArray> values = str.split('|').toVector();

    vallist.push_back(QPair<QString, int>(constants.cooloff_name, std::atoi(values[0].data())));
    vallist.push_back(QPair<QString, int>(constants.cool35_name, std::atoi(values[1].data())));
    vallist.push_back(QPair<QString, int>(constants.cool50_name, std::atoi(values[2].data())));
    vallist.push_back(QPair<QString, int>(constants.cool70_name, std::atoi(values[3].data())));
    vallist.push_back(QPair<QString, int>(constants.cool90_name, std::atoi(values[4].data())));
    vallist.push_back(QPair<QString, int>(constants.cool100_name, std::atoi(values[5].data())));
    vallist.push_back(QPair<QString, int>(constants.alarmon_name, std::atoi(values[6].data())));
    vallist.push_back(QPair<QString, int>(constants.alarmoff_name, std::atoi(values[7].data())));
    vallist.push_back(QPair<QString, int>(constants.poweroff_name, std::atoi(values[8].data())));

    emit presetValueReady(vallist);
}

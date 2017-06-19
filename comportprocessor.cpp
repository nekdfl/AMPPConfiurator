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
    {
        Constants &constants = Constants::getInstance();
        QString msg;
        msg.append(constants.failtoopenport_error).append(m_serialport->portName()).append(constants.witherror_error).append(m_serialport->errorString());
        std::runtime_error ex(std::string(msg.toLocal8Bit()));

        qDebug() << constants.failtoopenport_error << m_serialport->portName() << constants.witherror_error << m_serialport->errorString() << endl;
        throw ex;
    }
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
    QByteArray data;
    while (!a_vallist.empty())
    {
        data.clear();
        auto val = a_vallist.front().second;
        a_vallist.pop_front();
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
    Constants &constants = Constants::getInstance();
    qint64 bytesWritten = m_serialport->write(writeData);

    if (bytesWritten == -1)
    {
        QString msg;
        msg.append(constants.cant_write_error).append(m_serialport->portName()).append(constants.witherror_error).append(m_serialport->errorString());
        std::runtime_error ex(std::string(msg.toLocal8Bit()));

        qDebug() << constants.cant_write_error << m_serialport->portName() << constants.witherror_error << m_serialport->errorString() << endl;
        throw ex;
    }
    else if (bytesWritten != writeData.size())
    {
        QString msg;
        msg.append(constants.cantwrite_all_error).append(m_serialport->portName()).append(constants.witherror_error).append(m_serialport->errorString());
        std::runtime_error ex(std::string(msg.toLocal8Bit()));

        qDebug() << constants.cantwrite_all_error << m_serialport->portName() << constants.witherror_error << m_serialport->errorString() << endl;
        throw ex;
    }
    else if (!m_serialport->waitForBytesWritten(500))
    {
        QString msg;
        msg.append(constants.operationtimeout_error).append(m_serialport->portName()).append(constants.witherror_error).append(m_serialport->errorString());
        std::runtime_error ex(std::string(msg.toLocal8Bit()));

        qDebug() << constants.operationtimeout_error << m_serialport->portName() << constants.witherror_error << m_serialport->errorString() << endl;
        throw ex;
    }
    else
        emit dataTransfered(writeData);
}

QByteArray ComPortProcessor::read()
{
    Constants &constants = Constants::getInstance();
    QByteArray readData = m_serialport->readAll();

    while (m_serialport->waitForReadyRead(500))
        readData.append(m_serialport->readAll());

    if (m_serialport->error() == QSerialPort::ReadError)
    {
        QString msg;
        msg.append(constants.cantread_error).append(m_serialport->portName()).append(constants.witherror_error).append(m_serialport->errorString());
        std::runtime_error ex(std::string(msg.toLocal8Bit()));

        qDebug() << constants.cantread_error << m_serialport->portName() << constants.witherror_error << m_serialport->errorString() << endl;
        throw ex;
    }
    else if (m_serialport->error() == QSerialPort::TimeoutError && readData.isEmpty())
    {
        QString msg;
        msg.append(constants.nodatatoread_error).append(m_serialport->portName()).append(constants.witherror_error).append(m_serialport->errorString());
        std::runtime_error ex(std::string(msg.toLocal8Bit()));

        qDebug() << constants.nodatatoread_error << m_serialport->portName() << endl;
        throw ex;
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

    vallist.push_back(QPair<QString, int>(constants.cooloff_key, std::atoi(values[0].data())));
    vallist.push_back(QPair<QString, int>(constants.cool35_key, std::atoi(values[1].data())));
    vallist.push_back(QPair<QString, int>(constants.cool50_ley, std::atoi(values[2].data())));
    vallist.push_back(QPair<QString, int>(constants.cool70_key, std::atoi(values[3].data())));
    vallist.push_back(QPair<QString, int>(constants.cool90_key, std::atoi(values[4].data())));
    vallist.push_back(QPair<QString, int>(constants.cool100_key, std::atoi(values[5].data())));
    vallist.push_back(QPair<QString, int>(constants.alarmon_key, std::atoi(values[6].data())));
    vallist.push_back(QPair<QString, int>(constants.alarmoff_key, std::atoi(values[7].data())));
    vallist.push_back(QPair<QString, int>(constants.poweroff_key, std::atoi(values[8].data())));

    emit presetValueReady(vallist);
}

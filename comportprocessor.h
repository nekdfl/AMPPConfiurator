#ifndef COMPORTPROCESSOR_H
#define COMPORTPROCESSOR_H

#include <QObject>
#include <QPointer>
#include <QSerialPort>
#include <QString>
#include <QQueue>
#include <QTimer>

class ComPortProcessor: public QObject
{
    Q_OBJECT
public:
    explicit ComPortProcessor();
    ~ComPortProcessor();
    ComPortProcessor(QString a_comportname);
    void setComportName(QString a_comportname);
    void open();
    void close();
    void requestPresetValue();
    void sendPresetValue();

protected:
    QByteArray m_writedata;
    QByteArray m_readdata;
    qint64 m_byteswritten;
    QPointer<QSerialPort> m_serialport;
    QTimer m_pingpongtimer;
    QString m_comportname;

protected:
    void onRead();

private:
    void write(const QByteArray &writeData);

signals:
    void dataRecived(QByteArray a_recievbuff );
    void dataTransfered(QByteArray a_transfbuff);
    void presetValueReady(const QList<QPair<QString, int>> &a_vallist);

 private slots:
    void handleBytesWritten(qint64 bytes);
    void handleBytesRead(qint64 bytes);
    void handleTimeout();
    void handleError(QSerialPort::SerialPortError error);

};

#endif // COMPORTPROCESSOR_H

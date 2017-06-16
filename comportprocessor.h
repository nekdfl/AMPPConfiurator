#ifndef COMPORTPROCESSOR_H
#define COMPORTPROCESSOR_H

#include <QObject>
#include <QPointer>
#include <QSerialPort>
#include <QString>
#include <QQueue>
#include <QTimer>
#include <QThread>
#include <QDebug>

#include "constants.h"

class ComPortProcessor: public QObject
{
    Q_OBJECT
public:
    explicit ComPortProcessor();
    ~ComPortProcessor();
    ComPortProcessor(const QString &a_comportname);
    void setComportName(const QString & a_comportname);
    void open();
    void close();
    void requestPresetValue();
    void sendPresetValue(QList<QPair<QString, int>> a_vallist);
    QString getStatus();

protected:
    QByteArray m_writedata;
    QByteArray m_readdata;
    qint64 m_byteswritten;
    QPointer<QSerialPort> m_serialport;
    QTimer m_pingpongtimer;

private:
    void write(const QByteArray &writeData);
    QByteArray read();
    void parseResponse(const QByteArray& a_recievbuff);

signals:
    void dataRecived(QByteArray a_recievbuff );
    void dataTransfered(QByteArray a_transfbuff);
    void presetValueReady(const QList<QPair<QString, int>> &a_vallist);

private slots:


};

#endif // COMPORTPROCESSOR_H

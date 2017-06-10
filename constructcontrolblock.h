#ifndef CONSTRUCTCONTROLBLOCK_H
#define CONSTRUCTCONTROLBLOCK_H

#include <QObject>
#include <QString>

class ConstructControlBlock
{

public:
    ConstructControlBlock(const QString &a_name, const QString &a_label, const int &a_mint, const int &a_maxt, const int &a_deft):
    m_name(a_name),
    m_label(a_label),
    m_mintemp_qi8(a_mint),
    m_maxtemp_qi8(a_maxt),
    m_deftemp_qi8(a_deft)
    {

    }

    int getMaxTemperature() const
    {return m_maxtemp_qi8;}

    int getMintemperature() const
    {return m_mintemp_qi8;}

    int getDefTemperature() const
    {return m_deftemp_qi8;}

    QString getName() const
    {return m_name;}

    QString getLabel() const
    {return m_label;}

private:
    QString m_name;
    QString m_label;
    int m_mintemp_qi8;
    int m_maxtemp_qi8;
    int m_deftemp_qi8;



};

#endif // CONSTRUCTCONTROLBLOCK_H

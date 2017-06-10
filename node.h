#ifndef NODE_H
#define NODE_H

#include <QString>

class Node
{
public:
    Node()
    {

        m_val=0;
    }

    Node(const QString &a_name, const int a_val )
    {
        m_name=a_name;
        m_val=a_val;
    }

    Node(const Node &anode):
        m_name(anode.m_name),
        m_val(anode.m_val)
    {

    }

    ~Node()
    {


    }

    void setVal(const int &a_val)
    {
        m_val=a_val;
    }

    int getVal()
    {
        return m_val;
    }

    void setName(QString &a_name)
    {
        m_name=a_name;
    }

    QString getName() const
    {
        return m_name;
    }

protected:
    QString m_name;
    int m_val;

};

#endif // NODE_H

#ifndef BINARYNODE_H
#define BINARYNODE_H

#include <QObject>
#include <QString>
#include <QPointer>
#include <QSharedPointer>



class BinaryNode
{
public:
    BinaryNode()
    {
        m_name="";
        m_val=0;
    }

    BinaryNode(const QString &a_name, const int a_val )
    {
        m_name=a_name;
        m_val=a_val;
    }

    BinaryNode(const QString &a_name, const int a_val, const QSharedPointer <BinaryNode> a_left)
    {
        m_name=a_name;
        m_val=a_val;
        m_left=a_left;
    }

    BinaryNode(const BinaryNode &anode):
        m_name(anode.m_name),
        m_val(anode.m_val),
        m_left(anode.m_left),
        m_right(anode.m_right)
    {

    }

    ~BinaryNode()
    {
        m_left.clear();
        m_right.clear();

    }

    void setLeftNode(QSharedPointer <BinaryNode> a_node)
    {
        m_left=a_node;
    }

    QSharedPointer <BinaryNode> getLeft()
    {
        return m_left;
    }

    bool hasLeftNode()
    {
        return m_left.isNull();
    }

    void setRightNode(QSharedPointer <BinaryNode> a_node)
    {
        m_right=a_node;
    }

    QSharedPointer <BinaryNode> getRight()
    {
        return m_right;
    }

    void addBinaryNode(QSharedPointer <BinaryNode> a_right )
    {
        m_right=a_right;
    }

    bool hasRightNode()
    {
        return m_right.isNull();
    }

    void setVal(const int &a_val)
    {
        m_val=a_val;
    }

    int getVal()
    {
        return m_val;
    }

    void updateVal(const int &a_val)
    {
        m_val=a_val;

    }

    QString getName()
    {
        return m_name;
    }

protected:
    QString m_name;
    int m_val;
    QSharedPointer <BinaryNode> m_left;
    QSharedPointer <BinaryNode> m_right;


};

#endif // BINARYNODE_H

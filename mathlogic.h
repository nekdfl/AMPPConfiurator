#ifndef MATHLOGIC_H
#define MATHLOGIC_H

#include <QObject>
#include <QPair>
#include <QList>
#include <QMap>
#include <QString>
#include <algorithm>

#include <QDebug>

#include "node.h"

class MathLogic : public QObject
{
    Q_OBJECT
private:
    typedef QList <Node> NodeList_t;
    typedef QMap <QString, Node> ExtraNodeMap_t;
    const char* cooloff="cooloff";
    const char* alarmoff="alarmoff";
    const char* alarmon="alarmon";
    const char* poweroff="poweroff";
    const char* cool70="cool70";
    const char* cool90="cool90";
    const char* cool100="cool100";
public:
    explicit MathLogic(const int &a_min, const int &a_max);
    ~MathLogic();

    void addVal(const QString &a_name, const int &a_val);
    void addExtraVal(const QString &a_name, const int &a_val);

protected:
    NodeList_t m_bintree_lst;
    ExtraNodeMap_t m_extraval_map;

    const int m_min;
    const int m_max;
private:
    void updateBintree(const QString &a_name, const int &a_val);
    inline void recalcLeft(const NodeList_t::iterator &res_it);
    inline void recalcRight(NodeList_t::iterator res_it);
    int checkMaxMin(const int &a_val);

    void recalcExtraVal();
    void recalcAlarmOff();
    void recalcAlarmON();
    void recalcPowerOff();

    void updateAlarmOff_node(const int &a_val);
    void updateAlarmON_node(const int &a_val);
    void updatePowerOff_node(const int &a_val);

    QList<QPair<QString, int>> getPairListFromBtree();
    void send_signal();

signals:
    void presetValueReady(const QList<QPair<QString, int> > &a_vallist);
    void extraValueReady(const ExtraNodeMap_t &a_vallist);

public slots:
    void onDialMoved(const QString &a_name, const int &a_val)
    {
//        qWarning() << " ";
//        qDebug() << "moved: " << a_name << ": " <<a_val;

        if (a_name == alarmoff)
        {
            updateAlarmOff_node(a_val);
            send_signal();
        }else if (a_name == alarmon)
        {
            updateAlarmON_node(a_val);
            send_signal();
        }else if (a_name == poweroff)
        {
            updatePowerOff_node(a_val);
            send_signal();
        }
        else
        {
            updateBintree(a_name, a_val);

            recalcExtraVal();

            send_signal();
        }





    }
};


























































//class MathLogic : public QObject
//{
//    Q_OBJECT
//private:
//    typedef QList <QPair <QString, int>> ValueList_t;
//public:
//    explicit MathLogic()
//    {
//        m_bintree.clear();
//    }

//    ~MathLogic()
//    {
//        m_bintree.clear();
//    }

//    void addVal(const QString &a_name, const int &a_val)
//    {
//        if (m_bintree.isNull())
//        {
//            qDebug() << "create root node";
//            m_bintree =  QSharedPointer <BinaryNode>::create(a_name, a_val);
//        }
//        else
//        {
//            auto vcurrentnode = m_bintree;
//            while (!vcurrentnode->getRight().isNull())
//            {
//                vcurrentnode=vcurrentnode->getRight();
//            }

//            qDebug() << "add " << a_name << ": " << a_val << "; to " << vcurrentnode->getName();
//            QSharedPointer<BinaryNode> vnode = QSharedPointer<BinaryNode>::create(a_name, a_val, vcurrentnode);
//            vcurrentnode->addBinaryNode(vnode);
//        }
//    }

//    void addExtraVal(const QString &a_name, const int &a_val)
//    {
//        auto ptr =  QSharedPointer <BinaryNode>::create(a_name, a_val);
//        m_extbintree_lst.push_back(ptr);
//    }

//protected:
////    QSharedPointer <BinaryNode> m_bintree;
//    QList< QSharedPointer <BinaryNode>> m_bintree_lst;
//    QList< QSharedPointer <BinaryNode>> m_extbintree_lst;

//private:
//    inline QSharedPointer <BinaryNode> updateBintree(const QString &a_name, const int &a_val)
//    {
//        auto vcurrentnode = m_bintree;
//        if (!vcurrentnode.isNull())
//        {
//            while (vcurrentnode->getName() != a_name)
//            {
//                vcurrentnode=vcurrentnode->getRight();
//            }
//            vcurrentnode->updateVal(a_val);
//        }

//        return vcurrentnode;
//    }

//    inline void recalcRight(QSharedPointer<BinaryNode> vcurrentnode)
//    {
//        if (!vcurrentnode.isNull())
//        {
//            while (!vcurrentnode->getRight().isNull())
//            {
//                const auto &right= vcurrentnode->getRight();
//                if (vcurrentnode->getVal() > right->getVal() )
//                {
//                    right->setVal(vcurrentnode->getVal());
//                    qDebug() << "update " << right->getName() << ": " << right->getVal();
//                }

//                vcurrentnode=vcurrentnode->getRight();
//            }
//        }
//    }

//    inline void recalcLeft( QSharedPointer<BinaryNode> vcurrentnode)
//    {
//        if (!vcurrentnode.isNull())
//        {
//            while (!vcurrentnode->getLeft().isNull())
//            {
//                const auto &left= vcurrentnode->getLeft();
//                if (vcurrentnode->getVal() < left->getVal() )
//                {
//                    left->setVal(vcurrentnode->getVal());
//                }

//                vcurrentnode=vcurrentnode->getLeft();
//            }
//        }
//    }

//    inline void calcExtraBTree()
//    {
//        for (auto &it : m_extbintree_lst)
//        {
//            if (it->getName() == "" )
//            {

//            }
//        }
//    }

//    inline QList<QPair<QString, int> > getPairListFromBtree()
//    {
//        QList<QPair<QString, int> > vpairlist;
//        auto vcurrentnode = m_bintree;
//        while (!vcurrentnode->getRight().isNull())
//        {
//            vpairlist.push_back(QPair<QString, int>(vcurrentnode->getName(), vcurrentnode->getVal()));
//            vcurrentnode=vcurrentnode->getRight();
//        }

//        vpairlist.push_back(QPair<QString, int>(vcurrentnode->getName(), vcurrentnode->getVal()));

//        return vpairlist;
//    }

//signals:
//    void previewValueReady(const QList<QPair<QString, int> > &a_vallist);

//public slots:
//    void onDialMoved(const QString &a_name, const int &a_val)
//    {
//        qDebug() << "moved: " << a_name << ": " <<a_val;

//        auto triggednode = updateBintree(a_name, a_val);

//        if (!triggednode.isNull())
//        {
//            recalcLeft(triggednode);
//            recalcRight(triggednode);

//            emit previewValueReady(getPairListFromBtree());
//        }
//    }
//};

#endif // MATHLOGIC_H

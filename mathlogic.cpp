#include "mathlogic.h"

MathLogic::MathLogic(const int &a_min, const int &a_max)
    : m_min(a_min), m_max(a_max)
{
}

MathLogic::~MathLogic()
{
    m_bintree_lst.clear();
}

void MathLogic::addVal(const QString &a_name, const int &a_val)
{
    m_bintree_lst.push_back(Node(a_name, a_val));
}

void MathLogic::addExtraVal(const QString &a_name, const int &a_val)
{
    auto node = Node(a_name, a_val);
    m_extraval_map.insert(a_name, node);
}

void MathLogic::updateBintree(const QString &a_name, const int &a_val)
{
    qWarning() << "==============================================";
    qWarning() << "update: " << a_name << " " << a_val;
    const NodeList_t::iterator &res_it = std::find_if(m_bintree_lst.begin(), m_bintree_lst.end(), [this, &a_name](const Node &vnode) {
        return vnode.getName() == a_name;
    });

    if (res_it != m_bintree_lst.end())
    {
        res_it->setVal(a_val);
        recalcLeft(res_it);
        recalcRight(res_it);
    }
}

int MathLogic::checkMaxMin(const int &a_val)
{
    if (a_val > m_max)
        return m_max;

    if (a_val < m_min)
        return m_min;

    return a_val;
}

void MathLogic::recalcLeft(const NodeList_t::iterator &res_it)
{
    auto it = res_it - 1;
    while (it >= m_bintree_lst.begin())
    {
        //            qDebug() << "update: " << it->getName() << ": " << it->getVal();
        const auto &next_val = it + 1;
        if (it->getVal() > next_val->getVal())
        {
            //                qDebug() << it->getVal() <<  " < "  << next_val->getVal();
            it->setVal(next_val->getVal());
        }
        it--;
    }
}

void MathLogic::recalcRight(NodeList_t::iterator res_it)
{
    auto it = res_it + 1;
    while (it != m_bintree_lst.end())
    {
        //        qDebug() << "update: " << it->getName() << ": " << it->getVal();
        const auto &prev_val = it - 1;
        if (it->getVal() < prev_val->getVal())
        {
            //                qDebug() << it->getVal() <<  " < "  << next_val->getVal();
            it->setVal(prev_val->getVal());
        }
        it++;
    }
}

QList<QPair<QString, int>> MathLogic::getPairListFromBtree()
{
    QList<QPair<QString, int>> vpairlist;
    qDebug() << "NEW VALUE TABLE";

    for (auto &it : m_bintree_lst)
    {
        qDebug() << "new val " << it.getName() << " : " << it.getVal();
        auto p = QPair<QString, int>(it.getName(), it.getVal());
        vpairlist.push_back(p);
    }

    auto al_off = QPair<QString, int>(m_extraval_map[alarmoff].getName(), m_extraval_map[alarmoff].getVal());
    auto al_on = QPair<QString, int>(m_extraval_map[alarmon].getName(), m_extraval_map[alarmon].getVal());
    auto pow_off = QPair<QString, int>(m_extraval_map[poweroff].getName(), m_extraval_map[poweroff].getVal());

    vpairlist.push_back(al_off);
    vpairlist.push_back(al_on);
    vpairlist.push_back(pow_off);

    qDebug() << "new val " << m_extraval_map[alarmoff].getName() << " : " << m_extraval_map[alarmoff].getVal();
    qDebug() << "new val " << m_extraval_map[alarmon].getName() << " : " << m_extraval_map[alarmon].getVal();
    qDebug() << "new val " << m_extraval_map[poweroff].getName() << " : " << m_extraval_map[poweroff].getVal();

    qDebug() << "-----------------------------------------------------\n\n";

    return vpairlist;
}

void MathLogic::send_signal()
{
    auto p_list = getPairListFromBtree();
    emit presetValueReady(p_list);
}

void MathLogic::recalcExtraVal()
{
    recalcPowerOff();
    recalcAlarmON();
    recalcAlarmOff();
}

void MathLogic::recalcAlarmOff()
{
    auto v_cooloff_it = std::find_if(
        m_bintree_lst.begin(), m_bintree_lst.end(), [this](Node &vnode) { return vnode.getName() == cooloff; });

    if (v_cooloff_it != m_bintree_lst.end())
    {
        const int &cooloffval = v_cooloff_it->getVal();
        if (cooloffval > m_extraval_map[alarmoff].getVal())
        {
            m_extraval_map[alarmoff].setVal(cooloffval);
        }
    }

    auto v_cool100_it = std::find_if(
        m_bintree_lst.begin(), m_bintree_lst.end(), [this](Node &vnode) { return vnode.getName() == cool100; });

    if (v_cool100_it != m_bintree_lst.end())
    {
        const int &cool100val = v_cool100_it->getVal();
        if (cool100val < m_extraval_map[alarmoff].getVal())
        {
            m_extraval_map[alarmoff].setVal(cool100val);
        }
    }
}

void MathLogic::recalcAlarmON()
{
    if (m_extraval_map[alarmoff].getVal() > m_extraval_map[alarmon].getVal())
        m_extraval_map[alarmon].setVal(m_extraval_map[alarmoff].getVal());
}

void MathLogic::recalcPowerOff()
{
    auto v_cool100_it = std::find_if(
        m_bintree_lst.begin(), m_bintree_lst.end(), [this](Node &vnode) { return vnode.getName() == cool100; });

    if (v_cool100_it != m_bintree_lst.end())
    {
        const int &cool100val = v_cool100_it->getVal();
        if (cool100val > m_extraval_map[poweroff].getVal())
            m_extraval_map[poweroff].setVal(cool100val);
    }

    //    auto v_cooloff_it = std::find_if(m_bintree_lst.begin(), m_bintree_lst.end(), [this](Node &vnode)
    //     {
    //        return vnode.getName() == cooloff;
    //    });

    //    if (v_cooloff_it != m_bintree_lst.end())
    //    {
    //        const int &cooloffval=v_cooloff_it->getVal();
    //        if (cooloffval > m_extraval_map[poweroff].getVal()  )
    //            m_extraval_map[poweroff].setVal(cooloffval);
    //    }
}

void MathLogic::updateAlarmOff_node(const int &a_val)
{
    m_extraval_map[alarmoff].setVal(a_val);

    auto v_cooloff_it = std::find_if(
        m_bintree_lst.begin(), m_bintree_lst.end(), [this](Node &vnode) { return vnode.getName() == cooloff; });

    if (v_cooloff_it != m_bintree_lst.end())
    {
        const int &cooloffval = v_cooloff_it->getVal();
        if (cooloffval > m_extraval_map[alarmoff].getVal())
        {
            updateBintree(cooloff, a_val);
        }
    }

    if (m_extraval_map[alarmoff].getVal() > m_extraval_map[alarmon].getVal())
        updateAlarmON_node(m_extraval_map[alarmoff].getVal());

    //    if (m_extraval_map[alarmon].getVal() > m_extraval_map[poweroff].getVal())
    //        m_extraval_map[poweroff].setVal(checkMaxMin(m_extraval_map[alarmon].getVal()+1));
}

void MathLogic::updateAlarmON_node(const int &a_val)
{
    m_extraval_map[alarmon].setVal(a_val);

    if (m_extraval_map[alarmon].getVal() < m_extraval_map[alarmoff].getVal())
        updateAlarmOff_node(m_extraval_map[alarmon].getVal());

    if (m_extraval_map[alarmon].getVal() > m_extraval_map[poweroff].getVal())
        updatePowerOff_node(m_extraval_map[alarmon].getVal());
}

void MathLogic::updatePowerOff_node(const int &a_val)
{
    m_extraval_map[poweroff].setVal(a_val);

    auto v_cool100_it = std::find_if(
        m_bintree_lst.begin(), m_bintree_lst.end(), [this](Node &vnode) { return vnode.getName() == cool100; });

    if (v_cool100_it != m_bintree_lst.end())
    {
        const int &cool100val = v_cool100_it->getVal();
        if (m_extraval_map[poweroff].getVal() < cool100val)
        {
            updateBintree(cool100, a_val);
        }
    }

    if (m_extraval_map[alarmon].getVal() > m_extraval_map[poweroff].getVal())
        updateAlarmON_node(m_extraval_map[poweroff].getVal());
}

#include "cpanel.h"

CPanel::CPanel(const QList<ConstructControlBlock> &controlBlockElements,
               const int &a_min, const int &a_max, QWidget *parent)
    : QWidget(parent),
      m_controlBlockElements(controlBlockElements),
      m_constants(Constants::getInstance())
{

    this->setMaximumHeight(m_constants.maxwindowheight);
    m_hbox_qptr = new QHBoxLayout(this);
    loadSettings(a_min, a_max);

    setLayout(m_hbox_qptr);
    setStyleSheet("QWidget {background: 'black'; background-color:'black';  "
                  "color: 'white'}");

    connectMathLogicToControlBlocks();
    connectControlBlocksToMathLogic();
}

MathLogic *CPanel::getMathLogicInstance()
{
    return m_mathlogic_qptr.data();
}

void CPanel::loadSettings(const int &a_min, const int &a_max)
{
    m_mathlogic_qptr = new MathLogic(a_min, a_max);
    for (auto &it : m_controlBlockElements)
    {
        auto ptr = new ControlBlock(this, it.getName(), it.getLabel(),
                                    it.getMintemperature(), it.getMaxTemperature(),
                                    it.getDefTemperature());
        m_controlblock_map.insert(it.getName(), ptr);
        m_hbox_qptr->addWidget(m_controlblock_map[it.getName()]);

        addToMathLogic(it);
    }
}

void CPanel::reloadSettings(const QList<ConstructControlBlock> &controlBlockElements)
{
    m_mathlogic_qptr->clear();
    for (auto &it : controlBlockElements)
    {
        addToMathLogic(it);
    }
    updateControlBlocks();
}

void CPanel::setPresetValue(const QList<QPair<QString, int>> &a_vallist)
{
    for (auto &it : a_vallist)
    {
        qDebug() << "set preset " << it.first << " : " << it.second;
        m_mathlogic_qptr->onDialMoved(it.first, it.second);
        //        m_controlblock_map[it.first]->onValueChange(it.second);
        m_controlblock_map[it.first]->onValueChanged();
    }
}

void CPanel::updateControlBlocks()
{
    m_mathlogic_qptr->sendValueToLCD();
    for (auto &it : m_controlblock_map)
    {
        it->onValueChanged();
    }
}

void CPanel::connectControlBlocksToMathLogic()
{
    for (auto &it : m_controlblock_map)
    {
        connect(it, &ControlBlock::ValueChanging, m_mathlogic_qptr,
                &MathLogic::onDialMoved);
        connect(it, &ControlBlock::ValueChanged, [this]() {
            for (auto &it : m_controlblock_map)
            {
                it->onValueChanged();
            }
        });
    }
}

void CPanel::connectMathLogicToControlBlocks()
{
    connect(m_mathlogic_qptr, &MathLogic::presetValueReady,
            [this](auto &a_vallist) {
                for (auto &val : a_vallist)
                {
                    m_controlblock_map[val.first]->onValueChange(val.second);
                }

            });
}

void CPanel::addToMathLogic(auto &it)
{
    if (it.getName() == m_constants.alarmoff_key ||
        it.getName() == m_constants.alarmon_key ||
        it.getName() == m_constants.poweroff_key)
        m_mathlogic_qptr->addExtraVal(it.getName(), it.getDefTemperature());
    else
        m_mathlogic_qptr->addVal(it.getName(), it.getDefTemperature());
}

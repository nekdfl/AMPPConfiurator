#include "cpanel.h"

CPanel::CPanel(const QList<ConstructControlBlock> &controlBlockElements,
               const int &a_min, const int &a_max, QWidget *parent)
    : QWidget(parent), m_constants(Constants::getInstance())
{
    m_mathlogic_qptr = new MathLogic(a_min, a_max);
    m_hbox_qptr = new QHBoxLayout(this);
    for (auto &it : controlBlockElements)
    {
        auto ptr = new ControlBlock(this, it.getName(), it.getLabel(),
                                    it.getMintemperature(), it.getMaxTemperature(),
                                    it.getDefTemperature());
        m_controlblock_map.insert(it.getName(), ptr);
        m_hbox_qptr->addWidget(m_controlblock_map[it.getName()]);

        addToMathLogic(it);
    }

    setLayout(m_hbox_qptr);
    setStyleSheet("QWidget {background: 'black'; background-color:'black';  "
                  "color: 'white'}");

    connectMathLogicToControlBlocks();
    connectControlBlocksToMathLogic();
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
    if (it.getName() == m_constants.alarmoff_name ||
        it.getName() == m_constants.alarmon_name ||
        it.getName() == m_constants.poweroff_name)
        m_mathlogic_qptr->addExtraVal(it.getName(), it.getDefTemperature());
    else
        m_mathlogic_qptr->addVal(it.getName(), it.getDefTemperature());
}

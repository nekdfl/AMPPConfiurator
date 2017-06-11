#include "controlblock.h"

ControlBlock::ControlBlock(QWidget *parent, const QString &a_name,
                           const QString &a_label, const int &a_min,
                           const int &a_max, int a_val)
    : QWidget(parent)
{
    m_name = a_name;
    createGUI(this, a_label);
    updateLimits(a_min, a_max);

    connect(m_dial_qptr, SIGNAL(valueChanged(int)), m_lcd_qtr,
            SLOT(display(int)));
    connect(m_dial_qptr, &QDial::sliderMoved,
            [this](int a_val) { emit ValueChanging(m_name, a_val); });

    connect(m_dial_qptr, &QDial::sliderReleased,
            [this]() { emit ValueChanged(); });

    connect(m_dial_qptr, &QDial::valueChanged, [this](int a_val) {
        emit ValueChanging(m_name, a_val);
        emit ValueChanged();
    });

    m_dial_qptr->setValue(a_val);
}

void ControlBlock::createGUI(QWidget *parent, const QString &a_label)
{
    m_layout_qptr = new QVBoxLayout(parent);
    m_dial_qptr = new QDial();
    m_label_qptr = new QLabel(a_label);
    m_lcd_qtr = new QLCDNumber();

    m_layout_qptr->addWidget(m_lcd_qtr);
    m_layout_qptr->addWidget(m_dial_qptr);
    m_layout_qptr->addWidget(m_label_qptr);

    m_label_qptr->setStyleSheet(
        "QLabel {background: 'lightgrey'; color: 'black'}");
    m_label_qptr->setAlignment(Qt::AlignCenter);

    m_lcd_qtr->setStyleSheet("QLCDNumber {background: 'black'; color: '#FF0C0C'; "
                             "selection-background-color: 'red'; "
                             "selection-background-color: 'red'}");
    m_lcd_qtr->setDigitCount(3);

    m_dial_qptr->setStyleSheet("QDial {background: 'white'; color: 'white'; "
                               "selection-background-color: 'red'; "
                               "selection-background-color: 'red'}; ");
    m_dial_qptr->setNotchTarget(5);
    m_dial_qptr->setNotchesVisible(true);
}

void ControlBlock::updateLimits(const int &a_min, const int &a_max)
{
    m_dial_qptr->setMinimum(a_min);
    m_dial_qptr->setMaximum(a_max);
}

void ControlBlock::onValueChange(const int &a_val)
{
    if (a_val > m_lcd_qtr->value())
    {
        m_lcd_qtr->display(a_val);
    }
    else if (a_val < m_lcd_qtr->value())
    {
        m_lcd_qtr->display(a_val);
    }

    m_lcd_qtr->repaint();
}

void ControlBlock::onValueChanged()
{
    m_dial_qptr->setValue(m_lcd_qtr->value());
}

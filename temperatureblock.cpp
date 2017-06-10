#include "temperatureblock.h"

TemperatureBlock::TemperatureBlock(const QString &a_name,
                                   const QString &a_label, const int &a_min,
                                   const int &a_max, int a_val)

{
  m_name = a_name;
  createGUI(a_label);
  updateLimits(a_min, a_max);

  connect(m_spinbox_qptr, SIGNAL(valueChanged(int)), this,
          SLOT(sendSignals(int)));

  m_val = a_val;
  m_spinbox_qptr->setValue(a_val);
}

void TemperatureBlock::createGUI(const QString &a_label) {
  m_hbox_qptr = new QHBoxLayout();
  m_label_qptr = new QLabel(a_label);
  m_spinbox_qptr = new QSpinBox();

  m_hbox_qptr->addWidget(m_label_qptr);
  m_hbox_qptr->addWidget(m_spinbox_qptr);

  this->setLayout(m_hbox_qptr);
}

void TemperatureBlock::updateLimits(const int &a_min, const int &a_max) {
  m_spinbox_qptr->setMaximum(a_min);
  m_spinbox_qptr->setMaximum(a_max);
}

void TemperatureBlock::sendSignals(int a_val) {
  emit ValueChanging(m_name, a_val);
  emit ValueChanged();
}

void TemperatureBlock::onValueChange(const int &a_val) { m_val = a_val; }

void TemperatureBlock::onValueChanged() { m_spinbox_qptr->setValue(m_val); }

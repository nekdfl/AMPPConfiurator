#ifndef TEMPERATUREBLOCK_H
#define TEMPERATUREBLOCK_H

#include <QLabel>
#include <QLayout>
#include <QPointer>
#include <QSpinBox>
#include <QWidget>

class TemperatureBlock : public QWidget {
  Q_OBJECT
public:
  explicit TemperatureBlock(const QString &a_name = "",
                            const QString &a_label = "",
                            const int &a_min = int8_t(0),
                            const int &a_max = int(130), int a_val = 0);

private:
  QPointer<QLabel> m_label_qptr;
  QPointer<QSpinBox> m_spinbox_qptr;
  QPointer<QHBoxLayout> m_hbox_qptr;
  QString m_name;
  int m_val;

private:
  inline void createGUI(const QString &a_label);
  inline void updateLimits(const int &a_min, const int &a_max);

signals:
  //двигаем слайдер
  void ValueChanging(const QString &a_name, const int &a_val);
  //слайдер отпущен
  void ValueChanged();
private slots:
  void sendSignals(int a_val);

public slots:
  //установка значения из матлогики
  void onValueChange(const int &a_val);
  //установка значения из матлогики
  void onValueChanged();
};

#endif // TEMPERATUREBLOCK_H

#ifndef CONTROLBLOCK_H
#define CONTROLBLOCK_H

#include <QDebug>
#include <QDial>
#include <QLCDNumber>
#include <QLabel>
#include <QLayout>
#include <QObject>
#include <QPointer>
#include <QSlider>
#include <QWidget>

class ControlBlock : public QWidget
{
    Q_OBJECT
  public:
    explicit ControlBlock(QWidget *parent = 0, const QString &a_name = "", const QString &a_label = "",
                          const int &a_min = int8_t(0), const int &a_max = int(130), int a_val = 0);

  protected:
    QString m_name;
    QPointer<QVBoxLayout> m_layout_qptr;
    QPointer<QLabel> m_label_qptr;
    QPointer<QLCDNumber> m_lcd_qtr;
    QPointer<QDial> m_dial_qptr;

  private:
    inline void createGUI(QWidget *parent, const QString &a_label);
    inline void updateLimits(const int &a_min, const int &a_max);

  signals:
    //двигаем слайдер
    void ValueChanging(const QString &a_name, const int &a_val);
    //слайдер отпущен
    void ValueChanged();

  public slots:
    //установка значения из матлогики
    void onValueChange(const int &a_val);
    //установка значения из матлогики
    void onValueChanged();
};

#endif // CONTROLBLOCK_H

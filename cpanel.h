#ifndef CPANEL_H
#define CPANEL_H

#include <QMap>
#include <QObject>
#include <QPointer>
#include <QWidget>

#include "constants.h"
#include "constructcontrolblock.h"
#include "controlblock.h"
#include "mathlogic.h"

class CPanel : public QWidget
{
    Q_OBJECT
  public:
    explicit CPanel(const QList<ConstructControlBlock> &controlBlockElements, const int &a_min, const int &a_max,
                    QWidget *parent = 0);

    MathLogic *getMathLogicInstance();
    void reloadSettings(const QList<ConstructControlBlock> &controlBlockElements);
    void setPresetValue(const QList<QPair<QString, int>> &a_vallist);

  protected:
    QList<ConstructControlBlock> m_controlBlockElements;

    QPointer<QHBoxLayout> m_hbox_qptr;
    QMap<QString, QPointer<ControlBlock>> m_controlblock_map;
    QPointer<MathLogic> m_mathlogic_qptr;
    const Constants &m_constants;

  private:
    inline void connectControlBlocksToMathLogic();
    inline void connectMathLogicToControlBlocks();
    inline void addToMathLogic(auto &it);
    inline void loadSettings(const int &a_min, const int &a_max);
    inline void updateControlBlocks();

  signals:
    void DialMoved(const QString &a_control, const int &a_val);
    void setValues();
};

#endif // CPANEL_H

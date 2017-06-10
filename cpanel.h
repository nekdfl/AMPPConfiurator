#ifndef CPANEL_H
#define CPANEL_H

#include <QObject>
#include <QWidget>
#include <QPointer>
#include <QMap>

#include "controlblock.h"
#include "constructcontrolblock.h"
#include "mathlogic.h"
#include "constants.h"

class CPanel : public QWidget
{
    Q_OBJECT
public:
    explicit CPanel(const QList<ConstructControlBlock> &controlBlockElements, const int &a_min, const int &a_max, QWidget *parent = 0 );

protected:
    QPointer <QHBoxLayout>  m_hbox_qptr;
    QMap< QString, QPointer<ControlBlock> > m_controlblock_map;
    QPointer <MathLogic> m_mathlogic_qptr;
    const Constants &m_constants;

private:
    inline void connectControlBlocksToMathLogic();
    inline void connectMathLogicToControlBlocks();
    inline void addToMathLogic(auto &it);


signals:
    void DialMoved(const QString& a_control, const int &a_val);
    void setValues();

//public slots:
//    void onPreviewReady(const QList <QPair <QString, int> > &a_vallist);

//protected slots:
//    void onSetReady();

};

#endif // CPANEL_H

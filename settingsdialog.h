#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QComboBox>
#include <QDialog>
#include <QDialogButtonBox>
#include <QLabel>
#include <QLayout>
#include <QPointer>
#include <QPushButton>
#include <QSettings>
#include <QWidget>

#include <QSerialPort>
#include <QSerialPortInfo>

#include "constants.h"
#include "constructcontrolblock.h"
#include "mathlogic.h"
#include "temperatureblock.h"

namespace Ui
{
class SettingsDialog;
}

class SettingsDialog : public QDialog
{
    Q_OBJECT

  public:
    explicit SettingsDialog(QSettings *a_settings_ptr,
                            const QList<ConstructControlBlock> &a_cntrBlckList,
                            QWidget *parent = 0);
    ~SettingsDialog();

  private:
    Ui::SettingsDialog *ui;
    Constants &m_constants;
    QSettings *m_settings_ptr;
    QPointer<QVBoxLayout> m_mainvb_lay;
    QPointer<QHBoxLayout> m_horizrs232_lay;
    QPointer<QLabel> m_rs232_lbl;
    QPointer<QComboBox> m_rs232_combo;
    QPointer<MathLogic> m_mathlogic_qptr;
    QPointer<QDialogButtonBox> m_dialogbuttonbox;
    QPointer<QPushButton> m_btnok_qptr;
    QPointer<QPushButton> m_btncancel_qptr;
    QPointer<QWidget> m_comportwidget_qptr;
    QMap<QString, QPointer<TemperatureBlock>> m_temperatureblock_map;

  private:
    inline void addComPortWidget();
    inline void
    addTermperatureBlocks(const QList<ConstructControlBlock> &a_cntrBlckList);
    inline void addButtonBox();
    inline void connectTemperatureBlocksToMathLogic();
    inline void connectMathLogicToTemperaturelBlocks();
    inline void saveComportToConfig();
    inline void saveTemperatureListToConfig();
};

#endif // SETTINGSDIALOG_H

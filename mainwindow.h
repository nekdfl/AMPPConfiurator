#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QHBoxLayout>
#include <QMainWindow>
#include <QSettings>
#include <QWidget>
#include <QtGui>
#include <QTextEdit>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QPointer>

#include "comportprocessor.h"
#include "constants.h"
#include "cpanel.h"
#include "settingsdialog.h"

#include "constructcontrolblock.h"

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

  public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QSettings *getSettingsPtr();

  private:
    inline void initSettings();
    inline void initCntrolBlockList();
    inline void createGUI();
    inline void createComPortProcessor();

    void resizeEvent(QResizeEvent *event);

  private:
    // vars
    Ui::MainWindow *ui;

    QPointer<QWidget> m_mainwindow;
    QPointer<QVBoxLayout> m_mainlayout_vb;
    QPointer<CPanel> m_cpanel_qptr;
    QPointer<QTextEdit> m_console_qptr;
    QPointer<QSettings> m_settings_qptr;
    QPointer<SettingsDialog> m_settingsdialog_qptr;
    QPointer<ComPortProcessor> m_comportprocessor_qptr;
    QList<ConstructControlBlock> m_controlBlockElements;
    const Constants &m_constants;

    QPointer<QComboBox> m_serialport_cbb;

  private slots:
    // menu action
    void onConnectAct();
    void onDisconnecAct();
    void onQuitAct();
    void onConfigureAct();
    void onSaveDefaults();
    void onLoadDefaults();
    void onShowHideConsoleAct();
    void onClearConsoleAct();
    void onHelpAct();
    void onAboutAct();

    void onDataRecieved(QByteArray a_recievbuff);
    void onDataTransfered(QByteArray a_recievbuff);
};

#endif // MAINWINDOW_H

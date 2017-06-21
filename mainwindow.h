#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QHBoxLayout>
#include <QMainWindow>
#include <QMessageBox>
#include <QPlainTextEdit>
#include <QPointer>
#include <QSettings>
#include <QWidget>
#include <QtGui>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

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
    inline void initQActionConnections();
    inline void initControlsState();
    inline void enableControls();
    inline void disableControls();
    inline void updateStatusBar();
    inline void addComportComBoxToToolBar();
    inline void moveConsoleCursorToEnd();
    void handleException(std::exception &ex);

    void resizeEvent(QResizeEvent *event);

  private:
    // vars
    Ui::MainWindow *ui;

    QPointer<QWidget> m_mainwindow;
    QPointer<QVBoxLayout> m_mainlayout_vb;
    QPointer<CPanel> m_cpanel_qptr;
    QPointer<QPlainTextEdit> m_console_qptr;
    QPointer<QLabel> m_status_lbl;
    QPointer<QSettings> m_settings_qptr;
    QPointer<SettingsDialog> m_settingsdialog_qptr;
    QPointer<ComPortProcessor> m_comportprocessor_qptr;
    QList<ConstructControlBlock> m_controlBlockElements;

    const Constants &m_constants;

    QPointer<QComboBox> m_serialport_cbb;

  private slots:
    // menu action
    void onConfigureAct();
    void onHelpAct();
    void onAboutAct();
    //menu and tool bar
    void onConnectAct();
    void onDisconnecAct();
    void onShowHideConsoleAct();
    void onClearConsoleAct();
    void onSaveDefaults();
    void onLoadDefaults();
    void onReadFromDevice();
    void onWriteToDevice();
    void onQuitAct();

    //comport events
    void onDataRecieved(QByteArray a_recievbuff);
    void onDataTransfered(QByteArray a_recievbuff);
    void onComPortReadFromDevice(const QList<QPair<QString, int>> &a_vallist);
};

#endif // MAINWINDOW_H

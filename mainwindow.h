#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QHBoxLayout>
#include <QMainWindow>
#include <QSettings>
#include <QWidget>
#include <QtGui>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

#include <QPointer>

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

    void resizeEvent(QResizeEvent *event);

  private:
    // constants

    // vars
    Ui::MainWindow *ui;
    QPointer<CPanel> m_cpanel_qptr;
    QPointer<QSettings> m_settings_qptr;
    QPointer<SettingsDialog> m_settingsdialog_qptr;
    QList<ConstructControlBlock> m_cntrBlckList;
    const Constants &m_constants;

  private slots:
    // menu action
    void onConnectAct();
    void onDisconnecAct();
    void onQuitAct();
    void onConfigureAct();
    void onLoadDefaults();
    void onClearConsoleAct();
    void onHelpAct();
    void onAboutAct();
};

#endif // MAINWINDOW_H

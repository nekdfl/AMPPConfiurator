#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <QWidget>
#include <QHBoxLayout>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QSettings>


#include <QPointer>


#include "cpanel.h"
#include "constants.h"
#include "settingsdialog.h"


#include "constructcontrolblock.h"

namespace Ui {
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
    inline void createGUI(const QList < ConstructControlBlock> & a_cntrBlckList);
    void resizeEvent(QResizeEvent *event);

private:
    //constants


    //vars
    Ui::MainWindow *ui;
    QPointer <CPanel> m_cpanel_qptr;
    QPointer <QSettings> m_settings_qptr;
    QPointer <SettingsDialog> m_settingsdialog_qptr;
    QList < ConstructControlBlock>  m_cntrBlckList;
    const Constants &m_constants;


private slots:
    //menu action
    void onConnectAct();
    void onDisconnecAct();
    void onQuitAct();
    void onConfigureAct();
    void onClearConsoleAct();
    void onHelpAct();
    void onAboutAct();


};

#endif // MAINWINDOW_H

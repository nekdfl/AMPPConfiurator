#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), m_constants(Constants::getInstance())
{
    QCoreApplication::setApplicationVersion(m_constants.applicationversion);
    QCoreApplication::setOrganizationName(m_constants.organizationName);
    QCoreApplication::setOrganizationDomain(m_constants.organizationdomain);
    QCoreApplication::setApplicationName(m_constants.applicationname);

    initSettings();
    ui->setupUi(this);

    initCntrolBlockList();
    createGUI();

    connect(ui->action_Preferances, &QAction::triggered, this, &MainWindow::onConfigureAct);
    connect(ui->action_Load_defaults, &QAction::triggered, this, &MainWindow::onLoadDefaults);
    connect(ui->action_Quit, &QAction::triggered, this, &MainWindow::onQuitAct);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initSettings()
{
    // init settings to default values; For future may be save in file.

    m_settings_qptr = new QSettings(QDir::currentPath() + "/" + m_constants.configfilename, QSettings::IniFormat);

    qDebug() << "config path: " << QDir::currentPath() + "/" + m_constants.configfilename;

    const int min = m_settings_qptr->value(m_constants.mintemp_name, m_constants.mintemp).toInt();
    const int max = m_settings_qptr->value(m_constants.maxtemp_name, m_constants.maxtemp).toInt();

    const int cooloff = m_settings_qptr->value(m_constants.cooloff_name, m_constants.cooloff).toInt();
    const int cool35 = m_settings_qptr->value(m_constants.cool35_name, m_constants.cool35).toInt();
    const int cool50 = m_settings_qptr->value(m_constants.cool50_name, m_constants.cool50).toInt();
    const int cool70 = m_settings_qptr->value(m_constants.cool70_name, m_constants.cool70).toInt();
    const int cool90 = m_settings_qptr->value(m_constants.cool90_name, m_constants.cool90).toInt();
    const int cool100 = m_settings_qptr->value(m_constants.cool100_name, m_constants.cool100).toInt();
    const int alarmoff = m_settings_qptr->value(m_constants.alarmoff_name, m_constants.alarmoff).toInt();
    const int alarmon = m_settings_qptr->value(m_constants.alarmon_name, m_constants.alarmon).toInt();
    const int poweroff = m_settings_qptr->value(m_constants.poweroff_name, m_constants.poweroff).toInt();

    m_settings_qptr->setValue(m_constants.mintemp_name, min);
    m_settings_qptr->setValue(m_constants.maxtemp_name, max);

    m_settings_qptr->setValue(m_constants.cooloff_name, cooloff);
    m_settings_qptr->setValue(m_constants.cool35_name, cool35);
    m_settings_qptr->setValue(m_constants.cool50_name, cool50);
    m_settings_qptr->setValue(m_constants.cool70_name, cool70);
    m_settings_qptr->setValue(m_constants.cool90_name, cool90);
    m_settings_qptr->setValue(m_constants.cool100_name, cool100);
    m_settings_qptr->setValue(m_constants.alarmoff_name, alarmoff);
    m_settings_qptr->setValue(m_constants.alarmon_name, alarmon);
    m_settings_qptr->setValue(m_constants.poweroff_name, poweroff);
}

void MainWindow::initCntrolBlockList()
{
    const int &min = m_settings_qptr->value(m_constants.mintemp_name).toInt();
    const int &max = m_settings_qptr->value(m_constants.maxtemp_name).toInt();

    const int &cooloff = m_settings_qptr->value(m_constants.cooloff_name).toInt();
    const int &cool35 = m_settings_qptr->value(m_constants.cool35_name).toInt();
    const int &cool50 = m_settings_qptr->value(m_constants.cool50_name).toInt();
    const int &cool70 = m_settings_qptr->value(m_constants.cool70_name).toInt();
    const int &cool90 = m_settings_qptr->value(m_constants.cool90_name).toInt();
    const int &cool100 = m_settings_qptr->value(m_constants.cool100_name).toInt();
    const int &alarmoff = m_settings_qptr->value(m_constants.alarmoff_name).toInt();
    const int &alarmon = m_settings_qptr->value(m_constants.alarmon_name).toInt();
    const int &poweroff = m_settings_qptr->value(m_constants.poweroff_name).toInt();

    m_cntrBlckList = {ConstructControlBlock(m_constants.cooloff_name, m_constants.cooloff_label, min, max, cooloff),
                      ConstructControlBlock(m_constants.cool35_name, m_constants.cool35_label, min, max, cool35),
                      ConstructControlBlock(m_constants.cool50_name, m_constants.cool50_label, min, max, cool50),
                      ConstructControlBlock(m_constants.cool70_name, m_constants.cool70_label, min, max, cool70),
                      ConstructControlBlock(m_constants.cool90_name, m_constants.cool90_label, min, max, cool90),
                      ConstructControlBlock(m_constants.cool100_name, m_constants.cool100_label, min, max, cool100),
                      ConstructControlBlock(m_constants.alarmoff_name, m_constants.alarmoff_label, min, max, alarmoff),
                      ConstructControlBlock(m_constants.alarmon_name, m_constants.alarmon_label, min, max, alarmon),
                      ConstructControlBlock(m_constants.poweroff_name, m_constants.poweroff_label, min, max, poweroff)};
}

void MainWindow::createGUI()
{
    this->setWindowTitle(m_constants.windowtitle);
    this->setMaximumSize(m_constants.maxwindowwidth, m_constants.maxwindowheight);
    this->setMinimumSize(m_constants.minwindowwidth, m_constants.minwindowheight);

    m_cpanel_qptr = new CPanel(m_cntrBlckList, m_settings_qptr->value(m_constants.mintemp_name).toInt(),
                               m_settings_qptr->value(m_constants.maxtemp_name).toInt());
    setCentralWidget(m_cpanel_qptr);
}

void MainWindow::onAboutAct()
{
}

void MainWindow::onClearConsoleAct()
{
}

void MainWindow::onConfigureAct()
{
    m_settingsdialog_qptr = new SettingsDialog(m_settings_qptr.data(), m_cntrBlckList);
    m_settingsdialog_qptr->exec();
}

void MainWindow::onLoadDefaults()
{
    m_cpanel_qptr.clear();
    m_cntrBlckList.clear();

    initSettings();
    initCntrolBlockList();
    createGUI();
}

void MainWindow::onConnectAct()
{
}

void MainWindow::onDisconnecAct()
{
}

void MainWindow::onHelpAct()
{
}

void MainWindow::onQuitAct()
{
    this->close();
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);
    //     QString caption;
    //     caption.append(QString::number(this->width())).append("x").append(QString::number(this->height()));
    //    this->setWindowTitle(caption);
}

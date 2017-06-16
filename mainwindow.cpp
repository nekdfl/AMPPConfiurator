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
    createComPortProcessor();
    ui->setupUi(this);

    initCntrolBlockList();
    createGUI();
    initQActionConnections();
    initControlsState();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initSettings()
{
    // init settings to default values; For future may be save in file.
    qDebug() << "config path: " << QDir::currentPath() + "/" + m_constants.configfilename;
    m_settings_qptr = new QSettings(QDir::currentPath() + "/" + m_constants.configfilename, QSettings::IniFormat);



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

    m_controlBlockElements.clear();
    m_controlBlockElements = {ConstructControlBlock(m_constants.cooloff_name, m_constants.cooloff_label, min, max, cooloff),
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

    m_console_qptr = new QPlainTextEdit();
    QPalette pal = palette();
    pal.setColor(QPalette::Base, Qt::black);
    pal.setColor(QPalette::Text, Qt::green);
    m_console_qptr->hide();
    m_console_qptr->setReadOnly(true);
    m_console_qptr->setCursorWidth(0);
    m_console_qptr->setMaximumHeight(m_constants.consoleheght);
    m_console_qptr->setPalette(pal);

    m_cpanel_qptr = new CPanel(m_controlBlockElements, m_settings_qptr->value(m_constants.mintemp_name).toInt(),
                               m_settings_qptr->value(m_constants.maxtemp_name).toInt());

    m_mainwindow = new QWidget();
    m_mainlayout_vb = new QVBoxLayout();
    m_mainlayout_vb->setMargin(0);
    m_mainwindow->setLayout(m_mainlayout_vb);

    m_mainlayout_vb->addWidget(m_cpanel_qptr);
    m_mainlayout_vb->addWidget(m_console_qptr);

    setCentralWidget(m_mainwindow);

    m_status_lbl = new QLabel("");
    ui->statusBar->addWidget(m_status_lbl);
    updateStatusBar();
}

void MainWindow::createComPortProcessor()
{
    m_comportprocessor_qptr = new ComPortProcessor();
    connect(m_comportprocessor_qptr, &ComPortProcessor::dataRecived, this, &MainWindow::onDataRecieved) ;
    connect(m_comportprocessor_qptr, &ComPortProcessor::dataTransfered, this, &MainWindow::onDataTransfered);
}

void MainWindow::initQActionConnections()
{
    connect(ui->action_Preferances, &QAction::triggered, this, &MainWindow::onConfigureAct);

    connect(ui->action_Connect, &QAction::triggered, this , & MainWindow::onConnectAct);
    connect(ui->action_Disconnect, &QAction::triggered, this , & MainWindow::onDisconnecAct);
    connect (ui->action_Show_hide_console, &QAction::triggered, this, &MainWindow::onShowHideConsoleAct);
    connect (ui->action_Clear_console, &QAction::triggered, this, &MainWindow::onClearConsoleAct);
    connect(ui->action_Save_as_default, &QAction::triggered, this, &MainWindow::onSaveDefaults);
    connect(ui->action_Load_default, &QAction::triggered, this, &MainWindow::onLoadDefaults);
    connect(ui->action_Read_from_device, &QAction::triggered, this, &MainWindow::onReadFromDevice);
    connect(ui->action_Write_to_device, &QAction::triggered, this, &MainWindow::onWriteToDevice);
    connect(ui->action_Quit, &QAction::triggered, this, &MainWindow::onQuitAct);
}

void MainWindow::initControlsState()
{
    m_cpanel_qptr->setEnabled(false);
    ui->action_Disconnect->setEnabled(false);
    ui->action_Clear_console->setEnabled(false);
    ui->action_Save_as_default->setEnabled(false);
    ui->action_Load_default->setEnabled(false);
    ui->action_Read_from_device->setEnabled(false);
    ui->action_Write_to_device->setEnabled(false);

}

void MainWindow::enableControls()
{
    ui->action_Connect->setEnabled(false);
    ui->action_Disconnect->setEnabled(true);
    m_cpanel_qptr->setEnabled(true);
    m_console_qptr->setEnabled(true);
    ui->action_Disconnect->setEnabled(true);
    ui->action_Clear_console->setEnabled(true);
    ui->action_Save_as_default->setEnabled(true);
    ui->action_Load_default->setEnabled(true);
    ui->action_Read_from_device->setEnabled(true);
    ui->action_Write_to_device->setEnabled(true);

}

void MainWindow::disableControls()
{
    ui->action_Connect->setEnabled(true);
    ui->action_Disconnect->setEnabled(false);
    m_cpanel_qptr->setEnabled(false);
    m_console_qptr->setEnabled(false);
    ui->action_Disconnect->setEnabled(false);
    ui->action_Clear_console->setEnabled(false);
    ui->action_Save_as_default->setEnabled(false);
    ui->action_Load_default->setEnabled(false);
    ui->action_Read_from_device->setEnabled(false);
    ui->action_Write_to_device->setEnabled(false);

}

void MainWindow::updateStatusBar()
{
    m_status_lbl->setText( m_comportprocessor_qptr->getStatus());
}

void MainWindow::addComportComBoxToToolBar()
{
    //    auto vtoolbar = this->findChild<QToolBar *>("maintoolBar");
    //    if (vtoolbar)
    //    {
    //        qDebug() << "toolbars: " << vtoolbar->objectName()  ;
    //    }
}

void MainWindow::onConfigureAct()
{
    m_settingsdialog_qptr = new SettingsDialog(m_settings_qptr.data(), m_controlBlockElements);
    m_settingsdialog_qptr->exec();
}

void MainWindow::onHelpAct()
{

}

void MainWindow::onAboutAct()
{

}

void MainWindow::onConnectAct()
{
    auto comportname = m_settings_qptr->value(m_constants.comport_name).toString();
    m_comportprocessor_qptr->setComportName(comportname);
    m_comportprocessor_qptr->open();
    updateStatusBar();
    enableControls();
}

void MainWindow::onDisconnecAct()
{
    m_comportprocessor_qptr->close();
    updateStatusBar();
    disableControls();
}

void MainWindow::onShowHideConsoleAct()
{
    if (m_console_qptr->isVisible())
    {
        m_console_qptr->hide();
        this->setMaximumHeight(m_constants.maxwindowheight);
        this->resize(m_constants.maxwindowwidth, this->maximumHeight());
        ui->action_Clear_console->setEnabled(false);
    }
    else
    {
        m_console_qptr->show();
        this->setMaximumHeight(m_constants.maxwindowheight + m_constants.consoleheght);
        this->resize(m_constants.maxwindowwidth, this->maximumHeight());
        ui->action_Clear_console->setEnabled(true);
    }
}

void MainWindow::onClearConsoleAct()
{
    m_console_qptr->clear();
}

void MainWindow::onSaveDefaults()
{
    auto vmathlogic= m_cpanel_qptr->getMathLogicInstance();
    auto vtemperature_list = vmathlogic->getPairListFromBtree();
    for (auto &it : vtemperature_list)
    {
        m_settings_qptr->setValue(it.first, it.second);
    }
}

void MainWindow::onLoadDefaults()
{
    initSettings();
    initCntrolBlockList();
    m_cpanel_qptr->reloadSettings(m_controlBlockElements);
}

void MainWindow::onReadFromDevice()
{
    m_comportprocessor_qptr->requestPresetValue();
}

void MainWindow::onWriteToDevice()
{
    auto vmathlogic= m_cpanel_qptr->getMathLogicInstance();
    m_comportprocessor_qptr->sendPresetValue(vmathlogic->getPairListFromBtree());
}

void MainWindow::onQuitAct()
{
    this->close();
}

void MainWindow::onDataRecieved(QByteArray a_recievbuff)
{
    m_console_qptr->insertPlainText("<<");
    m_console_qptr->insertPlainText(a_recievbuff);
}

void MainWindow::onDataTransfered(QByteArray a_recievbuff)
{
    m_console_qptr->insertPlainText(">>");
    m_console_qptr->insertPlainText(a_recievbuff);
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);
    //     QString caption;
    //     caption.append(QString::number(this->width())).append("x").append(QString::number(this->height()));
    //    this->setWindowTitle(caption);
}

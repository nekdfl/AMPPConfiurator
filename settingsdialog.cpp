#include "settingsdialog.h"
#include "ui_settingsdialog.h"

SettingsDialog::SettingsDialog(QSettings *a_settings_ptr, const QList<ConstructControlBlock> &a_cntrBlckList, QWidget *parent)
    : QDialog(parent),
      ui(new Ui::SettingsDialog),
      m_constants(Constants::getInstance()),
      m_settings_ptr(a_settings_ptr)
{
    ui->setupUi(this);

    m_mathlogic_qptr = new MathLogic(m_settings_ptr->value(m_constants.mintemp_name).toInt(),
                                     m_settings_ptr->value(m_constants.maxtemp_name).toInt());

    m_mainvb_lay = new QVBoxLayout();

    addComPortWidget();
    addTermperatureBlocks(a_cntrBlckList);
    addButtonBox();

    connectTemperatureBlocksToMathLogic();
    connectMathLogicToTemperaturelBlocks();

    connect(m_btncancel_qptr, &QPushButton::clicked, [this]()
    {
        this->close();
    });

    connect(m_btnok_qptr, &QPushButton::clicked, [this]()
    {
        saveComportToConfig();
        saveTemperatureListToConfig();
        this->close();
    });

    this->setLayout(m_mainvb_lay);
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

void SettingsDialog::addComPortWidget()
{
    m_horizrs232_lay = new QHBoxLayout();

    m_comportwidget_qptr = new QWidget();
    m_comportwidget_qptr->setLayout(m_horizrs232_lay);

    m_rs232_lbl = new QLabel("Com port");
    m_rs232_combo = new QComboBox();

    auto port_list = QSerialPortInfo::availablePorts();
    if (!port_list.empty())
    {
        for (auto &it : port_list)
        {
            m_rs232_combo->addItem(it.portName());
        }
    }
    else
    {
        auto default_comport = m_settings_ptr->value(m_constants.comport_name,
                                                     m_constants.nocomport_value);
        m_rs232_combo->addItem(default_comport.toString());
    }

    m_horizrs232_lay->addWidget(m_rs232_lbl);
    m_horizrs232_lay->addWidget(m_rs232_combo);

    m_mainvb_lay->addWidget(m_comportwidget_qptr);
}

void SettingsDialog::addTermperatureBlocks(
    const QList<ConstructControlBlock> &a_cntrBlckList)
{
    for (auto &it : a_cntrBlckList)
    {
        auto ptr = new TemperatureBlock(
            it.getName(), it.getLabel(), it.getMintemperature(),
            it.getMaxTemperature(), it.getDefTemperature());
        m_temperatureblock_map.insert(it.getName(), ptr);
        m_mainvb_lay->addWidget(ptr);

        if (it.getName() == m_constants.alarmoff_name ||
            it.getName() == m_constants.alarmon_name ||
            it.getName() == m_constants.poweroff_name)
            m_mathlogic_qptr->addExtraVal(it.getName(), it.getDefTemperature());
        else
            m_mathlogic_qptr->addVal(it.getName(), it.getDefTemperature());
    }
}

void SettingsDialog::addButtonBox()
{
    m_dialogbuttonbox = new QDialogButtonBox();

    m_btnok_qptr = new QPushButton("&Ok");
    m_btncancel_qptr = new QPushButton("&Cancel");

    m_dialogbuttonbox->addButton(m_btnok_qptr, QDialogButtonBox::AcceptRole);
    m_dialogbuttonbox->addButton(m_btncancel_qptr, QDialogButtonBox::RejectRole);

    m_mainvb_lay->addWidget(m_dialogbuttonbox);
}

void SettingsDialog::connectMathLogicToTemperaturelBlocks()
{
    connect(m_mathlogic_qptr, &MathLogic::presetValueReady,
            [this](auto &a_vallist) {
                for (auto &val : a_vallist)
                {
                    m_temperatureblock_map[val.first]->onValueChange(val.second);
                }
            });
}

void SettingsDialog::connectTemperatureBlocksToMathLogic()
{
    for (auto &it : m_temperatureblock_map)
    {
        connect(it, &TemperatureBlock::ValueChanging, m_mathlogic_qptr,
                &MathLogic::onDialMoved);
        connect(it, &TemperatureBlock::ValueChanged, [this]() {
            for (auto &it : m_temperatureblock_map)
            {
                it->onValueChanged();
            }
        });
    }
}

void SettingsDialog::saveComportToConfig()
{
    m_settings_ptr->setValue(m_constants.comport_name,
                             m_rs232_combo->currentText());
}

void SettingsDialog::saveTemperatureListToConfig()
{
    auto vtemperature_list = m_mathlogic_qptr->getPairListFromBtree();
    for (auto &it : vtemperature_list)
    {
        m_settings_ptr->setValue(it.first, it.second);
    }
}

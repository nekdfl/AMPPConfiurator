#ifndef CONSTANTS_H
#define CONSTANTS_H

class Constants
{
  public:
    static Constants &getInstance();
    ~Constants();

    const char *debug_fromdevice = " 0 | 1 | 2 | 3 | 4 |  5 |   6  |  7  |   8   |\rOff|35%|50%|70%|90%|100%|Al_off|Al_on|OFF_pow|\r 35|40 |50 |60 |70 |80  |60    |95   |110\rWrite EEPROM - w  Read EEPROM - r\r----------------------------------------\r";

    const int readtimeout_ms = 1000;
    const int writetimeout_ms = 1000;

    const int minwindowwidth = 1024;
    const int minwindowheight = 360;
    const int maxwindowwidth = 1024;
    const int maxwindowheight = 360;
    const int consoleheght = 360;

    const char *connected_port_msg = "Connected to comport: ";
    const char *connected_speed_msg = " with boudrate: ";
    const char *disconnected_msg = "Disconnected";

    const char *applicationversion = "0.1a";
    const char *organizationName = "Garkushenko Nick";
    const char *organizationdomain = "localhost";
    const char *applicationname = "AMPPConfigurator";

    const char *windowtitle = "AMP Protection configurator";
    const char *configfilename = "config.ini";

    const char *comport_name = "comport";
    const char *nocomport_value = "no selected";

    const char *maxtemp_name = "mintemp";
    const char *mintemp_name = "maxtemp";
    const int maxtemp = 120;
    const int mintemp = 0;

    const int cooloff = 35;
    const int cool35 = 40;
    const int cool50 = 50;
    const int cool70 = 60;
    const int cool90 = 70;
    const int cool100 = 80;
    const int alarmoff = 60;
    const int alarmon = 95;
    const int poweroff = 110;

    const char *cooloff_name = "cooloff";
    const char *cool35_name = "cool35";
    const char *cool50_name = "cool50";
    const char *cool70_name = "cool70";
    const char *cool90_name = "cool90";
    const char *cool100_name = "cool100";
    const char *alarmoff_name = "alarmoff";
    const char *alarmon_name = "alarmon";
    const char *poweroff_name = "poweroff";

    const char *cooloff_label = "Cooler: OFF ";
    const char *cool35_label = "Cooler: 35% ";
    const char *cool50_label = "Cooler: 50% ";
    const char *cool70_label = "Cooler: 70% ";
    const char *cool90_label = "Cooler: 90% ";
    const char *cool100_label = "Cooler: 100%";
    const char *alarmoff_label = "Alarm off   ";
    const char *alarmon_label = "Alarm on    ";
    const char *poweroff_label = "Poweroff    ";

  private:
    static Constants *m_pinstance;

  private:
    Constants();
};

#endif // CONSTANTS_H

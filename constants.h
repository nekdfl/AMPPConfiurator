#ifndef CONSTANTS_H
#define CONSTANTS_H

class Constants
{
  public:
    static Constants &getInstance();
    ~Constants();

    const char *debug_fromdevice = " 0 | 1 | 2 | 3 | 4 |  5 |   6  |  7  |   8   |\rOff|35%|50%|70%|90%|100%|Al_off|Al_on|OFF_pow|\r 35|40 |50 |60 |70 |80  |60    |95   |110\rWrite EEPROM - w  Read EEPROM - r\r----------------------------------------\r";
    const char *witherror_error = " with error: ";
    const char *cant_write_error = "Failed to write the data to port: ";
    const char *cantwrite_all_error = "Failed to write the all data to port: ";

    const char *failtoopenport_error = "Failed to open port: ";

    const char *cantread_error = "Failed to read from port: ";
    const char *nodatatoread_error = "No data was currently available for reading from port: ";
    const char *operationtimeout_error = "Operation timed out or an error occurred for port: ";

    const char *about_title = "About";
    const char *about_text = "This program is distributed under the GNU3 or later license, development at the request of Glotov Yuri Vladimirovich.\n\
The source code can be downloaded from\n\
https://github.com/nekdfl/AMPPConfiurator.\n\
Author: Garkushenko Nikolai Sergeevich.";

    const char *help_title = "First help";
    const char *help_text = "Still under construction";

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
    const char *organizationName = "Garkushenko Nickolay Sergeevich";
    const char *organizationdomain = "localhost";
    const char *applicationname = "AMPPConfigurator";

    const char *windowtitle = "AMP Protection configurator";
    const char *configfilename = "config.ini";

    const char *comport_key = "comport";
    const char *nocomport_value = "no selected";

    const char *maxtemp_key = "mintemp";
    const char *mintemp_key = "maxtemp";
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

    const char *cooloff_key = "cooloff";
    const char *cool35_key = "cool35";
    const char *cool50_ley = "cool50";
    const char *cool70_key = "cool70";
    const char *cool90_key = "cool90";
    const char *cool100_key = "cool100";
    const char *alarmoff_key = "alarmoff";
    const char *alarmon_key = "alarmon";
    const char *poweroff_key = "poweroff";

    const char *cooloff_label = "Cooler: OFF ";
    const char *cool35_label = "Cooler: 35% ";
    const char *cool50_label = "Cooler: 50% ";
    const char *cool70_label = "Cooler: 70% ";
    const char *cool90_label = "Cooler: 90% ";
    const char *cool100_label = "Cooler: 100%";
    const char *alarmoff_label = "Alarm off   ";
    const char *alarmon_label = "Alarm on    ";
    const char *poweroff_label = "Poweroff    ";

    const char *windowpostionx_key = "windowx";
    const char *windowpostiony_key = "windowy";
    const int windowxpostion = 100;
    const int windowypostion = 100;

    const int consolemaxline = 300;

    const char *handshare_request = "255\r\n";

  private:
    static Constants *m_pinstance;

  private:
    Constants();
};

#endif // CONSTANTS_H

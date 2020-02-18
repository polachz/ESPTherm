#ifndef __esp_therm_config_H_
#define __esp_therm_config_H_


class EspThermConfig
{
    public:
    EspThermConfig();

    bool Setup();

    bool FSMounted()const {return m_Mounted;}

    bool LoadFromFS();
    bool SaveToFS();

    const char* HostName() const {return m_HostName;}
    const char* MQTTHost() const {return m_MQTTHost;}
    const char* MQTTPort() const {return m_MQTTPort;} 
    const char* MQTTUser() const {return m_MQTTUser;}
    const char* MQTTPass() const {return m_MQTTPass;}

    static String FormatBytes(size_t bytes);
protected:

    bool MountFS();
    void FillByDefaults();
    bool m_Mounted;
    char m_HostName[32];

    char m_MQTTHost[64];
    char m_MQTTPort[6];
    char m_MQTTUser[32];
    char m_MQTTPass[32];
};

void config_storage_setup();

bool load_config_from_fs();

#endif

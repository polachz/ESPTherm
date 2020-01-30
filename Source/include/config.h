#ifndef __config_H_
#define __config_H_

void config_storage_setup();

bool load_config_from_fs();


extern char host_name[];

#if defined(ENABLE_AMQTT)

extern char mqtt_host[];
extern char mqtt_port[];
extern char mqtt_user[];
extern char mqtt_pass[];

#endif

#endif
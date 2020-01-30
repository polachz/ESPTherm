#ifndef __web_server_H_
#define __web_server_H_

#include <ESPAsyncWebServer.h>     //Local WebServer used to serve the configuration portal


void web_server_register_handlers(AsyncWebServer& server);


void on_cus(AsyncWebServerRequest *request);

#endif
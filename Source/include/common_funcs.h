
#ifndef __common_funcs_H_
#define __common_funcs_H_

#include <stdlib.h>
#include <WString.h>
#include <Ticker.h>

extern Ticker ticker;

void BlinkLed(double intervalInSecs);

void BlinkLedStop(bool ledOn);

String formatBytes(size_t bytes);

void signal_hard_error();

unsigned long GetTimestamp();

#endif
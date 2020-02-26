#ifndef __debug_H_
#define __debug_H_


// Disable all debug ? Good to release builds (production)
// as nothing of SerialDebug is compiled, zero overhead :-)
// For it just uncomment the DEBUG_DISABLED
//#define DEBUG_DISABLED true

// Disable SerialDebug debugger ? No more commands and features as functions and globals
// Uncomment this to disable it 
//#define DEBUG_DISABLE_DEBUGGER true

// Define the initial debug level here (uncomment to do it)
#define DEBUG_INITIAL_LEVEL DEBUG_LEVEL_INFO  	
//#define DEBUG_INITIAL_LEVEL DEBUG_LEVEL_DEBUG  	
//#define DEBUG_INITIAL_LEVEL DEBUG_LEVEL_VERBOSE  	

// Disable auto function name (good if your debug yet contains it)
//#define DEBUG_AUTO_FUNC_DISABLED true

#include <SerialDebug.h> //https://github.com/JoaoLopesF/SerialDebug

#endif
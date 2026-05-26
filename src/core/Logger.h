#ifndef TERAVOX_LOGGER_H
#define TERAVOX_LOGGER_H

#include <stdio.h>

#define TV_LOG(msg)     printf("[LOG]   %s\n",msg)
#define TV_WARN(msg)    printf("[WARN]  %s\n",msg)
#define TV_ERROR(msg)   printf("[ERROR] %s\n",msg)
#define TV_INFO(msg)    printf("[INFO]  %s\n",msg)

#endif //TERAVOX_LOGGER_H
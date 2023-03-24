#ifndef LOGGER_H_
#define LOGGER_H_

#include <spdlog/spdlog.h>

#ifdef LOGGING
    #define TRACE SPDLOG_TRACE
    #define DEBUG SPDLOG_DEBUG
    #define INFO SPDLOG_INFO
    #define WARNING SPDLOG_WARN
    #define ERROR SPDLOG_ERROR
    #define CRITICAL SPDLOG_CRITICAL
#else
    #define TRACE(...)
    #define DEBUG(...)
    #define INFO(...)
    #define WARNING(...)
    #define ERROR(...)
    #define CRITICAL(...)
#endif

#endif /* !LOGGER_H_ */

#ifndef AGS_LOGGING_HPP
#define AGS_LOGGING_HPP

#define QUILL_DISABLE_NON_PREFIXED_MACROS
#include <quill/Quill.h>

//#include <spdlog/spdlog.h>
//#include <spdlog/sinks/stdout_color_sinks.h>

//=========================================================
// Utility macros
//=========================================================

/// Copied from
/// https://www.decompile.com/cpp/faq/file_and_line_error_string.htm
#define AGS_STRINGIFY(x) #x
#define AGS_TO_STRING(x) AGS_STRINGIFY(x)


//#if !defined(AGS_MODULE_NAME)
//    #define AGS_MODULE_NAME "UNRECOGNIZED_MODULE"
//#endif

///
/// Macro intended to be used for reporting place in code where error was
/// identified.
///
//#define AGS_CODE_LOCATION AGS_TO_STRING(AGS_MODULE_NAME) ":" __FILE__ ":" AGS_TO_STRING(__LINE__)
#define AGS_CODE_LOCATION __FILE__ ":" AGS_TO_STRING(__LINE__)

//=========================================================
// Loggers
//=========================================================


//=========================================================
// Logging macros
//=========================================================

/*
#if defined(AGS_LOGGING_LEVEL_NONE)
    #define AGS_NOTIFY(message)
    #define AGS_WARN(message)
    #define AGS_ERROR(message)
    #define AGS_FATAL(message)
#elif defined(AGS_LOGGING_LEVEL_LOW)
    #define AGS_NOTIFY(message)
    #define AGS_WARN(message)
    #define AGS_ERROR(message)
    #define AGS_FATAL(...) spdlog::critical(AGS_CODE_LOCATION "\n" __VA_ARGS__)
#elif defined(AGS_LOGGING_LEVEL_MEDIUM)
    #define AGS_NOTIFY(message)
    #define AGS_WARN(message)
    #define AGS_ERROR(...) spdlog::error(AGS_CODE_LOCATION "\n" __VA_ARGS__)
    #define AGS_FATAL(...) spdlog::critical(AGS_CODE_LOCATION "\n" __VA_ARGS__)
#elif defined(AGS_LOGGING_LEVEL_HIGH)
    #define AGS_NOTIFY(message)
    #define AGS_WARN(...)  spdlog::warn(AGS_CODE_LOCATION "\n" __VA_ARGS__)
    #define AGS_ERROR(...) spdlog::error(AGS_CODE_LOCATION "\n" __VA_ARGS__)
    #define AGS_FATAL(...) spdlog::critical(AGS_CODE_LOCATION "\n" __VA_ARGS__)
#else
    #define AGS_NOTIFY(...) spdlog::info(AGS_CODE_LOCATION "\n", __VA_ARGS__)
    #define AGS_WARN(...)   spdlog::warn(AGS_CODE_LOCATION "\n", __VA_ARGS__)
    #define AGS_ERROR(...)  spdlog::error(AGS_CODE_LOCATION "\n", __VA_ARGS__)
    #define AGS_FATAL(...)  spdlog::critical(AGS_CODE_LOCATION "\n", __VA_ARGS__)
#endif
*/


#if defined(AGS_LOGGING_LEVEL_NONE)
    #define AGS_INFO(message)
    #define AGS_WARN(message)
    #define AGS_ERROR(message)
    #define AGS_FATAL(message)
#elif defined(AGS_LOGGING_LEVEL_LOW)
    #define AGS_INFO(message)
    #define AGS_WARN(message)
    #define AGS_ERROR(message)
    #define AGS_FATAL(...) LOG_CRITICAL(quill::get_logger(), AGS_CODE_LOCATION "\n") LOG_CRITICAL(quill::get_logger(), __VA_ARGS__, );
#elif defined(AGS_LOGGING_LEVEL_MEDIUM)
    #define AGS_INFO(message)
    #define AGS_WARN(message)
    #define AGS_ERROR(...) LOG_ERROR(quill::get_logger(), AGS_CODE_LOCATION "\n") LOG_ERROR(quill::get_logger(), __VA_ARGS__, );
    #define AGS_FATAL(...) LOG_CRITICAL(quill::get_logger(), AGS_CODE_LOCATION "\n") LOG_CRITICAL(quill::get_logger(), __VA_ARGS__, );
#elif defined(AGS_LOGGING_LEVEL_HIGH)
    #define AGS_INFO(message)
    #define AGS_WARN(...)  LOG_WARNING(quill::get_logger(), AGS_CODE_LOCATION "\n") LOG_WARNING(quill::get_logger(), __VA_ARGS__, );
    #define AGS_ERROR(...) LOG_ERROR(quill::get_logger(), AGS_CODE_LOCATION "\n") LOG_ERROR(quill::get_logger(), __VA_ARGS__, );
    #define AGS_FATAL(...) LOG_CRITICAL(quill::get_logger(), AGS_CODE_LOCATION "\n") LOG_CRITICAL(quill::get_logger(), __VA_ARGS__, );
#else
    #define AGS_INFO(...)  /*LOG_INFO(quill::get_logger(), AGS_CODE_LOCATION "\n")    */ QUILL_LOG_INFO(quill::get_logger(), __VA_ARGS__);
    #define AGS_WARN(...)  /*LOG_WARNING(quill::get_logger(), AGS_CODE_LOCATION "\n") */ QUILL_LOG_WARNING(quill::get_logger(), __VA_ARGS__);
    #define AGS_ERROR(...) /*LOG_ERROR(quill::get_logger(), AGS_CODE_LOCATION "\n")   */ QUILL_LOG_ERROR(quill::get_logger(), __VA_ARGS__);
    #define AGS_FATAL(...) /*LOG_CRITICAL(quill::get_logger(), AGS_CODE_LOCATION "\n")*/ QUILL_LOG_CRITICAL(quill::get_logger(), __VA_ARGS__);
#endif


#endif //AGS_LOGGING_HPP

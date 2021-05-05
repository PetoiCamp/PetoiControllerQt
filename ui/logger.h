#ifndef LOGGER_H
#define LOGGER_H

//#include <QtCore/qglobal.h>

//#if defined(LOGGER_LIBRARY)
//#  define LOGGERSHARED_EXPORT Q_DECL_EXPORT
//#else
//#  define LOGGERSHARED_EXPORT Q_DECL_IMPORT
//#endif


#include <QtCore>
#include <QTextStream>
#include <QIODevice>

namespace logger
{

#define MACRO_ROUTER(x, A, FUNC, ...)  FUNC


#define PRIVATE_LOG_FATAL_0()           (logger::Logger(__FILE__, __func__, __LINE__, logger::Fatal, true)).log()
#define PRIVATE_LOG_FATAL_1(logIf)      (logger::Logger(__FILE__, __func__, __LINE__, logger::Fatal, logIf)).log()
#define LOG_FATAL(...)                  MACRO_ROUTER(,##__VA_ARGS__, PRIVATE_LOG_FATAL_1(__VA_ARGS__), PRIVATE_LOG_FATAL_0(__VA_ARGS__))


#define PRIVATE_LOG_CRITICAL_0()        (logger::Logger(__FILE__, __func__, __LINE__, logger::Critical, true)).log()
#define PRIVATE_LOG_CRITICAL_1(logIf)   (logger::Logger(__FILE__, __func__, __LINE__, logger::Critical, logIf)).log()
#define LOG_CRITICAL(...)               MACRO_ROUTER(,##__VA_ARGS__, PRIVATE_LOG_CRITICAL_1(__VA_ARGS__), PRIVATE_LOG_CRITICAL_0(__VA_ARGS__))


#define PRIVATE_LOG_WARNING_0()         (logger::Logger(__FILE__, __func__, __LINE__, logger::Warning, true)).log()
#define PRIVATE_LOG_WARNING_1(logIf)    (logger::Logger(__FILE__, __func__, __LINE__, logger::Warning, logIf)).log()
#define LOG_WARNING(...)                MACRO_ROUTER(,##__VA_ARGS__, PRIVATE_LOG_WARNING_1(__VA_ARGS__), PRIVATE_LOG_WARNING_0(__VA_ARGS__))


#define PRIVATE_LOG_INFO_0()            (logger::Logger(__FILE__, __func__, __LINE__, logger::Info, true)).log()
#define PRIVATE_LOG_INFO_1(logIf)       (logger::Logger(__FILE__, __func__, __LINE__, logger::Info, logIf)).log()
#define LOG_INFO(...)                   MACRO_ROUTER(,##__VA_ARGS__, PRIVATE_LOG_INFO_1(__VA_ARGS__), PRIVATE_LOG_INFO_0(__VA_ARGS__))


#define PRIVATE_LOG_DEBUG_0()           (logger::Logger(__FILE__, __func__, __LINE__, logger::Debug, true)).log()
#define PRIVATE_LOG_DEBUG_1(logIf)      (logger::Logger(__FILE__, __func__, __LINE__, logger::Debug, logIf)).log()
#define LOG_DEBUG(...)                  MACRO_ROUTER(,##__VA_ARGS__, PRIVATE_LOG_DEBUG_1(__VA_ARGS__), PRIVATE_LOG_DEBUG_0(__VA_ARGS__))


#define PRIVATE_LOG_VERBOSE_0()         (logger::Logger(__FILE__, __func__, __LINE__, logger::Verbose, true)).log()
#define PRIVATE_LOG_VERBOSE_1(logIf)    (logger::Logger(__FILE__, __func__, __LINE__, logger::Verbose, logIf)).log()
#define LOG_VERBOSE(...)                MACRO_ROUTER(,##__VA_ARGS__, PRIVATE_LOG_VERBOSE_1(__VA_ARGS__), PRIVATE_LOG_VERBOSE_0(__VA_ARGS__))

    enum Level {
        Fatal, Critical, Warning, Info, Debug, Verbose
    };

    typedef struct LoggerCfg
    {
        bool logToConsole;
        bool flushImmediatly;
        logger::Level logLvl;
        QIODevice *logDest;
        QTextStream *logWriter;

        LoggerCfg(bool logToConsole, bool flushImmediatly, logger::Level logLvl, QIODevice *logDest);
        LoggerCfg(QIODevice *logDest);
        LoggerCfg();

        ~LoggerCfg();

    } LoggerCfg;

    class Logger
    {
    public:
        Logger(const std::string &clazz, const std::string &func, int line, Level lvl, bool logif);
        QDebug log();

        static void init(LoggerCfg *loggerCgf = NULL);
        static void destroy();
        static void msgHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg);

    private:
        QString msg;
        QString dummyStr;
        bool logif;

        static QTextStream cout;
        static LoggerCfg *cfg;
        static inline QString lvlName(Level level);
        static inline bool doLog(Level level);
        static inline QString removeQuotesIfLogHeader(const QString &);
    };
};

#endif // LOGGER_H


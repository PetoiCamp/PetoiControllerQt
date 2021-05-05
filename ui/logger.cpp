#include "ui/logger.h"

#include <QDateTime>
#include <QtCore/QDebug>

namespace logger
{

using namespace std;

logger::LoggerCfg *Logger::cfg = new LoggerCfg();
QTextStream Logger::cout(stdout, QIODevice::WriteOnly);

LoggerCfg::LoggerCfg(bool logToConsole, bool flushImmediatly, logger::Level logLvl, QIODevice *logDest) :
    logToConsole(logToConsole),
    flushImmediatly(flushImmediatly),
    logLvl(logLvl),
    logDest(logDest)
{
    if (logDest->open(QIODevice::WriteOnly | QIODevice::Append))
    {
        logWriter = new QTextStream(logDest);
    }
    else
    {
        throw "Can't open log device";
    }
}

LoggerCfg::LoggerCfg(QIODevice *logDest) :
    logToConsole(true),
    flushImmediatly(true),
    logLvl(logger::Verbose),
    logDest(logDest)
{
    if (logDest->open(QIODevice::WriteOnly | QIODevice::Append))
    {
        logWriter = new QTextStream(logDest);
    }
    else
    {
        throw "Can't open log device";
    }
}

LoggerCfg::LoggerCfg() :
    logToConsole(true),
    flushImmediatly(true),
    logLvl(logger::Verbose),
    logDest(NULL),
    logWriter(NULL)
{

}

LoggerCfg::~LoggerCfg()
{
    if (logWriter != NULL)
    {
        delete logWriter;
        logWriter = NULL;
    }
    if (logDest != NULL)
    {
        delete logDest;
        logDest = NULL;
    }
}

Logger::Logger(const string &clazz, const string &func, int line, Level lvl, bool logif) :
    logif(logif && doLog(lvl))
{
   if (this->logif)
   {
       msg =   "<LOG_HEADER>" +

               // the log level name
               lvlName(lvl) +

               // the current date time
               " {" + QDateTime::currentDateTime().toString(Qt::ISODate) + "} " +

               // class name
               "[" + QString::fromStdString(clazz) +

               // the function name
               "::" + QString::fromStdString(func) + "]#" +

               // the line number
               QString::number(line) + ":" +

               "</LOG_HEADER>";
   }
}

QDebug Logger::log()
{
    if (logif)
    {
        QDebug writer(QtDebugMsg);
        writer << msg;
        return writer;
    }
    else
    {
        QDebug writer(&dummyStr);
        return writer;
    }
}

void Logger::msgHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    Q_UNUSED(type);
    Q_UNUSED(context);

    if (cfg != NULL)
    {
        QString newMsg = removeQuotesIfLogHeader(msg);

        if (cfg->logToConsole)
        {
            cout << newMsg << "\n";

            if (cfg->flushImmediatly)
            {
                cout.flush();
            }
        }

        if (cfg->logWriter != NULL && cfg->logDest != NULL)
        {
            *cfg->logWriter << newMsg << "\n";

            if (cfg->flushImmediatly)
            {
                cfg->logWriter->flush();
            }
        }
    }
    else
    {
        throw "Configuration for logger is not instantiated, Logger::destroy was called prior to calling LOG_*";
    }
}

inline QString Logger::removeQuotesIfLogHeader(const QString &msg)
{
    if (msg.startsWith("\"<LOG_HEADER>"))
    {
        QString quotesRemoved(msg);
        quotesRemoved = quotesRemoved.remove(0, 13);
        return quotesRemoved.remove(quotesRemoved.indexOf("</LOG_HEADER>\""), 14);
    }
    return msg;
}

inline QString Logger::lvlName(Level level)
{
    switch(level)
    {
        case Fatal: return QString("***FATAL***");
        case Critical: return QString("**CRITICAL**");
        case Warning: return QString("*WARNING*");
        case Info: return QString("INFO");
        case Debug: return QString("DEBUG");
        case Verbose: return QString("VERBOSE");
        default: return QString("DEBUG");
    }
}

inline bool Logger::doLog(Level level)
{
    if (cfg != NULL)
    {
        return level <= cfg->logLvl;
    }
    throw "Configuration for logger is not instantiated, Logger::destroy was called prior to calling LOG_*";
}

void Logger::init(LoggerCfg *loggerCgf)
{
    if (loggerCgf != NULL)
    {
        destroy();
        Logger::cfg = loggerCgf;
    }

    qInstallMessageHandler(msgHandler);
}

void Logger::destroy()
{
    if (Logger::cfg != NULL)
    {
        delete Logger::cfg;
        Logger::cfg = NULL;
    }
}

}


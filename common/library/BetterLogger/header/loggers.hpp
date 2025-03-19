#pragma once

// #file: logger.hpp, header file
// #info: holds class definition and its method declorations for the logger class and its related variables and enums'
// #attach: betterLogger.hpp, internal dependency
// #attach: defaultLogStacks.hpp, internal includes

// project header
#include "betterLogger.hpp"
// built-in log stacks
#include "defaultLogStacks.hpp"
// logger format constants
#include "formats.hpp"

namespace worTech::betterLogger::loggers{
    
    // #namespace: defaultFormats(deflt), variable namespace
    // #scope: loggers, component namespace
    // #info: holds default values for loggers
    // #uses: FormatType, enum class
    // #uses: logFormatting, variable namespace
    namespace defaultFormats{
        const std::array<Format, log::FORMAT_SIZE> FORMAT_ORDER = {
            Format::LOGGER,
            Format::TIME,
            Format::LEVEL,
            Format::MESSAGE,
            Format::LOCATION
        };
        const bool USES_BOLD = true;
    }
    // #class: Logger, abstract singleton class 
    // #info: interface singleton class for loggers
    // #scope: loggers, component namespace
    // #uses: LogLevel, enum class
    class Logger{
    public:
    // #div: public factory methods
        virtual ~Logger() = default;
    // #div: public static methods
        template<class T_derived> static Logger& get();
    // #div: public methods
        const Logger& log(const std::string& p_message)const;
        const Logger& log(const std::string& p_message, const std::source_location& p_location)const;
        const Logger& log(const std::string& p_message, const time_t& p_time)const;
        const Logger& log(const std::string& p_message, const std::source_location& p_location, const time_t& p_time)const;
        const Logger& log(std::string&& p_message)const;
        const Logger& log(std::string&& p_message, const std::source_location& p_location)const;
        const Logger& log(std::string&& p_message, const time_t& p_time)const;
        const Logger& log(std::string&& p_message, const std::source_location& p_location, const time_t& p_time)const;
        template<Level t_logLevel> const Logger& log(const std::string& p_message)const;
        template<Level t_logLevel> const Logger& log(const std::string& p_message, const std::source_location& p_location)const;
        template<Level t_logLevel> const Logger& log(const std::string& p_message, const time_t& p_time)const;
        template<Level t_logLevel> const Logger& log(const std::string& p_message, const std::source_location& p_location, 
            const time_t& p_time)const;
        template<Level t_logLevel> const Logger& log(std::string&& p_message)const;
        template<Level t_logLevel> const Logger& log(std::string&& p_message, const std::source_location& p_location)const;
        template<Level t_logLevel> const Logger& log(std::string&& p_message, const time_t& p_time)const;
        template<Level t_logLevel> const Logger& log(std::string&& p_message, const std::source_location& p_location, const time_t& p_time)const;
    protected:
    // #div: protected factory methods
        Logger(const std::string& p_name);
        Logger(const std::string& p_name, const std::array<Format, log::FORMAT_SIZE>& p_formatOrder);
        Logger(const std::string& p_name, bool p_usesBold);
        Logger(const std::string& p_name, const std::array<Format, log::FORMAT_SIZE>& p_formatOrder, bool p_usesBold);
        Logger(std::string&& p_name);
        Logger(std::string&& p_name, const std::array<Format, log::FORMAT_SIZE>& p_formatOrder);
        Logger(std::string&& p_name, bool p_usesBold);
        Logger(std::string&& p_name, const std::array<Format, log::FORMAT_SIZE>& p_formatOrder, bool p_usesBold);
        Logger(const Logger&) = delete;
        Logger(Logger&&) = delete;
    // #div: protected operators
        Logger& operator=(const Logger&) = delete;
        Logger& operator=(Logger&&) = delete;
    // #div: protected members
        std::string m_name;
        std::array<Format, log::FORMAT_SIZE> m_formatOrder = deflt::FORMAT_ORDER;
        bool m_usesBold = deflt::USES_BOLD;
    // #div: protected methods
        virtual const Logger& sendLog(std::string&& p_log)const;
        virtual std::string formatLogger(const Level p_logLevel)const;
        virtual std::string formatLevel(const Level p_logLevel)const;
        virtual std::string formatTime(const Level p_logLevel, const time_t& p_time)const;
        virtual std::string formatMessage(const Level p_logLevel, const std::string& p_message)const;
        virtual std::string formatMessage(const Level p_logLevel, std::string&& p_message)const;
        virtual std::string formatLocation(const Level p_logLevel, const std::source_location& p_location)const;
        virtual std::string getLogColor(const Level p_logLevel)const;
        virtual std::string getLogColorBold(const Level p_logLevel)const;
        virtual std::string getLogLevelName(const Level p_logLevel)const;
        template<Level t_logLevel> std::string formatLog(const std::string& p_message, const std::optional<std::source_location> p_location, 
            const std::optional<time_t> p_time)const;
        template<Level t_logLevel> std::string formatLog(std::string&& p_message, const std::optional<std::source_location> p_location, 
            const std::optional<time_t> p_time)const;
    }; 
    
}
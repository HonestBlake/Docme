#include "better/logger.hpp"

class TestLogger: public btr::Logger{
public:
    TestLogger(): Logger("Test", false){}
private:
    const Logger& sendLog(std::string&& p_log)const override{
        btr::LogStack::get<btr::TerminateFlush>().pushLog(std::forward<std::string>(p_log));
        return *this;
    }
};

class TestDebugLogger: public btr::Logger{
public:
    TestDebugLogger(): Logger("TestDebug", {btr::Format::TIME, btr::Format::LOGGER, btr::Format::LEVEL, btr::Format::MESSAGE, 
        btr::Format::LOCATION}){}
private:
    const Logger& sendLog(std::string&& p_log)const override{
        btr::LogStack::get<btr::AutoFlush>().pushLog(std::forward<std::string>(p_log));
        return *this;
    }
};

int main(){
    std::string test = "test log on built in main logger";

    btr::Logger::get<btr::Main>().log(test);
    btr::Logger::get<btr::Debug>().log<btr::Level::ERROR>("test log on built in debug logger");
    btr::Logger::get<TestDebugLogger>().log<btr::Level::INFO>("test log on custom debug logger", btr::Help::getCurrentTime());
    btr::Logger::get<TestDebugLogger>().log<btr::Level::TRACE>("test log on custom debug logger", std::source_location::current());
    btr::Logger::get<TestLogger>().log<btr::Level::WARNING>("test log on custom logger with end flush");
    btr::Logger::get<TestLogger>().log<btr::Level::ERROR>("test log on custom logger with end flush", std::source_location::current(), btr::Help::getCurrentTime());
    btr::Logger::get<TestDebugLogger>().log<btr::Level::CRITICAL>("test log on custom debug logger", std::source_location::current());

    return EXIT_SUCCESS;
}
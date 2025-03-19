#include "cdocs.hpp"
#include "helpers.hpp"

// #include "better/logger.hpp"


// class CDocTracer: public btr::Logger{
// public:
//     CDocTracer(): btr::Logger("CDoc Tracer", {btr::Format::LOGGER, btr::Format::LEVEL, btr::Format::LOCATION, btr::Format::TIME, btr::Format::MESSAGE}){}
// private:
//     std::string formatLocation(const btr::Level p_logLevel, const std::source_location& p_location)const override{
//         return getLogColor(p_logLevel) + p_location.function_name() + btr::log::SPACE + btr::ansii::RESET;
//     }
// };

// void trace(std::source_location&& p_location){
//     btr::Logger::get<CDocTracer>().log<btr::Level::TRACE>("", std::forward<std::source_location>(p_location), btr::Help::getCurrentTime());
// }

int main(int argc, char** argv){

    // btr::Logger::get<CDocTracer>().log<btr::Level::TRACE>("", std::source_location::current(), btr::Help::getCurrentTime());

    // another test

    std::vector<std::string> fileLocations = {"genorator/include/nodes.hpp"};
    std::string outputLocation = "g";
    cdoc::Genorator::getInstance().setLocations(argc, argv).parseProgramFiles().generateDocumentation();
    return 0;
}
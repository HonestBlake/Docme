// #file: packetManager.cpp, source file

#include "docPackets.hpp"

#include "jsonTools.hpp" // include jsonTools module

namespace worTech::docme::genorator::docPackets{

// public factory methods

    DocPacket::DocPacket(std::string&& p_name, std::unordered_set<std::string>&& p_fileTypes): m_name(std::forward<std::string>(p_name)), m_fileTypes(std::forward<std::unordered_set<std::string>>(p_fileTypes)){
        if constexpr(state::TRACING){ // Function tracing
            debug::trace(std::source_location::current());
        }
    } 

// public operators

    // #func: operator==(), public inline const noexcept method

    // #param: const DocPacket& p_packet, given packet
    // #return: bool, weather packets have same name
    bool DocPacket::operator==(const DocPacket& p_packet)const noexcept{
        if constexpr(state::TRACING){ // Function tracing
            debug::trace(std::source_location::current());
        }
        return m_name == p_packet.name();
    }

// public static methods

    // #func: get(const std::string&), public static noexcept method

    // #param: const std::string& p_packetName, given packet name
    // #return: DocPacket, constructed packet object
    DocPacket DocPacket::get(const std::string& p_packetName)noexcept{
        if constexpr(state::TRACING){ // Function tracing
            debug::trace(std::source_location::current());
        }
        const std::filesystem::path filePath = packet::PATH_TO_PACKETS / std::filesystem::path(p_packetName + packet::FILE_EXTENSION); // Create path to json file
        std::cout << filePath.string() << std::endl; // Debugging output
        // parse json file
        std::expected<Json, std::string> jsonResult = Json::parse(filePath);
        if(!jsonResult){ // Check if error parsing json file
            debug::error(jsonResult.error());
        }
        const Json json = jsonResult.value();
        // get name from json
        std::expected<std::string, std::string> nameResult = json.getString(packetFileKeys::NAME);
        if(!nameResult){ // Check if error getting name from json
            debug::error(nameResult.error());
        }
        // get file types from json
        std::expected<std::unordered_set<std::string>, std::string> fileTypesResult = json.getUnorderedSet(packetFileKeys::FILE_TYPES);
        if(!fileTypesResult){ // Check if error getting file types from json
            debug::error(fileTypesResult.error());
        }
        return DocPacket(std::move(nameResult.value()), std::move(fileTypesResult.value())); // return constructed Packet
    }   

// public methods

    // #func: hash(), public inline const noexcept method

    // #return: size_t, hash of packet name
    size_t DocPacket::hash()const noexcept{
        if constexpr(state::TRACING){ // Function tracing
            debug::trace(std::source_location::current());
        }
        return std::hash<std::string>{}(m_name);
    }
    // #func: name(), public inline const noexcept method

    // #return: const std::string&, reference to packet name
    const std::string& DocPacket::name()const noexcept{
        if constexpr(state::TRACING){ // Function tracing
            debug::trace(std::source_location::current());
        }
        return m_name;
    }
    // #func: fileTypes(), public inline const noexcept method

    // #return: const std::unordered_set<std::string>&, reference to file types
    const std::unordered_set<std::string>& DocPacket::fileTypes()const noexcept{
        if constexpr(state::TRACING){ // Function tracing
            debug::trace(std::source_location::current());
        }
        return m_fileTypes;
    }

} // namespace worTech::docme::genorator::packetManager

namespace std{

    // #func: operator(), public inline const noexcept method
    
    // #param: const docme::DocPacket& p_packet, given packet
    // #return: std::size_t, hash of packet
    std::size_t hash<docme::DocPacket>::operator()(const docme::DocPacket& p_packet)const noexcept{
        if constexpr(docme::state::TRACING){ // Function tracing
            docme::debug::trace(std::source_location::current());
        }
        return p_packet.hash();
    }

} // namespace std
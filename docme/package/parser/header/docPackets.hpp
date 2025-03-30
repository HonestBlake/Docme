// #file: packetManager.hpp, header file

#pragma once

#include "parser.hpp"

namespace worTech::docme::genorator::docPackets{

    // #namespace: packetVariables(packet), inline variable namespace
    namespace packetVariables{
        const std::string PATH_TO_PACKETS = "../docme/resource/doc packets/";
        constexpr std::string DOCME = "docme";
        constexpr std::string FILE_EXTENSION = ".json";
    }
    // #namespace: packetFileKeys(key), inline variable namespace
    namespace packetFileKeys{
        constexpr std::string NAME = "packet_name";
        const std::string FILE_TYPES = "accepted_file_types";
    }
    // #class: DocPacket(Packet), class object
    class DocPacket{
    public:
    // public factory methods
        DocPacket(std::string&& p_name, std::unordered_set<std::string>&& p_fileTypes); 
    // public operators
        bool operator==(const DocPacket& p_packet)const noexcept;
    // public static methods
        static DocPacket get(const std::string& p_packetName)noexcept;
    // public methods
        size_t hash()const noexcept;
        const std::string& name()const noexcept;
        const std::unordered_set<std::string>& fileTypes()const noexcept;
    private:
    // private members
        std::string m_name;
        std::unordered_set<std::string> m_fileTypes;
    };

} // namespace worTech::docme::genorator::packetManager

namespace std{

    // #struct: hash<docme::DocPacket>, hash structure
    template<> struct hash<docme::DocPacket>{
        size_t operator()(const docme::DocPacket& p_packet)const noexcept;
    };

} // namespace std
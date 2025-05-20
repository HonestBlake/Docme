// #file: packetManager.hpp, header file

#pragma once

#include "processor.hpp"

namespace worTech::docme::processor::docPackets{

    // #namespace: packetVariables(packet), inline variable namespace
    namespace packetVariables{
        const std::filesystem::path PATH_TO_PACKETS = std::filesystem::path(std::source_location::current().file_name()).parent_path().parent_path().parent_path().parent_path() / std::filesystem::path("resource/doc packets/");
        constexpr std::string DOCME = "docme";
        constexpr std::string FILE_EXTENSION = ".json";
    }
    // #namespace: packetFileKeys(key), inline variable namespace
    namespace packetFileKeys{
        constexpr std::string NAME = "packet_name";
        const std::string FILE_TYPES = "accepted_file_types";
    }
    // #struct: MultiLineComment, data structure
    struct MultiLineComment{
        std::string start;
        std::string end;
    };
    // #class: DocPacket(Packet), class object
    // TODO support new additions with getters and setters
    // TODO add parsing and building for new additions
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
        std::unordered_set<std::string> m_singleComment;
        std::unordered_set<MultiLineComment> m_multiComment;
        std::unordered_set<std::string> m_documentationTag;
    };

} // namespace worTech::docme::generator::packetManager

namespace std{

    // #struct: hash<docme::DocPacket>, hash structure
    template<> struct hash<docme::DocPacket>{
        std::size_t operator()(const docme::DocPacket& p_packet)const noexcept;
    };

} // namespace std
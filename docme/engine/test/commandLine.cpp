// #file: commandLine.cpp, Module test file

#include <gtest/gtest.h> // #include gtest/gtest.h, External library

#define private public
#include "docme/header/commandLine.hpp" // #include commandLine.hpp, Module header
#undef private

#include "header/debugging.hpp" // #include debugging.hpp, Module header


namespace worTech::docme::commandLine{

    TEST(CommandLineTest, FlagComparison){
        CommandLineFlagComparer comparer;
        EXPECT_TRUE(comparer(Flag::CONFIG_FILE, Flag::ROOT_DIR)) << "Flag::CONFIG_FILE should be before Flag::ROOT_DIR";
        EXPECT_FALSE(comparer(Flag::ROOT_DIR, Flag::CONFIG_FILE)) << "Flag::ROOT_DIR should be after Flag::CONFIG_FILE";
        EXPECT_TRUE(comparer(Flag::ROOT_DIR, Flag::DOC_PACKET)) << "Flag::ROOT_DIR should be before Flag::DOC_PACKET";
        EXPECT_FALSE(comparer(Flag::DOC_PACKET, Flag::ROOT_DIR)) << "Flag::DOC_PACKET should be after Flag::ROOT_DIR"; 
        EXPECT_TRUE(comparer(Flag::DOC_PACKET, Flag::OUTPUT_DIRECTORY)) << "Flag::DOC_PACKET should be before Flag::OUTPUT_DIRECTORY";
        EXPECT_FALSE(comparer(Flag::OUTPUT_DIRECTORY, Flag::DOC_PACKET)) << "Flag::OUTPUT_DIRECTORY should be after Flag::DOC_PACKET";
        EXPECT_TRUE(comparer(Flag::OUTPUT_DIRECTORY, Flag::SOURCE)) << "Flag::OUTPUT_DIRECTORY should be before Flag::SOURCE";
        EXPECT_FALSE(comparer(Flag::SOURCE, Flag::OUTPUT_DIRECTORY)) << "Flag::SOURCE should be after Flag::OUTPUT_DIRECTORY";
        EXPECT_TRUE(comparer(Flag::SOURCE, Flag::IGNORE)) << "Flag::SOURCE should be before Flag::IGNORE";
        EXPECT_FALSE(comparer(Flag::IGNORE, Flag::SOURCE)) << "Flag::IGNORE should be after Flag::SOURCE";
    }

    TEST(CommandLineTest, Get){
        EXPECT_DEATH(CommandLineParser::get(), error::COMMAND_LINE_NOT_INITIALIZED_WITH_ARGS) << "CommandLineParser::get() should fail first call without arguments";
        int argc = 2;
        const char* argv[] = {"docme", "--help"};
        CommandLineParser::get(argc, const_cast<char**>(argv));
        CommandLineParser::get();
    }

    TEST(CommandLineTest, Construction){
        int argc = 3;
        const char* argv[] = {"docme", "--help", "--version"};

        EXPECT_DEATH(CommandLineParser(2, nullptr), error::NULL_COMMAND_LINE_ARGUMENTS) << "CommandLineParser should fail with null arguments";
        EXPECT_DEATH(CommandLineParser(1, const_cast<char**>(argv)), error::NO_COMMAND_LINE_ARGUMENTS) << "CommandLineParser should fail with zero arguments";

        CommandLineParser parser = CommandLineParser(argc, const_cast<char**>(argv));
        EXPECT_TRUE(parser.s_isInitialized) << "CommandLineParser should be initialized after construction";
        EXPECT_EQ(parser.m_args.size(), 2) << "CommandLineParser should have two arguments";
        EXPECT_EQ(parser.m_args[0], "--help") << "First argument should be --help";
        EXPECT_EQ(parser.m_args[1], "--version") << "Second argument should be --version";
        EXPECT_EQ(parser.m_rootDirectory, std::filesystem::current_path()) << "Default root directory should be current path";
    }

    TEST(CommandLineTest, Parse){

        const char* argv[] = {"docme", "--help", "--version"};
        CommandLineParser parser = CommandLineParser(3, const_cast<char**>(argv));
        EXPECT_DEATH(parser.parse(), "Cannot use any other arguments or flags when using special flag:") << "Should fail to parser with with other args with special flag";

        const char* argv2[] = {"docme", "--configure"};
        CommandLineParser parser2 = CommandLineParser(2, const_cast<char**>(argv2));
        parser2.parse(); // should not fail

        const char* argv3[] = {"docme", "test.cpp"};
        CommandLineParser parser3 = CommandLineParser(2, const_cast<char**>(argv3));
        EXPECT_DEATH(parser3.parse(), "Command line argument has no flag:") << "Should fail to parse with no flags";

        const char* argv4[] = {"docme", "-s", "test.cpp"};
        CommandLineParser parser4 = CommandLineParser(3, const_cast<char**>(argv4));
        parser4.parse(); // should not fail

        // const char* argv5[] = {"docme", "-c", "config","-r", "root", "-o", "output", "-p", "docme", "-s", "test.cpp", "-i", "ignore.cpp"};
        // CommandLineParser parser5 = CommandLineParser(8, const_cast<char**>(argv5));
        // parser5.parse();
    }

}
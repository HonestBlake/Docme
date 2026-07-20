// #FILE: parser.cpp, Component Source File
// #BRIEF: Source file for parser component

module;

#include "generator.hpp" // #INCLUDE: generator.hpp, Package wide header

module docme.generator; // #IMPLEMENTS: docme.generator:parser
import :parser;

namespace docme::generator{ // #SCOPE: docme::generator

// ------------------------------------------------------------------------
//                                 class Parser
// ------------------------------------------------------------------------

// #SCOPE: Parser

// #DIV: Public

// ---- Public Static Methods ----

    // #METHOD: build(ParserContext&&), Static Method
    // #BRIEF: Builds a parser from the given parser context
    // #PARAM: ParserContext&& p_context, The parser context to build the parser from
    // #RETURN: Parser>, The built parser
    Parser Parser::build(ParserContext&& p_context){
        return Parser(std::move(p_context));
    } // #END: build(ParserContext&&)


// ---- Public Methods ----

    // #METHOD: parse(), Method
    // #BRIEF: Parses the given parser context
    // #RETURN: Result<>, Void on successful parsing, Error on failure
    Result<> Parser::parse(){
        logger.info("Parsing");
        return {};  
    } // #END: parse()


// #DIV: Private

// ---- Private Special Methods ----

    // #METHOD: Parser(ParserContext&&), Constructor
    // #BRIEF: Constructs a parser from the given parser context
    // #PARAM: ParserContext&& p_context, The parser context to construct the parser from
    Parser::Parser(ParserContext&& p_context): m_context(std::move(p_context)){

    } // #END: Parser(ParserContext&&)

} // #END: docme::generator

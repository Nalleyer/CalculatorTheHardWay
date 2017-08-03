//
// Created by Nalley on 2017/7/27.
//

#include <iostream>
#include "lexer.h"

using std::string;

Lexer::Lexer()
    : mColumn(0)
    , mNumLine(0)
{
}

std::vector<Token> Lexer::getTokens()
{
    return mTokens;
}

void Lexer::runLexer(const std::string &input)
{
    clear();
    auto nowState = State::INIT;
    string nowStr = "";
    auto lastLine = mNumLine;
    auto lastColumn = mColumn;
    for(auto i = 0; i < input.length() + 1; i++)
    {
        char ch = ( i== input.length() ) ? '\0' : input.at(i) ;
        CharType cht;
        try
        {
            cht = charType( ch );
        }
        catch ( std::invalid_argument & e)
        {
            error(e.what());
        }
        catch (...)
        {
            error("unkown error");
        }

        auto outPair = mLexerTable.at(std::make_pair(nowState, cht));
        if ( outPair.second == TokenType::BAD_TOKEN )
        {
            error("bad token !");
        }
        else if ( outPair.second != TokenType::NO_TOKEN )
        {
            mTokens.emplace_back(Token{outPair.second, nowStr, lastLine + 1, lastColumn - nowStr.length() + 2});
            nowStr = "";
        }

        if ( ch != ' ')
        {
            nowStr.push_back(ch);
        }
        nowState = outPair.first;

        lastLine = mNumLine;
        lastColumn = mColumn;
        updatePosition(nowState);
    }
}

void Lexer::updatePosition(const State &nowState)
{
    mColumn++;
    if ( nowState == State::ENDL )
    {
        mNumLine++;
        mColumn = 0;
    }
}

/*
std::vector<string> Lexer::getTokens()
{

}
 */

void Lexer::clear()
{
    mColumn = 0;
    mNumLine = 0;
}

CharType Lexer::charType(char ch)
{
    switch(ch)
    {
        case '\0' : return CharType::END;
        case ' '  : return CharType::SPACE;
        case '\n' : return CharType::ENDL;
        case '+'  : return CharType::ADD;
        case '-'  : return CharType::SUB;
        case '*'  : return CharType::MUL;
        case '/'  : return CharType::DIV;
        case '('  : return CharType::LP;
        case ')'  : return CharType::RP;
        case '.'  : return CharType::POINT;
        case '='  : return CharType::ASN;
        default   :
        {
            if ('0' <= ch and ch <= '9')
            {
                return CharType::NUM;
            }
            if (    ('a' <= ch and ch <= 'z')
                      or ('A' <= ch and ch <= 'Z') )
            {
                return CharType::WORD;
            }
            else
            {
                string info = "char ";
                info += ch;
                info += " is unacceptable";
                throw std::invalid_argument(info);
            }
        }
    }
}

void Lexer::error(const std::string &info)
{
    std::cerr << "on line " << mNumLine + 1 << ", column " << mColumn + 1 << ":\n";
    std::cerr << info << '\n';
    exit(1);
}


const std::unordered_map< MapInType, MapOUtType, pair_hash > Lexer::mLexerTable{
        /* init */
        { {State::INIT, CharType::END},   {State::OVER, TokenType::NO_TOKEN}},
        { {State::INIT, CharType::SPACE}, {State::INIT,      TokenType::NO_TOKEN} },
        { {State::INIT, CharType::ENDL},  {State::ENDL,      TokenType::NO_TOKEN} },
        { {State::INIT, CharType::ADD},   {State::ADD,       TokenType::NO_TOKEN} },
        { {State::INIT, CharType::SUB},   {State::SUB,       TokenType::NO_TOKEN} },
        { {State::INIT, CharType::MUL},   {State::MUL,       TokenType::NO_TOKEN} },
        { {State::INIT, CharType::DIV},   {State::DIV,       TokenType::NO_TOKEN} },
        { {State::INIT, CharType::LP},    {State::LP,        TokenType::NO_TOKEN} },
        { {State::INIT, CharType::RP},    {State::RP,        TokenType::NO_TOKEN} },
        { {State::INIT, CharType::NUM},   {State::NUM_INT,   TokenType::NO_TOKEN} },
        { {State::INIT, CharType::POINT}, {State::POINT_FNT, TokenType::NO_TOKEN} },
        { {State::INIT, CharType::WORD},  {State::VAR,       TokenType::NO_TOKEN} },
        { {State::INIT, CharType::ASN},   {State::ASN,       TokenType::NO_TOKEN} },
        /* add */
        { {State::ADD, CharType::END},   {State::OVER,      TokenType::ADD} },
        { {State::ADD, CharType::SPACE}, {State::INIT,       TokenType::ADD} },
        { {State::ADD, CharType::ENDL},  {State::ENDL,      TokenType::ADD} },
        { {State::ADD, CharType::ADD},   {State::ADD,       TokenType::ADD} },
        { {State::ADD, CharType::SUB},   {State::SUB,       TokenType::ADD} },
        { {State::ADD, CharType::MUL},   {State::MUL,       TokenType::ADD} },
        { {State::ADD, CharType::DIV},   {State::DIV,       TokenType::ADD} },
        { {State::ADD, CharType::LP},    {State::LP,        TokenType::ADD} },
        { {State::ADD, CharType::RP},    {State::RP,        TokenType::ADD} },
        { {State::ADD, CharType::NUM},   {State::NUM_INT,   TokenType::ADD} },
        { {State::ADD, CharType::POINT}, {State::POINT_FNT, TokenType::ADD} },
        { {State::ADD, CharType::WORD},  {State::VAR,       TokenType::ADD} },
        { {State::ADD, CharType::ASN},   {State::ASN,       TokenType::ADD} },
        /* sub */
        { {State::SUB, CharType::END},   {State::OVER,      TokenType::SUB} },
        { {State::SUB, CharType::SPACE}, {State::INIT,      TokenType::SUB} },
        { {State::SUB, CharType::ENDL},  {State::ENDL,      TokenType::SUB} },
        { {State::SUB, CharType::ADD},   {State::ADD,       TokenType::SUB} },
        { {State::SUB, CharType::SUB},   {State::SUB,       TokenType::SUB} },
        { {State::SUB, CharType::MUL},   {State::MUL,       TokenType::SUB} },
        { {State::SUB, CharType::DIV},   {State::DIV,       TokenType::SUB} },
        { {State::SUB, CharType::LP},    {State::LP,        TokenType::SUB} },
        { {State::SUB, CharType::RP},    {State::RP,        TokenType::SUB} },
        { {State::SUB, CharType::NUM},   {State::NUM_INT,   TokenType::SUB} },
        { {State::SUB, CharType::POINT}, {State::POINT_FNT, TokenType::SUB} },
        { {State::SUB, CharType::WORD},  {State::VAR,       TokenType::SUB} },
        { {State::SUB, CharType::ASN},   {State::ASN,       TokenType::SUB} },
        /* mul */
        { {State::MUL, CharType::END},   {State::OVER,      TokenType::MUL} },
        { {State::MUL, CharType::SPACE}, {State::INIT,      TokenType::MUL} },
        { {State::MUL, CharType::ENDL},  {State::ENDL,      TokenType::MUL} },
        { {State::MUL, CharType::ADD},   {State::ADD,       TokenType::MUL} },
        { {State::MUL, CharType::SUB},   {State::SUB,       TokenType::MUL} },
        { {State::MUL, CharType::MUL},   {State::MUL,       TokenType::MUL} },
        { {State::MUL, CharType::DIV},   {State::DIV,       TokenType::MUL} },
        { {State::MUL, CharType::LP},    {State::LP,        TokenType::MUL} },
        { {State::MUL, CharType::RP},    {State::RP,        TokenType::MUL} },
        { {State::MUL, CharType::NUM},   {State::NUM_INT,   TokenType::MUL} },
        { {State::MUL, CharType::POINT}, {State::POINT_FNT, TokenType::MUL} },
        { {State::MUL, CharType::WORD},  {State::VAR,       TokenType::MUL} },
        { {State::MUL, CharType::ASN},   {State::ASN,       TokenType::MUL} },
        /* div */
        { {State::DIV, CharType::END},   {State::OVER,      TokenType::DIV} },
        { {State::DIV, CharType::SPACE}, {State::INIT,      TokenType::DIV} },
        { {State::DIV, CharType::ENDL},  {State::ENDL,      TokenType::DIV} },
        { {State::DIV, CharType::ADD},   {State::ADD,       TokenType::DIV} },
        { {State::DIV, CharType::SUB},   {State::SUB,       TokenType::DIV} },
        { {State::DIV, CharType::MUL},   {State::MUL,       TokenType::DIV} },
        { {State::DIV, CharType::DIV},   {State::DIV,       TokenType::DIV} },
        { {State::DIV, CharType::LP},    {State::LP,        TokenType::DIV} },
        { {State::DIV, CharType::RP},    {State::RP,        TokenType::DIV} },
        { {State::DIV, CharType::NUM},   {State::NUM_INT,   TokenType::DIV} },
        { {State::DIV, CharType::POINT}, {State::POINT_FNT, TokenType::DIV} },
        { {State::DIV, CharType::WORD},  {State::VAR,       TokenType::DIV} },
        { {State::DIV, CharType::ASN},   {State::ASN,       TokenType::DIV} },
        /* left par */
        { {State::LP, CharType::END},   {State::OVER,      TokenType::LEFT_PAR} },
        { {State::LP, CharType::SPACE}, {State::INIT,      TokenType::LEFT_PAR} },
        { {State::LP, CharType::ENDL},  {State::ENDL,      TokenType::LEFT_PAR} },
        { {State::LP, CharType::ADD},   {State::ADD,       TokenType::LEFT_PAR} },
        { {State::LP, CharType::SUB},   {State::SUB,       TokenType::LEFT_PAR} },
        { {State::LP, CharType::MUL},   {State::MUL,       TokenType::LEFT_PAR} },
        { {State::LP, CharType::DIV},   {State::DIV,       TokenType::LEFT_PAR} },
        { {State::LP, CharType::LP},    {State::LP,        TokenType::LEFT_PAR} },
        { {State::LP, CharType::RP},    {State::RP,        TokenType::LEFT_PAR} },
        { {State::LP, CharType::NUM},   {State::NUM_INT,   TokenType::LEFT_PAR} },
        { {State::LP, CharType::POINT}, {State::POINT_FNT, TokenType::LEFT_PAR} },
        { {State::LP, CharType::WORD},  {State::VAR,       TokenType::LEFT_PAR} },
        { {State::LP, CharType::ASN},   {State::ASN,       TokenType::LEFT_PAR} },
        /* right par */
        { {State::RP, CharType::END},   {State::OVER,      TokenType::RIGHT_PAR} },
        { {State::RP, CharType::SPACE}, {State::INIT,      TokenType::RIGHT_PAR} },
        { {State::RP, CharType::ENDL},  {State::ENDL,      TokenType::RIGHT_PAR} },
        { {State::RP, CharType::ADD},   {State::ADD,       TokenType::RIGHT_PAR} },
        { {State::RP, CharType::SUB},   {State::SUB,       TokenType::RIGHT_PAR} },
        { {State::RP, CharType::MUL},   {State::MUL,       TokenType::RIGHT_PAR} },
        { {State::RP, CharType::DIV},   {State::DIV,       TokenType::RIGHT_PAR} },
        { {State::RP, CharType::LP},    {State::LP,        TokenType::RIGHT_PAR} },
        { {State::RP, CharType::RP},    {State::RP,        TokenType::RIGHT_PAR} },
        { {State::RP, CharType::NUM},   {State::NUM_INT,   TokenType::RIGHT_PAR} },
        { {State::RP, CharType::POINT}, {State::POINT_FNT, TokenType::RIGHT_PAR} },
        { {State::RP, CharType::WORD},  {State::VAR,       TokenType::RIGHT_PAR} },
        { {State::RP, CharType::ASN},   {State::ASN,       TokenType::RIGHT_PAR} },
        /* num integer part */
        { {State::NUM_INT, CharType::END},     {State::OVER,      TokenType::NUMBER} },
        { {State::NUM_INT, CharType::SPACE},   {State::INIT,      TokenType::NUMBER} },
        { {State::NUM_INT, CharType::ENDL},    {State::ENDL,      TokenType::NUMBER} },
        { {State::NUM_INT, CharType::ADD},     {State::ADD,       TokenType::NUMBER} },
        { {State::NUM_INT, CharType::SUB},     {State::SUB,       TokenType::NUMBER} },
        { {State::NUM_INT, CharType::MUL},     {State::MUL,       TokenType::NUMBER} },
        { {State::NUM_INT, CharType::DIV},     {State::DIV,       TokenType::NUMBER} },
        { {State::NUM_INT, CharType::LP},      {State::LP,        TokenType::NUMBER} },
        { {State::NUM_INT, CharType::RP},      {State::RP,        TokenType::NUMBER} },
        { {State::NUM_INT, CharType::NUM},     {State::NUM_INT,   TokenType::NO_TOKEN} },
        { {State::NUM_INT, CharType::POINT},   {State::POINT_NML, TokenType::NO_TOKEN} },
        { {State::NUM_INT, CharType::WORD},    {State::OVER,      TokenType::BAD_TOKEN} },
        { {State::NUM_INT, CharType::ASN},     {State::ASN,       TokenType::NUMBER} },
        /* front point */
        { {State::POINT_FNT, CharType::END},     {State::OVER,    TokenType::BAD_TOKEN} },
        { {State::POINT_FNT, CharType::SPACE},   {State::OVER,    TokenType::BAD_TOKEN} },
        { {State::POINT_FNT, CharType::ENDL},    {State::OVER,    TokenType::BAD_TOKEN} },
        { {State::POINT_FNT, CharType::ADD},     {State::OVER,    TokenType::BAD_TOKEN} },
        { {State::POINT_FNT, CharType::SUB},     {State::OVER,    TokenType::BAD_TOKEN} },
        { {State::POINT_FNT, CharType::MUL},     {State::OVER,    TokenType::BAD_TOKEN} },
        { {State::POINT_FNT, CharType::DIV},     {State::OVER,    TokenType::BAD_TOKEN} },
        { {State::POINT_FNT, CharType::LP},      {State::OVER,    TokenType::BAD_TOKEN} },
        { {State::POINT_FNT, CharType::RP},      {State::OVER,    TokenType::BAD_TOKEN} },
        { {State::POINT_FNT, CharType::NUM},     {State::NUM_INT, TokenType::NO_TOKEN} },
        { {State::POINT_FNT, CharType::POINT},   {State::OVER,    TokenType::BAD_TOKEN} },
        { {State::POINT_FNT, CharType::WORD},    {State::OVER,    TokenType::BAD_TOKEN} },
        { {State::POINT_FNT, CharType::ASN},     {State::OVER,    TokenType::BAD_TOKEN} },
        /* normal point, which is after number */
        { {State::POINT_NML, CharType::END},     {State::OVER,      TokenType::NUMBER} },
        { {State::POINT_NML, CharType::SPACE},   {State::INIT,      TokenType::NUMBER} },
        { {State::POINT_NML, CharType::ENDL},    {State::ENDL,      TokenType::NUMBER} },
        { {State::POINT_NML, CharType::ADD},     {State::ADD,       TokenType::NUMBER} },
        { {State::POINT_NML, CharType::SUB},     {State::SUB,       TokenType::NUMBER} },
        { {State::POINT_NML, CharType::MUL},     {State::MUL,       TokenType::NUMBER} },
        { {State::POINT_NML, CharType::DIV},     {State::DIV,       TokenType::NUMBER} },
        { {State::POINT_NML, CharType::LP},      {State::LP,        TokenType::NUMBER} },
        { {State::POINT_NML, CharType::RP},      {State::RP,        TokenType::NUMBER} },
        { {State::POINT_NML, CharType::NUM},     {State::NUM_DEC,   TokenType::NO_TOKEN} },
        { {State::POINT_NML, CharType::POINT},   {State::OVER,      TokenType::BAD_TOKEN} },
        { {State::POINT_NML, CharType::WORD},    {State::OVER,      TokenType::BAD_TOKEN} },
        { {State::POINT_NML, CharType::ASN},     {State::ASN,       TokenType::NUMBER} },
        /* number, decimal part */
        { {State::NUM_DEC, CharType::END},     {State::OVER,      TokenType::NUMBER} },
        { {State::NUM_DEC, CharType::SPACE},   {State::INIT,      TokenType::NUMBER} },
        { {State::NUM_DEC, CharType::ENDL},    {State::ENDL,      TokenType::NUMBER} },
        { {State::NUM_DEC, CharType::ADD},     {State::ADD,       TokenType::NUMBER} },
        { {State::NUM_DEC, CharType::SUB},     {State::SUB,       TokenType::NUMBER} },
        { {State::NUM_DEC, CharType::MUL},     {State::MUL,       TokenType::NUMBER} },
        { {State::NUM_DEC, CharType::DIV},     {State::DIV,       TokenType::NUMBER} },
        { {State::NUM_DEC, CharType::LP},      {State::LP,        TokenType::NUMBER} },
        { {State::NUM_DEC, CharType::RP},      {State::RP,        TokenType::NUMBER} },
        { {State::NUM_DEC, CharType::NUM},     {State::NUM_DEC,   TokenType::NO_TOKEN} },
        { {State::NUM_DEC, CharType::POINT},   {State::OVER,      TokenType::BAD_TOKEN} },
        { {State::NUM_DEC, CharType::WORD},    {State::OVER,      TokenType::BAD_TOKEN} },
        { {State::NUM_DEC, CharType::ASN},     {State::ASN,       TokenType::NUMBER} },
        /* variable */
        { {State::VAR, CharType::END},     {State::OVER,      TokenType::VAR} },
        { {State::VAR, CharType::SPACE},   {State::INIT,      TokenType::VAR} },
        { {State::VAR, CharType::ENDL},    {State::ENDL,      TokenType::VAR} },
        { {State::VAR, CharType::ADD},     {State::ADD,       TokenType::VAR} },
        { {State::VAR, CharType::SUB},     {State::SUB,       TokenType::VAR} },
        { {State::VAR, CharType::MUL},     {State::MUL,       TokenType::VAR} },
        { {State::VAR, CharType::DIV},     {State::DIV,       TokenType::VAR} },
        { {State::VAR, CharType::LP},      {State::LP,        TokenType::VAR} },
        { {State::VAR, CharType::RP},      {State::RP,        TokenType::VAR} },
        { {State::VAR, CharType::NUM},     {State::VAR,       TokenType::NO_TOKEN} },
        { {State::VAR, CharType::POINT},   {State::OVER,      TokenType::BAD_TOKEN} },
        { {State::VAR, CharType::WORD},    {State::VAR,       TokenType::NO_TOKEN} },
        { {State::VAR, CharType::ASN},     {State::ASN,       TokenType::VAR} },
        /* = */
        { {State::ASN, CharType::END},   {State::OVER,      TokenType::ASSIGN} },
        { {State::ASN, CharType::SPACE}, {State::INIT,      TokenType::ASSIGN} },
        { {State::ASN, CharType::ENDL},  {State::ENDL,      TokenType::ASSIGN} },
        { {State::ASN, CharType::ADD},   {State::ADD,       TokenType::ASSIGN} },
        { {State::ASN, CharType::SUB},   {State::SUB,       TokenType::ASSIGN} },
        { {State::ASN, CharType::MUL},   {State::MUL,       TokenType::ASSIGN} },
        { {State::ASN, CharType::DIV},   {State::DIV,       TokenType::ASSIGN} },
        { {State::ASN, CharType::LP},    {State::LP,        TokenType::ASSIGN} },
        { {State::ASN, CharType::RP},    {State::RP,        TokenType::ASSIGN} },
        { {State::ASN, CharType::NUM},   {State::NUM_INT,   TokenType::ASSIGN} },
        { {State::ASN, CharType::POINT}, {State::POINT_FNT, TokenType::ASSIGN} },
        { {State::ASN, CharType::WORD},  {State::VAR,       TokenType::ASSIGN} },
        { {State::ASN, CharType::ASN},   {State::ASN,       TokenType::ASSIGN} },
        /* \n */
        { {State::ENDL, CharType::END},   {State::OVER,      TokenType::ENDL} },
        { {State::ENDL, CharType::SPACE}, {State::INIT,      TokenType::ENDL} },
        { {State::ENDL, CharType::ENDL},  {State::ENDL,      TokenType::ENDL} },
        { {State::ENDL, CharType::ADD},   {State::ADD,       TokenType::ENDL} },
        { {State::ENDL, CharType::SUB},   {State::SUB,       TokenType::ENDL} },
        { {State::ENDL, CharType::MUL},   {State::MUL,       TokenType::ENDL} },
        { {State::ENDL, CharType::DIV},   {State::DIV,       TokenType::ENDL} },
        { {State::ENDL, CharType::LP},    {State::LP,        TokenType::ENDL} },
        { {State::ENDL, CharType::RP},    {State::RP,        TokenType::ENDL} },
        { {State::ENDL, CharType::NUM},   {State::NUM_INT,   TokenType::ENDL} },
        { {State::ENDL, CharType::POINT}, {State::POINT_FNT, TokenType::ENDL} },
        { {State::ENDL, CharType::WORD},  {State::VAR,       TokenType::ENDL} },
        { {State::ENDL, CharType::ASN},   {State::ASN,       TokenType::ENDL} }
};



#pragma once

#include <cstddef>
#include <string>
#include <vector>
#include <unordered_map>
#include <utility>
#include <stdexcept>


struct Token;
enum class CharType;
enum class TokenType;
enum class State;
struct pair_hash;


class Lexer
{
    using MapInType  = std::pair<State,CharType>;
    using MapOUtType = std::pair<State,TokenType>;
public:

    void runLexer(const std::string & input);
    std::vector<Token> getTokens(void);

    Lexer();
    ~Lexer() = default;

private:
    std::vector<Token> mTokens;
    static const std::unordered_map< Lexer::MapInType, Lexer::MapOUtType, pair_hash > mLexerTable;
    size_t mNumLine;
    size_t mColumn;

    void clear(void);
    CharType charType(char ch);
    void error(const std::string & info);

    void updatePosition(const State &nowState);
};

enum class TokenType
{
    NO_TOKEN,       // in lexer table, sometimes there is no token for output
    BAD_TOKEN,
    NUMBER,
    ADD,
    MUL,
    DIV,
    SUB,
    LEFT_PAR,
    RIGHT_PAR,
    ASSIGN,
    VAR,
    ENDL
};

enum class State
{
    INIT,
    ADD,
    SUB,
    MUL,
    DIV,
    LP,
    RP,
    NUM_INT,
    POINT_FNT,      // point at front
    POINT_NML,      // point after some \d
    NUM_DEC,
    VAR,
    ASN,            // =
    ENDL,
    OVER
};

enum class CharType
{
    END,
    SPACE,
    ENDL,
    ADD,
    SUB,
    MUL,
    DIV,
    LP,
    RP,
    NUM,
    POINT,
    WORD,
    ASN
};

struct Token
{
    TokenType mTokenType;
    std::string mValue;
    std::size_t mLine;
    std::size_t mColumn;
};

struct pair_hash
{
    std::size_t operator () (const std::pair<State,CharType > &p) const
    {
        auto h1 = std::hash<State>{}(p.first);
        auto h2 = std::hash<CharType>{}(p.second);
        return h1 ^ h2;
    }
};



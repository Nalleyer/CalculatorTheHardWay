#include <iostream>
#include <algorithm>
#include <string>
#include <fstream>
#include <sstream>

#include "lexer.h"

using namespace std;

std::string type2Str(const TokenType & type)
{
    switch( type )
    {
        case TokenType::NO_TOKEN  : return "no_token";
        case TokenType::BAD_TOKEN : return "bad_token";
        case TokenType::NUMBER    : return "token_number";
        case TokenType::ADD       : return "token_add";
        case TokenType::MUL       : return "token_mul";
        case TokenType::DIV       : return "token_div";
        case TokenType::SUB       : return "token_sub";
        case TokenType::LEFT_PAR  : return "token_lPar";
        case TokenType::RIGHT_PAR : return "token_rPar";
        case TokenType::ASSIGN    : return "token_=";
        case TokenType::VAR       : return "token_var";
        case TokenType::ENDL      : return "token_endl";
    }
}

std::ostream& operator << (std::ostream &o, const TokenType & type)
{
    o << type2Str(type) << " ";
    return o;
}
int main() {
    ifstream ifs("input.txt");
    stringstream ss;
    ss << ifs.rdbuf();

    Lexer l;
    l.runLexer(ss.str());
    auto out = l.getTokens();

    cout << "done\n" ;
    cout << "all " << out.size() << " tokens got\n";

    /* test for lexer */
    for_each(out.begin(),out.end(), [](Token tk) {
        cout << "{ " << tk.mTokenType << "," << ( tk.mValue == "\n" ? "\\n" : tk.mValue )
            << ", (" << tk.mLine << ", " << tk.mColumn << ") };\n";
    });

    return 0;
}
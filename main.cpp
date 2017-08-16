#include <iostream>
#include <algorithm>
#include <string>
#include <fstream>
#include <sstream>

#include "Lexer.h"
#include "parser.h"

//#include "PrintVisitor.h"
#include "EvalVisitor.h"

using namespace std;

/*
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
 */

void usage(std::string const &progName)
{
    cout << "Usage: " << progName << " <FILE_NAME>\n";
    exit(0);
}

int main(int argc, char *argv[]) {

    if ( argc != 2)
    {
        std::string progName(argv[0]);
        usage(progName);
    }

    ifstream ifs(argv[1]);
    stringstream ss;
    ss << ifs.rdbuf();

    Lexer l;
    l.runLexer(ss.str());
    auto tokenList = l.getTokens();

    /*
    cout << "done\n" ;
    cout << "all " << tokenList.size() << " tokens got\n";
     */

    /* test for lexer */
    /*
    for_each(tokenList.begin(),tokenList.end(), [i = 0](Token tk) mutable {
        cout << i++ << "\t{ " << tk.mTokenType << "," << ( tk.mValue == "\n" ? "\\n" : tk.mValue )
            << ", (" << tk.mLine << ", " << tk.mColumn << ") };\n";
    });
     */

    Parser p;
    p.parse(tokenList);
    auto prog = p.getProg();

    /* test for print */
    /*
    PrintVisitor pv;
    for_each(prog.begin(), prog.end(), [&pv](auto ast){
        ast -> accept(pv);
    });
     */

    /* test for eval */
    EvalVisitor ev;
    for_each(prog.begin(), prog.end(), [&ev](auto ast){
        ast -> accept(ev);
        if ( ev.getResult() != "")
        {
            cout << ev.getResult() << "\n";
        }
    });

    return 0;
}
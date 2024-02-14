%{
    #include <cerrno>
    #include <climits>
    #include <cstdlib>
    #include <cstring> // strerror
    #include <string>
    #include <iostream>
    #include "driver.hh"
    #include "parser.hh"
%}

%option noyywrap nounput noinput batch debug

%option c++
%option yyclass="Scanner"

%{
  yy::parser::symbol_type make_NUMBER(
    const std::string &s,
    const yy::parser::location_type& loc
  );

  void Scanner::UpdateLocation() {
    if (driver.location_debug) {
        std::cerr << "Action called " << driver.location << std::endl;
    }
    driver.location.columns(yyleng);
  }
%}

string [\"].*[\"]
id    [a-zA-Z][a-zA-Z_0-9]*
int   [0-9]+
blank [ \t\r]

%{
  #define YY_USER_ACTION UpdateLocation();
%}

%%


%{
  yy::location& loc = driver.location;
  if (driver.location_debug) {
    std::cerr << "BEFORE " << loc << std::endl;
  }
  if (driver.location_debug) {
    std::cerr << "AFTER " <<  loc << std::endl;
  }
%}

{blank}+   {
    if (driver.location_debug) {
        std::cerr << "Blank matched" << std::endl;
    }
    // loc.step();
}
\n+ {
    if (driver.location_debug) {
        std::cerr << "EOL called" << std::endl;
    }
    loc.lines(yyleng);
    loc.step();
}

"-"        return yy::parser::make_MINUS  (loc);
"+"        return yy::parser::make_PLUS   (loc);
"*"        return yy::parser::make_STAR   (loc);
"/"        return yy::parser::make_SLASH  (loc);
"("        return yy::parser::make_LPAREN (loc);
")"        return yy::parser::make_RPAREN (loc);
"{"        return yy::parser::make_LFIGURE (loc);
"}"        return yy::parser::make_RFIGURE (loc);
":="       return yy::parser::make_ASSIGN (loc);
";"        return yy::parser::make_SEMICOLON(loc);
":"        return yy::parser::make_COLON(loc);
"if"        return yy::parser::make_IF(loc);
"<"        return yy::parser::make_LESS(loc);
"<="        return yy::parser::make_LESSE(loc);
">"        return yy::parser::make_GREATER(loc);
">="        return yy::parser::make_GREATERE(loc);
","        return yy::parser::make_COMA(loc);
"."        return yy::parser::make_DOT(loc);
"="        return yy::parser::make_EQUAL(loc);
"!="        return yy::parser::make_NEQUAL(loc);
"print"    return yy::parser::make_PRINT (loc);
"div"    return yy::parser::make_DIV (loc);
"mod"    return yy::parser::make_MOD (loc);
"begin"    return yy::parser::make_SBEGIN (loc);
"end"    return yy::parser::make_SEND (loc);
"or"    return yy::parser::make_OR (loc);
"and"    return yy::parser::make_AND (loc);
"not"    return yy::parser::make_NOT (loc);
"then"    return yy::parser::make_THEN (loc);
"else"    return yy::parser::make_ELSE (loc);
"for"    return yy::parser::make_FOR (loc);
"to"    return yy::parser::make_TO (loc);
"do"    return yy::parser::make_DO (loc);
"while"    return yy::parser::make_WHILE (loc);
"var"    return yy::parser::make_VAR (loc);
"integer"    return yy::parser::make_TYPEINT (loc);
"str"    return yy::parser::make_TYPESTR (loc);
"bool"    return yy::parser::make_TYPEBOOL (loc);
"break"  return yy::parser::make_BREAK (loc);
"true"  return yy::parser::make_TRUE (loc);
"false"  return yy::parser::make_FALSE (loc);


{string} return yy::parser::make_STRING(yytext, loc);

{int}      return make_NUMBER(yytext, loc);
{id}       {
                if (driver.location_debug) {
                    std::cerr << "ID found " << yytext << std::endl;
                }
                return yy::parser::make_IDENTIFIER(yytext, loc);
           }
.          {
                throw yy::parser::syntax_error(loc, "invalid character: " + std::string(yytext));
           }
<<EOF>>    return yy::parser::make_END (loc);
%%

yy::parser::symbol_type make_NUMBER(
  const std::string &s,
  const yy::parser::location_type& loc
) {
  errno = 0;
  long n = strtol(s.c_str(), NULL, 10);
  if (! (INT_MIN <= n && n <= INT_MAX && errno != ERANGE))
    throw yy::parser::syntax_error(loc, "integer is out of range: " + s);
  return yy::parser::make_NUMBER((int) n, loc);
}
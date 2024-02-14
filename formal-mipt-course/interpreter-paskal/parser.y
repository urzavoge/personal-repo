%skeleton "lalr1.cc"
%require "3.5"

%defines
%define api.token.constructor
%define api.value.type variant
%define parse.assert

%code requires {
    #include <string>
    #include <memory>
    #include <vector>

    class Scanner;

    class Expression;
    class Program;
    class Driver;

    class Declaration;
    class IntDecl;
    class StrDecl;
    class BoolDecl;
    class EmptyDecl;
    class Declarations;

    class NumExp;
    class AddExp;
    class MinusExp;
    class MulExp;
    class DivExp;
    class ModExp;
    class IdentExp;
    class NegExp;

    class Condition;
    class BoolCond;
    class EqualCond;
    class IdentCond;
    class NotEqualCond;
    class LessCond;
    class LessOrEqCond;
    class GreaterCond;
    class GreaterOrEqCond;
    class ExpCond;
    class AndCond;
    class OrCond;

    class Line;
    class EmptyLine;
    class BreakLine;
    class ForLine;
    class WhileLine;
    class AssIntLine;
    class AssStrLine;
    class AssBoolLine;
    class PrintLine;
    class PrintStrLine;
    class PrintIdentLine;
    class CaseLine;
    class Lines;
}


%define parse.trace
%define parse.error verbose

%code {
    #include "driver.hh"
    #include "location.hh"

    /* Redefine parser to use our function from scanner */
    static yy::parser::symbol_type yylex(Scanner &scanner) {
        return scanner.ScanToken();
    }
}

%lex-param { Scanner &scanner }

%parse-param { Scanner &scanner }
%parse-param { Driver &driver }

%locations

%define api.token.prefix {TOK_}
// token name in variable
%token
    END 0 "end of file"
    ASSIGN ":="
    VAR "var"
    TYPEINT "integer"
    TYPESTR "str"
    TYPEBOOL "bool"

    MINUS "-"
    PLUS "+"
    STAR "*"
    SLASH "/"
    LPAREN "("
    RPAREN ")"
    LFIGURE "{"
    RFIGURE "}"
    SEMICOLON ";"
    COLON ":"
    LESS "<"
    LESSE "<="
    GREATER ">"
    GREATERE ">="
    COMA ","
    DOT "."

    IF "if"
    EQUAL "="
    NEQUAL "!="
    PRINT "print"
    MOD "mod"
    DIV "div"
    TRUE "true"
    FALSE "false"

    SBEGIN "begin"
    SEND "end"

    AND "and"
    OR "or"
    NOT "not"
    THEN "then"
    ELSE "else"

    FOR "for"
    TO "to"
    DO "do"
    WHILE "while"
    BREAK "break";
;

%token <std::string> IDENTIFIER "identifier"
%token <int> NUMBER "number"
%token <std::string> STRING "string"

%nterm <std::shared_ptr<Expression>> exp
%nterm <std::shared_ptr<AssIntLine>> assignment_int
%nterm <std::shared_ptr<AssStrLine>> assignment_str
%nterm <std::shared_ptr<AssBoolLine>> assignment_bool
%nterm <std::shared_ptr<PrintLine>> printexp
%nterm <std::shared_ptr<PrintStrLine>> printstr
%nterm <std::shared_ptr<PrintIdentLine>> printident
%nterm <std::shared_ptr<Lines>> lines
%nterm <std::shared_ptr<Line>> line
%nterm <std::shared_ptr<Condition>> condition
%nterm <std::shared_ptr<CaseLine>> case
%nterm <std::shared_ptr<ForLine>> forcycle
%nterm <std::shared_ptr<WhileLine>> whilecycle
%nterm <std::shared_ptr<Declarations>> declarations
%nterm <std::shared_ptr<Declaration>> declaration
%nterm <std::shared_ptr<std::vector<std::string>>> identifiers

// Prints output in parsing option for debugging location terminal
%printer { yyo << $$; } <*>;

%%
%left "+" "-";
%left "*" "mod" "div";
%left "and" "or";

%start unit;
unit: declarations SBEGIN lines SEND DOT {
    driver.program->set_decls($1);
    driver.program->set_lines($3); };

declarations:
    %empty { $$ = std::make_shared<Declarations>(); }
    | declarations declaration { $$ = Declarations::Add($1, $2); };

declaration:
    ";" { $$ = std::make_shared<EmptyDecl>(); }
    | VAR identifiers ":" TYPEINT ";" { $$ = std::make_shared<IntDecl>(&driver, std::move($2)); }
    | VAR identifiers ":" TYPEBOOL ";" { $$ = std::make_shared<BoolDecl>(&driver, std::move($2)); }
    | VAR identifiers ":" TYPESTR ";" { $$ = std::make_shared<StrDecl>(&driver, std::move($2)); };

identifiers:
    "identifier" { $$ = std::make_shared<std::vector<std::string>>(1, $1); }
    | identifiers "," "identifier" { $$ = Program::Add($1, $3); };


lines:
    %empty { $$ = std::make_shared<Lines>(); }
    | lines line { $$ = Lines::Add($1, $2); };

line:
    ";" { $$ = std::make_shared<EmptyLine>(); }
    | assignment_int ";" { $$ = $1; }
    | assignment_str ";" { $$ = $1; }
    | BREAK ";" { $$ = std::make_shared<BreakLine>(); }
    | assignment_bool ";" { $$ = $1; }
    | case { $$ = $1; }
    | forcycle { $$ = $1; }
    | whilecycle { $$ = $1; }
    | printexp ";" { $$ = $1; }
    | printident ";" { $$ = $1; }
    | printstr ";" { $$ = $1; };

printident: PRINT "(" "identifier" ")" {$$ = std::make_shared<PrintIdentLine>(&driver, $3); };

printexp: PRINT "(" exp ")" { $$ = std::make_shared<PrintLine>($3); };

printstr: PRINT "(" "string" ")" {$$ = std::make_shared<PrintStrLine>($3); };

forcycle: FOR "identifier" ":=" exp TO exp DO SBEGIN lines SEND {
    $$ = std::make_shared<ForLine>(&driver, $4, $6, $2, $9); }
          | FOR "identifier" ":=" exp TO exp DO line {
    $$ = std::make_shared<ForLine>(&driver, $4, $6, $2, std::make_shared<Lines>($8));
          };

whilecycle: WHILE condition DO SBEGIN lines SEND {
    $$ = std::make_shared<WhileLine>($2, $5); }
            | WHILE condition DO line {
    $$ = std::make_shared<WhileLine>($2, std::make_shared<Lines>($4));
            };

case:   IF condition THEN SBEGIN lines SEND ELSE SBEGIN lines SEND {
            $$ = std::make_shared<CaseLine>($2, $5, $9); }
        | IF condition THEN SBEGIN lines SEND {
            $$ = std::make_shared<CaseLine>($2, $5); }
        | IF condition THEN line {
            $$ = std::make_shared<CaseLine>($2, std::make_shared<Lines>($4)); }
        | IF condition THEN line ELSE SBEGIN lines SEND {
            $$ = std::make_shared<CaseLine>($2, std::make_shared<Lines>($4), $7); }
        | IF condition THEN line ELSE line {
            $$ = std::make_shared<CaseLine>($2, std::make_shared<Lines>($4), std::make_shared<Lines>($6)); }
        | IF condition THEN SBEGIN lines SEND ELSE line {
            $$ = std::make_shared<CaseLine>($2, $5, std::make_shared<Lines>($8)); };

condition:
        exp "=" exp { $$ = std::make_shared<EqualCond>($1, $3); }
//        | "identifier" { $$ = std::make_shared<IdentCond>(&driver, $1); }
        | exp "!=" exp { $$ = std::make_shared<NotEqualCond>($1, $3); }
        | exp "<" exp { $$ = std::make_shared<LessCond>($1, $3); }
        | exp ">" exp { $$ = std::make_shared<GreaterCond>($1, $3); }
        | exp "<=" exp { $$ = std::make_shared<LessOrEqCond>($1, $3); }
        | exp ">=" exp { $$ = std::make_shared<GreaterOrEqCond>($1, $3); }
//        | exp { $$ = std::make_shared<ExpCond>($1); }
        | "(" condition ")" { $$ = $2; }
        | condition "and" condition { $$ = std::make_shared<AndCond>($1, $3); }
        | condition "or" condition { $$ = std::make_shared<OrCond>($1, $3); }
        | FALSE { $$ = std::make_shared<BoolCond>(false); }
        | TRUE { $$ = std::make_shared<BoolCond>(true); }
        | "not" condition { $$ = std::make_shared<NotCond>($2); };

assignment_int:
    "identifier" ":=" exp {
        $$ = std::make_shared<AssIntLine>(&driver, $1, $3);
        if (driver.location_debug) {
            std::cerr << driver.location << std::endl;
        }
    }
    | error ";" {
    	std::cerr << "You should provide assignment in the form: variable := expression ; " << std::endl;
    };

assignment_str: "identifier" ":=" STRING {
    $$ = std::make_shared<AssStrLine>(&driver, $1, $3);
    if (driver.location_debug) {
                std::cerr << driver.location << std::endl;
            }
    };

assignment_bool: "identifier" ":=" condition {
    $$ = std::make_shared<AssBoolLine>(&driver, $1, $3);
    if (driver.location_debug) {
                std::cerr << driver.location << std::endl;
            }
    };

exp:
    "number" { $$ = std::make_shared<NumExp>($1); }
    | "identifier" { $$ = std::make_shared<IdentExp>(&driver, $1); }
    | exp "+" exp {$$ = std::make_shared<AddExp>($1, $3); }
    | exp "-" exp {$$ = std::make_shared<MinusExp>($1, $3); }
    | exp "*" exp {$$ = std::make_shared<MulExp>($1, $3); }
    | exp "div" exp {$$ = std::make_shared<DivExp>($1, $3); }
    | exp "mod" exp {$$ = std::make_shared<ModExp>($1, $3); }
    | "-" exp {$$ = std::make_shared<NegExp>($2); }
    | "(" exp ")" {$$ = $2; };

%%

void
yy::parser::error(const location_type& l, const std::string& m)
{
  std::cerr << l << ": " << m << '\n';
}

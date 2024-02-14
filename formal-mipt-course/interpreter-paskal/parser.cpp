// A Bison parser, made by GNU Bison 3.8.2.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2021 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.

// DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
// especially those whose name start with YY_ or yy_.  They are
// private implementation details that can be changed or removed.





#include "parser.hh"


// Unqualified %code blocks.
#line 68 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.y"

    #include "driver.hh"
    #include "location.hh"

    /* Redefine parser to use our function from scanner */
    static yy::parser::symbol_type yylex(Scanner &scanner) {
        return scanner.ScanToken();
    }

#line 56 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.cpp"


#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif


// Whether we are compiled with exception support.
#ifndef YY_EXCEPTIONS
# if defined __GNUC__ && !defined __EXCEPTIONS
#  define YY_EXCEPTIONS 0
# else
#  define YY_EXCEPTIONS 1
# endif
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K].location)
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# ifndef YYLLOC_DEFAULT
#  define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).begin  = YYRHSLOC (Rhs, 1).begin;                   \
          (Current).end    = YYRHSLOC (Rhs, N).end;                     \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;      \
        }                                                               \
    while (false)
# endif


// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << '\n';                       \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yy_stack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YY_USE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

namespace yy {
#line 148 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.cpp"

  /// Build a parser object.
  parser::parser (Scanner &scanner_yyarg, Driver &driver_yyarg)
#if YYDEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr),
#else
    :
#endif
      scanner (scanner_yyarg),
      driver (driver_yyarg)
  {}

  parser::~parser ()
  {}

  parser::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------.
  | symbol.  |
  `---------*/



  // by_state.
  parser::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

  parser::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
  parser::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
  parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  parser::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

  parser::symbol_kind_type
  parser::by_state::kind () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return symbol_kind::S_YYEMPTY;
    else
      return YY_CAST (symbol_kind_type, yystos_[+state]);
  }

  parser::stack_symbol_type::stack_symbol_type ()
  {}

  parser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state), YY_MOVE (that.location))
  {
    switch (that.kind ())
    {
      case symbol_kind::S_NUMBER: // "number"
        value.YY_MOVE_OR_COPY< int > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_assignment_bool: // assignment_bool
        value.YY_MOVE_OR_COPY< std::shared_ptr<AssBoolLine> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_assignment_int: // assignment_int
        value.YY_MOVE_OR_COPY< std::shared_ptr<AssIntLine> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_assignment_str: // assignment_str
        value.YY_MOVE_OR_COPY< std::shared_ptr<AssStrLine> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_case: // case
        value.YY_MOVE_OR_COPY< std::shared_ptr<CaseLine> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_condition: // condition
        value.YY_MOVE_OR_COPY< std::shared_ptr<Condition> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_declaration: // declaration
        value.YY_MOVE_OR_COPY< std::shared_ptr<Declaration> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_declarations: // declarations
        value.YY_MOVE_OR_COPY< std::shared_ptr<Declarations> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_exp: // exp
        value.YY_MOVE_OR_COPY< std::shared_ptr<Expression> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_forcycle: // forcycle
        value.YY_MOVE_OR_COPY< std::shared_ptr<ForLine> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_line: // line
        value.YY_MOVE_OR_COPY< std::shared_ptr<Line> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_lines: // lines
        value.YY_MOVE_OR_COPY< std::shared_ptr<Lines> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_printident: // printident
        value.YY_MOVE_OR_COPY< std::shared_ptr<PrintIdentLine> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_printexp: // printexp
        value.YY_MOVE_OR_COPY< std::shared_ptr<PrintLine> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_printstr: // printstr
        value.YY_MOVE_OR_COPY< std::shared_ptr<PrintStrLine> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_whilecycle: // whilecycle
        value.YY_MOVE_OR_COPY< std::shared_ptr<WhileLine> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_identifiers: // identifiers
        value.YY_MOVE_OR_COPY< std::shared_ptr<std::vector<std::string>> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_IDENTIFIER: // "identifier"
      case symbol_kind::S_STRING: // "string"
        value.YY_MOVE_OR_COPY< std::string > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

#if 201103L <= YY_CPLUSPLUS
    // that is emptied.
    that.state = empty_state;
#endif
  }

  parser::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s, YY_MOVE (that.location))
  {
    switch (that.kind ())
    {
      case symbol_kind::S_NUMBER: // "number"
        value.move< int > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_assignment_bool: // assignment_bool
        value.move< std::shared_ptr<AssBoolLine> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_assignment_int: // assignment_int
        value.move< std::shared_ptr<AssIntLine> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_assignment_str: // assignment_str
        value.move< std::shared_ptr<AssStrLine> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_case: // case
        value.move< std::shared_ptr<CaseLine> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_condition: // condition
        value.move< std::shared_ptr<Condition> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_declaration: // declaration
        value.move< std::shared_ptr<Declaration> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_declarations: // declarations
        value.move< std::shared_ptr<Declarations> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_exp: // exp
        value.move< std::shared_ptr<Expression> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_forcycle: // forcycle
        value.move< std::shared_ptr<ForLine> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_line: // line
        value.move< std::shared_ptr<Line> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_lines: // lines
        value.move< std::shared_ptr<Lines> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_printident: // printident
        value.move< std::shared_ptr<PrintIdentLine> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_printexp: // printexp
        value.move< std::shared_ptr<PrintLine> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_printstr: // printstr
        value.move< std::shared_ptr<PrintStrLine> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_whilecycle: // whilecycle
        value.move< std::shared_ptr<WhileLine> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_identifiers: // identifiers
        value.move< std::shared_ptr<std::vector<std::string>> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_IDENTIFIER: // "identifier"
      case symbol_kind::S_STRING: // "string"
        value.move< std::string > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

    // that is emptied.
    that.kind_ = symbol_kind::S_YYEMPTY;
  }

#if YY_CPLUSPLUS < 201103L
  parser::stack_symbol_type&
  parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_NUMBER: // "number"
        value.copy< int > (that.value);
        break;

      case symbol_kind::S_assignment_bool: // assignment_bool
        value.copy< std::shared_ptr<AssBoolLine> > (that.value);
        break;

      case symbol_kind::S_assignment_int: // assignment_int
        value.copy< std::shared_ptr<AssIntLine> > (that.value);
        break;

      case symbol_kind::S_assignment_str: // assignment_str
        value.copy< std::shared_ptr<AssStrLine> > (that.value);
        break;

      case symbol_kind::S_case: // case
        value.copy< std::shared_ptr<CaseLine> > (that.value);
        break;

      case symbol_kind::S_condition: // condition
        value.copy< std::shared_ptr<Condition> > (that.value);
        break;

      case symbol_kind::S_declaration: // declaration
        value.copy< std::shared_ptr<Declaration> > (that.value);
        break;

      case symbol_kind::S_declarations: // declarations
        value.copy< std::shared_ptr<Declarations> > (that.value);
        break;

      case symbol_kind::S_exp: // exp
        value.copy< std::shared_ptr<Expression> > (that.value);
        break;

      case symbol_kind::S_forcycle: // forcycle
        value.copy< std::shared_ptr<ForLine> > (that.value);
        break;

      case symbol_kind::S_line: // line
        value.copy< std::shared_ptr<Line> > (that.value);
        break;

      case symbol_kind::S_lines: // lines
        value.copy< std::shared_ptr<Lines> > (that.value);
        break;

      case symbol_kind::S_printident: // printident
        value.copy< std::shared_ptr<PrintIdentLine> > (that.value);
        break;

      case symbol_kind::S_printexp: // printexp
        value.copy< std::shared_ptr<PrintLine> > (that.value);
        break;

      case symbol_kind::S_printstr: // printstr
        value.copy< std::shared_ptr<PrintStrLine> > (that.value);
        break;

      case symbol_kind::S_whilecycle: // whilecycle
        value.copy< std::shared_ptr<WhileLine> > (that.value);
        break;

      case symbol_kind::S_identifiers: // identifiers
        value.copy< std::shared_ptr<std::vector<std::string>> > (that.value);
        break;

      case symbol_kind::S_IDENTIFIER: // "identifier"
      case symbol_kind::S_STRING: // "string"
        value.copy< std::string > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    return *this;
  }

  parser::stack_symbol_type&
  parser::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_NUMBER: // "number"
        value.move< int > (that.value);
        break;

      case symbol_kind::S_assignment_bool: // assignment_bool
        value.move< std::shared_ptr<AssBoolLine> > (that.value);
        break;

      case symbol_kind::S_assignment_int: // assignment_int
        value.move< std::shared_ptr<AssIntLine> > (that.value);
        break;

      case symbol_kind::S_assignment_str: // assignment_str
        value.move< std::shared_ptr<AssStrLine> > (that.value);
        break;

      case symbol_kind::S_case: // case
        value.move< std::shared_ptr<CaseLine> > (that.value);
        break;

      case symbol_kind::S_condition: // condition
        value.move< std::shared_ptr<Condition> > (that.value);
        break;

      case symbol_kind::S_declaration: // declaration
        value.move< std::shared_ptr<Declaration> > (that.value);
        break;

      case symbol_kind::S_declarations: // declarations
        value.move< std::shared_ptr<Declarations> > (that.value);
        break;

      case symbol_kind::S_exp: // exp
        value.move< std::shared_ptr<Expression> > (that.value);
        break;

      case symbol_kind::S_forcycle: // forcycle
        value.move< std::shared_ptr<ForLine> > (that.value);
        break;

      case symbol_kind::S_line: // line
        value.move< std::shared_ptr<Line> > (that.value);
        break;

      case symbol_kind::S_lines: // lines
        value.move< std::shared_ptr<Lines> > (that.value);
        break;

      case symbol_kind::S_printident: // printident
        value.move< std::shared_ptr<PrintIdentLine> > (that.value);
        break;

      case symbol_kind::S_printexp: // printexp
        value.move< std::shared_ptr<PrintLine> > (that.value);
        break;

      case symbol_kind::S_printstr: // printstr
        value.move< std::shared_ptr<PrintStrLine> > (that.value);
        break;

      case symbol_kind::S_whilecycle: // whilecycle
        value.move< std::shared_ptr<WhileLine> > (that.value);
        break;

      case symbol_kind::S_identifiers: // identifiers
        value.move< std::shared_ptr<std::vector<std::string>> > (that.value);
        break;

      case symbol_kind::S_IDENTIFIER: // "identifier"
      case symbol_kind::S_STRING: // "string"
        value.move< std::string > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    // that is emptied.
    that.state = empty_state;
    return *this;
  }
#endif

  template <typename Base>
  void
  parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if YYDEBUG
  template <typename Base>
  void
  parser::yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YY_USE (yyoutput);
    if (yysym.empty ())
      yyo << "empty symbol";
    else
      {
        symbol_kind_type yykind = yysym.kind ();
        yyo << (yykind < YYNTOKENS ? "token" : "nterm")
            << ' ' << yysym.name () << " ("
            << yysym.location << ": ";
        switch (yykind)
    {
      case symbol_kind::S_IDENTIFIER: // "identifier"
#line 159 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.y"
                 { yyo << yysym.value.template as < std::string > (); }
#line 592 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.cpp"
        break;

      case symbol_kind::S_NUMBER: // "number"
#line 159 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.y"
                 { yyo << yysym.value.template as < int > (); }
#line 598 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.cpp"
        break;

      case symbol_kind::S_STRING: // "string"
#line 159 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.y"
                 { yyo << yysym.value.template as < std::string > (); }
#line 604 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.cpp"
        break;

      case symbol_kind::S_declarations: // declarations
#line 159 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.y"
                 { yyo << yysym.value.template as < std::shared_ptr<Declarations> > (); }
#line 610 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.cpp"
        break;

      case symbol_kind::S_declaration: // declaration
#line 159 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.y"
                 { yyo << yysym.value.template as < std::shared_ptr<Declaration> > (); }
#line 616 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.cpp"
        break;

      case symbol_kind::S_identifiers: // identifiers
#line 159 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.y"
                 { yyo << yysym.value.template as < std::shared_ptr<std::vector<std::string>> > (); }
#line 622 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.cpp"
        break;

      case symbol_kind::S_lines: // lines
#line 159 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.y"
                 { yyo << yysym.value.template as < std::shared_ptr<Lines> > (); }
#line 628 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.cpp"
        break;

      case symbol_kind::S_line: // line
#line 159 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.y"
                 { yyo << yysym.value.template as < std::shared_ptr<Line> > (); }
#line 634 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.cpp"
        break;

      case symbol_kind::S_printident: // printident
#line 159 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.y"
                 { yyo << yysym.value.template as < std::shared_ptr<PrintIdentLine> > (); }
#line 640 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.cpp"
        break;

      case symbol_kind::S_printexp: // printexp
#line 159 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.y"
                 { yyo << yysym.value.template as < std::shared_ptr<PrintLine> > (); }
#line 646 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.cpp"
        break;

      case symbol_kind::S_printstr: // printstr
#line 159 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.y"
                 { yyo << yysym.value.template as < std::shared_ptr<PrintStrLine> > (); }
#line 652 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.cpp"
        break;

      case symbol_kind::S_forcycle: // forcycle
#line 159 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.y"
                 { yyo << yysym.value.template as < std::shared_ptr<ForLine> > (); }
#line 658 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.cpp"
        break;

      case symbol_kind::S_whilecycle: // whilecycle
#line 159 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.y"
                 { yyo << yysym.value.template as < std::shared_ptr<WhileLine> > (); }
#line 664 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.cpp"
        break;

      case symbol_kind::S_case: // case
#line 159 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.y"
                 { yyo << yysym.value.template as < std::shared_ptr<CaseLine> > (); }
#line 670 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.cpp"
        break;

      case symbol_kind::S_condition: // condition
#line 159 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.y"
                 { yyo << yysym.value.template as < std::shared_ptr<Condition> > (); }
#line 676 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.cpp"
        break;

      case symbol_kind::S_assignment_int: // assignment_int
#line 159 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.y"
                 { yyo << yysym.value.template as < std::shared_ptr<AssIntLine> > (); }
#line 682 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.cpp"
        break;

      case symbol_kind::S_assignment_str: // assignment_str
#line 159 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.y"
                 { yyo << yysym.value.template as < std::shared_ptr<AssStrLine> > (); }
#line 688 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.cpp"
        break;

      case symbol_kind::S_assignment_bool: // assignment_bool
#line 159 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.y"
                 { yyo << yysym.value.template as < std::shared_ptr<AssBoolLine> > (); }
#line 694 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.cpp"
        break;

      case symbol_kind::S_exp: // exp
#line 159 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.y"
                 { yyo << yysym.value.template as < std::shared_ptr<Expression> > (); }
#line 700 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.cpp"
        break;

      default:
        break;
    }
        yyo << ')';
      }
  }
#endif

  void
  parser::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
  parser::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
  parser::yypop_ (int n) YY_NOEXCEPT
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  parser::debug_level_type
  parser::debug_level () const
  {
    return yydebug_;
  }

  void
  parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  parser::state_type
  parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - YYNTOKENS] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - YYNTOKENS];
  }

  bool
  parser::yy_pact_value_is_default_ (int yyvalue) YY_NOEXCEPT
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  parser::yy_table_value_is_error_ (int yyvalue) YY_NOEXCEPT
  {
    return yyvalue == yytable_ninf_;
  }

  int
  parser::operator() ()
  {
    return parse ();
  }

  int
  parser::parse ()
  {
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The locations where the error started and ended.
    stack_symbol_type yyerror_range[3];

    /// The return value of parse ().
    int yyresult;

#if YY_EXCEPTIONS
    try
#endif // YY_EXCEPTIONS
      {
    YYCDEBUG << "Starting parse\n";


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, YY_MOVE (yyla));

  /*-----------------------------------------------.
  | yynewstate -- push a new symbol on the stack.  |
  `-----------------------------------------------*/
  yynewstate:
    YYCDEBUG << "Entering state " << int (yystack_[0].state) << '\n';
    YY_STACK_PRINT ();

    // Accept?
    if (yystack_[0].state == yyfinal_)
      YYACCEPT;

    goto yybackup;


  /*-----------.
  | yybackup.  |
  `-----------*/
  yybackup:
    // Try to take a decision without lookahead.
    yyn = yypact_[+yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token\n";
#if YY_EXCEPTIONS
        try
#endif // YY_EXCEPTIONS
          {
            symbol_type yylookahead (yylex (scanner));
            yyla.move (yylookahead);
          }
#if YY_EXCEPTIONS
        catch (const syntax_error& yyexc)
          {
            YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
            error (yyexc);
            goto yyerrlab1;
          }
#endif // YY_EXCEPTIONS
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    if (yyla.kind () == symbol_kind::S_YYerror)
    {
      // The scanner already issued an error message, process directly
      // to error recovery.  But do not keep the error token as
      // lookahead, it is too special and may lead us to an endless
      // loop in error recovery. */
      yyla.kind_ = symbol_kind::S_YYUNDEF;
      goto yyerrlab1;
    }

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.kind ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.kind ())
      {
        goto yydefault;
      }

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", state_type (yyn), YY_MOVE (yyla));
    goto yynewstate;


  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[+yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;


  /*-----------------------------.
  | yyreduce -- do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_ (yystack_[yylen].state, yyr1_[yyn]);
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
      switch (yyr1_[yyn])
    {
      case symbol_kind::S_NUMBER: // "number"
        yylhs.value.emplace< int > ();
        break;

      case symbol_kind::S_assignment_bool: // assignment_bool
        yylhs.value.emplace< std::shared_ptr<AssBoolLine> > ();
        break;

      case symbol_kind::S_assignment_int: // assignment_int
        yylhs.value.emplace< std::shared_ptr<AssIntLine> > ();
        break;

      case symbol_kind::S_assignment_str: // assignment_str
        yylhs.value.emplace< std::shared_ptr<AssStrLine> > ();
        break;

      case symbol_kind::S_case: // case
        yylhs.value.emplace< std::shared_ptr<CaseLine> > ();
        break;

      case symbol_kind::S_condition: // condition
        yylhs.value.emplace< std::shared_ptr<Condition> > ();
        break;

      case symbol_kind::S_declaration: // declaration
        yylhs.value.emplace< std::shared_ptr<Declaration> > ();
        break;

      case symbol_kind::S_declarations: // declarations
        yylhs.value.emplace< std::shared_ptr<Declarations> > ();
        break;

      case symbol_kind::S_exp: // exp
        yylhs.value.emplace< std::shared_ptr<Expression> > ();
        break;

      case symbol_kind::S_forcycle: // forcycle
        yylhs.value.emplace< std::shared_ptr<ForLine> > ();
        break;

      case symbol_kind::S_line: // line
        yylhs.value.emplace< std::shared_ptr<Line> > ();
        break;

      case symbol_kind::S_lines: // lines
        yylhs.value.emplace< std::shared_ptr<Lines> > ();
        break;

      case symbol_kind::S_printident: // printident
        yylhs.value.emplace< std::shared_ptr<PrintIdentLine> > ();
        break;

      case symbol_kind::S_printexp: // printexp
        yylhs.value.emplace< std::shared_ptr<PrintLine> > ();
        break;

      case symbol_kind::S_printstr: // printstr
        yylhs.value.emplace< std::shared_ptr<PrintStrLine> > ();
        break;

      case symbol_kind::S_whilecycle: // whilecycle
        yylhs.value.emplace< std::shared_ptr<WhileLine> > ();
        break;

      case symbol_kind::S_identifiers: // identifiers
        yylhs.value.emplace< std::shared_ptr<std::vector<std::string>> > ();
        break;

      case symbol_kind::S_IDENTIFIER: // "identifier"
      case symbol_kind::S_STRING: // "string"
        yylhs.value.emplace< std::string > ();
        break;

      default:
        break;
    }


      // Default location.
      {
        stack_type::slice range (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, range, yylen);
        yyerror_range[1].location = yylhs.location;
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
#if YY_EXCEPTIONS
      try
#endif // YY_EXCEPTIONS
        {
          switch (yyn)
            {
  case 2: // unit: declarations "begin" lines "end" "."
#line 167 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.y"
                                         {
    driver.program->set_decls(yystack_[4].value.as < std::shared_ptr<Declarations> > ());
    driver.program->set_lines(yystack_[2].value.as < std::shared_ptr<Lines> > ()); }
#line 1028 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.cpp"
    break;

  case 3: // declarations: %empty
#line 172 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.y"
           { yylhs.value.as < std::shared_ptr<Declarations> > () = std::make_shared<Declarations>(); }
#line 1034 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.cpp"
    break;

  case 4: // declarations: declarations declaration
#line 173 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.y"
                               { yylhs.value.as < std::shared_ptr<Declarations> > () = Declarations::Add(yystack_[1].value.as < std::shared_ptr<Declarations> > (), yystack_[0].value.as < std::shared_ptr<Declaration> > ()); }
#line 1040 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.cpp"
    break;

  case 5: // declaration: ";"
#line 176 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.y"
        { yylhs.value.as < std::shared_ptr<Declaration> > () = std::make_shared<EmptyDecl>(); }
#line 1046 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.cpp"
    break;

  case 6: // declaration: "var" identifiers ":" "integer" ";"
#line 177 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.y"
                                      { yylhs.value.as < std::shared_ptr<Declaration> > () = std::make_shared<IntDecl>(&driver, std::move(yystack_[3].value.as < std::shared_ptr<std::vector<std::string>> > ())); }
#line 1052 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.cpp"
    break;

  case 7: // declaration: "var" identifiers ":" "bool" ";"
#line 178 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.y"
                                       { yylhs.value.as < std::shared_ptr<Declaration> > () = std::make_shared<BoolDecl>(&driver, std::move(yystack_[3].value.as < std::shared_ptr<std::vector<std::string>> > ())); }
#line 1058 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.cpp"
    break;

  case 8: // declaration: "var" identifiers ":" "str" ";"
#line 179 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.y"
                                      { yylhs.value.as < std::shared_ptr<Declaration> > () = std::make_shared<StrDecl>(&driver, std::move(yystack_[3].value.as < std::shared_ptr<std::vector<std::string>> > ())); }
#line 1064 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.cpp"
    break;

  case 9: // identifiers: "identifier"
#line 182 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.y"
                 { yylhs.value.as < std::shared_ptr<std::vector<std::string>> > () = std::make_shared<std::vector<std::string>>(1, yystack_[0].value.as < std::string > ()); }
#line 1070 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.cpp"
    break;

  case 10: // identifiers: identifiers "," "identifier"
#line 183 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.y"
                                   { yylhs.value.as < std::shared_ptr<std::vector<std::string>> > () = Program::Add(yystack_[2].value.as < std::shared_ptr<std::vector<std::string>> > (), yystack_[0].value.as < std::string > ()); }
#line 1076 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.cpp"
    break;

  case 11: // lines: %empty
#line 187 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.y"
           { yylhs.value.as < std::shared_ptr<Lines> > () = std::make_shared<Lines>(); }
#line 1082 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.cpp"
    break;

  case 12: // lines: lines line
#line 188 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.y"
                 { yylhs.value.as < std::shared_ptr<Lines> > () = Lines::Add(yystack_[1].value.as < std::shared_ptr<Lines> > (), yystack_[0].value.as < std::shared_ptr<Line> > ()); }
#line 1088 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.cpp"
    break;

  case 13: // line: ";"
#line 191 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.y"
        { yylhs.value.as < std::shared_ptr<Line> > () = std::make_shared<EmptyLine>(); }
#line 1094 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.cpp"
    break;

  case 14: // line: assignment_int ";"
#line 192 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.y"
                         { yylhs.value.as < std::shared_ptr<Line> > () = yystack_[1].value.as < std::shared_ptr<AssIntLine> > (); }
#line 1100 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.cpp"
    break;

  case 15: // line: assignment_str ";"
#line 193 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.y"
                         { yylhs.value.as < std::shared_ptr<Line> > () = yystack_[1].value.as < std::shared_ptr<AssStrLine> > (); }
#line 1106 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.cpp"
    break;

  case 16: // line: "break" ";"
#line 194 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.y"
                { yylhs.value.as < std::shared_ptr<Line> > () = std::make_shared<BreakLine>(); }
#line 1112 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.cpp"
    break;

  case 17: // line: assignment_bool ";"
#line 195 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.y"
                          { yylhs.value.as < std::shared_ptr<Line> > () = yystack_[1].value.as < std::shared_ptr<AssBoolLine> > (); }
#line 1118 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.cpp"
    break;

  case 18: // line: case
#line 196 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.y"
           { yylhs.value.as < std::shared_ptr<Line> > () = yystack_[0].value.as < std::shared_ptr<CaseLine> > (); }
#line 1124 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.cpp"
    break;

  case 19: // line: forcycle
#line 197 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.y"
               { yylhs.value.as < std::shared_ptr<Line> > () = yystack_[0].value.as < std::shared_ptr<ForLine> > (); }
#line 1130 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.cpp"
    break;

  case 20: // line: whilecycle
#line 198 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.y"
                 { yylhs.value.as < std::shared_ptr<Line> > () = yystack_[0].value.as < std::shared_ptr<WhileLine> > (); }
#line 1136 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.cpp"
    break;

  case 21: // line: printexp ";"
#line 199 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.y"
                   { yylhs.value.as < std::shared_ptr<Line> > () = yystack_[1].value.as < std::shared_ptr<PrintLine> > (); }
#line 1142 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.cpp"
    break;

  case 22: // line: printident ";"
#line 200 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.y"
                     { yylhs.value.as < std::shared_ptr<Line> > () = yystack_[1].value.as < std::shared_ptr<PrintIdentLine> > (); }
#line 1148 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.cpp"
    break;

  case 23: // line: printstr ";"
#line 201 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.y"
                   { yylhs.value.as < std::shared_ptr<Line> > () = yystack_[1].value.as < std::shared_ptr<PrintStrLine> > (); }
#line 1154 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.cpp"
    break;

  case 24: // printident: "print" "(" "identifier" ")"
#line 203 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.y"
                                       {yylhs.value.as < std::shared_ptr<PrintIdentLine> > () = std::make_shared<PrintIdentLine>(&driver, yystack_[1].value.as < std::string > ()); }
#line 1160 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.cpp"
    break;

  case 25: // printexp: "print" "(" exp ")"
#line 205 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.y"
                            { yylhs.value.as < std::shared_ptr<PrintLine> > () = std::make_shared<PrintLine>(yystack_[1].value.as < std::shared_ptr<Expression> > ()); }
#line 1166 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.cpp"
    break;

  case 26: // printstr: "print" "(" "string" ")"
#line 207 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.y"
                                 {yylhs.value.as < std::shared_ptr<PrintStrLine> > () = std::make_shared<PrintStrLine>(yystack_[1].value.as < std::string > ()); }
#line 1172 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.cpp"
    break;

  case 27: // forcycle: "for" "identifier" ":=" exp "to" exp "do" "begin" lines "end"
#line 209 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.y"
                                                                {
    yylhs.value.as < std::shared_ptr<ForLine> > () = std::make_shared<ForLine>(&driver, yystack_[6].value.as < std::shared_ptr<Expression> > (), yystack_[4].value.as < std::shared_ptr<Expression> > (), yystack_[8].value.as < std::string > (), yystack_[1].value.as < std::shared_ptr<Lines> > ()); }
#line 1179 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.cpp"
    break;

  case 28: // forcycle: "for" "identifier" ":=" exp "to" exp "do" line
#line 211 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.y"
                                                     {
    yylhs.value.as < std::shared_ptr<ForLine> > () = std::make_shared<ForLine>(&driver, yystack_[4].value.as < std::shared_ptr<Expression> > (), yystack_[2].value.as < std::shared_ptr<Expression> > (), yystack_[6].value.as < std::string > (), std::make_shared<Lines>(yystack_[0].value.as < std::shared_ptr<Line> > ()));
          }
#line 1187 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.cpp"
    break;

  case 29: // whilecycle: "while" condition "do" "begin" lines "end"
#line 215 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.y"
                                                 {
    yylhs.value.as < std::shared_ptr<WhileLine> > () = std::make_shared<WhileLine>(yystack_[4].value.as < std::shared_ptr<Condition> > (), yystack_[1].value.as < std::shared_ptr<Lines> > ()); }
#line 1194 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.cpp"
    break;

  case 30: // whilecycle: "while" condition "do" line
#line 217 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.y"
                                      {
    yylhs.value.as < std::shared_ptr<WhileLine> > () = std::make_shared<WhileLine>(yystack_[2].value.as < std::shared_ptr<Condition> > (), std::make_shared<Lines>(yystack_[0].value.as < std::shared_ptr<Line> > ()));
            }
#line 1202 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.cpp"
    break;

  case 31: // case: "if" condition "then" "begin" lines "end" "else" "begin" lines "end"
#line 221 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.y"
                                                                   {
            yylhs.value.as < std::shared_ptr<CaseLine> > () = std::make_shared<CaseLine>(yystack_[8].value.as < std::shared_ptr<Condition> > (), yystack_[5].value.as < std::shared_ptr<Lines> > (), yystack_[1].value.as < std::shared_ptr<Lines> > ()); }
#line 1209 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.cpp"
    break;

  case 32: // case: "if" condition "then" "begin" lines "end"
#line 223 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.y"
                                              {
            yylhs.value.as < std::shared_ptr<CaseLine> > () = std::make_shared<CaseLine>(yystack_[4].value.as < std::shared_ptr<Condition> > (), yystack_[1].value.as < std::shared_ptr<Lines> > ()); }
#line 1216 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.cpp"
    break;

  case 33: // case: "if" condition "then" line
#line 225 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.y"
                                 {
            yylhs.value.as < std::shared_ptr<CaseLine> > () = std::make_shared<CaseLine>(yystack_[2].value.as < std::shared_ptr<Condition> > (), std::make_shared<Lines>(yystack_[0].value.as < std::shared_ptr<Line> > ())); }
#line 1223 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.cpp"
    break;

  case 34: // case: "if" condition "then" line "else" "begin" lines "end"
#line 227 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.y"
                                                        {
            yylhs.value.as < std::shared_ptr<CaseLine> > () = std::make_shared<CaseLine>(yystack_[6].value.as < std::shared_ptr<Condition> > (), std::make_shared<Lines>(yystack_[4].value.as < std::shared_ptr<Line> > ()), yystack_[1].value.as < std::shared_ptr<Lines> > ()); }
#line 1230 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.cpp"
    break;

  case 35: // case: "if" condition "then" line "else" line
#line 229 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.y"
                                           {
            yylhs.value.as < std::shared_ptr<CaseLine> > () = std::make_shared<CaseLine>(yystack_[4].value.as < std::shared_ptr<Condition> > (), std::make_shared<Lines>(yystack_[2].value.as < std::shared_ptr<Line> > ()), std::make_shared<Lines>(yystack_[0].value.as < std::shared_ptr<Line> > ())); }
#line 1237 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.cpp"
    break;

  case 36: // case: "if" condition "then" "begin" lines "end" "else" line
#line 231 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.y"
                                                        {
            yylhs.value.as < std::shared_ptr<CaseLine> > () = std::make_shared<CaseLine>(yystack_[6].value.as < std::shared_ptr<Condition> > (), yystack_[3].value.as < std::shared_ptr<Lines> > (), std::make_shared<Lines>(yystack_[0].value.as < std::shared_ptr<Line> > ())); }
#line 1244 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.cpp"
    break;

  case 37: // condition: exp "=" exp
#line 235 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.y"
                    { yylhs.value.as < std::shared_ptr<Condition> > () = std::make_shared<EqualCond>(yystack_[2].value.as < std::shared_ptr<Expression> > (), yystack_[0].value.as < std::shared_ptr<Expression> > ()); }
#line 1250 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.cpp"
    break;

  case 38: // condition: exp "!=" exp
#line 237 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.y"
                       { yylhs.value.as < std::shared_ptr<Condition> > () = std::make_shared<NotEqualCond>(yystack_[2].value.as < std::shared_ptr<Expression> > (), yystack_[0].value.as < std::shared_ptr<Expression> > ()); }
#line 1256 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.cpp"
    break;

  case 39: // condition: exp "<" exp
#line 238 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.y"
                      { yylhs.value.as < std::shared_ptr<Condition> > () = std::make_shared<LessCond>(yystack_[2].value.as < std::shared_ptr<Expression> > (), yystack_[0].value.as < std::shared_ptr<Expression> > ()); }
#line 1262 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.cpp"
    break;

  case 40: // condition: exp ">" exp
#line 239 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.y"
                      { yylhs.value.as < std::shared_ptr<Condition> > () = std::make_shared<GreaterCond>(yystack_[2].value.as < std::shared_ptr<Expression> > (), yystack_[0].value.as < std::shared_ptr<Expression> > ()); }
#line 1268 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.cpp"
    break;

  case 41: // condition: exp "<=" exp
#line 240 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.y"
                       { yylhs.value.as < std::shared_ptr<Condition> > () = std::make_shared<LessOrEqCond>(yystack_[2].value.as < std::shared_ptr<Expression> > (), yystack_[0].value.as < std::shared_ptr<Expression> > ()); }
#line 1274 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.cpp"
    break;

  case 42: // condition: exp ">=" exp
#line 241 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.y"
                       { yylhs.value.as < std::shared_ptr<Condition> > () = std::make_shared<GreaterOrEqCond>(yystack_[2].value.as < std::shared_ptr<Expression> > (), yystack_[0].value.as < std::shared_ptr<Expression> > ()); }
#line 1280 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.cpp"
    break;

  case 43: // condition: "(" condition ")"
#line 243 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.y"
                            { yylhs.value.as < std::shared_ptr<Condition> > () = yystack_[1].value.as < std::shared_ptr<Condition> > (); }
#line 1286 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.cpp"
    break;

  case 44: // condition: condition "and" condition
#line 244 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.y"
                                    { yylhs.value.as < std::shared_ptr<Condition> > () = std::make_shared<AndCond>(yystack_[2].value.as < std::shared_ptr<Condition> > (), yystack_[0].value.as < std::shared_ptr<Condition> > ()); }
#line 1292 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.cpp"
    break;

  case 45: // condition: condition "or" condition
#line 245 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.y"
                                   { yylhs.value.as < std::shared_ptr<Condition> > () = std::make_shared<OrCond>(yystack_[2].value.as < std::shared_ptr<Condition> > (), yystack_[0].value.as < std::shared_ptr<Condition> > ()); }
#line 1298 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.cpp"
    break;

  case 46: // condition: "false"
#line 246 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.y"
                { yylhs.value.as < std::shared_ptr<Condition> > () = std::make_shared<BoolCond>(false); }
#line 1304 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.cpp"
    break;

  case 47: // condition: "true"
#line 247 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.y"
               { yylhs.value.as < std::shared_ptr<Condition> > () = std::make_shared<BoolCond>(true); }
#line 1310 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.cpp"
    break;

  case 48: // condition: "not" condition
#line 248 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.y"
                          { yylhs.value.as < std::shared_ptr<Condition> > () = std::make_shared<NotCond>(yystack_[0].value.as < std::shared_ptr<Condition> > ()); }
#line 1316 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.cpp"
    break;

  case 49: // assignment_int: "identifier" ":=" exp
#line 251 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.y"
                          {
        yylhs.value.as < std::shared_ptr<AssIntLine> > () = std::make_shared<AssIntLine>(&driver, yystack_[2].value.as < std::string > (), yystack_[0].value.as < std::shared_ptr<Expression> > ());
        if (driver.location_debug) {
            std::cerr << driver.location << std::endl;
        }
    }
#line 1327 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.cpp"
    break;

  case 50: // assignment_int: error ";"
#line 257 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.y"
                {
    	std::cerr << "You should provide assignment in the form: variable := expression ; " << std::endl;
    }
#line 1335 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.cpp"
    break;

  case 51: // assignment_str: "identifier" ":=" "string"
#line 261 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.y"
                                         {
    yylhs.value.as < std::shared_ptr<AssStrLine> > () = std::make_shared<AssStrLine>(&driver, yystack_[2].value.as < std::string > (), yystack_[0].value.as < std::string > ());
    if (driver.location_debug) {
                std::cerr << driver.location << std::endl;
            }
    }
#line 1346 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.cpp"
    break;

  case 52: // assignment_bool: "identifier" ":=" condition
#line 268 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.y"
                                             {
    yylhs.value.as < std::shared_ptr<AssBoolLine> > () = std::make_shared<AssBoolLine>(&driver, yystack_[2].value.as < std::string > (), yystack_[0].value.as < std::shared_ptr<Condition> > ());
    if (driver.location_debug) {
                std::cerr << driver.location << std::endl;
            }
    }
#line 1357 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.cpp"
    break;

  case 53: // exp: "number"
#line 276 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.y"
             { yylhs.value.as < std::shared_ptr<Expression> > () = std::make_shared<NumExp>(yystack_[0].value.as < int > ()); }
#line 1363 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.cpp"
    break;

  case 54: // exp: "identifier"
#line 277 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.y"
                   { yylhs.value.as < std::shared_ptr<Expression> > () = std::make_shared<IdentExp>(&driver, yystack_[0].value.as < std::string > ()); }
#line 1369 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.cpp"
    break;

  case 55: // exp: exp "+" exp
#line 278 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.y"
                  {yylhs.value.as < std::shared_ptr<Expression> > () = std::make_shared<AddExp>(yystack_[2].value.as < std::shared_ptr<Expression> > (), yystack_[0].value.as < std::shared_ptr<Expression> > ()); }
#line 1375 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.cpp"
    break;

  case 56: // exp: exp "-" exp
#line 279 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.y"
                  {yylhs.value.as < std::shared_ptr<Expression> > () = std::make_shared<MinusExp>(yystack_[2].value.as < std::shared_ptr<Expression> > (), yystack_[0].value.as < std::shared_ptr<Expression> > ()); }
#line 1381 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.cpp"
    break;

  case 57: // exp: exp "*" exp
#line 280 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.y"
                  {yylhs.value.as < std::shared_ptr<Expression> > () = std::make_shared<MulExp>(yystack_[2].value.as < std::shared_ptr<Expression> > (), yystack_[0].value.as < std::shared_ptr<Expression> > ()); }
#line 1387 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.cpp"
    break;

  case 58: // exp: exp "div" exp
#line 281 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.y"
                    {yylhs.value.as < std::shared_ptr<Expression> > () = std::make_shared<DivExp>(yystack_[2].value.as < std::shared_ptr<Expression> > (), yystack_[0].value.as < std::shared_ptr<Expression> > ()); }
#line 1393 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.cpp"
    break;

  case 59: // exp: exp "mod" exp
#line 282 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.y"
                    {yylhs.value.as < std::shared_ptr<Expression> > () = std::make_shared<ModExp>(yystack_[2].value.as < std::shared_ptr<Expression> > (), yystack_[0].value.as < std::shared_ptr<Expression> > ()); }
#line 1399 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.cpp"
    break;

  case 60: // exp: "-" exp
#line 283 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.y"
              {yylhs.value.as < std::shared_ptr<Expression> > () = std::make_shared<NegExp>(yystack_[0].value.as < std::shared_ptr<Expression> > ()); }
#line 1405 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.cpp"
    break;

  case 61: // exp: "(" exp ")"
#line 284 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.y"
                  {yylhs.value.as < std::shared_ptr<Expression> > () = yystack_[1].value.as < std::shared_ptr<Expression> > (); }
#line 1411 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.cpp"
    break;


#line 1415 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.cpp"

            default:
              break;
            }
        }
#if YY_EXCEPTIONS
      catch (const syntax_error& yyexc)
        {
          YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
          error (yyexc);
          YYERROR;
        }
#endif // YY_EXCEPTIONS
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, YY_MOVE (yylhs));
    }
    goto yynewstate;


  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        context yyctx (*this, yyla);
        std::string msg = yysyntax_error_ (yyctx);
        error (yyla.location, YY_MOVE (msg));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.kind () == symbol_kind::S_YYEOF)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:
    /* Pacify compilers when the user code never invokes YYERROR and
       the label yyerrorlab therefore never appears in user code.  */
    if (false)
      YYERROR;

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    YY_STACK_PRINT ();
    goto yyerrlab1;


  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    // Pop stack until we find a state that shifts the error token.
    for (;;)
      {
        yyn = yypact_[+yystack_[0].state];
        if (!yy_pact_value_is_default_ (yyn))
          {
            yyn += symbol_kind::S_YYerror;
            if (0 <= yyn && yyn <= yylast_
                && yycheck_[yyn] == symbol_kind::S_YYerror)
              {
                yyn = yytable_[yyn];
                if (0 < yyn)
                  break;
              }
          }

        // Pop the current state because it cannot handle the error token.
        if (yystack_.size () == 1)
          YYABORT;

        yyerror_range[1].location = yystack_[0].location;
        yy_destroy_ ("Error: popping", yystack_[0]);
        yypop_ ();
        YY_STACK_PRINT ();
      }
    {
      stack_symbol_type error_token;

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

      // Shift the error token.
      error_token.state = state_type (yyn);
      yypush_ ("Shifting", YY_MOVE (error_token));
    }
    goto yynewstate;


  /*-------------------------------------.
  | yyacceptlab -- YYACCEPT comes here.  |
  `-------------------------------------*/
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;


  /*-----------------------------------.
  | yyabortlab -- YYABORT comes here.  |
  `-----------------------------------*/
  yyabortlab:
    yyresult = 1;
    goto yyreturn;


  /*-----------------------------------------------------.
  | yyreturn -- parsing is finished, return the result.  |
  `-----------------------------------------------------*/
  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    YY_STACK_PRINT ();
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
#if YY_EXCEPTIONS
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack\n";
        // Do not try to display the values of the reclaimed symbols,
        // as their printers might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
#endif // YY_EXCEPTIONS
  }

  void
  parser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what ());
  }

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  parser::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr;
        char const *yyp = yystr;

        for (;;)
          switch (*++yyp)
            {
            case '\'':
            case ',':
              goto do_not_strip_quotes;

            case '\\':
              if (*++yyp != '\\')
                goto do_not_strip_quotes;
              else
                goto append;

            append:
            default:
              yyr += *yyp;
              break;

            case '"':
              return yyr;
            }
      do_not_strip_quotes: ;
      }

    return yystr;
  }

  std::string
  parser::symbol_name (symbol_kind_type yysymbol)
  {
    return yytnamerr_ (yytname_[yysymbol]);
  }



  // parser::context.
  parser::context::context (const parser& yyparser, const symbol_type& yyla)
    : yyparser_ (yyparser)
    , yyla_ (yyla)
  {}

  int
  parser::context::expected_tokens (symbol_kind_type yyarg[], int yyargn) const
  {
    // Actual number of expected tokens
    int yycount = 0;

    const int yyn = yypact_[+yyparser_.yystack_[0].state];
    if (!yy_pact_value_is_default_ (yyn))
      {
        /* Start YYX at -YYN if negative to avoid negative indexes in
           YYCHECK.  In other words, skip the first -YYN actions for
           this state because they are default actions.  */
        const int yyxbegin = yyn < 0 ? -yyn : 0;
        // Stay within bounds of both yycheck and yytname.
        const int yychecklim = yylast_ - yyn + 1;
        const int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
        for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
          if (yycheck_[yyx + yyn] == yyx && yyx != symbol_kind::S_YYerror
              && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
            {
              if (!yyarg)
                ++yycount;
              else if (yycount == yyargn)
                return 0;
              else
                yyarg[yycount++] = YY_CAST (symbol_kind_type, yyx);
            }
      }

    if (yyarg && yycount == 0 && 0 < yyargn)
      yyarg[0] = symbol_kind::S_YYEMPTY;
    return yycount;
  }






  int
  parser::yy_syntax_error_arguments_ (const context& yyctx,
                                                 symbol_kind_type yyarg[], int yyargn) const
  {
    /* There are many possibilities here to consider:
       - If this state is a consistent state with a default action, then
         the only way this function was invoked is if the default action
         is an error action.  In that case, don't check for expected
         tokens because there are none.
       - The only way there can be no lookahead present (in yyla) is
         if this state is a consistent state with a default action.
         Thus, detecting the absence of a lookahead is sufficient to
         determine that there is no unexpected or expected token to
         report.  In that case, just report a simple "syntax error".
       - Don't assume there isn't a lookahead just because this state is
         a consistent state with a default action.  There might have
         been a previous inconsistent state, consistent state with a
         non-default action, or user semantic action that manipulated
         yyla.  (However, yyla is currently not documented for users.)
       - Of course, the expected token list depends on states to have
         correct lookahead information, and it depends on the parser not
         to perform extra reductions after fetching a lookahead from the
         scanner and before detecting a syntax error.  Thus, state merging
         (from LALR or IELR) and default reductions corrupt the expected
         token list.  However, the list is correct for canonical LR with
         one exception: it will still contain any token that will not be
         accepted due to an error action in a later state.
    */

    if (!yyctx.lookahead ().empty ())
      {
        if (yyarg)
          yyarg[0] = yyctx.token ();
        int yyn = yyctx.expected_tokens (yyarg ? yyarg + 1 : yyarg, yyargn - 1);
        return yyn + 1;
      }
    return 0;
  }

  // Generate an error message.
  std::string
  parser::yysyntax_error_ (const context& yyctx) const
  {
    // Its maximum.
    enum { YYARGS_MAX = 5 };
    // Arguments of yyformat.
    symbol_kind_type yyarg[YYARGS_MAX];
    int yycount = yy_syntax_error_arguments_ (yyctx, yyarg, YYARGS_MAX);

    char const* yyformat = YY_NULLPTR;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
      default: // Avoid compiler warnings.
        YYCASE_ (0, YY_("syntax error"));
        YYCASE_ (1, YY_("syntax error, unexpected %s"));
        YYCASE_ (2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_ (3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_ (4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_ (5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    std::string yyres;
    // Argument number.
    std::ptrdiff_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += symbol_name (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  const signed char parser::yypact_ninf_ = -67;

  const signed char parser::yytable_ninf_ = -1;

  const short
  parser::yypact_[] =
  {
     -67,    17,    -1,   -67,   -25,   -67,   -67,   -67,   -67,    39,
      27,    76,   -23,    -9,   -67,   231,    13,     4,     0,   231,
      34,    56,   -67,    46,    49,    60,   -67,   -67,   -67,    63,
      69,    72,    77,    79,    80,   -67,   -67,     8,   231,   -67,
     -67,   231,   -67,   -67,   -24,   284,   103,   -67,    95,   -29,
     -67,   190,   -67,   -67,   -67,   -67,   -67,   -67,   -67,   -67,
     -67,     8,    -6,    -5,   270,    33,   231,   231,    48,     8,
       8,     8,     8,     8,     8,     8,     8,     8,     8,     8,
      87,    89,   245,     8,    62,   -67,    33,   284,   298,   -67,
     -67,   -67,   -67,   -67,    65,    -6,    -6,   -67,   306,   306,
     306,   306,   306,   306,   -67,   -67,   -67,   -67,   -67,   242,
     -67,   -67,    83,    96,     8,   117,    70,   -67,   -67,   236,
     -67,   130,   151,   164,   -67,   -67,   -67,   -67,   -67,   185,
     198,   -67,   -67
  };

  const signed char
  parser::yydefact_[] =
  {
       3,     0,     0,     1,     0,     5,    11,     4,     9,     0,
       0,     0,     0,     0,    13,     0,     0,     0,     0,     0,
       0,     0,    12,     0,     0,     0,    19,    20,    18,     0,
       0,     0,     0,     0,     0,    10,    50,     0,     0,    47,
      46,     0,    54,    53,     0,     0,     0,     2,     0,     0,
      16,     0,    22,    21,    23,    14,    15,    17,     6,     8,
       7,     0,    60,     0,     0,    48,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      54,     0,     0,     0,     0,    51,    52,    49,     0,    43,
      61,    44,    45,    11,    33,    56,    55,    57,    39,    41,
      40,    42,    37,    38,    59,    58,    24,    26,    25,     0,
      11,    30,     0,     0,     0,     0,    32,    11,    35,     0,
      29,     0,     0,     0,    11,    36,    34,    11,    28,     0,
       0,    31,    27
  };

  const short
  parser::yypgoto_[] =
  {
     -67,   -67,   -67,   -67,   -67,   139,   -66,   -67,   -67,   -67,
     -67,   -67,   -67,     7,   -67,   -67,   -67,   -37
  };

  const signed char
  parser::yydefgoto_[] =
  {
       0,     1,     2,     7,     9,    10,    22,    23,    24,    25,
      26,    27,    28,    44,    29,    30,    31,    45
  };

  const unsigned char
  parser::yytable_[] =
  {
      62,    64,    94,     4,    71,    66,    67,    36,    89,    82,
      66,    67,    84,    68,    87,     5,    37,     3,   111,     8,
      61,    35,    78,    79,    88,    46,    49,    47,    13,    66,
      67,     6,    95,    96,    97,    98,    99,   100,   101,   102,
     103,   104,   105,    14,    48,    63,   109,   118,    65,    13,
      50,    15,    42,    43,    16,   125,    11,   128,    86,    51,
      17,    12,    52,    13,    14,    53,    18,    66,    67,    19,
      20,    21,    15,    91,    92,    16,    54,   119,    14,    55,
      93,    32,    33,    34,    13,    56,    15,    18,    57,    16,
      19,    20,    21,    58,   110,    59,    60,    13,    83,    14,
     106,    18,   107,   113,    19,    20,    21,    15,   121,     0,
      16,    37,    14,     0,     0,    61,   116,     0,    13,     0,
      15,     0,    18,    16,     0,    19,    20,    21,   117,     0,
       0,    13,     0,    14,     0,    18,     0,     0,    19,    20,
      21,    15,     0,     0,    16,     0,    14,    80,    43,    81,
     120,     0,    13,     0,    15,     0,    18,    16,     0,    19,
      20,    21,   124,     0,     0,    13,     0,    14,     0,    18,
       0,     0,    19,    20,    21,    15,     0,     0,    16,     0,
      14,     0,     0,     0,   126,     0,    13,     0,    15,     0,
      18,    16,     0,    19,    20,    21,   127,     0,    37,    13,
       0,    14,    38,    18,     0,     0,    19,    20,    21,    15,
       0,     0,    16,     0,    14,     0,     0,     0,   131,     0,
      39,    40,    15,     0,    18,    16,    41,    19,    20,    21,
       0,   132,   112,     0,    42,    43,    85,    18,     0,    37,
      19,    20,    21,    38,    69,    70,    71,     0,     0,   115,
      69,    70,    71,    69,    70,    71,   122,     0,   108,     0,
       0,    39,    40,   129,    78,    79,   130,    41,     0,     0,
      78,    79,     0,    78,    79,    42,    43,   123,    69,    70,
      71,     0,   114,    90,     0,     0,     0,     0,    72,    73,
      74,    75,    69,    70,    71,    76,    77,     0,    78,    79,
       0,     0,    72,    73,    74,    75,    69,    70,    71,    76,
      77,    90,    78,    79,    69,    70,    71,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    78,    79,     0,     0,
       0,     0,     0,     0,    78,    79
  };

  const signed char
  parser::yycheck_[] =
  {
      37,    38,    68,     4,    10,    34,    35,    16,    13,    46,
      34,    35,    41,    37,    51,    16,     8,     0,    84,    44,
      12,    44,    28,    29,    61,    12,    19,    23,     1,    34,
      35,    32,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    16,    44,    38,    83,   113,    41,     1,
      16,    24,    44,    45,    27,   121,    17,   123,    51,     3,
      33,    22,    16,     1,    16,    16,    39,    34,    35,    42,
      43,    44,    24,    66,    67,    27,    16,   114,    16,    16,
      32,     5,     6,     7,     1,    16,    24,    39,    16,    27,
      42,    43,    44,    16,    32,    16,    16,     1,     3,    16,
      13,    39,    13,    38,    42,    43,    44,    24,    38,    -1,
      27,     8,    16,    -1,    -1,    12,    33,    -1,     1,    -1,
      24,    -1,    39,    27,    -1,    42,    43,    44,    32,    -1,
      -1,     1,    -1,    16,    -1,    39,    -1,    -1,    42,    43,
      44,    24,    -1,    -1,    27,    -1,    16,    44,    45,    46,
      33,    -1,     1,    -1,    24,    -1,    39,    27,    -1,    42,
      43,    44,    32,    -1,    -1,     1,    -1,    16,    -1,    39,
      -1,    -1,    42,    43,    44,    24,    -1,    -1,    27,    -1,
      16,    -1,    -1,    -1,    33,    -1,     1,    -1,    24,    -1,
      39,    27,    -1,    42,    43,    44,    32,    -1,     8,     1,
      -1,    16,    12,    39,    -1,    -1,    42,    43,    44,    24,
      -1,    -1,    27,    -1,    16,    -1,    -1,    -1,    33,    -1,
      30,    31,    24,    -1,    39,    27,    36,    42,    43,    44,
      -1,    33,    93,    -1,    44,    45,    46,    39,    -1,     8,
      42,    43,    44,    12,     8,     9,    10,    -1,    -1,   110,
       8,     9,    10,     8,     9,    10,   117,    -1,    13,    -1,
      -1,    30,    31,   124,    28,    29,   127,    36,    -1,    -1,
      28,    29,    -1,    28,    29,    44,    45,    41,     8,     9,
      10,    -1,    40,    13,    -1,    -1,    -1,    -1,    18,    19,
      20,    21,     8,     9,    10,    25,    26,    -1,    28,    29,
      -1,    -1,    18,    19,    20,    21,     8,     9,    10,    25,
      26,    13,    28,    29,     8,     9,    10,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    28,    29,    -1,    -1,
      -1,    -1,    -1,    -1,    28,    29
  };

  const signed char
  parser::yystos_[] =
  {
       0,    48,    49,     0,     4,    16,    32,    50,    44,    51,
      52,    17,    22,     1,    16,    24,    27,    33,    39,    42,
      43,    44,    53,    54,    55,    56,    57,    58,    59,    61,
      62,    63,     5,     6,     7,    44,    16,     8,    12,    30,
      31,    36,    44,    45,    60,    64,    12,    23,    44,    60,
      16,     3,    16,    16,    16,    16,    16,    16,    16,    16,
      16,    12,    64,    60,    64,    60,    34,    35,    37,     8,
       9,    10,    18,    19,    20,    21,    25,    26,    28,    29,
      44,    46,    64,     3,    41,    46,    60,    64,    64,    13,
      13,    60,    60,    32,    53,    64,    64,    64,    64,    64,
      64,    64,    64,    64,    64,    64,    13,    13,    13,    64,
      32,    53,    52,    38,    40,    52,    33,    32,    53,    64,
      33,    38,    52,    41,    32,    53,    33,    32,    53,    52,
      52,    33,    33
  };

  const signed char
  parser::yyr1_[] =
  {
       0,    47,    48,    49,    49,    50,    50,    50,    50,    51,
      51,    52,    52,    53,    53,    53,    53,    53,    53,    53,
      53,    53,    53,    53,    54,    55,    56,    57,    57,    58,
      58,    59,    59,    59,    59,    59,    59,    60,    60,    60,
      60,    60,    60,    60,    60,    60,    60,    60,    60,    61,
      61,    62,    63,    64,    64,    64,    64,    64,    64,    64,
      64,    64
  };

  const signed char
  parser::yyr2_[] =
  {
       0,     2,     5,     0,     2,     1,     5,     5,     5,     1,
       3,     0,     2,     1,     2,     2,     2,     2,     1,     1,
       1,     2,     2,     2,     4,     4,     4,    10,     8,     6,
       4,    10,     6,     4,     8,     6,     8,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     1,     1,     2,     3,
       2,     3,     3,     1,     1,     3,     3,     3,     3,     3,
       2,     3
  };


#if YYDEBUG || 1
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a YYNTOKENS, nonterminals.
  const char*
  const parser::yytname_[] =
  {
  "\"end of file\"", "error", "\"invalid token\"", "\":=\"", "\"var\"",
  "\"integer\"", "\"str\"", "\"bool\"", "\"-\"", "\"+\"", "\"*\"", "\"/\"",
  "\"(\"", "\")\"", "\"{\"", "\"}\"", "\";\"", "\":\"", "\"<\"", "\"<=\"",
  "\">\"", "\">=\"", "\",\"", "\".\"", "\"if\"", "\"=\"", "\"!=\"",
  "\"print\"", "\"mod\"", "\"div\"", "\"true\"", "\"false\"", "\"begin\"",
  "\"end\"", "\"and\"", "\"or\"", "\"not\"", "\"then\"", "\"else\"",
  "\"for\"", "\"to\"", "\"do\"", "\"while\"", "\"break\"",
  "\"identifier\"", "\"number\"", "\"string\"", "$accept", "unit",
  "declarations", "declaration", "identifiers", "lines", "line",
  "printident", "printexp", "printstr", "forcycle", "whilecycle", "case",
  "condition", "assignment_int", "assignment_str", "assignment_bool",
  "exp", YY_NULLPTR
  };
#endif


#if YYDEBUG
  const short
  parser::yyrline_[] =
  {
       0,   167,   167,   172,   173,   176,   177,   178,   179,   182,
     183,   187,   188,   191,   192,   193,   194,   195,   196,   197,
     198,   199,   200,   201,   203,   205,   207,   209,   211,   215,
     217,   221,   223,   225,   227,   229,   231,   235,   237,   238,
     239,   240,   241,   243,   244,   245,   246,   247,   248,   251,
     257,   261,   268,   276,   277,   278,   279,   280,   281,   282,
     283,   284
  };

  void
  parser::yy_stack_print_ () const
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << int (i->state);
    *yycdebug_ << '\n';
  }

  void
  parser::yy_reduce_print_ (int yyrule) const
  {
    int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):\n";
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG


} // yy
#line 2009 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.cpp"

#line 286 "/Users/urzavoge/Desktop/work/unused-repos/practice-interpreter/parser.y"


void
yy::parser::error(const location_type& l, const std::string& m)
{
  std::cerr << l << ": " << m << '\n';
}

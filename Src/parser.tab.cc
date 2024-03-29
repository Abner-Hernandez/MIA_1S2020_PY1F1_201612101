// A Bison parser, made by GNU Bison 3.0.4.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

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


// First part of user declarations.

#line 37 "parser.tab.cc" // lalr1.cc:404

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

#include "parser.tab.hh"

// User implementation prologue.

#line 51 "parser.tab.cc" // lalr1.cc:412
// Unqualified %code blocks.
#line 20 "parser.yy" // lalr1.cc:413

#include "driver.h"
#include <iostream>
#include "methods.cpp"

#line 59 "parser.tab.cc" // lalr1.cc:413


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
    while (/*CONSTCOND*/ false)
# endif


// Suppress unused-variable warnings by "using" E.
#define YYUSE(E) ((void) (E))

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
      *yycdebug_ << std::endl;                  \
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
      yystack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE(Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void>(0)
# define YY_STACK_PRINT()                static_cast<void>(0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

#line 5 "parser.yy" // lalr1.cc:479
namespace yy {
#line 145 "parser.tab.cc" // lalr1.cc:479

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  analizer_parser::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr = "";
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
              // Fall through.
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


  /// Build a parser object.
  analizer_parser::analizer_parser (analizer_driver& driver_yyarg)
    :
#if YYDEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      driver (driver_yyarg)
  {}

  analizer_parser::~analizer_parser ()
  {}


  /*---------------.
  | Symbol types.  |
  `---------------*/



  // by_state.
  inline
  analizer_parser::by_state::by_state ()
    : state (empty_state)
  {}

  inline
  analizer_parser::by_state::by_state (const by_state& other)
    : state (other.state)
  {}

  inline
  void
  analizer_parser::by_state::clear ()
  {
    state = empty_state;
  }

  inline
  void
  analizer_parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  inline
  analizer_parser::by_state::by_state (state_type s)
    : state (s)
  {}

  inline
  analizer_parser::symbol_number_type
  analizer_parser::by_state::type_get () const
  {
    if (state == empty_state)
      return empty_symbol;
    else
      return yystos_[state];
  }

  inline
  analizer_parser::stack_symbol_type::stack_symbol_type ()
  {}


  inline
  analizer_parser::stack_symbol_type::stack_symbol_type (state_type s, symbol_type& that)
    : super_type (s, that.location)
  {
      switch (that.type_get ())
    {
      case 20: // unitl
      case 23: // typep
        value.move< char > (that.value);
        break;

      case 28: // numero
        value.move< float > (that.value);
        break;

      case 3: // size
      case 4: // fit
      case 5: // unit
      case 6: // path
      case 7: // mkdisk
      case 8: // rmdisk
      case 9: // mount
      case 10: // unmount
      case 11: // id
      case 12: // fdisk
      case 13: // deleter
      case 14: // add
      case 15: // rep
      case 16: // name
      case 17: // exec
      case 18: // typer
      case 19: // pather
      case 21: // assign
      case 22: // adj
      case 24: // idvda
      case 25: // tpdelete
      case 26: // minus
      case 27: // npart
      case 30: // INICIO
      case 31: // ADMINIST
      case 32: // MKPARM
      case 33: // FDISK
      case 34: // SIMBOL
      case 35: // DMOUNT
      case 36: // DREP
        value.move< string > (that.value);
        break;

      default:
        break;
    }

    // that is emptied.
    that.type = empty_symbol;
  }

  inline
  analizer_parser::stack_symbol_type&
  analizer_parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
      switch (that.type_get ())
    {
      case 20: // unitl
      case 23: // typep
        value.copy< char > (that.value);
        break;

      case 28: // numero
        value.copy< float > (that.value);
        break;

      case 3: // size
      case 4: // fit
      case 5: // unit
      case 6: // path
      case 7: // mkdisk
      case 8: // rmdisk
      case 9: // mount
      case 10: // unmount
      case 11: // id
      case 12: // fdisk
      case 13: // deleter
      case 14: // add
      case 15: // rep
      case 16: // name
      case 17: // exec
      case 18: // typer
      case 19: // pather
      case 21: // assign
      case 22: // adj
      case 24: // idvda
      case 25: // tpdelete
      case 26: // minus
      case 27: // npart
      case 30: // INICIO
      case 31: // ADMINIST
      case 32: // MKPARM
      case 33: // FDISK
      case 34: // SIMBOL
      case 35: // DMOUNT
      case 36: // DREP
        value.copy< string > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    return *this;
  }


  template <typename Base>
  inline
  void
  analizer_parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if YYDEBUG
  template <typename Base>
  void
  analizer_parser::yy_print_ (std::ostream& yyo,
                                     const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YYUSE (yyoutput);
    symbol_number_type yytype = yysym.type_get ();
    // Avoid a (spurious) G++ 4.8 warning about "array subscript is
    // below array bounds".
    if (yysym.empty ())
      std::abort ();
    yyo << (yytype < yyntokens_ ? "token" : "nterm")
        << ' ' << yytname_[yytype] << " ("
        << yysym.location << ": ";
    switch (yytype)
    {
            case 3: // size

#line 65 "parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< string > (); }
#line 396 "parser.tab.cc" // lalr1.cc:636
        break;

      case 4: // fit

#line 65 "parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< string > (); }
#line 403 "parser.tab.cc" // lalr1.cc:636
        break;

      case 5: // unit

#line 65 "parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< string > (); }
#line 410 "parser.tab.cc" // lalr1.cc:636
        break;

      case 6: // path

#line 65 "parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< string > (); }
#line 417 "parser.tab.cc" // lalr1.cc:636
        break;

      case 7: // mkdisk

#line 65 "parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< string > (); }
#line 424 "parser.tab.cc" // lalr1.cc:636
        break;

      case 8: // rmdisk

#line 65 "parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< string > (); }
#line 431 "parser.tab.cc" // lalr1.cc:636
        break;

      case 9: // mount

#line 65 "parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< string > (); }
#line 438 "parser.tab.cc" // lalr1.cc:636
        break;

      case 10: // unmount

#line 65 "parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< string > (); }
#line 445 "parser.tab.cc" // lalr1.cc:636
        break;

      case 11: // id

#line 65 "parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< string > (); }
#line 452 "parser.tab.cc" // lalr1.cc:636
        break;

      case 12: // fdisk

#line 65 "parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< string > (); }
#line 459 "parser.tab.cc" // lalr1.cc:636
        break;

      case 13: // deleter

#line 65 "parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< string > (); }
#line 466 "parser.tab.cc" // lalr1.cc:636
        break;

      case 14: // add

#line 65 "parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< string > (); }
#line 473 "parser.tab.cc" // lalr1.cc:636
        break;

      case 15: // rep

#line 65 "parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< string > (); }
#line 480 "parser.tab.cc" // lalr1.cc:636
        break;

      case 16: // name

#line 65 "parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< string > (); }
#line 487 "parser.tab.cc" // lalr1.cc:636
        break;

      case 17: // exec

#line 65 "parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< string > (); }
#line 494 "parser.tab.cc" // lalr1.cc:636
        break;

      case 18: // typer

#line 65 "parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< string > (); }
#line 501 "parser.tab.cc" // lalr1.cc:636
        break;

      case 19: // pather

#line 65 "parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< string > (); }
#line 508 "parser.tab.cc" // lalr1.cc:636
        break;

      case 20: // unitl

#line 65 "parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< char > (); }
#line 515 "parser.tab.cc" // lalr1.cc:636
        break;

      case 21: // assign

#line 65 "parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< string > (); }
#line 522 "parser.tab.cc" // lalr1.cc:636
        break;

      case 22: // adj

#line 65 "parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< string > (); }
#line 529 "parser.tab.cc" // lalr1.cc:636
        break;

      case 23: // typep

#line 65 "parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< char > (); }
#line 536 "parser.tab.cc" // lalr1.cc:636
        break;

      case 24: // idvda

#line 65 "parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< string > (); }
#line 543 "parser.tab.cc" // lalr1.cc:636
        break;

      case 25: // tpdelete

#line 65 "parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< string > (); }
#line 550 "parser.tab.cc" // lalr1.cc:636
        break;

      case 26: // minus

#line 65 "parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< string > (); }
#line 557 "parser.tab.cc" // lalr1.cc:636
        break;

      case 27: // npart

#line 65 "parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< string > (); }
#line 564 "parser.tab.cc" // lalr1.cc:636
        break;

      case 28: // numero

#line 65 "parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< float > (); }
#line 571 "parser.tab.cc" // lalr1.cc:636
        break;

      case 30: // INICIO

#line 65 "parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< string > (); }
#line 578 "parser.tab.cc" // lalr1.cc:636
        break;

      case 31: // ADMINIST

#line 65 "parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< string > (); }
#line 585 "parser.tab.cc" // lalr1.cc:636
        break;

      case 32: // MKPARM

#line 65 "parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< string > (); }
#line 592 "parser.tab.cc" // lalr1.cc:636
        break;

      case 33: // FDISK

#line 65 "parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< string > (); }
#line 599 "parser.tab.cc" // lalr1.cc:636
        break;

      case 34: // SIMBOL

#line 65 "parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< string > (); }
#line 606 "parser.tab.cc" // lalr1.cc:636
        break;

      case 35: // DMOUNT

#line 65 "parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< string > (); }
#line 613 "parser.tab.cc" // lalr1.cc:636
        break;

      case 36: // DREP

#line 65 "parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< string > (); }
#line 620 "parser.tab.cc" // lalr1.cc:636
        break;


      default:
        break;
    }
    yyo << ')';
  }
#endif

  inline
  void
  analizer_parser::yypush_ (const char* m, state_type s, symbol_type& sym)
  {
    stack_symbol_type t (s, sym);
    yypush_ (m, t);
  }

  inline
  void
  analizer_parser::yypush_ (const char* m, stack_symbol_type& s)
  {
    if (m)
      YY_SYMBOL_PRINT (m, s);
    yystack_.push (s);
  }

  inline
  void
  analizer_parser::yypop_ (unsigned int n)
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  analizer_parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  analizer_parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  analizer_parser::debug_level_type
  analizer_parser::debug_level () const
  {
    return yydebug_;
  }

  void
  analizer_parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  inline analizer_parser::state_type
  analizer_parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

  inline bool
  analizer_parser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  inline bool
  analizer_parser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  analizer_parser::parse ()
  {
    // State.
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

    // FIXME: This shoud be completely indented.  It is not yet to
    // avoid gratuitous conflicts when merging into the master branch.
    try
      {
    YYCDEBUG << "Starting parse" << std::endl;


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, yyla);

    // A new symbol was pushed on the stack.
  yynewstate:
    YYCDEBUG << "Entering state " << yystack_[0].state << std::endl;

    // Accept?
    if (yystack_[0].state == yyfinal_)
      goto yyacceptlab;

    goto yybackup;

    // Backup.
  yybackup:

    // Try to take a decision without lookahead.
    yyn = yypact_[yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token: ";
        try
          {
            symbol_type yylookahead (yylex (driver));
            yyla.move (yylookahead);
          }
        catch (const syntax_error& yyexc)
          {
            error (yyexc);
            goto yyerrlab1;
          }
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.type_get ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.type_get ())
      goto yydefault;

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
    yypush_ ("Shifting", yyn, yyla);
    goto yynewstate;

  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;

  /*-----------------------------.
  | yyreduce -- Do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_(yystack_[yylen].state, yyr1_[yyn]);
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
        switch (yyr1_[yyn])
    {
      case 20: // unitl
      case 23: // typep
        yylhs.value.build< char > ();
        break;

      case 28: // numero
        yylhs.value.build< float > ();
        break;

      case 3: // size
      case 4: // fit
      case 5: // unit
      case 6: // path
      case 7: // mkdisk
      case 8: // rmdisk
      case 9: // mount
      case 10: // unmount
      case 11: // id
      case 12: // fdisk
      case 13: // deleter
      case 14: // add
      case 15: // rep
      case 16: // name
      case 17: // exec
      case 18: // typer
      case 19: // pather
      case 21: // assign
      case 22: // adj
      case 24: // idvda
      case 25: // tpdelete
      case 26: // minus
      case 27: // npart
      case 30: // INICIO
      case 31: // ADMINIST
      case 32: // MKPARM
      case 33: // FDISK
      case 34: // SIMBOL
      case 35: // DMOUNT
      case 36: // DREP
        yylhs.value.build< string > ();
        break;

      default:
        break;
    }


      // Compute the default @$.
      {
        slice<stack_symbol_type, stack_type> slice (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, slice, yylen);
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
      try
        {
          switch (yyn)
            {
  case 2:
#line 69 "parser.yy" // lalr1.cc:859
    { std::cout << yystack_[0].value.as< string > () << '\n';  }
#line 882 "parser.tab.cc" // lalr1.cc:859
    break;

  case 3:
#line 71 "parser.yy" // lalr1.cc:859
    { mkdisk();}
#line 888 "parser.tab.cc" // lalr1.cc:859
    break;

  case 4:
#line 72 "parser.yy" // lalr1.cc:859
    { path = yystack_[0].value.as< string > (); verificar_comillas(path); rmdisk();}
#line 894 "parser.tab.cc" // lalr1.cc:859
    break;

  case 5:
#line 73 "parser.yy" // lalr1.cc:859
    { fdisk();}
#line 900 "parser.tab.cc" // lalr1.cc:859
    break;

  case 6:
#line 74 "parser.yy" // lalr1.cc:859
    { mount();}
#line 906 "parser.tab.cc" // lalr1.cc:859
    break;

  case 7:
#line 75 "parser.yy" // lalr1.cc:859
    { id = yystack_[0].value.as< string > (); unmount();}
#line 912 "parser.tab.cc" // lalr1.cc:859
    break;

  case 8:
#line 76 "parser.yy" // lalr1.cc:859
    { rep();}
#line 918 "parser.tab.cc" // lalr1.cc:859
    break;

  case 9:
#line 77 "parser.yy" // lalr1.cc:859
    { path = yystack_[0].value.as< string > (); verificar_comillas(path); exec = true;}
#line 924 "parser.tab.cc" // lalr1.cc:859
    break;

  case 10:
#line 79 "parser.yy" // lalr1.cc:859
    { size = yystack_[0].value.as< float > ();}
#line 930 "parser.tab.cc" // lalr1.cc:859
    break;

  case 11:
#line 80 "parser.yy" // lalr1.cc:859
    { fit = yystack_[0].value.as< string > ();}
#line 936 "parser.tab.cc" // lalr1.cc:859
    break;

  case 12:
#line 81 "parser.yy" // lalr1.cc:859
    { unit = yystack_[0].value.as< char > ();}
#line 942 "parser.tab.cc" // lalr1.cc:859
    break;

  case 13:
#line 82 "parser.yy" // lalr1.cc:859
    { path = yystack_[0].value.as< string > (); verificar_comillas(path);}
#line 948 "parser.tab.cc" // lalr1.cc:859
    break;

  case 14:
#line 83 "parser.yy" // lalr1.cc:859
    { yylhs.value.as< string > () = "empty";}
#line 954 "parser.tab.cc" // lalr1.cc:859
    break;

  case 15:
#line 85 "parser.yy" // lalr1.cc:859
    { size = yystack_[0].value.as< float > ();}
#line 960 "parser.tab.cc" // lalr1.cc:859
    break;

  case 16:
#line 86 "parser.yy" // lalr1.cc:859
    { fit = yystack_[0].value.as< string > ();}
#line 966 "parser.tab.cc" // lalr1.cc:859
    break;

  case 17:
#line 87 "parser.yy" // lalr1.cc:859
    { unit = yystack_[0].value.as< char > ();}
#line 972 "parser.tab.cc" // lalr1.cc:859
    break;

  case 18:
#line 88 "parser.yy" // lalr1.cc:859
    { path = yystack_[0].value.as< string > (); verificar_comillas(path);}
#line 978 "parser.tab.cc" // lalr1.cc:859
    break;

  case 19:
#line 89 "parser.yy" // lalr1.cc:859
    { type = yystack_[0].value.as< char > ();}
#line 984 "parser.tab.cc" // lalr1.cc:859
    break;

  case 20:
#line 90 "parser.yy" // lalr1.cc:859
    { tdelete = yystack_[0].value.as< string > ();}
#line 990 "parser.tab.cc" // lalr1.cc:859
    break;

  case 21:
#line 91 "parser.yy" // lalr1.cc:859
    { add = yystack_[0].value.as< float > ();}
#line 996 "parser.tab.cc" // lalr1.cc:859
    break;

  case 22:
#line 92 "parser.yy" // lalr1.cc:859
    { name = yystack_[0].value.as< string > ();}
#line 1002 "parser.tab.cc" // lalr1.cc:859
    break;

  case 23:
#line 93 "parser.yy" // lalr1.cc:859
    { yylhs.value.as< string > () = "empty";}
#line 1008 "parser.tab.cc" // lalr1.cc:859
    break;

  case 24:
#line 96 "parser.yy" // lalr1.cc:859
    { sign = "menos";}
#line 1014 "parser.tab.cc" // lalr1.cc:859
    break;

  case 25:
#line 97 "parser.yy" // lalr1.cc:859
    { sign = "mas";}
#line 1020 "parser.tab.cc" // lalr1.cc:859
    break;

  case 26:
#line 99 "parser.yy" // lalr1.cc:859
    { path = yystack_[0].value.as< string > (); verificar_comillas(path);}
#line 1026 "parser.tab.cc" // lalr1.cc:859
    break;

  case 27:
#line 100 "parser.yy" // lalr1.cc:859
    { name = yystack_[0].value.as< string > ();}
#line 1032 "parser.tab.cc" // lalr1.cc:859
    break;

  case 28:
#line 102 "parser.yy" // lalr1.cc:859
    { path = yystack_[0].value.as< string > (); verificar_comillas(path);}
#line 1038 "parser.tab.cc" // lalr1.cc:859
    break;

  case 29:
#line 103 "parser.yy" // lalr1.cc:859
    { name = yystack_[0].value.as< string > ();}
#line 1044 "parser.tab.cc" // lalr1.cc:859
    break;

  case 30:
#line 104 "parser.yy" // lalr1.cc:859
    { id = yystack_[0].value.as< string > ();}
#line 1050 "parser.tab.cc" // lalr1.cc:859
    break;


#line 1054 "parser.tab.cc" // lalr1.cc:859
            default:
              break;
            }
        }
      catch (const syntax_error& yyexc)
        {
          error (yyexc);
          YYERROR;
        }
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;
      YY_STACK_PRINT ();

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, yylhs);
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
        error (yyla.location, yysyntax_error_ (yystack_[0].state, yyla));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.type_get () == yyeof_)
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

    /* Pacify compilers like GCC when the user code never invokes
       YYERROR and the label yyerrorlab therefore never appears in user
       code.  */
    if (false)
      goto yyerrorlab;
    yyerror_range[1].location = yystack_[yylen - 1].location;
    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    goto yyerrlab1;

  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    {
      stack_symbol_type error_token;
      for (;;)
        {
          yyn = yypact_[yystack_[0].state];
          if (!yy_pact_value_is_default_ (yyn))
            {
              yyn += yyterror_;
              if (0 <= yyn && yyn <= yylast_ && yycheck_[yyn] == yyterror_)
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

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

      // Shift the error token.
      error_token.state = yyn;
      yypush_ ("Shifting", error_token);
    }
    goto yynewstate;

    // Accept.
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;

    // Abort.
  yyabortlab:
    yyresult = 1;
    goto yyreturn;

  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack"
                 << std::endl;
        // Do not try to display the values of the reclaimed symbols,
        // as their printer might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
  }

  void
  analizer_parser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what());
  }

  // Generate an error message.
  std::string
  analizer_parser::yysyntax_error_ (state_type yystate, const symbol_type& yyla) const
  {
    // Number of reported tokens (one for the "unexpected", one per
    // "expected").
    size_t yycount = 0;
    // Its maximum.
    enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
    // Arguments of yyformat.
    char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];

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
         scanner and before detecting a syntax error.  Thus, state
         merging (from LALR or IELR) and default reductions corrupt the
         expected token list.  However, the list is correct for
         canonical LR with one exception: it will still contain any
         token that will not be accepted due to an error action in a
         later state.
    */
    if (!yyla.empty ())
      {
        int yytoken = yyla.type_get ();
        yyarg[yycount++] = yytname_[yytoken];
        int yyn = yypact_[yystate];
        if (!yy_pact_value_is_default_ (yyn))
          {
            /* Start YYX at -YYN if negative to avoid negative indexes in
               YYCHECK.  In other words, skip the first -YYN actions for
               this state because they are default actions.  */
            int yyxbegin = yyn < 0 ? -yyn : 0;
            // Stay within bounds of both yycheck and yytname.
            int yychecklim = yylast_ - yyn + 1;
            int yyxend = yychecklim < yyntokens_ ? yychecklim : yyntokens_;
            for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
              if (yycheck_[yyx + yyn] == yyx && yyx != yyterror_
                  && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
                {
                  if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                    {
                      yycount = 1;
                      break;
                    }
                  else
                    yyarg[yycount++] = yytname_[yyx];
                }
          }
      }

    char const* yyformat = YY_NULLPTR;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
        YYCASE_(0, YY_("syntax error"));
        YYCASE_(1, YY_("syntax error, unexpected %s"));
        YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    std::string yyres;
    // Argument number.
    size_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += yytnamerr_ (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  const signed char analizer_parser::yypact_ninf_ = -31;

  const signed char analizer_parser::yytable_ninf_ = -1;

  const signed char
  analizer_parser::yypact_[] =
  {
      21,    17,     2,     3,    -1,     0,     1,    -8,    15,   -31,
      11,    13,    14,    16,    17,    18,    19,    20,     3,    22,
      23,    24,    25,    26,    29,    30,    31,    32,     0,    33,
      37,    38,     1,   -31,   -31,    -4,    39,    40,    43,    17,
      44,    45,    41,   -31,    42,    46,    47,    50,    48,    51,
      49,    52,    54,     0,    53,    56,    55,     1,   -31,   -31,
     -31,   -31,    17,   -31,   -31,   -31,   -31,   -31,   -31,   -31,
     -31,   -31,   -31,    57,   -31,   -31,     0,   -31,   -31,   -31,
     -31,   -31,   -31,     0,     0,     0,   -31
  };

  const unsigned char
  analizer_parser::yydefact_[] =
  {
       0,    14,     0,     0,     0,    23,     0,     0,     0,     2,
       0,     0,     0,     0,    14,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    23,     0,
       0,     0,     0,     9,     1,     0,     0,     0,     0,    14,
       0,     0,     0,     6,     0,     0,     0,     0,     0,     0,
      25,     0,     0,    23,     0,     0,     0,     0,    10,    11,
      12,    13,    14,     4,    26,    27,     7,    15,    16,    17,
      18,    20,    24,     0,    22,    19,    23,    28,    30,    29,
       8,     3,    21,    23,    23,    23,     5
  };

  const signed char
  analizer_parser::yypgoto_[] =
  {
     -31,   -31,   -31,   -13,   -28,   -31,    60,   -30
  };

  const signed char
  analizer_parser::yydefgoto_[] =
  {
      -1,     8,     9,    14,    28,    73,    18,    32
  };

  const unsigned char
  analizer_parser::yytable_[] =
  {
      53,    39,    57,    20,    21,    22,    23,    29,    15,    16,
      19,    33,    30,    24,    25,    34,    26,    31,    27,    17,
      10,    11,    12,    13,    58,    76,    62,    80,     1,     2,
       3,     4,    35,     5,    36,    37,     6,    38,     7,    40,
      41,    42,     0,    44,    45,    46,    47,    48,    83,    81,
      49,    50,    51,    52,    54,    84,    85,    86,    55,    56,
      60,    59,    61,    63,    64,     0,    66,    70,    65,    68,
      69,     0,    77,     0,    67,    72,    71,    75,    43,    74,
      78,     0,    79,     0,     0,    82
  };

  const signed char
  analizer_parser::yycheck_[] =
  {
      28,    14,    32,     3,     4,     5,     6,     6,     6,     6,
      11,    19,    11,    13,    14,     0,    16,    16,    18,    16,
       3,     4,     5,     6,    28,    53,    39,    57,     7,     8,
       9,    10,    21,    12,    21,    21,    15,    21,    17,    21,
      21,    21,    -1,    21,    21,    21,    21,    21,    76,    62,
      21,    21,    21,    21,    21,    83,    84,    85,    21,    21,
      20,    22,    19,    19,    19,    -1,    24,    19,    27,    22,
      20,    -1,    19,    -1,    28,    26,    25,    23,    18,    27,
      24,    -1,    27,    -1,    -1,    28
  };

  const unsigned char
  analizer_parser::yystos_[] =
  {
       0,     7,     8,     9,    10,    12,    15,    17,    30,    31,
       3,     4,     5,     6,    32,     6,     6,    16,    35,    11,
       3,     4,     5,     6,    13,    14,    16,    18,    33,     6,
      11,    16,    36,    19,     0,    21,    21,    21,    21,    32,
      21,    21,    21,    35,    21,    21,    21,    21,    21,    21,
      21,    21,    21,    33,    21,    21,    21,    36,    28,    22,
      20,    19,    32,    19,    19,    27,    24,    28,    22,    20,
      19,    25,    26,    34,    27,    23,    33,    19,    24,    27,
      36,    32,    28,    33,    33,    33,    33
  };

  const unsigned char
  analizer_parser::yyr1_[] =
  {
       0,    29,    30,    31,    31,    31,    31,    31,    31,    31,
      32,    32,    32,    32,    32,    33,    33,    33,    33,    33,
      33,    33,    33,    33,    34,    34,    35,    35,    36,    36,
      36
  };

  const unsigned char
  analizer_parser::yyr2_[] =
  {
       0,     2,     1,     5,     4,     8,     3,     4,     4,     2,
       3,     3,     3,     3,     0,     3,     3,     3,     3,     3,
       3,     4,     3,     0,     1,     0,     3,     3,     3,     3,
       3
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const analizer_parser::yytname_[] =
  {
  "\"eof\"", "error", "$undefined", "size", "fit", "unit", "path",
  "mkdisk", "rmdisk", "mount", "unmount", "id", "fdisk", "deleter", "add",
  "rep", "name", "exec", "typer", "pather", "unitl", "assign", "adj",
  "typep", "idvda", "tpdelete", "minus", "npart", "numero", "$accept",
  "INICIO", "ADMINIST", "MKPARM", "FDISK", "SIMBOL", "DMOUNT", "DREP", YY_NULLPTR
  };

#if YYDEBUG
  const unsigned char
  analizer_parser::yyrline_[] =
  {
       0,    69,    69,    71,    72,    73,    74,    75,    76,    77,
      79,    80,    81,    82,    83,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    96,    97,    99,   100,   102,   103,
     104
  };

  // Print the state stack on the debug stream.
  void
  analizer_parser::yystack_print_ ()
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << i->state;
    *yycdebug_ << std::endl;
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  analizer_parser::yy_reduce_print_ (int yyrule)
  {
    unsigned int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):" << std::endl;
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG


#line 5 "parser.yy" // lalr1.cc:1167
} // yy
#line 1469 "parser.tab.cc" // lalr1.cc:1167
#line 106 "parser.yy" // lalr1.cc:1168


void yy::analizer_parser::error(const location_type& lugar, const std::string& lexema)
{
  std::cout << "Error Sintactico " << lexema << " var " << std::endl;
}

void analizer_driver::init_mount()
{
    init_mounts();
}

bool analizer_driver::get_bool_exec()
{
    if(exec == true)
        return true;
    else
        return false;
}

string analizer_driver::get_path()
{
    if(path.compare("notdefined") != 0)
        return path;
    else
        return "notdefined";
}

void analizer_driver::set_exec_bool()
{
    exec = false;
}



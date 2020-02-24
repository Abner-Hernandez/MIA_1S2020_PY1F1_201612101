%{
# include <cerrno>
#include <stdio.h>
#include <string>
#include "driver.h"
#include "parser.tab.hh"
#undef yywrap
#define yywrap() 1
static yy::location loc;
%}
%option case-insensitive
%option noyywrap nounput batch debug noinput
%option outfile="scanner.cpp"
LETRA [a-zñA-ZÑ]+
DIGITO [0-9]
UNITD ("m"|"k")
ADJ ("BF"|"FF"|"WF")
TYPEP ("P"|"E"|"L")
TPDELETE ("FAST"|"FULL")

PATHER [\"]?([/][^/]+)+"."{LETRA}+[\"]?
VDA ["vd"]{LETRA}{DIGITO}
PARTNAME [\"]?({LETRA}|{DIGITO})*[\"]?
NUMERO {DIGITO}+
COMENTARIOM "/*"[^'*']*"*/"
COMENTARIOL "#"[^*\n]*
COMENTARIOLL "//"[^*\n]*

DELIMITADOR [ \t\r\f\n]+
%%

"-size"         {return yy::analizer_parser::make_size(yytext, loc);}
"-fit"          {return yy::analizer_parser::make_fit(yytext, loc);}
"-unit"         {return yy::analizer_parser::make_unit(yytext, loc);}
"-path"         {return yy::analizer_parser::make_path(yytext, loc);}
"MKDISK"	{return yy::analizer_parser::make_mkdisk(yytext, loc);}
"RMDISK"	{return yy::analizer_parser::make_rmdisk(yytext, loc);}
"MOUNT"         {return yy::analizer_parser::make_mount(yytext, loc);}
"UNMOUNT"       {return yy::analizer_parser::make_unmount(yytext, loc);}
"-id"           {return yy::analizer_parser::make_id(yytext, loc);}
"FDISK"         {return yy::analizer_parser::make_fdisk(yytext, loc);}
"-delete"	{return yy::analizer_parser::make_deleter(yytext, loc);}
"-name"         {return yy::analizer_parser::make_name(yytext, loc);}
"-add"          {return yy::analizer_parser::make_add(yytext, loc);}
"-type"         {return yy::analizer_parser::make_typer(yytext, loc);}
"="             {return yy::analizer_parser::make_assign(yytext, loc);}
"-"             {return yy::analizer_parser::make_minus(yytext, loc);}
"REP"           {return yy::analizer_parser::make_rep(yytext, loc);}
"EXEC"          {return yy::analizer_parser::make_exec(yytext, loc);}
{NUMERO}        {return yy::analizer_parser::make_numero(strtol (yytext, NULL, 10),loc);}
{PATHER}        {return yy::analizer_parser::make_pather(yytext, loc);}
{UNITD}         {return yy::analizer_parser::make_unitl(yytext[0], loc);}
{ADJ}           {return yy::analizer_parser::make_adj(yytext, loc);}
{TYPEP}         {return yy::analizer_parser::make_typep(yytext[0], loc);}
{VDA}           {return yy::analizer_parser::make_idvda(yytext, loc);}
{TPDELETE}      {return yy::analizer_parser::make_tpdelete(yytext, loc);}
{PARTNAME}      {return yy::analizer_parser::make_npart(yytext, loc);}

{DELIMITADOR}   {}
{COMENTARIOM}   {}
{COMENTARIOL}   {}
{COMENTARIOLL}   {}

.               {printf("ERROR LEXICO %s\n",yytext);}
<<EOF>>		{return yy::analizer_parser::make_FIN(loc);}
%%
void analizer_driver::iniciarScanner()
{

    yy_scan_string(file.c_str());
/*
    yy_flex_debug = false;
    if(file.empty() || file == "-"){
      std::cout << "No se encuentra el archivo de entrada \n";
      exit(1);
    }else{
      yyin = fopen (file.c_str (), "r");
    }

*/
}

void analizer_driver::terminarScanner()
{
    fclose(yyin);
}

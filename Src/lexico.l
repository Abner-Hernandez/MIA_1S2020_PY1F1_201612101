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
%option noyywrap nounput batch debug noinput
%option outfile="scanner.cpp"
DIGITO [0-9]
LETRA [a-zA-Z]

NUMERO {DIGITO}+("."{DIGITO}+)?
PATHER ["\""]?[".disk"]+["\""]?

DELIMITADOR [\t\r\f" "]
%%
{NUMERO}        {return yy::analizer_parser::make_numero(strtol (yytext, NULL, 10),loc);}
{PATHER}        {return yy::analizer_parser::make_pather(yytext, loc);}
"-size"         {return yy::analizer_parser::make_size(yytext,loc);}
"-fit"          {return yy::analizer_parser::make_fit(loc);}
"-unit"         {return yy::analizer_parser::make_unit(loc);}
"-path"         {return yy::analizer_parser::make_path(loc);}
"MKDISK"	{return yy::analizer_parser::make_mkdisk(loc);}
"RMDISK"	{return yy::analizer_parser::make_rmdisk(loc);}
"MOUNT"         {return yy::analizer_parser::make_mount(loc);}
"UNMOUNT"       {return yy::analizer_parser::make_unmount(loc);}
"-id"           {return yy::analizer_parser::make_id(loc);}
"FDISK"         {return yy::analizer_parser::make_fdisk(loc);}
"-delete"	{return yy::analizer_parser::make_delete(loc);}
"-name"         {return yy::analizer_parser::make_name(loc);}
"-add"          {return yy::analizer_parser::make_add(loc);}
"REP"           {return yy::analizer_parser::make_rep(loc);}
"EXEC"          {return yy::analizer_parser::make_exec(loc);}


{DELIMITADOR}   {}
.               {printf("ERROR LEXICO %s\n",yytext);}
<<EOF>>		{return yy::analizer_parser::make_FIN(loc);}
%%
void analizer_driver::iniciarScanner()
{
    yy_flex_debug = false;
    if(file.empty() || file == "-"){
      std::cout << "No se encuentra el archivo de entrada \n";
      exit(1);
    }else{
      yyin = fopen (file.c_str (), "r");
    }
}
void analizer_driver::terminarScanner()
{
    fclose(yyin);
}

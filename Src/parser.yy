%skeleton "lalr1.cc" /* -*- C++ -*- */
%require "3.0.2"
%defines
%define parser_class_name {analizer_parser}
%define api.token.constructor
%define api.namespace {yy}
%define api.value.type variant
%define parse.assert
%code requires
{
#include <string>
#include <stdio.h>
using namespace std;
class analizer_driver;
}
%param { analizer_driver& driver }
%locations
%define parse.trace
%define parse.error verbose
%code
{
#include "driver.h"
#include <iostream>

string fit = "notdefined";
string unit = "notdefined";
string path = "notdefined";
string type = "notdefined";
string del = "notdefined";
string name = "notdefined";
string id = "notdefined";
int add = 0;
int size = 0;

void create_disk()
{
    if(path.compare("notdefined") != 0 && size > 0)
    {
        cout << path;


        try {
            FILE *fileC = fopen(path.c_str(), "w+b");
            if (fileC==NULL)
            {
                cout << "\nProblema para crear el archivo\n";
            }
            char letra[1024];
            fwrite(&letra, sizeof(char), 1, fileC);
            fclose(fileC);
        } catch( std::exception& e) {
            std::cout << " a standard exception was caught, with message '" << e.what() << "'\n";
        }
    }
}

}
%define api.token.prefix {TOK_}

//Listadode Terminales
%token <string> size
%token <string> fit
%token <string> unit
%token <string> path
%token <string> mkdisk
%token <string> rmdisk
%token <string> mount
%token <string> unmount
%token <string> id
%token <string> fdisk
%token <string> deleter
%token <string> add
%token <string> rep
%token <string> name
%token <string> exec
%token <string> typer
%token <string> pather
%token <string> unitl
%token <string> assign
%token <string> adj
%token <string> typep
%token <string> namep
%token <string> tpdelete
%token <string> minus
%token <float> numero
%token FIN 0 "eof"

//Listado de No Terminales
%type <string> INICIO
%type <string> ADMINIST
%type <string> MKPARM
%type <string> FDISK
%type <string> DMOUNT
%type <string> DREP
%type <string> SIMBOL

%printer { yyoutput << $$; } <*>;
%%
%start INICIO;

INICIO : ADMINIST { std::cout << $1 << '\n';  };

ADMINIST :  mkdisk MKPARM MKPARM MKPARM MKPARM                          { create_disk();}
            |rmdisk path assign pather
            |fdisk FDISK FDISK FDISK FDISK FDISK FDISK FDISK FDISK
            |mount DMOUNT DMOUNT
            |unmount id assign namep
            |rep DREP DREP DREP
            |exec path assign pather

MKPARM :    size assign numero                                          { size = $3;}
            |fit assign adj                                             { fit = $3;}
            |unit assign unitl                                          { unit = $3;}
            |path assign pather                                         { path = $3;}
            |%empty                                                     { $$ = "empty";};

FDISK :     MKPARM
            |typer assign typep
            |deleter assign tpdelete
            |name assign namep
            |add SIMBOL numero

SIMBOL :    minus
            |%empty;

DMOUNT :    path assign pather
            |name assign namep

DREP :      DMOUNT
            |id assign namep

%%

void yy::analizer_parser::error(const location_type& lugar, const std::string& lexema)
{
  std::cout << "Error Sintactico " << lexema << " var " << std::endl;
}

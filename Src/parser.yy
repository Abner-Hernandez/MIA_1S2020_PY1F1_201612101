%skeleton "lalr1.cc" /* -*- C++ -*- */
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
#include "methods.cpp"
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
%token <char> unitl
%token <string> assign
%token <string> adj
%token <char> typep
%token <string> idvda
%token <string> tpdelete
%token <string> minus
%token <string> npart
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

ADMINIST :  mkdisk MKPARM MKPARM MKPARM MKPARM                          { mkdisk();}
            |rmdisk path assign pather                                  { path = $4; verificar_comillas(path); rmdisk();}
            |fdisk FDISK FDISK FDISK FDISK FDISK FDISK FDISK            { fdisk();}
            |mount DMOUNT DMOUNT                                        { mount();}
            |unmount id assign idvda                                    { id = $4; unmount();}
            |rep DREP DREP DREP                                         { rep();}
            |exec pather                                                { path = $2; verificar_comillas(path); exec = true;};

MKPARM :    size assign numero                                          { size = $3;}
            |fit assign adj                                             { fit = $3;}
            |unit assign unitl                                          { unit = $3;}
            |path assign pather                                         { path = $3; verificar_comillas(path);}
            |%empty                                                     { $$ = "empty";};

FDISK :     size assign numero                                          { size = $3;}
            |fit assign adj                                             { fit = $3;}
            |unit assign unitl                                          { unit = $3;}
            |path assign pather                                         { path = $3; verificar_comillas(path);}
            |typer assign typep                                         { type = $3;}
            |deleter assign tpdelete                                    { tdelete = $3;}
            |add assign SIMBOL numero                                   { add = $4;}
            |name assign npart                                          { name = $3;}
            |%empty                                                     { $$ = "empty";};


SIMBOL :    minus                                                       { sign = "menos";}
            |%empty                                                     { sign = "mas";};

DMOUNT :    path assign pather                                          { path = $3; verificar_comillas(path);}
            |name assign npart                                          { name = $3;};

DREP :      path assign pather                                          { path = $3; verificar_comillas(path);}
            |name assign npart                                          { name = $3;}
            |id assign idvda                                            { id = $3;};

%%

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



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
}
%define api.token.prefix {TOK_}

//Listadode Terminales
%token <string> size
%token fit
%token unit
%token path
%token mkdisk
%token rmdisk
%token mount
%token unmount
%token id
%token fdisk
%token delete
%token add
%token rep
%token name
%token exec
%token <string> pather
%token <float> numero
%token FIN 0 "eof"

//Listado de No Terminales
%type <string> INICIO

%printer { yyoutput << $$; } <*>;
%%
%start INICIO;

INICIO : pather { std::cout << $1 << '\n'; };
   
%%
void yy::analizer_parser::error(const location_type& lugar, const std::string& lexema)
{
  std::cout << "Error Sintactico " << lexema << std::endl;
}

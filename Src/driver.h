#ifndef DRIVER
# define DRIVER
# include <string>
# include "parser.tab.hh"
#define YY_DECL \
  yy::analizer_parser::symbol_type yylex (analizer_driver& driver)
YY_DECL;

class analizer_driver
{
public:
  float resultado;
  void iniciarScanner();
  void terminarScanner();
  void init_mount();
  bool get_bool_exec();
  string get_path();
  void set_exec_bool();

  int parse(const std::string& archivo);
  
  std::string file;
};
#endif

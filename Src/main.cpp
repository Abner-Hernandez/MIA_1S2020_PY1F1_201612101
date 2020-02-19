#include <iostream>
#include <driver.h>
using namespace std;

int main()
{
    string entry = "/home/battleab/analizer/calificacion.sh";
    analizer_driver driver;
    if(driver.parse(entry)){
      printf("La entrada es incorrecta\n");
    }else{
      printf("La entrada es correcta\n");
      //printf("Resultado = %f\n",driver.resultado);
    }
    return 0;
}

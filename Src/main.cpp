#include <iostream>
#include <driver.h>
using namespace std;

int main()
{
    string entry = "";
    analizer_driver driver;
    while (true) {

        getline(cin, entry);
        if(entry.compare("exit") != 0)
        {
            if(driver.parse(entry)){
              printf("La entrada es incorrecta\n");
            }else{
              printf("La entrada es correcta\n");
            }
        }else
            break;
    }

    return 0;
}

#include <iostream>
#include <driver.h>
#include<iostream>
#include<fstream>

using namespace std;

void create_folder_img();

int main()
{
    create_folder_img();
    string entry = "";
    analizer_driver driver;
    driver.init_mount();
    while (true) {

        getline(cin, entry);
        if(entry.compare("exit") != 0 && entry.compare("") != 0)
        {
            if(driver.parse(entry)){
              printf("La entrada es incorrecta\n");
            }else{
                if(driver.get_bool_exec() == true)
                {
                    driver.set_exec_bool();
                    ifstream  file(driver.get_path());
                    if(file.is_open())
                    {
                        string line;
                        while (getline(file, line)) {
                            if(line.compare("") != 0)
                                if(!driver.parse(line))
                                    printf("La entrada es correcta\n");
                        }
                        file.close();
                    }

                }
              printf("La entrada es correcta\n");
            }
        }else if(entry.compare("exit") == 0)
            break;
    }

    return 0;
}

void create_folder_img()
{
    FILE *f = fopen("./Images", "rb");
    if(f == NULL)
        system("mkdir ./Images");
}

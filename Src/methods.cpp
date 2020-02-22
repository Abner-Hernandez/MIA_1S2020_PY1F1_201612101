#include <iostream>
#include <string>
#include <cstdlib>
#include <math.h>
#include <cstring>

using namespace  std;

typedef struct
{
    char part_status;
    char part_type;
    char part_fit;
    int part_start;
    int part_size;
    char part_name[16];
}Particion;

typedef struct
{
    int mbr_tam;
    char mbr_fecha_creacion[18];
    int mbr_disk_signature;
    char disk_fit;
    Particion mbr_particion[4];
}MBR;

typedef struct
{
    char part_status;
    char part_fit;
    int part_start;
    int part_size;
    int part_next;
    char part_name[16];
}EBR;

typedef struct
{
    string id;
    string name;
    int montadas;
    int part_size;
    char type;
    int direccion;
    string path;
}PM;

PM mounts[26][26];
int maxd = 26, maxp = 26;


string fit = "notdefined";
char unit = '*';
string path = "notdefined";
string path_copy = "notdefined";
char type = '*';
string del = "notdefined";
string name = "notdefined";
string id = "notdefined";
string sign = "notdefined";
string tdelete = "notdefined";
FILE *f;
FILE *f_copy;
int add = 0;
int size = 0;
int number = 0;

void mkdisk();
void clean_char(char cad[], int tam);
void default_vars();
void unmount_partitions();
void rmdik();
void get_path_copy();
void agregarAparticion(string path);
void sort_array(Particion n[]);
void setEBR(EBR& val);
void setEBR(EBR& val,int start);
void mount();
void unmount();
void unmount2();
void eliminarParticion(string path);
void setParticion(Particion& val,int start);
void insertaParticion(string path);
void insertaParticionMejor(string path);
void insertaParticionPeor(string path);
void mbr_graph();
void crear_imagen();
void crear_folder();
void disk_graph();
void insertarEBR(EBR& part);
int existepart(int fil);
int existepath();
int pathvacio();
void insertarP(Particion& part);

void default_vars()
{
    fit = "notdefined";
    unit = '*';
    path = "notdefined";
    path_copy = "notdefined";
    type = '*';
    del = "notdefined";
    name = "notdefined";
    id = "notdefined";
    sign = "notdefined";
    tdelete = "notdefined";
    add = 0;
    size = 0;
    number = 0;
}

void crear_folder()
{
    for (unsigned i = 2; i < path.size()  ; i++) {
        if(path.at(i) == '/')
        {
            FILE *f = fopen(path.substr(0, i).c_str(), "rb");
            if(f == NULL)
            {
                string folder = "mkdir " + path.substr(0, i);
                system(folder.c_str());
            }
        }
    }
}

void mkdisk()   // Crear discos
{

    if(path.compare("notdefined") != 0 && size > 0)
    {

        crear_folder();
        f = fopen(path.c_str(), "w+b");

        get_path_copy();
        f_copy = fopen(path_copy.c_str(), "w+b");

        cout << "\n\n" << path_copy << "\n\n";
        if(f == NULL)
            printf("No se pudo crear el archivo\n");
        else
        {
            int tam = 0;
            if(unit == '*' || tolower(unit)  == 'm')
                tam = 1024*1024;
            else
                tam = 1024;
            char t[tam];
            for(int i = 0; i < tam; i++)
            {
                t[i] = '\0';
            }

            fseek(f,0,SEEK_SET);
            for(int j = 0; j < size; j++)
            {
                fwrite(&t,sizeof(t),1,f);
            }

            fseek(f_copy,0,SEEK_SET);
            for(int j = 0; j < size; j++)
            {
                fwrite(&t,sizeof(t),1,f_copy);
            }

            MBR att;
            for(int i = 0; i< 4; i++)
            {
                att.mbr_particion[i].part_fit = '*';
                att.mbr_particion[i].part_size = -1;
                att.mbr_particion[i].part_start = 2147483647;
                att.mbr_particion[i].part_status = '*';
                att.mbr_particion[i].part_type = '*';
                clean_char(att.mbr_particion[i].part_name, 16);
            }
            att.mbr_tam = size*tam;
            time_t tiempo = time(0);
            struct tm *tiem = localtime(&tiempo);
            //tiempo=time(NULL);
            strftime(att.mbr_fecha_creacion, 18, "%d/%m/%Y %H:%M", tiem);


            //att.mbr_fecha_creacion = "123456789127";
            att.mbr_disk_signature = rand();;
            if(fit.compare("notdefined") == 0)
                att.disk_fit = 'f';
            else
                att.disk_fit = tolower(fit.at(0));

            fseek(f,0,SEEK_SET);
            fwrite(&att,sizeof(att),1,f);

            fclose(f);

            fseek(f_copy,0,SEEK_SET);
            att.mbr_disk_signature = rand();;
            fwrite(&att,sizeof(att),1,f_copy);

            fclose(f_copy);
            printf("Se creo correctamete el disco en la ruta %s\n",path.c_str());
            default_vars();

        }
    }else
    {
        printf("Faltan campos obligatorios\n");
    }
}

void rmdisk()
{
    if(path.compare("notdefined"))
    {
        printf("Desea Eliminar el Disco %s\n Ingrese [s/n] :  ", path.c_str());
        char confirm = '*';
        while(1)
        {
            confirm = char(getchar());
            if(tolower(confirm) == 's')
                break;
            if(tolower(confirm) == 'n')
                return;
        }
        unmount_partitions();
        int rm = remove(path.c_str());
        if(rm == 0)
        {
            printf("Se elimino correctamente el disco ubicado en %s\n",path.c_str());
        }else
        {
            printf("No se pudo eliminar correctamente el disco ubicado en %s\n",path.c_str());
        }
        path = "notdefined";
    }
}

void fdisk()
{
    cout << path << name << fit << unit << "size: "<< size ;
    if(path != "notdefined" && name != "notdefined")
    {
        if(unit == '*' || tolower(unit) == 'k')
        {
            size = size*1024;
            add = add*1024;
        }else if(tolower(unit) == 'm')
        {
            size = size*1024*1024;
            add = add*1024*1024;
        }
        cout << size;
        if(type == '*')
            type = 'p';

        if(fit.compare("notdefined") == 0)
            fit = 'w';


        FILE* f = fopen(path.c_str(),"r+b");
        get_path_copy();
        if(f == NULL)
        {
            printf("No se encontro el disco para su modificacion\n");
            return;
        }
        if(tdelete.compare("notdefined") != 0)
        {
            eliminarParticion(path);
            if(path_copy.compare("notdefined") != 0)
                eliminarParticion(path_copy);
            return;
        }
        if(add != 0)
        {
            agregarAparticion(path);
            if(path_copy.compare("notdefined") != 0)
                agregarAparticion(path_copy);
        }
        if(size > 0)
        {
            MBR arr;
            fread(&arr,sizeof(arr),1,f);
            if(type != 'l')
            {
                if(arr.disk_fit == 'f')
                {
                    insertaParticion(path);
                    if(path_copy.compare("notdefined") != 0)
                        insertaParticion(path_copy);
                }else if(arr.disk_fit == 'b')
                {
                    insertaParticionMejor(path);
                    if(path_copy.compare("notdefined") != 0)
                        insertaParticionMejor(path_copy);
                }else if(arr.disk_fit == 'w')
                {
                    insertaParticionPeor(path);
                    if(path_copy.compare("notdefined") != 0)
                        insertaParticionPeor(path_copy);
                }
            }else
            {
                char tp = '*';
                for(int ty = 0; ty <4; ty++)
                {
                    if(arr.mbr_particion[ty].part_type == 'e')
                    {
                        tp = arr.mbr_particion[ty].part_fit;
                    }
                }
                if(tp == 'f')
                {
                    insertaParticion(path);
                    if(path_copy.compare("notdefined") != 0)
                        insertaParticion(path_copy);
                }else if(tp == 'b')
                {
                    insertaParticionMejor(path);
                    if(path_copy.compare("notdefined") != 0)
                        insertaParticionMejor(path_copy);
                }else if(tp == 'w')
                {
                    insertaParticionPeor(path);
                    if(path_copy.compare("notdefined") != 0)
                        insertaParticionPeor(path_copy);
                }else
                {
                    printf("No se puede agregar la particion logica por que no hay una extendida\n");
                }
            }
        }
    }else
    {
        cout << "Hace falta un parametro obligatorio para poder usar la funcion fdisk";
    }
    default_vars();
}

void clean_char(char cad[], int tam){
    for(int i = 0; i< tam; i++){
        cad[i] = '\0';
    }
}

void get_path_copy()
{
    for (int i = path.size()-1; i > 0  ; i--) {

        if(path.substr(i,i+4).compare("copy") == 0)
        {
            return;
        }else if(path.substr(i,i+5) == ".disk")
        {
            path_copy = path.substr(0,i) + "_copy.disk";
            break;
        }
    }
}

void agregarAparticion(string path)
{
    FILE* f = fopen(path.c_str(),"rb+");
    char exit = '*';
    if(f == NULL)
    {
        printf("Error, la ruta del disco a añadir es invalida para la particion %s",name.c_str());
    }else
    {
        MBR att;
        fread(&att,sizeof(att),1,f);
        sort_array(att.mbr_particion);
        int i = 0;
        for(i = 0; i<4; i++)
        {
            if(strcmp(name.c_str(),att.mbr_particion[i].part_name) == 0)
            {
                if(i<3)
                {
                    if(add > 0)
                    {
                        if(fabs(att.mbr_particion[i+1].part_start-(att.mbr_particion[i].part_start+att.mbr_particion[i].part_size))>=fabs(add))
                        {
                            att.mbr_particion[i].part_size = att.mbr_particion[i].part_size + add;
                            printf("Se aumento el tamaño de la particio %s\n", name.c_str());
                            break;
                        }else
                        {
                            printf("No se puede modificar el tamaño de la particion %s no se puede expandir, espacio insuficiente\n", name.c_str());
                        }
                    }else
                    {
                        if(att.mbr_particion[i].part_size-fabs(add)>0)
                        {
                            att.mbr_particion[i].part_size = att.mbr_particion[i].part_size + add;
                            printf("Se disminuyo el tamaño de la particion %s\n", name.c_str());
                            break;
                        }
                        else
                        {
                            printf("No se puede modificar el tamaño de la particion %s no se puede reducir, tamaño demasiado grande\n",name.c_str());
                        }
                    }

                }else
                {
                    if(add > 0)
                    {
                        if((att.mbr_particion[i].part_start+att.mbr_particion[i].part_size+add)<=fabs(att.mbr_tam))
                        {
                            att.mbr_particion[i].part_size = att.mbr_particion[i].part_size + add;
                            printf("Se aumento el tamaño de la particio %s\n", name.c_str());
                            break;
                        }else
                        {
                            printf("No se puede modificar el tamaño de la particion %s no se puede expandir, espacio en disco insuficiente\n", name.c_str());
                        }
                    }else
                    {
                        if(att.mbr_particion[i].part_size-fabs(add)>0)
                        {
                            att.mbr_particion[i].part_size = att.mbr_particion[i].part_size + add;
                            printf("Se aumento el tamaño de la particio %s\n", name.c_str());
                            break;
                        }
                        else
                        {
                            printf("No se puede modificar el tamaño de la particion %s no se puede reducir, tamaño demasiado grande\n", name.c_str());
                        }
                    }
                }
            }
        }

        if(i != 4)
            exit = 's';
        if(exit == '*')
        {
            for(int j = 0; j < 4 ; j++)
            {
                if(att.mbr_particion[j].part_type == 'e')
                {
                    EBR auxE;
                    fseek(f,att.mbr_particion[j].part_start,SEEK_SET);
                    fread(&auxE,sizeof(auxE),1,f);
                    while(auxE.part_next != -1)
                    {
                        if(strcmp(auxE.part_name,name.c_str()) == 0)
                        {
                            break;
                        }
                        fseek(f,auxE.part_next,SEEK_SET);
                        fread(&auxE,sizeof(auxE),1,f);
                    }

                    if(strcmp(auxE.part_name, name.c_str()) != 0)
                    {
                        printf("No se pudo modificar la particion %s debido a que no se encuentra una con ese nombre\n", name.c_str());
                        fclose(f);
                        return;
                    }

                    if(add >0)
                    {
                        if(auxE.part_next != -1)
                        {
                            EBR auxEE;
                            fseek(f,auxE.part_next,SEEK_SET);
                            fread(&auxEE,sizeof(auxEE),1,f);
                            if(auxE.part_start+auxE.part_size+ add < auxEE.part_start)
                            {
                                auxE.part_size = auxE.part_size + add;
                                fseek(f,auxE.part_start,SEEK_SET);
                                fwrite(&auxE,sizeof(auxE),1,f);
                                fclose(f);
                                return;
                            }else
                            {
                                printf("No se puede aumentar el tamaño de la particion %s debido a que no hay espacio libre\n", name.c_str());
                                fclose(f);
                                return;
                            }
                        }else
                        {

                            if((auxE.part_start+auxE.part_size+ add) < (att.mbr_particion[j].part_start +att.mbr_particion[j].part_size))
                            {
                                auxE.part_size = auxE.part_size + add;
                                fseek(f,auxE.part_start,SEEK_SET);
                                fwrite(&auxE,sizeof(auxE),1,f);
                                fclose(f);
                                return;
                            }else
                            {
                                printf("No se puede aumentar el tamaño de la particion %s debido a que no hay espacio libre\n", name.c_str());
                                fclose(f);
                                return;
                            }
                        }

                    }else
                    {
                        if(auxE.part_size + add > 0)
                        {
                            auxE.part_size = auxE.part_size + add;
                            fseek(f,auxE.part_start,SEEK_SET);
                            fwrite(&auxE,sizeof(auxE),1,f);
                            fclose(f);
                            return;

                        }else
                        {
                            printf("Error no se puede reducir tanto espacio a la particion\n");
                            fclose(f);
                            return;
                        }
                    }
                }

            }
        }

        if(exit == '*')
        {
            printf("No se encontro la particion %s para su modificacion\n",name.c_str());
        }
        sort_array(att.mbr_particion);
        fseek(f,0,SEEK_SET);
        fwrite(&att,sizeof(att),1,f);
        fclose(f);
    }

}

void sort_array(Particion n[])
{
    Particion aux;
    for(int i=1; i<4; i++)
    {
        for(int j=0; j<4-i; j++)
        {
            if(n[j].part_start > n[j+1].part_start)
            {
                aux    = n[j+1];
                n[j+1] = n[j];
                n[j]   = aux;
            }
        }
    }
}

void eliminarParticion(string path)
{
    printf("Desea Eliminar la particion %s en el disco %s\n Ingrese [s/n] :  ", name.c_str(),path.c_str());
    char confirm = '*';
    while(1)
    {
        confirm = char(getchar());
        if(tolower(confirm) == 's')
            break;
        if(tolower(confirm) == 'n')
            return;
    }
    FILE* f = fopen(path.c_str(),"rb+");
    char exit = '*';
    if(f == NULL)
    {
        printf("Error, la ruta para eliminar la particion %s es invalida",name.c_str());
    }else
    {
        MBR att;
        fread(&att,sizeof(att),1,f);
        sort_array(att.mbr_particion);
        for(int i = 0; i<4; i++)
        {
            if(strcmp(name.c_str(),att.mbr_particion[i].part_name) == 0)
            {
                char fr = '\0';
                if(tdelete.compare("full"))
                {
                    for(int ty = 0; ty< att.mbr_particion[i].part_size; ty++)
                    {
                        fseek(f,att.mbr_particion[i].part_start+ty,SEEK_SET);
                        fwrite(&fr,sizeof(fr),1,f);
                    }
                }
                unmount2();
                att.mbr_particion[i].part_fit = ' ';
                clean_char(att.mbr_particion[i].part_name,16);
                att.mbr_particion[i].part_size = -1;
                att.mbr_particion[i].part_start = 2147483647;
                att.mbr_particion[i].part_status = 'n';
                att.mbr_particion[i].part_type = 'v';
                printf("particion Eliminada: %s\n",name.c_str());
                exit = 's';

            }
        }
        if(exit == '*')
            for(int i = 0; i < 4; i++)
            {
                if(att.mbr_particion[i].part_type == 'e')
                {
                    EBR aux, aux2;
                    fseek(f,att.mbr_particion[i].part_start,SEEK_SET);
                    fread(&aux2,sizeof(aux2),1,f);
                    setEBR(aux);
                    if(aux2.part_next != -1 && strcmp(aux2.part_name,name.c_str()) != 0)
                    {
                        aux = aux2;
                        fseek(f,aux2.part_next,SEEK_SET);
                        fread(&aux2,sizeof(aux2),1,f);
                    }
                    while(aux2.part_next != -1)
                    {
                        if(strcmp(aux2.part_name,name.c_str()) == 0)
                        {
                            break;
                        }
                        aux = aux2;
                        fseek(f,aux2.part_next,SEEK_SET);
                        fread(&aux2,sizeof(aux2),1,f);
                    }
                    if(strcmp(aux2.part_name,name.c_str()) == 0)
                    {
                        if(aux.part_size != -1)
                        {
                            aux.part_next = aux2.part_next;
                            unmount2();
                            fseek(f,aux.part_start,SEEK_SET);
                            fwrite(&aux,sizeof(aux),1,f);

                            fseek(f,aux2.part_start,SEEK_SET);
                            if(tdelete.compare("full"))
                            {
                                int ggg = sizeof(aux2);

                                for(int n = 0; n<ggg ; n++)
                                {
                                    fwrite("\0",sizeof(char),1,f);
                                }
                            }

                            printf("particion Eliminada: %s\n",name.c_str());
                            exit = 's';
                        }else
                        {
                            unmount2();
                            int nexxt = aux2.part_next;
                            fseek(f,aux2.part_start,SEEK_SET);
                            setEBR(aux2);
                            aux2.part_next = nexxt;
                            fwrite(&aux2,sizeof(aux2),1,f);
                            printf("particion Eliminada: %s\n",name.c_str());
                            exit = 's';

                        }
                    }


                }
            }
        if(exit == '*')
        {
            printf("La particion %s no se encontro para su eliminacion, nombre invalido.\n",name.c_str());
        }
        sort_array(att.mbr_particion);
        fseek(f,0,SEEK_SET);
        fwrite(&att,sizeof(att),1,f);
        fclose(f);
    }
}

void setEBR(EBR& val)
{
    val.part_status = '*';
    val.part_fit = '*';
    val.part_start = -1;
    val.part_size = -1;
    val.part_next = -1;
    clean_char(val.part_name,16);
}

void setEBR2(EBR& val,int start)
{
    val.part_status = 'n';
    val.part_fit = fit.at(0);
    val.part_start = start;
    val.part_size = size;
    val.part_next = -1;
    clean_char(val.part_name,16);
    strcat(val.part_name,name.c_str());
}

void mount()
{
    FILE* f = fopen(path.c_str(),"r+b");
    if(f == NULL)
    {
        printf("No se encontro el disco en la ruta %s para montar la particion %s\n", path.c_str(), name.c_str());

    }else
    {
        fseek(f,0,SEEK_SET);
        MBR aux;
        EBR auxE;
        fread(&aux,sizeof(aux),1,f);
        int t = 0,ext = -1;
        char rtr[16];
        for(t = 0; t<4 ; t++)
        {
            if(aux.mbr_particion[t].part_type == 'e')
            {
                ext = t;
            }
            clean_char(rtr,16);
            strcat(rtr,aux.mbr_particion[t].part_name);
            if(strcmp(aux.mbr_particion[t].part_name,name.c_str()) == 0)
            {
                break;
            }
        }
        if(t == 4)
        {
            if(ext == -1)
            {
                printf("Error no se encontro la particion %s para montarla\n",name.c_str());
                fclose(f);
                return;
            }
            fseek(f,aux.mbr_particion[ext].part_start,SEEK_SET);
            fread(&auxE,sizeof(auxE),1,f);
            while(auxE.part_next != -1)
            {
                if(strcmp(auxE.part_name,name.c_str()) == 0)
                {
                    break;
                }
                fseek(f,auxE.part_next,SEEK_SET);
                fread(&auxE,sizeof(auxE),1,f);
            }

            if(strcmp(auxE.part_name,name.c_str()) != 0)
            {
                printf("Error no se encontro la particion %s para montarla\n",name.c_str());
                fclose(f);
                return;
            }
            insertarEBR(auxE);

            auxE.part_status = 'm';
            fseek(f,auxE.part_start,SEEK_SET);
            fwrite(&auxE,sizeof(auxE),1,f);

            fclose(f);
            return;
        }else
        {
            insertarP(aux.mbr_particion[t]);

            aux.mbr_particion[t].part_status = 'm';
            fseek(f,0,SEEK_SET);
            fwrite(&aux,sizeof(aux),1,f);

            fclose(f);
            return;
        }
    }
}

void insertarEBR(EBR& part)
{
    int e = existepath();
    int v = 0;
    if(e == -1)
    {
        v = pathvacio();
        if(v == -1)
        {
            printf("Error no se pueden agregar nuevas particiones\n");
            return;
        }
        int l = existepart(v);
        if(l != -1)
        {
            mounts[v][l].direccion = part.part_start;
            mounts[v][l].part_size = part.part_size;
            mounts[v][l].name = name;
            if(strcmp(mounts[v][l].path.c_str(),"") == 0)
            {
                mounts[v][l].path = path;
            }
            if(strcmp(mounts[v][0].path.c_str(),"") == 0)
            {
                mounts[v][0].path = path;
            }
            mounts[v][l].type = 'l';
            mounts[v][0].montadas = mounts[v][0].montadas + 1;
            printf("Se monto la particion correctamente\n");
            return;
        }

    }else
    {
        int l = existepart(e);
        if(l != -1)
        {
            mounts[e][l].direccion = part.part_start;
            mounts[e][l].part_size = part.part_size;
            mounts[e][l].name = name;
            if(strcmp(mounts[e][l].path.c_str(),"") == 0)
            {
                mounts[e][l].path = path;
            }
            mounts[e][l].type = 'l';
            mounts[e][0].montadas = mounts[e][0].montadas + 1;
            //printf("%s\n",mounts[v][l].name)
            printf("Se monto la particion %s correctamente\n",name.c_str());
            return;
        }
    }

}

void insertarP(Particion& part)
{
    int e = existepath();
    int v = 0;
    if(e == -1)
    {
        v = pathvacio();
        if(v == -1)
        {
            printf("Error no se pueden agregar nuevas particiones\n");
            return;
        }
        int l = existepart(v);
        if(l != -1)
        {
            mounts[v][l].direccion = part.part_start;
            mounts[v][l].part_size = part.part_size;
            mounts[v][l].name = name;
            if(strcmp(mounts[v][l].path.c_str(),"") == 0)
            {
                mounts[v][l].path = path;
            }
            if(strcmp(mounts[v][0].path.c_str(),"") == 0)
            {
                mounts[v][0].path = path;
            }
            mounts[v][l].type = 'p';
            mounts[v][0].montadas = mounts[v][0].montadas + 1;
            printf("Se monto la particion correctamente\n");
            return;
        }

    }else
    {
        int l = existepart(e);
        if(l != -1)
        {
            mounts[e][l].direccion = part.part_start;
            mounts[e][l].part_size = part.part_size;
            mounts[e][l].name = name;
            if(strcmp(mounts[e][l].path.c_str(),"") == 0)
            {
                mounts[e][l].path = path;
            }
            mounts[e][l].type = 'l';
            mounts[e][0].montadas = mounts[e][0].montadas + 1;
            printf("Se monto la particion correctamente\n");
            return;
        }
    }

}

int existepart(int fil)
{
    for(int j = 1; j<maxp ; j++)
    {
        if(name == mounts[fil][j].name)
        {
            printf("La particion %s ya fue montada anteriormente\n",name.c_str());
            return -1;
        }
    }
    for(int j = 1; j<maxp ; j++)
    {
        if(mounts[fil][j].direccion == -1)
        {
            return j;
        }
    }
    printf("Error no se pueden agregar nuevas particiones\n");
    return -1;
}

int existepath()
{
    for(int i = 0; i<maxd ; i++)
    {
        if(path == mounts[i][0].path)
        {
            return i;
        }
    }
    return -1;
}

int pathvacio()
{
    for(int i = 0; i<maxd ; i++)
    {
        if("" == mounts[i][0].path)
        {
            return i;
        }
    }
    return -1;
}

void unmount()
{
    int i = 0;
    int j = 0;
    if(id[0] != 'v' || id[1] != 'd')
    {
        printf("El id de la particion montada es invalido\n");
        return;
    }
    for(i = 0; i<maxd ; i++)
    {
        for(j = 0; j<maxp ; j++)
        {
            if(mounts[i][j].id == id)
            {
                if(mounts[i][j].direccion == -1)
                {
                    printf("No se puede demontar la particion %s por que aun no ha sido montada\n",id.c_str());
                    return;
                }
                if(mounts[i][j].type == 'l')
                {
                    EBR eb;
                    FILE* f = fopen(mounts[i][j].path.c_str(),"r+b");
                    fseek(f,mounts[i][j].direccion,SEEK_SET);
                    fread(&eb,sizeof(eb),1,f);
                    eb.part_status = 'n';
                    fseek(f,mounts[i][j].direccion,SEEK_SET);
                    fwrite(&eb,sizeof(eb),1,f);
                    fclose(f);
                }else
                    if(mounts[i][j].type == 'p')
                    {
                        MBR eb;
                        FILE* f = fopen(mounts[i][j].path.c_str(),"r+b");
                        fseek(f,0,SEEK_SET);
                        fread(&eb,sizeof(eb),1,f);
                        for(int ty = 0; ty<4 ; ty++)
                        {
                            if(strcmp(mounts[i][j].name.c_str(),eb.mbr_particion[ty].part_name) == 0)
                            {
                                eb.mbr_particion[ty].part_status = 'n';
                            }
                        }

                        fseek(f,0,SEEK_SET);
                        fwrite(&eb,sizeof(eb),1,f);
                        fclose(f);
                    }
                mounts[i][j].direccion = -1;
                mounts[i][j].name = "";
                if(j != 0)
                {
                    mounts[i][j].path = "";

                }

                mounts[i][0].montadas--;
                if(mounts[i][0].montadas == 0)
                {
                    mounts[i][0].path = "";

                }
                printf("Se desmonto correctamente la particion %s\n",id.c_str());
                return;
            }
        }
    }
    if(j == maxp && i == maxd)
    {
        printf("No se pudo desmontar la particion %s no se encontro la particion\n",name.c_str());
    }
}

void unmount2()
{
    for(int i = 0; i<maxd ; i++)
    {
        if(strcmp(path.c_str(),mounts[i][0].path.c_str()) == 0)
        {
            for(int j = 0; j<maxp ; j++)
            {
                if(strcmp(mounts[i][j].name.c_str(), name.c_str()) == 0)
                {
                    mounts[i][j].direccion = -1;
                    mounts[i][j].part_size = 0;
                    mounts[i][j].type = '*';
                    mounts[i][j].name = "";
                    if(j != 0)
                        mounts[i][j].path = "";
                    mounts[i][0].montadas--;
                    if(mounts[i][0].montadas == 0)
                        mounts[i][0].path = "";
                    printf("Se desmonto correctamente la particion %s\n",name.c_str());
                    return;
                }
            }
        }
    }
}

void unmount_partitions()
{
    for(int i = 0 ; i < maxd ; i++)
    {
        if(path == mounts[i][0].path)
        {
            for(int j = 0; j < maxp ; j++)
            {
                mounts[i][j].direccion = -1;
                mounts[i][j].montadas = 0;
                mounts[i][j].part_size = 0;
                mounts[i][j].type = '*';
                mounts[i][j].name = "";
                mounts[i][j].path = "";
            }
            printf("Se desmontaron con exito todas las particiones\n");
            break;
        }
    }
}

void insertaParticion(string path)
{
    FILE* f = fopen(path.c_str(),"r+b");
    int result = 0;
    if(f == NULL)
    {
        printf("No se encontro el disco para su modificacion");

    }else
    {
        MBR arr;
        EBR aux;
        fread(&arr,sizeof(arr),1,f);
        sort_array(arr.mbr_particion);
        int c = 0;
        int v = 0;
        int e = 0;
        for(int i = 0; i<4; i++)
        {
            if(strcmp(arr.mbr_particion[i].part_name,name.c_str()) == 0)
            {
                printf("No se pudo crear la particion %s debido a que ya se encuentra una con ese nombre\n",name.c_str());
                fclose(f);
                return;
            }
        }
        for(int i = 0; i<4;i++)
        {
            if(arr.mbr_particion[i].part_start != 2147483647)
            {
                c = c + 1;
            }else
            {
                v = v + 1;
            }
            if(arr.mbr_particion[i].part_type == 'e')
            {
                e = e +1;
            }
        }
        if(e > 0 && type == 'e')
        {
            printf("Ya exite una particion extendida no se pueden crear mas, no se creo %s\n",name.c_str());
        }else if(type == 'l')
        {
            int m = -1;
            for(m = 0; m<4; m++)
            {
                if(arr.mbr_particion[m].part_type == 'e')
                {
                    break;
                }
            }
            if(m != 4)
            {
                fseek(f,arr.mbr_particion[m].part_start,SEEK_SET);
                fread(&aux,sizeof(aux),1,f);
                int start_aux = aux.part_start;
                start_aux = aux.part_next;
                int ant = aux.part_size+aux.part_start;
                int an = aux.part_start;

                EBR  auxx;
                fseek(f,arr.mbr_particion[m].part_start,SEEK_SET);
                fread(&auxx,sizeof(auxx),1,f);
                while(auxx.part_next != -1)
                {
                    if(strcmp(auxx.part_name,name.c_str()) == 0)
                    {
                        printf("No se pudo crear la particion logica %s debido a que ya se encuentra una con ese nombre\n",name.c_str());
                        fclose(f);
                        return;
                    }
                    fseek(f,auxx.part_next,SEEK_SET);
                    fread(&auxx,sizeof(auxx),1,f);
                }
                while(start_aux != -1)
                {
                    if(aux.part_size == -1)
                    {
                        if(aux.part_next != -1 && aux.part_size == -1)
                        {
                            int rrr = aux.part_next;
                            fseek(f,arr.mbr_particion[m].part_start,SEEK_SET);
                            setEBR2(aux,arr.mbr_particion[m].part_start);
                            aux.part_next = rrr;
                            fwrite(&aux,sizeof(aux),1,f);
                            fclose(f);
                            printf("Se agrego la particion logica %s\n",name.c_str());
                            return;
                        }
                    }
                    if(ant != -2 && aux.part_start-ant >= size)
                    {
                        fseek(f,an,SEEK_SET);
                        fread(&aux,sizeof(aux),1,f);
                        aux.part_next = ant;
                        fwrite(&aux,sizeof(aux),1,f);
                        setEBR2(aux,ant);
                        fseek(f,ant,SEEK_SET);
                        fwrite(&aux,sizeof(aux),1,f);
                        fclose(f);
                        printf("Se agrego la particion logica %s\n",name.c_str());
                        return;
                    }
                    ant = aux.part_size+aux.part_start;
                    an = aux.part_start;
                    fseek(f,aux.part_next,SEEK_SET);
                    fread(&aux,sizeof(aux),1,f);
                    start_aux = aux.part_next;
                }
                if(strcmp(aux.part_name,name.c_str()) == 0)
                {
                    printf("No se pudo crear la particion logica %s debido a que ya se encuentra una con ese nombre\n",name.c_str());
                    fclose(f);
                    return;
                }

                if(ant != -2 && aux.part_start-ant >= size)
                {
                    int nexxt = aux.part_start;

                    fseek(f,an,SEEK_SET);
                    fread(&aux,sizeof(aux),1,f);

                    aux.part_next = ant;

                    fseek(f,an,SEEK_SET);
                    fwrite(&aux,sizeof(aux),1,f);

                    setEBR2(aux,ant);
                    aux.part_next = nexxt;

                    fseek(f,ant,SEEK_SET);
                    fwrite(&aux,sizeof(aux),1,f);

                    fclose(f);
                    printf("Se agrego la particion logica %s\n",name.c_str());
                    return;
                }
                if(aux.part_size != -1)
                {
                    result = arr.mbr_particion[m].part_start+arr.mbr_particion[m].part_size-aux.part_start-aux.part_size;
                    if( result < size)
                    {
                        printf("No se pudo agregar la particion logica %s por que ya no hay espacio en la extendida\n",name.c_str());
                        return;
                    }

                    int next = aux.part_start+aux.part_size;
                    int start = aux.part_start;
                    aux.part_next = next;
                    fseek(f,start,SEEK_SET);
                    fwrite(&aux,sizeof(aux),1,f);
                    EBR aux2;
                    setEBR2(aux2,next);
                    fseek(f,next,SEEK_SET);
                    fwrite(&aux2,sizeof(aux2),1,f);
                    fclose(f);
                }else
                {
                    int sss = arr.mbr_particion[m].part_start;
                    setEBR2(aux,sss);

                    fseek(f,sss,SEEK_SET);
                    fwrite(&aux,sizeof(aux),1,f);
                    fclose(f);
                }

                printf("Se agrego la particion logica %s\n",name.c_str());
            }else
            {
                printf("Error no hay una particion extendida para crear la particion logica %s\n",name.c_str());
            }
        }else
        {
            if(c == 4)
            {
                printf("No se pueden crear mas particiones primarias o extendidas, no se creo %s\n",name.c_str());
            }else
            {
                if(v == 4)
                {
                    int jj = arr.mbr_tam-sizeof(arr);
                    if(jj >= size)
                    {
                        setParticion(arr.mbr_particion[0],sizeof(arr));
                        if(type == 'e')
                        {

                            setEBR2(aux,sizeof(arr));
                            fseek(f,sizeof(arr),SEEK_SET);
                            fwrite(&aux,sizeof(aux),1,f);
                        }
                        cout << "particion ingresada: " << &arr.mbr_particion[0].part_name << "\n";
                    }else
                    {
                        cout << "El espacio libre es insuficiente para agregar la particion " << name.c_str() << "\n";
                        return;
                    }

                }else
                {

                    for(int i = 0; i< 4; i++)
                    {
                        if(arr.mbr_particion[i].part_start != 2147483647)
                        {
                            if(i == 0)
                            {
                                if(arr.mbr_particion[i].part_start-sizeof(arr)>= size)
                                {
                                    for(int j = i+1; j< 4;j++)
                                    {
                                        if(arr.mbr_particion[j].part_start == 2147483647)
                                        {
                                            setParticion(arr.mbr_particion[j],sizeof(arr));
                                            if(type == 'e')
                                            {
                                                setEBR2(aux,sizeof(arr));
                                                fseek(f,sizeof(arr),SEEK_SET);
                                                fwrite(&aux,sizeof(aux),1,f);
                                            }
                                            sort_array(arr.mbr_particion);
                                            cout << "particion ingresada: " << arr.mbr_particion[j].part_name << "\n";
                                            fseek(f,0,SEEK_SET);
                                            fwrite(&arr,sizeof(arr),1,f);
                                            fclose(f);
                                            return;
                                        }
                                    }
                                }

                            }else if(i == 3)
                            {
                                if(arr.mbr_tam-(arr.mbr_particion[i-1].part_start+arr.mbr_particion[i-1].part_size)>=size)
                                {
                                    setParticion(arr.mbr_particion[i],arr.mbr_particion[i-1].part_start+arr.mbr_particion[i-1].part_size);
                                    if(type == 'e')
                                    {
                                        setEBR2(aux,arr.mbr_particion[i-1].part_start+arr.mbr_particion[i-1].part_size);
                                        fseek(f,arr.mbr_particion[i-1].part_start+arr.mbr_particion[i-1].part_size,SEEK_SET);
                                        fwrite(&aux,sizeof(aux),1,f);
                                    }
                                    sort_array(arr.mbr_particion);
                                    cout << "particion ingresada: " << arr.mbr_particion[i].part_name << "\n";
                                    fseek(f,0,SEEK_SET);
                                    fwrite(&arr,sizeof(arr),1,f);
                                    fclose(f);
                                    return;
                                }
                            }else
                            {
                                if(arr.mbr_particion[i].part_start-(arr.mbr_particion[i-1].part_start+arr.mbr_particion[i-1].part_size)>=size)
                                {
                                    for(int j = i+1; j< 4;j++)
                                    {
                                        if(arr.mbr_particion[j].part_start == 2147483647)
                                        {
                                            setParticion(arr.mbr_particion[j],arr.mbr_particion[i-1].part_start+arr.mbr_particion[i-1].part_size);
                                            if(type == 'e')
                                            {
                                                setEBR2(aux,arr.mbr_particion[i-1].part_start+arr.mbr_particion[i-1].part_size);
                                                fseek(f,arr.mbr_particion[i-1].part_start+arr.mbr_particion[i-1].part_size,SEEK_SET);
                                                fwrite(&aux,sizeof(aux),1,f);
                                            }
                                            sort_array(arr.mbr_particion);
                                            cout << "particion ingresada: " << arr.mbr_particion[j].part_name << "\n";
                                            fseek(f,0,SEEK_SET);
                                            fwrite(&arr,sizeof(arr),1,f);
                                            fclose(f);
                                            return;
                                        }
                                    }
                                }
                            }
                        }else
                        {
                            if(arr.mbr_tam-(arr.mbr_particion[i-1].part_start+arr.mbr_particion[i-1].part_size)>=size)
                            {
                                setParticion(arr.mbr_particion[i],arr.mbr_particion[i-1].part_start+arr.mbr_particion[i-1].part_size);
                                if(type == 'e')
                                {
                                    setEBR2(aux,arr.mbr_particion[i-1].part_start+arr.mbr_particion[i-1].part_size);
                                    fseek(f,arr.mbr_particion[i-1].part_start+arr.mbr_particion[i-1].part_size,SEEK_SET);
                                    fwrite(&aux,sizeof(aux),1,f);
                                }
                                sort_array(arr.mbr_particion);
                                cout << "particion ingresada: " << arr.mbr_particion[i].part_name << "\n";
                                fseek(f,0,SEEK_SET);
                                fwrite(&arr,sizeof(arr),1,f);
                                fclose(f);
                                return;
                            }
                        }
                    }
                }

            }
            fseek(f,0,SEEK_SET);
            fwrite(&arr,sizeof(arr),1,f);
            fclose(f);

        }

    }

}

void insertaParticionMejor(string path)
{
    FILE* f = fopen(path.c_str(),"r+b");
    int tam = 2147483647;
    int propuesta = -1;
    if(f == NULL)
    {
        printf("No se encontro el disco para su modificacion");

    }else
    {
        MBR arr;
        EBR aux;
        fread(&arr,sizeof(arr),1,f);
        sort_array(arr.mbr_particion);

        if(type == 'e' || type == 'p')
        {
            for(int i = 0; i<4 ; i++)
            {
                if(arr.mbr_particion[i].part_type == 'e' && type == 'e')
                {
                    printf("Error ya no se pueden agragar mas particiones extendidas\n");
                    fclose(f);
                    return;
                }
            }

            for(int i = 0; i<4 ; i++)
            {
                if(strcmp(arr.mbr_particion[i].part_name,name.c_str()) == 0)
                {
                    printf("Error la particion ya existe no se puede crear nuevamente\n");
                    fclose(f);
                    return;
                }
            }
            int i = 0;
            for(i = 0; i<4 ; i++)
            {
                if(arr.mbr_particion[i].part_size == -1)
                {
                    break;
                }
            }

            if(i == 4)
            {
                printf("Error ya no se pueden agragar mas particiones\n");
                fclose(f);
                return;
            }



            for(i = 0; i<4; i++)
            {
                if(i == 0)
                {
                    if(arr.mbr_particion[i].part_start != 2147483647)
                    {
                        if(arr.mbr_particion[i].part_start - sizeof(arr) >= size)
                        {
                            tam = arr.mbr_particion[i].part_start - sizeof(arr);
                            propuesta = sizeof(arr);
                        }
                    }else
                    {
                        if(size > arr.mbr_tam - sizeof(arr))
                        {
                            printf("Error, tamaño de la particion: %s nueva no valida, no se inserto la particion.\n",name.c_str());
                            return;
                        }
                        setParticion(arr.mbr_particion[i],sizeof(arr));
                        printf("Se inserto correctamente la particion %s\n",name.c_str());
                        if(type == 'e')
                        {

                            setEBR2(aux,sizeof(arr));
                            fseek(f,sizeof(arr),SEEK_SET);
                            fwrite(&aux,sizeof(aux),1,f);
                        }
                        sort_array(arr.mbr_particion);
                        fseek(f,0,SEEK_SET);
                        fwrite(&arr,sizeof(arr),1,f);
                        fclose(f);
                        return;
                        break;
                    }
                }else if(i == 3)
                {
                    if(arr.mbr_particion[i].part_start == 2147483647)
                    {

                        break;
                    }else
                    {
                        printf("No se pueden agregar mas particiones primarias o extendidas.\n");
                        return;
                    }
                }else
                {
                    if(arr.mbr_particion[i].part_start != 2147483647)
                    {
                        if(arr.mbr_particion[i].part_start - (arr.mbr_particion[i-1].part_start+arr.mbr_particion[i-1].part_size) >= size)
                        {
                            if(arr.mbr_particion[i].part_start - (arr.mbr_particion[i-1].part_start+arr.mbr_particion[i-1].part_size) < tam)
                            {
                                tam = arr.mbr_particion[i].part_start - (arr.mbr_particion[i-1].part_start+arr.mbr_particion[i-1].part_size);
                                propuesta = arr.mbr_particion[i-1].part_start+arr.mbr_particion[i-1].part_size;
                            }

                        }
                    }else
                    {

                        break;
                    }
                }
            }
            if(size > arr.mbr_tam - (arr.mbr_particion[i-1].part_start+arr.mbr_particion[i-1].part_size))
            {
                printf("Error, tamaño de la particion: %s nueva no valida, no se inserto la particion.\n",name.c_str());
                return;
            }
            if(arr.mbr_tam -(arr.mbr_particion[i-1].part_start+arr.mbr_particion[i-1].part_size) < tam)
            {
                tam = arr.mbr_tam -(arr.mbr_particion[i-1].part_start+arr.mbr_particion[i-1].part_size);
                propuesta = arr.mbr_particion[i-1].part_start+arr.mbr_particion[i-1].part_size;
            }
            setParticion(arr.mbr_particion[i],propuesta);
            printf("Se inserto correctamente la particion %s\n",name.c_str());
            if(type == 'e')
            {

                setEBR2(aux,propuesta);
                fseek(f,propuesta,SEEK_SET);
                fwrite(&aux,sizeof(aux),1,f);
            }
            sort_array(arr.mbr_particion);
            fseek(f,0,SEEK_SET);
            fwrite(&arr,sizeof(arr),1,f);
            fclose(f);
            return;
        }else
        {
            int i = 0;
            for(i = 0; i<4 ; i++)
            {
                if(arr.mbr_particion[i].part_type == 'e')
                {
                    break;
                }
            }

            if(i == 4)
            {
                printf("Error no se puede agregar la particion logica %s por que no hay una extendida\n",name.c_str());
                fclose(f);
                return;
            }
            EBR aux2;
            EBR aux3;
            fseek(f,arr.mbr_particion[i].part_start,SEEK_SET);
            fread(&aux,sizeof(aux),1,f);
            char ii = '*';
            while(aux.part_next != -1)
            {
                if(strcmp(name.c_str(),aux.part_name) == 0)
                {
                    printf("No se puede insertar la particion, ya existe\n");
                    return;
                }
                fseek(f,aux.part_next,SEEK_SET);
                fread(&aux,sizeof(aux),1,f);
            }
            if(strcmp(name.c_str(),aux.part_name) == 0)
            {
                printf("No se puede insertar la particion, ya existe\n");
                return;
            }
            fseek(f,arr.mbr_particion[i].part_start,SEEK_SET);
            fread(&aux,sizeof(aux),1,f);
            if(aux.part_size == -1 && aux.part_next != -1)
            {
                fseek(f,aux.part_next,SEEK_SET);
                fread(&aux2,sizeof(aux2),1,f);
                if(aux2.part_start-(arr.mbr_particion[i].part_start) >= size)
                {
                    if(aux2.part_start-(arr.mbr_particion[i].part_start) < tam)
                    {
                        tam = aux2.part_start-(arr.mbr_particion[i].part_start);
                        propuesta = arr.mbr_particion[i].part_start;
                    }

                }
            }
            if(aux.part_size != -1 && aux.part_next == -1)
            {
                fseek(f,aux.part_start+aux.part_size,SEEK_SET);
                setEBR2(aux2,aux.part_start+aux.part_size);
                fwrite(&aux2,sizeof(aux2),1,f);
                aux.part_next = aux2.part_start;
                fseek(f,aux.part_start,SEEK_SET);
                fwrite(&aux,sizeof(aux),1,f);
                ii = 'S';
            }
            if(aux.part_size == -1 && aux.part_next == -1)
            {
                fseek(f,arr.mbr_particion[i].part_start,SEEK_SET);
                setEBR2(aux,arr.mbr_particion[i].part_start);
                fwrite(&aux,sizeof(aux),1,f);
                ii = 'S';
            }
            if(ii == '*')
            {
                while(aux.part_next != -1)
                {
                    if(aux.part_next != -1)
                    {
                        fseek(f,aux.part_next,SEEK_SET);
                        fread(&aux2,sizeof(aux2),1,f);
                        if(aux.part_size == -1 && aux.part_start == -1)
                        {
                            if(aux2.part_start-arr.mbr_particion[i].part_start >= size)
                            {
                                if(aux2.part_start-arr.mbr_particion[i].part_start < tam)
                                {
                                    tam = aux2.part_start-arr.mbr_particion[i].part_start;
                                    propuesta = arr.mbr_particion[i].part_start;
                                }
                            }
                        }else
                            if(aux2.part_start-(aux.part_start+aux.part_size) >= size)
                            {
                                if(aux2.part_start-(aux.part_start+aux.part_size) < tam)
                                {
                                    tam = aux2.part_start-(aux.part_start+aux.part_size);
                                    propuesta = aux.part_start;
                                }

                            }
                    }else
                    {
                        fseek(f,aux.part_next,SEEK_SET);
                        fread(&aux,sizeof(aux),1,f);
                        break;
                    }
                    fseek(f,aux.part_next,SEEK_SET);
                    fread(&aux,sizeof(aux),1,f);
                }
            }

            if(aux.part_size != -1 && ii == '*')
            {
                if((arr.mbr_particion[i].part_size+arr.mbr_particion[i].part_start)-(aux.part_start+aux.part_size) >= size)
                {
                    if( (arr.mbr_particion[i].part_size+arr.mbr_particion[i].part_start)-(aux.part_start+aux.part_size) < tam)
                    {
                        tam = (arr.mbr_particion[i].part_size+arr.mbr_particion[i].part_start)-(aux.part_start+aux.part_size);
                        propuesta = aux.part_start;
                    }

                }
            }

            if(propuesta != -1 && ii == '*')
            {
                fseek(f,propuesta,SEEK_SET);
                fread(&aux,sizeof(aux),1,f);
                if(aux.part_next != -1 && aux.part_size != -1)
                {
                    fseek(f,aux.part_next,SEEK_SET);
                    fread(&aux2,sizeof(aux2),1,f);
                    setEBR2(aux3,aux.part_size+aux.part_start);
                    aux3.part_next = aux.part_next;
                    aux.part_next = aux3.part_start;

                    fseek(f,aux.part_start,SEEK_SET);
                    fwrite(&aux,sizeof(aux),1,f);

                    fseek(f,aux2.part_start,SEEK_SET);
                    fwrite(&aux2,sizeof(aux2),1,f);

                    fseek(f,aux3.part_start,SEEK_SET);
                    fwrite(&aux3,sizeof(aux3),1,f);

                    fseek(f,propuesta,SEEK_SET);
                    fread(&aux,sizeof(aux),1,f);

                }else if(aux.part_next != -1 && aux.part_start == -1)
                {
                    int t = aux.part_next;
                    setEBR2(aux,propuesta);
                    fseek(f,propuesta,SEEK_SET);
                    aux.part_next = t;
                    fwrite(&aux,sizeof(aux),1,f);
                }else
                {
                    setEBR2(aux2,aux.part_start+aux.part_size);
                    aux.part_next = aux2.part_start;

                    fseek(f,aux2.part_start,SEEK_SET);
                    fwrite(&aux2,sizeof(aux2),1,f);

                    fseek(f,aux.part_start,SEEK_SET);
                    fwrite(&aux,sizeof(aux),1,f);
                }
                ii = 'S';
            }
            if(ii != '*')
            {
                printf("Se inserto correctamente la particion logica %s\n",name.c_str());
                fclose(f);
                return;
            }

        }
    }
}

void insertaParticionPeor(string path)
{
    FILE* f = fopen(path.c_str(),"r+b");
    int tam = 0;
    int propuesta = -1;
    if(f == NULL)
    {
        printf("No se encontro el disco para su modificacion");

    }else
    {
        MBR arr;
        EBR aux;
        fread(&arr,sizeof(arr),1,f);
        sort_array(arr.mbr_particion);
        if(type == 'e' || type == 'p')
        {
            for(int i = 0; i<4 ; i++)
            {
                if(arr.mbr_particion[i].part_type == 'e' && type == 'e')
                {
                    printf("Error ya no se pueden agragar mas particiones extendidas\n");
                    fclose(f);
                    return;
                }
            }

            for(int i = 0; i<4 ; i++)
            {
                if(strcmp(arr.mbr_particion[i].part_name,name.c_str()) == 0)
                {
                    printf("Error la particion ya existe no se puede crear nuevamente\n");
                    fclose(f);
                    return;
                }
            }
            int i = 0;
            for(i = 0; i<4 ; i++)
            {
                if(arr.mbr_particion[i].part_size == -1)
                {
                    break;
                }
            }

            if(i == 4)
            {
                printf("Error ya no se pueden agragar mas particiones\n");
                fclose(f);
                return;
            }



            for(i = 0; i<4; i++)
            {
                if(i == 0)
                {
                    if(arr.mbr_particion[i].part_start != 2147483647)
                    {
                        if(arr.mbr_particion[i].part_start - sizeof(arr) >= size)
                        {
                            if((arr.mbr_particion[i].part_start - sizeof(arr)) > tam)
                            {
                                tam = arr.mbr_particion[i].part_start - sizeof(arr);
                                propuesta = sizeof(arr);
                            }

                        }
                    }else
                    {
                        if(size > arr.mbr_tam - sizeof(arr))
                        {
                            printf("Error, tamaño de la particion: %s nueva no valida, no se inserto la particion.\n",name.c_str());
                            return;
                        }
                        setParticion(arr.mbr_particion[i],sizeof(arr));
                        printf("Se inserto correctamente la particion %s\n",name.c_str());
                        if(type == 'e')
                        {

                            setEBR2(aux,sizeof(arr));
                            fseek(f,sizeof(arr),SEEK_SET);
                            fwrite(&aux,sizeof(aux),1,f);
                        }
                        sort_array(arr.mbr_particion);
                        fseek(f,0,SEEK_SET);
                        fwrite(&arr,sizeof(arr),1,f);
                        fclose(f);
                        return;
                        break;
                    }
                }else if(i == 3)
                {
                    if(arr.mbr_particion[i].part_start == 2147483647)
                    {

                        break;
                    }else
                    {
                        printf("No se pueden agregar mas particiones primarias o extendidas.\n");
                        return;
                    }
                }else
                {
                    if(arr.mbr_particion[i].part_start != 2147483647)
                    {
                        if(arr.mbr_particion[i].part_start - (arr.mbr_particion[i-1].part_start+arr.mbr_particion[i-1].part_size) >= size)
                        {
                            if(arr.mbr_particion[i].part_start - (arr.mbr_particion[i-1].part_start+arr.mbr_particion[i-1].part_size) > tam)
                            {
                                tam = arr.mbr_particion[i].part_start - (arr.mbr_particion[i-1].part_start+arr.mbr_particion[i-1].part_size);
                                propuesta = arr.mbr_particion[i-1].part_start+arr.mbr_particion[i-1].part_size;
                            }

                        }
                    }else
                    {

                        break;
                    }
                }
            }
            if(size > arr.mbr_tam - (arr.mbr_particion[i-1].part_start+arr.mbr_particion[i-1].part_size))
            {
                printf("Error, tamaño de la particion: %s nueva no valida, no se inserto la particion.\n",name.c_str());
                return;
            }
            if(arr.mbr_tam -(arr.mbr_particion[i-1].part_start+arr.mbr_particion[i-1].part_size) > tam)
            {
                tam = arr.mbr_tam -(arr.mbr_particion[i-1].part_start+arr.mbr_particion[i-1].part_size);
                propuesta = arr.mbr_particion[i-1].part_start+arr.mbr_particion[i-1].part_size;
            }
            setParticion(arr.mbr_particion[i],propuesta);
            printf("Se inserto correctamente la particion %s\n",name.c_str());
            if(type == 'e')
            {

                setEBR2(aux,propuesta);
                fseek(f,propuesta,SEEK_SET);
                fwrite(&aux,sizeof(aux),1,f);
            }
            sort_array(arr.mbr_particion);
            fseek(f,0,SEEK_SET);
            fwrite(&arr,sizeof(arr),1,f);
            fclose(f);
            return;
        }else
        {
            int i = 0;
            for(i = 0; i<4 ; i++)
            {
                if(arr.mbr_particion[i].part_type == 'e')
                {
                    break;
                }
            }

            if(i == 4)
            {
                printf("Error no se puede agregar la particion logica %s por que no hay una extendida\n",name.c_str());
                fclose(f);
                return;
            }
            EBR aux2;
            EBR aux3;
            fseek(f,arr.mbr_particion[i].part_start,SEEK_SET);
            fread(&aux,sizeof(aux),1,f);
            char ii = '*';
            while(aux.part_next != -1)
            {
                if(strcmp(name.c_str(),aux.part_name) == 0)
                {
                    printf("No se puede insertar la particion, ya existe\n");
                    return;
                }
                fseek(f,aux.part_next,SEEK_SET);
                fread(&aux,sizeof(aux),1,f);
            }
            if(strcmp(name.c_str(),aux.part_name) == 0)
            {
                printf("No se puede insertar la particion, ya existe\n");
                return;
            }
            fseek(f,arr.mbr_particion[i].part_start,SEEK_SET);
            fread(&aux,sizeof(aux),1,f);
            if(aux.part_size == -1 && aux.part_next != -1)
            {
                fseek(f,aux.part_next,SEEK_SET);
                fread(&aux2,sizeof(aux2),1,f);
                if(aux2.part_start-(arr.mbr_particion[i].part_start+sizeof(arr)) >= size)
                {
                    if(aux2.part_start-(arr.mbr_particion[i].part_start+sizeof(arr)) > tam)
                    {
                        tam = aux2.part_start-(arr.mbr_particion[i].part_start+sizeof(arr));
                        propuesta = arr.mbr_particion[i].part_start;
                    }

                }
            }
            if(aux.part_size != -1 && aux.part_next == -1)
            {
                fseek(f,aux.part_start+aux.part_size,SEEK_SET);
                setEBR2(aux2,aux.part_start+aux.part_size);
                fwrite(&aux2,sizeof(aux2),1,f);
                aux.part_next = aux2.part_start;
                fseek(f,aux.part_start,SEEK_SET);
                fwrite(&aux,sizeof(aux),1,f);
                ii = 'S';
            }
            if(aux.part_size == -1 && aux.part_next == -1)
            {
                fseek(f,arr.mbr_particion[i].part_start,SEEK_SET);
                setEBR2(aux,arr.mbr_particion[i].part_start);
                fwrite(&aux,sizeof(aux),1,f);
                ii = 'S';
            }
            if(ii == '*')
            {
                while(aux.part_next != -1)
                {
                    if(aux.part_next != -1)
                    {
                        fseek(f,aux.part_next,SEEK_SET);
                        fread(&aux2,sizeof(aux2),1,f);
                        if(aux.part_size == -1 && aux.part_start == -1)
                        {
                            if(aux2.part_start-arr.mbr_particion[i].part_start >= size)
                            {
                                if(aux2.part_start-arr.mbr_particion[i].part_start > tam)
                                {
                                    tam = aux2.part_start-arr.mbr_particion[i].part_start;
                                    propuesta = arr.mbr_particion[i].part_start;
                                }
                            }
                        }else
                            if(aux2.part_start-(aux.part_start+aux.part_size) >= size)
                            {
                                if(aux2.part_start-(aux.part_start+aux.part_size) > tam)
                                {
                                    tam = aux2.part_start-(aux.part_start+aux.part_size);
                                    propuesta = aux.part_start;
                                }

                            }
                    }else
                    {
                        fseek(f,aux.part_next,SEEK_SET);
                        fread(&aux,sizeof(aux),1,f);
                        break;
                    }
                    fseek(f,aux.part_next,SEEK_SET);
                    fread(&aux,sizeof(aux),1,f);
                }
            }

            if(aux.part_size != -1 && ii == '*')
            {
                if((arr.mbr_particion[i].part_size+arr.mbr_particion[i].part_start)-(aux.part_start+aux.part_size) >= size)
                {
                    if( (arr.mbr_particion[i].part_size+arr.mbr_particion[i].part_start)-(aux.part_start+aux.part_size) > tam)
                    {
                        tam = (arr.mbr_particion[i].part_size+arr.mbr_particion[i].part_start)-(aux.part_start+aux.part_size);
                        propuesta = aux.part_start;
                    }

                }
            }

            if(propuesta != -1 && ii == '*')
            {
                fseek(f,propuesta,SEEK_SET);
                fread(&aux,sizeof(aux),1,f);
                if(aux.part_next != -1 && aux.part_size != -1)
                {
                    fseek(f,aux.part_next,SEEK_SET);
                    fread(&aux2,sizeof(aux2),1,f);
                    setEBR2(aux3,aux.part_size+aux.part_start);
                    aux3.part_next = aux.part_next;
                    aux.part_next = aux3.part_start;

                    fseek(f,aux.part_start,SEEK_SET);
                    fwrite(&aux,sizeof(aux),1,f);

                    fseek(f,aux2.part_start,SEEK_SET);
                    fwrite(&aux2,sizeof(aux2),1,f);

                    fseek(f,aux3.part_start,SEEK_SET);
                    fwrite(&aux3,sizeof(aux3),1,f);

                    fseek(f,propuesta,SEEK_SET);
                    fread(&aux,sizeof(aux),1,f);

                }else if(aux.part_next != -1 && aux.part_start == -1)
                {
                    int t = aux.part_next;
                    setEBR2(aux,propuesta);
                    fseek(f,propuesta,SEEK_SET);
                    aux.part_next = t;
                    fwrite(&aux,sizeof(aux),1,f);
                }else
                {
                    setEBR2(aux2,aux.part_start+aux.part_size);
                    aux.part_next = aux2.part_start;

                    fseek(f,aux2.part_start,SEEK_SET);
                    fwrite(&aux2,sizeof(aux2),1,f);

                    fseek(f,aux.part_start,SEEK_SET);
                    fwrite(&aux,sizeof(aux),1,f);
                }
                ii = 'S';
            }
            if(ii != '*')
            {
                printf("Se inserto correctamente la particion logica %s\n",name.c_str());
                fclose(f);
                return;
            }

        }
    }
}

void setParticion(Particion& val,int start)
{
    val.part_fit = fit.at(0);
    clean_char(val.part_name,16);
    strcat(val.part_name,name.c_str());
    val.part_size = size;
    val.part_start = start;
    val.part_status = 'n';
    val.part_type = type;
}

void rep()
{
    if(name.compare("mbr") == 0)
    {
        mbr_graph();
    }
    else if(name.compare("disk") == 0)
    {
        disk_graph();
    }
    default_vars();
}

void mbr_graph()
{
    FILE* f = fopen("./grafo.dot","w");

    if(f == NULL)
    {
        printf("Error no se pudo crear el grafo\n");
        return;
    }else
    {
        for(int i = 0; i<maxd ; i++)
        {
            for(int j = 0; j<maxp ; j++)
            {
                if(mounts[i][j].id == id)
                {
                    if(mounts[i][j].direccion == -1)
                    {
                        printf("Error particion no montada para el id %s\n",id.c_str());
                        return;
                    }
                    FILE* file = fopen(mounts[i][j].path.c_str(),"r+b");
                    MBR auxM;
                    fseek(file,0,SEEK_SET);
                    fread(&auxM,sizeof(auxM),1,file);
                    fprintf(f,"digraph G {\r\n node[shape = \"textplain\" ]; \r\n s[ label=<<table border=\"0\" cellborder=\"1\" cellspacing=\"0\"><tr><td><b>Tabla de MBR</b></td></tr>\r\n<tr><td><b>Nombre</b></td><td>Valor</td></tr>\r\n","plain","text");
                    fprintf(f,"<tr><td><b>mbr_disk_signature</b></td><td>%i</td></tr>\r\n",auxM.mbr_disk_signature);
                    fprintf(f,"<tr><td><b>mbr_fecha_creacion</b></td><td>%s</td></tr>\r\n",&auxM.mbr_fecha_creacion);
                    fprintf(f,"<tr><td><b>mbr_tamanio</b></td><td>%i</td></tr>\r\n",auxM.mbr_tam);
                    for(int ss = 0; ss<4 ; ss++)
                    {
                        if(auxM.mbr_particion[ss].part_size != -1)
                        {
                            fprintf(f,"<tr><td><b>Particion %i</b></td></tr>\r\n",ss+1);
                            fprintf(f,"<tr><td><b>part_fit</b></td><td>%c</td></tr>\r\n",auxM.mbr_particion[ss].part_fit);
                            fprintf(f,"<tr><td><b>part_name</b></td><td>%s</td></tr>\r\n",&auxM.mbr_particion[ss].part_name);
                            fprintf(f,"<tr><td><b>part_size</b></td><td>%i</td></tr>\r\n",auxM.mbr_particion[ss].part_size);
                            fprintf(f,"<tr><td><b>part_start</b></td><td>%i</td></tr>\r\n",auxM.mbr_particion[ss].part_start);
                            fprintf(f,"<tr><td><b>part_status</b></td><td>%c</td></tr>\r\n",auxM.mbr_particion[ss].part_status);
                            fprintf(f,"<tr><td><b>part_type</b></td><td>%c</td></tr>\r\n",auxM.mbr_particion[ss].part_type);
                        }

                    }
                    EBR auxE;
                    int nn = 0;
                    for(int ss = 0; ss<4 ; ss++)
                    {
                        if(auxM.mbr_particion[ss].part_type == 'e')
                        {
                            fseek(file,auxM.mbr_particion[ss].part_start,SEEK_SET);
                            fread(&auxE,sizeof(auxE),1,file);
                            while(auxE.part_next != -1)
                            {
                                nn++;
                                fprintf(f,"<tr><td><b>Particion logica %i</b></td></tr>\r\n",nn);
                                fprintf(f,"<tr><td><b>part_fit</b></td><td>%c</td></tr>\r\n",auxE.part_fit);
                                fprintf(f,"<tr><td><b>part_name</b></td><td>%s</td></tr>\r\n",&auxE.part_name);
                                fprintf(f,"<tr><td><b>part_size</b></td><td>%i</td></tr>\r\n",auxE.part_size);
                                fprintf(f,"<tr><td><b>part_start</b></td><td>%i</td></tr>\r\n",auxE.part_start);
                                fprintf(f,"<tr><td><b>part_status</b></td><td>%c</td></tr>\r\n",auxE.part_status);
                                fprintf(f,"<tr><td><b>part_next</b></td><td>%i</td></tr>\r\n",auxE.part_next);
                                fseek(file,auxE.part_next,SEEK_SET);
                                fread(&auxE,sizeof(auxE),1,file);
                            }
                            if(auxE.part_size != -1)
                            {
                                nn++;
                                fprintf(f,"<tr><td><b>Particion logica %i</b></td></tr>\r\n",nn+1);
                                fprintf(f,"<tr><td><b>part_fit</b></td><td>%c</td></tr>\r\n",auxE.part_fit);
                                fprintf(f,"<tr><td><b>part_name</b></td><td>%s</td></tr>\r\n",&auxE.part_name);
                                fprintf(f,"<tr><td><b>part_size</b></td><td>%i</td></tr>\r\n",auxE.part_size);
                                fprintf(f,"<tr><td><b>part_start</b></td><td>%i</td></tr>\r\n",auxE.part_start);
                                fprintf(f,"<tr><td><b>part_status</b></td><td>%c</td></tr>\r\n",auxE.part_status);
                                fprintf(f,"<tr><td><b>part_next</b></td><td>%i</td></tr>\r\n",auxE.part_next);
                            }
                        }
                    }
                    fprintf(f,"</table>>];}");
                    fclose(f);
                    crear_folder();
                    return;
                }
            }
        }
    }
}

void disk_graph()
{
    FILE* f = fopen("/home/pixelcode/Escritorio/grafo.dot","w");
    float result = 0;
    char cmd[300];
    if(f == NULL)
    {
        printf("Error no se pudo crear el grafo\n");
        return;
    }else
    {
        for(int i = 0; i<maxd ; i++)
        {
            for(int j = 0; j<maxp ; j++)
            {
                if(mounts[i][j].id == id)
                {
                    if(mounts[i][j].direccion == -1)
                    {
                        printf("Error particion no montada para el id %s\n", id.c_str());
                        return;
                    }

                    EBR auxE;
                    int nn = 0;
                    int ant = 0,si =0;

                    FILE* file = fopen(mounts[i][j].path.c_str(),"r+b");
                    MBR auxM;
                    fseek(file,0,SEEK_SET);
                    fread(&auxM,sizeof(auxM),1,file);
                    for(int rr = 0; rr < 4 ; rr++)
                    {
                        printf("nombre: %s, tipo: %c \n",auxM.mbr_particion[rr].part_name,auxM.mbr_particion[rr].part_type);
                    }
                    fprintf(f,"digraph G {\r\n node[shape = \"textplain\" ]; \r\n s[ label=<<table border=\"0\" cellborder=\"1\" cellspacing=\"0\"><tr>\r\n");
                    fprintf(f,"<td colspan= \"100\">  MBR  <br></br>Tamaño: %i</td>",auxM.mbr_tam);
                    int ss = 0;
                    for(ss = 0; ss<4 ; ss++)
                    {
                        if(ss == 0)
                        {
                            if(auxM.mbr_particion[ss].part_type == 'e')
                            {
                                if(auxM.mbr_particion[ss].part_start - sizeof(auxM) > 0)
                                {
                                    result = (float) ((auxM.mbr_particion[ss].part_start - sizeof(auxM))*100)/ (float) auxM.mbr_tam;
                                    fprintf(f,"<td colspan= \"100\">Libre<br></br>%f %% libre<br></br> %i Bytes</td>",result,auxM.mbr_particion[ss].part_start - sizeof(auxM));
                                }
                                fseek(file,auxM.mbr_particion[ss].part_start,SEEK_SET);
                                fread(&auxE,sizeof(auxE),1,file);
                                ant = auxM.mbr_particion[ss].part_start;
                                fprintf(f,"<td><table border=\"0\" cellborder=\"1\" cellspacing=\"0\"><tr>\r\n");
                                fprintf(f,"<td colspan= \"100\">  Extendida  %s</td></tr><tr>",auxM.mbr_particion[ss].part_name);
                                while(auxE.part_next != -1)
                                {
                                    if(auxE.part_size != -1)
                                    {
                                        if(auxE.part_start -(ant+si) >0)
                                        {
                                            result = (float)((auxE.part_start -(ant+si))*100)/ (float)auxM.mbr_tam;
                                            fprintf(f,"<td colspan= \"100\">Libre<br></br>%f %% libre<br></br> %i Bytes</td>",result,auxE.part_start -(ant+si));
                                        }
                                        fprintf(f,"<td colspan= \"100\">EBR</td>");
                                        result = (float) ((auxE.part_size)*100)/ (float) auxM.mbr_tam;
                                        fprintf(f,"<td colspan= \"100\">Logica %s<br></br>%f %% ocupado<br></br> %i Bytes</td>",auxE.part_name,result,auxE.part_size);
                                        ant = auxE.part_start;
                                        si = auxE.part_size;
                                    }

                                    fseek(file,auxE.part_next,SEEK_SET);
                                    fread(&auxE,sizeof(auxE),1,file);
                                }
                                if(auxE.part_size != -1)
                                {
                                    if(auxE.part_start -(ant+si) >0)
                                    {
                                        result = (float)((auxE.part_start -(ant+si))*100)/ (float)auxM.mbr_tam;
                                        fprintf(f,"<td colspan= \"100\">Libre<br></br>%f %% libre<br></br> %i Bytes</td>",result,auxE.part_start -(ant+si));
                                    }
                                    fprintf(f,"<td colspan= \"100\">EBR</td>");
                                    result = (float) ((auxE.part_size)*100)/ (float) auxM.mbr_tam;
                                    fprintf(f,"<td colspan= \"100\">Logica %s<br></br>%f %% ocupado<br></br> %i Bytes</td>",auxE.part_name,result,auxE.part_size);
                                }
                                if(auxE.part_size == -1 && auxE.part_start == -1)
                                {
                                    result = (float) (((auxM.mbr_particion[ss].part_size))*100)/ (float) auxM.mbr_tam;
                                    fprintf(f,"<td colspan= \"100\">Libre<br></br>%f %% libre<br></br> %i Bytes</td>",result,auxM.mbr_particion[ss].part_size);
                                }else
                                {
                                    if((auxM.mbr_particion[ss].part_start+auxM.mbr_particion[ss].part_size) - (auxE.part_start+auxE.part_size) >0)
                                    {
                                        result = (float) (((auxM.mbr_particion[ss].part_start+auxM.mbr_particion[ss].part_size) - (auxE.part_start+auxE.part_size))*100)/ (float) auxM.mbr_tam;
                                        fprintf(f,"<td colspan= \"100\">Libre<br></br>%f %% libre<br></br> %i Bytes</td>",result,(auxM.mbr_particion[ss].part_start+auxM.mbr_particion[ss].part_size) - (auxE.part_start+auxE.part_size));
                                    }
                                }
                                fprintf(f,"</tr></table></td>");
                                continue;
                            }
                            else if(auxM.mbr_particion[ss].part_start == 2147483647)
                            {
                                fprintf(f,"<td colspan= \"100\">No hay particiones<br></br>100 %%libre</td>");
                                fprintf(f,"</tr></table>>];}");
                                fclose(f);
                                clean_char(cmd,300);
                                sprintf(cmd,"dot -Tjpg /home/pixelcode/Escritorio/grafo.dot -o %s", path.c_str());
                                system(cmd);
                                clean_char(cmd,300);
                                return;
                            }
                            else
                            {
                                if(auxM.mbr_particion[ss].part_start - sizeof(auxM) > 0)
                                {
                                    result = (float) ((auxM.mbr_particion[ss].part_start - sizeof(auxM))*100)/ (float) auxM.mbr_tam;
                                    fprintf(f,"<td colspan= \"100\">Libre<br></br>%f %% libre<br></br> %i Bytes</td>",result,auxM.mbr_particion[ss].part_start - sizeof(auxM));
                                }
                                if(auxM.mbr_particion[ss].part_size != 2147483647)
                                {
                                    fprintf(f,"<td colspan= \"100\">");
                                    if(auxM.mbr_particion[ss].part_type == 'p')
                                    {
                                        fprintf(f,"Primaria %s",auxM.mbr_particion[ss].part_name);
                                    }else if(auxM.mbr_particion[ss].part_type == 'e')
                                    {
                                        fprintf(f,"Extendida %s",auxM.mbr_particion[ss].part_name);
                                    }
                                    result = (float) ((auxM.mbr_particion[ss].part_size)*100)/ (float) auxM.mbr_tam;
                                    fprintf(f,"<br></br>%f %% ocupado<br></br> %i Bytes</td>",result,auxM.mbr_particion[ss].part_size);
                                }
                            }
                        }else
                        {
                            if(auxM.mbr_particion[ss].part_size == -1)
                            {
                                break;
                            }
                            if(auxM.mbr_particion[ss].part_type == 'e')
                            {
                                if(auxM.mbr_particion[ss].part_start - (auxM.mbr_particion[ss-1].part_start +auxM.mbr_particion[ss-1].part_size) > 0)
                                {
                                    result = (float) ((auxM.mbr_particion[ss].part_start - (auxM.mbr_particion[ss-1].part_start +auxM.mbr_particion[ss-1].part_size))*100)/ (float) auxM.mbr_tam;
                                    fprintf(f,"<td colspan= \"100\">Libre<br></br>%f %% libre<br></br> %i Bytes</td>",result,auxM.mbr_particion[ss].part_start - (auxM.mbr_particion[ss-1].part_start +auxM.mbr_particion[ss-1].part_size));
                                }
                                fseek(file,auxM.mbr_particion[ss].part_start,SEEK_SET);
                                fread(&auxE,sizeof(auxE),1,file);
                                ant = auxM.mbr_particion[ss].part_start;
                                fprintf(f,"<td><table border=\"0\" cellborder=\"1\" cellspacing=\"0\"><tr>\r\n");
                                fprintf(f,"<td colspan= \"100\">  Extendida %s</td></tr><tr>",auxM.mbr_particion[ss].part_name);
                                while(auxE.part_next != -1)
                                {
                                    if(auxE.part_size != -1)
                                    {
                                        if(auxE.part_start -(ant+si) >0)
                                        {
                                            result = (float)((auxE.part_start -(ant+si))*100)/ (float)auxM.mbr_tam;
                                            fprintf(f,"<td colspan= \"100\">Libre<br></br>%f %% libre<br></br> %i Bytes</td>",result,auxE.part_start -(ant+si));
                                        }
                                        fprintf(f,"<td colspan= \"100\">EBR</td>");
                                        result = (float) ((auxE.part_size)*100)/ (float) auxM.mbr_tam;
                                        fprintf(f,"<td colspan= \"100\">Logica %s<br></br>%f %% ocupado<br></br> %i Bytes</td>",auxE.part_name,result,auxE.part_size);
                                        ant = auxE.part_start;
                                        si = auxE.part_size;
                                    }

                                    fseek(file,auxE.part_next,SEEK_SET);
                                    fread(&auxE,sizeof(auxE),1,file);
                                }
                                if(auxE.part_size != -1)
                                {
                                    if(auxE.part_start -(ant+si) >0)
                                    {
                                        result = (float)((auxE.part_start -(ant+si))*100)/ (float)auxM.mbr_tam;
                                        fprintf(f,"<td colspan= \"100\">Libre<br></br>%f %% libre<br></br> %i Bytes</td>",result,auxE.part_start -(ant+si));
                                    }
                                    fprintf(f,"<td colspan= \"100\">EBR</td>");
                                    result = (float) ((auxE.part_size)*100)/ (float) auxM.mbr_tam;
                                    fprintf(f,"<td colspan= \"100\">Logica %s<br></br>%f %% ocupado<br></br> %i Bytes</td>",auxE.part_name,result,auxE.part_size);
                                }
                                if(auxE.part_size == -1 && auxE.part_start == -1)
                                {
                                    result = (float) (((auxM.mbr_particion[ss].part_size))*100)/ (float) auxM.mbr_tam;
                                    fprintf(f,"<td colspan= \"100\">Libre<br></br>%f libre<br></br> %i Bytes</td>",result,auxM.mbr_particion[ss].part_size);
                                }else
                                {
                                    if((auxM.mbr_particion[ss].part_start+auxM.mbr_particion[ss].part_size) - (auxE.part_start+auxE.part_size) >0)
                                    {
                                        result = (float) (((auxM.mbr_particion[ss].part_start+auxM.mbr_particion[ss].part_size) - (auxE.part_start+auxE.part_size))*100)/ (float) auxM.mbr_tam;
                                        fprintf(f,"<td colspan= \"100\">Libre<br></br>%f %% libre<br></br> %i Bytes</td>",result,auxM.mbr_particion[ss].part_start+(auxM.mbr_particion[ss].part_start+auxM.mbr_particion[ss].part_size) - (auxE.part_start+auxE.part_size));
                                    }
                                }

                                fprintf(f,"</tr></table></td>");
                                continue;
                            }
                            if(auxM.mbr_particion[ss].part_start - (auxM.mbr_particion[ss-1].part_start + auxM.mbr_particion[ss-1].part_size) > 0)
                            {
                                result = (float) ((auxM.mbr_particion[ss].part_start - (auxM.mbr_particion[ss-1].part_start + auxM.mbr_particion[ss-1].part_size))*100)/ (float) auxM.mbr_tam;
                                fprintf(f,"<td colspan= \"100\">Libre<br></br>%f %% libre<br></br> %i Bytes</td>",result,auxM.mbr_particion[ss].part_start - (auxM.mbr_particion[ss-1].part_start + auxM.mbr_particion[ss-1].part_size));
                            }
                            if(auxM.mbr_particion[ss].part_size != 2147483647)
                            {
                                fprintf(f,"<td colspan= \"100\">");
                                if(auxM.mbr_particion[ss].part_type == 'p')
                                {
                                    fprintf(f,"Primaria %s",auxM.mbr_particion[ss].part_name);
                                }else if(auxM.mbr_particion[ss].part_type == 'e')
                                {
                                    fprintf(f,"Extendida %s",auxM.mbr_particion[ss].part_name);
                                }
                                result = (float) ((auxM.mbr_particion[ss].part_size)*100)/ (float) auxM.mbr_tam;
                                fprintf(f,"<br></br>%f %% ocupado<br></br> %i Bytes</td>",result,auxM.mbr_particion[ss].part_size);
                            }
                        }
                    }

                    if(auxM.mbr_tam - (auxM.mbr_particion[ss-1].part_start+auxM.mbr_particion[ss-1].part_size) >0)
                    {
                        result = (float) auxM.mbr_tam - (auxM.mbr_particion[ss-1].part_start+auxM.mbr_particion[ss-1].part_size);
                        result = (float) result * 100;
                        result = (float) result/ (float) auxM.mbr_tam;
                        fprintf(f,"<td colspan= \"100\">Libre<br></br>%f %% libre<br></br> %i Bytes</td>",result,auxM.mbr_tam - (auxM.mbr_particion[ss-1].part_start+auxM.mbr_particion[ss-1].part_size));
                    }

                    for(int ss = 0; ss<4 ; ss++)
                    {

                    }
                    fprintf(f,"</tr></table>>];}");
                    fclose(f);
                    //limpiarP(&cmd,300);
                    //sprintf(cmd,"dot -Tjpg /home/pixelcode/Escritorio/grafo.dot -o %s",path);
                    //system(cmd);
                    //limpiarP(&cmd,300);
                    crear_imagen();
                    return;
                }
            }
        }
    }
}

void crear_imagen()
{
    char extension[6];
    clean_char(extension,6);
    char t = '*';
    int punte = 0;
    char cmd[300];
    for(int i = 0; i<300; i++)
    {
        if(path[i] == char('.'))
        {
            t = 'r';
            continue;
        }
        if(t != '*' && i < path.length())
        {
            extension[punte] = path[i];
            punte++;
        }
    }
    clean_char(cmd,300);
    sprintf(cmd,"dot -T%s /home/pixelcode/Escritorio/grafo.dot -o %s",extension, path.c_str());
    system(cmd);
    clean_char(cmd,300);
}



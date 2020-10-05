#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include <winbgim.h>

enum MainOpciones
{
    NewEsado = 1,
    ModEstado,
    DelEstado,
    NewPerson,
    ModPerson,
    DelPerson,
    RegCasos,
    MenuGraf,
    ListEstados,
    ListHumans,
    ListRegistros,
    Salir,
};

enum GrafOpciones
{
    GrafPastel = 1,
    GrafPastelGen,
    GrafPastelAge,
    EvolEstado,
    EvoTotalEstado,
    EvolGeneral,
    EvoTotalGeneral,
    CerrarGraficas,
    VolverMenu,
};

typedef struct
{
    int IDEstado;
    char Nombre[50];
    char Descripcion[200];
    bool Existe;
} Estado;

typedef struct Humans
{ //Datos personales
    int NumSS;
    char Nombre[100];
    char Apellidos[100];
    int Edad;
    bool Sexo; // 0 Masculino  1 Femenino

    // Direccon:
    char colonia[30];
    char Calle[30];
    int NumCalle;
    bool Existe;
} Humans;

typedef struct Document
{
    int IDEstado;
    int NumSS;
    char Fecha[20];
    int FechaInt;
    bool Covid19; // 0 Negativo 1 Positivo
} Document;

//HackLifes
void pausa();   //  151
void limpiar(); //  157
void linea();   //  162

//Menus
int Menu();         // 171
int MenuGraficos(); // 200

//Acciones

int NuevoEstado();                    // 224
int BuscarEstado(FILE *, int, int *); // 265
int ModificaEstado();                 // 291
int BorrarEstado();                   // 392

int NuevoPaciente();
int BuscarHumano(FILE *, int, int *);
int ModificaPaciente();
int BorrarPaciente();

int Fecha(struct Document *Registro); //465
int NuevoRegistro();                  //476

//Listas
int ListaEstados();
int ListaPaciente();
int ListaRegistros();

// Acciones de Graficos
int PastelCovid19();
int PastelCovid19Genero();
int PastelCovid19Edad();
int EstadoEvolucion();
int EstadoTotal();
int GeneralEvolucion();
int GeneralTotal();

//Graficos

void pantalla(char *, char *);              // 528
void rectangulo(int, int, int, int, int *); // 537
int VentanaPastel(char *);
int GraficaPastel(int, int, int);

int main()
{
    int opcion;

    linea();
    printf("Proyecto Final\n");
    printf("Actividad: Regsitro y graficacion de casos de Covid19\n\n");
    printf("Alumnos: \n- Franco Altamirano Shai Danao\n- Damian Hernandez Huchin \n- Perez Lugo Kevin Alejandro\n");
    printf("Materia: Programacion 2\n");
    printf("Semestre: 02\t");
    printf("Grupo: 2205\n");
    linea();
    pausa();

    do
    {
        limpiar();
        opcion = Menu();
        limpiar();

        switch (opcion)
        {
        case NewEsado:
            NuevoEstado();
            break;

        case ModEstado:
            ModificaEstado();
            break;

        case DelEstado:
            BorrarEstado();
            break;

        case NewPerson:
            NuevoPaciente();
            break;

        case ModPerson:
            ModificaPaciente();
            break;

        case DelPerson:
            BorrarPaciente();
            break;

        case RegCasos:
            NuevoRegistro();
            break;

        case MenuGraf:
            MenuGraficos();
            break;

        case Salir:
            return 0;
            break;

        case ListEstados:
            ListaEstados();
            break;

        case ListHumans:
            ListaPaciente();
            break;

        case ListRegistros:
            ListaRegistros();
            break;

        default:
            printf("Seleccione una opcion valida :D\n");
            break;
        }
        pausa();
    } while (1);

    return 0;
}

//  Hack Lifes

void pausa()
{
    printf("\n\n");
    system("pause");
}

void limpiar()
{
    system("cls");
}

void linea()
{
    printf("======================================\n");
}

//  Menus

int Menu()
{
    int opcion;

    limpiar();
    printf("\t\tBienvenido, que desea hacer?\n\n");
    printf("\t1. Agregar un Estado      \n");
    printf("\t2. Modificar un Estado    \n");
    printf("\t3. Eliminar un Estado     \n");
    linea();
    printf("\t4. Agregar una Persona\n");
    printf("\t5. Modificar una Persona\n");
    printf("\t6. Eliminar una persona\n");
    linea();
    printf("\t7. Registrar Caso.        \n");
    linea();
    printf("\t8. Ir al menu de graficas\n");
    linea();
    printf("\t9. Lista de Estados      \n");
    printf("\t10. Lista de Humans\n");
    printf("\t11. Lista de Registros    \n");
    linea();
    printf("\t12. Salir\n");

    scanf("%d", &opcion);

    return opcion;
}

int MenuGraficos()
{
    int opcion;
    do
    {
        limpiar();
        printf("\t\tMenu de Graficos, que desea visualizar?\n\n");
        linea();
        printf("\t1. Casos positivos y no positivos general \n");
        printf("\t2. Casos positivos y no positivos por genero\n");
        printf("\t3. Casos positivos y no positivos por rango de edad\n");
        linea();

        printf("\t4. Evolucion de casos positivos por estado\n");
        printf("\t5. Evolucion de casos totales positivos por estado\n");
        linea();
        printf("\t6. Evolucion de casos positivos general\n");
        printf("\t7. Evolucion de casos totales positivos general\n");
        linea();
        printf("\t8. Cerrar todas las graficas\n");
        linea();
        printf("\t9. Regresar a menu principal\n");
        scanf("%d", &opcion);

        limpiar();

        switch (opcion)
        {
        case GrafPastel:
            PastelCovid19();
            break;
        case GrafPastelGen:
            PastelCovid19Genero();
            break;
        case GrafPastelAge:
            PastelCovid19Edad();
            break;
        case EvolEstado:
            EstadoEvolucion();
            break;
        case EvoTotalEstado:
            EstadoTotal();
            break;
        case EvolGeneral:
            GeneralEvolucion();
            break;
        case EvoTotalGeneral:
            GeneralTotal();
            break;
        case CerrarGraficas:
            closegraph();
            printf("Graficas cerradas");
            break;
        case VolverMenu:
            printf("Volviendo al menu principal");
            return 0;
            break;
        default:
            printf("Seleccione una opcion disponible\n\n");
        }
        pausa();
    } while (1);
}

//Acciones

int NuevoEstado()
{
    Estado NewEstado;
    FILE *ArchEstado;
    int resultado, opcion, encontrado;

    ArchEstado = fopen("Estados.dat", "a+b");

    if (ArchEstado == NULL)
    {
        printf("No fue posible abrir el archivo");
        pausa();
    }
    else
    {
        do
        {
            do
            {
                printf("Ingrese el ID del nuevo Estado (Numero Entero)\n");
                scanf("%d", &NewEstado.IDEstado);

                BuscarEstado(ArchEstado, NewEstado.IDEstado, &encontrado);
                rewind(ArchEstado);
                if (encontrado == 1)
                {
                    limpiar();
                    printf("Ese ID ya esta en uso, porfavor ingrese uno nuevo\n\n");
                }
            } while (encontrado == 1);

            printf("\nIngrese el Nombre del nuevo Estado\n");
            getchar();
            fgets(NewEstado.Nombre, 49, stdin);

            printf("\nIngrese una Descripcion:\n");
            fflush(stdin);
            fgets(NewEstado.Descripcion, 199, stdin);

            limpiar();
            do
            {
                printf("Datos Obtenidos: \n");
                printf("ID del Nuevo Estado: %d\n", NewEstado.IDEstado);
                printf("Nombre del Estado: %s", NewEstado.Nombre);
                printf("Descripcion del Estado: %s", NewEstado.Descripcion);
                linea();

                printf("Desea guardar estos datos?\n");
                printf("1) Si\n");
                printf("2) Volver a ingresar datos\n");
                printf("3) Cancelar \n\n");
                scanf("%d", &opcion);

                limpiar();

                switch (opcion)
                {
                case 1:
                    NewEstado.Existe = true;

                    fwrite(&NewEstado, sizeof(Estado), 1, ArchEstado);
                    printf("Estado Agregado");
                    resultado = fclose(ArchEstado);

                    if (resultado == EOF)
                    {
                        printf("\nEl archivo no se pudo cerrar");
                    }
                    return 0;

                case 2:
                    printf("Ingrese de nuevo los datos que se solicitan:\n\n");
                    break;

                case 3:
                    printf("Se cancelo el registro del nuevo estado, volviendo al menu\n");
                    return 0;
                    break;

                default:
                    ("Seleccione una opcion que este disponible");
                    break;
                }
            } while (opcion != 2);
        } while (1);
    }
}

int BuscarEstado(FILE *p, int IDBuscado, int *encontrado)
{

    Estado EdoBuscado;
    int registro = 0;

    *encontrado = 0;

    fread(&EdoBuscado, sizeof(Estado), 1, p);

    while (!feof(p))
    {
        if (EdoBuscado.IDEstado == IDBuscado && EdoBuscado.Existe == true)
        {
            *encontrado = 1;
            break;
        }
        else
        {
            registro++;
            fread(&EdoBuscado, sizeof(Estado), 1, p);
        }
    }
    return registro;
}

int ModificaEstado()
{
    FILE *ArchEstado;
    int resultado, registro, IDBuscado, encontrado, opcion;

    Estado EdoModificado;

    //Abre para escritura/lectura (binario)
    ArchEstado = fopen("Estados.dat", "r+b");

    if (ArchEstado == NULL)
    {
        printf("No fue posible abrir el archivo");
    }
    else
    {
        printf("Cual es el ID del Estado? ");
        scanf("%d", &IDBuscado);

        registro = BuscarEstado(ArchEstado, IDBuscado, &encontrado);

        if (encontrado == 1)
        {

            //Localiza el registro (inicia en 0)
            fseek(ArchEstado, registro * sizeof(Estado), SEEK_SET);
            //Lee el contenido del registro
            fread(&EdoModificado, sizeof(Estado), 1, ArchEstado);

            do
            {
                printf("\nDatos Actuales:\n\n");
                linea();
                printf("ID: %d", EdoModificado.IDEstado);
                printf("\nNombre: %s", EdoModificado.Nombre);
                printf("\nDescripcion: %s\n", EdoModificado.Descripcion);
                linea();

                printf("\tQue desea modificar?\n");
                printf("\t1. Nombre del Estado\n");
                printf("\t2. Descripcion del Estado\n");
                linea();
                printf("\t3. Finalizar Edicion\n\nOpcion: ");

                scanf("%d", &opcion);

                switch (opcion)
                {
                case 1:
                    printf("\nIngrese el nuevo Nombre del Estado\n");
                    getchar();
                    fgets(EdoModificado.Nombre, 49, stdin);
                    printf("\nDatos obtenidos, para guardarlos inserte la opcion 4\n");
                    break;
                case 2:
                    printf("\nIngrese una nueva Descripcion:\n");
                    getchar();
                    fgets(EdoModificado.Descripcion, 199, stdin);
                    printf("\nDatos obtenidos, para guardarlos inserte la opcion 4\n");
                    break;

                case 3:
                    //Vuelve a posicionar el cursor ya que la lectura lo hab�a movido
                    fseek(ArchEstado, registro * sizeof(Estado), SEEK_SET);
                    //Sobreescribe el contenido de la memoria en el archivo
                    fwrite(&EdoModificado, sizeof(Estado), 1, ArchEstado);

                    printf("\nSe actualizaron los datos del estado");
                    break;

                default:
                    printf("Seleccione una opcion valida :D\n");
                    pausa();
                    break;
                }

                pausa();
                limpiar();
            } while (opcion != 3);
        }
        else
        {
            printf("\nNo se encontraron los datos del Estado");
            pausa();
        }

        resultado = fclose(ArchEstado);

        if (resultado == EOF)
        {
            printf("\nEl archivo no se pudo cerrar");
        }
    }
}

int BorrarEstado()
{
    FILE *ArchEstado;
    int resultado, registro, IDBuscado, encontrado, opcion;

    Estado EdoBorrar;

    //Abre para escritura/lectura (binario)
    ArchEstado = fopen("Estados.dat", "r+b");

    if (ArchEstado == NULL)
    {
        printf("No fue posible abrir el archivo");
    }
    else
    {
        printf("Cual es el ID del Estado que desea borrar? ");
        scanf("%d", &IDBuscado);

        registro = BuscarEstado(ArchEstado, IDBuscado, &encontrado);

        if (encontrado == 1)
        {
            //Localiza el registro (inicia en 0)
            fseek(ArchEstado, registro * sizeof(Estado), SEEK_SET);
            //Lee el contenido del registro
            fread(&EdoBorrar, sizeof(Estado), 1, ArchEstado);

            printf("\nDatos Del Estado:\n\n");
            linea();
            printf("ID: %d", EdoBorrar.IDEstado);
            printf("\nNombre: %s", EdoBorrar.Nombre);
            printf("\nDescripcion: %s\n", EdoBorrar.Descripcion);
            linea();

            printf("\nSeguro que desea borrar este estado?\n");
            printf("1: Si\n");
            printf("2: No\n");
            scanf("%d", &opcion);

            limpiar();

            if (opcion == 1)
            {
                EdoBorrar.Existe = false;

                //Vuelve a posicionar el cursor ya que la lectura lo hab�a movido
                fseek(ArchEstado, registro * sizeof(Estado), SEEK_SET);
                //Sobreescribe el contenido de la memoria en el archivo
                fwrite(&EdoBorrar, sizeof(Estado), 1, ArchEstado);

                printf("\nSe borro los datos del estado");
            }
            else
            {
                printf("\nEl Estado no fue eliminado");
            }
        }
        else
        {
            printf("\nNo se encontraron los datos del Estado");
        }

        resultado = fclose(ArchEstado);

        if (resultado == EOF)
        {
            printf("\nEl archivo no se pudo cerrar");
        }
    }
}

//Humans
int NuevoPaciente()
{
    Humans NewHuman;
    FILE *ArchHuman;
    int resultado, opcion, encontrado;

    ArchHuman = fopen("Humanos.dat", "a+b");

    if (ArchHuman == NULL)
    {
        printf("No fue posible abrir el archivo");
        pausa();
    }
    else
    {
        do
        {
            do
            {
                //Datos Personales del Paciente
                printf("Ingrese el Numero de Seguro Social del paciete (Numero Entero)\n");
                scanf("%d", &NewHuman.NumSS);

                BuscarHumano(ArchHuman, NewHuman.NumSS, &encontrado);

                if (encontrado)
                {
                    limpiar();
                    printf("Ese Numero de Seguro ya fue registrado, porfavor ingrese uno nuevo\n\n");
                }

            } while (encontrado);

            printf("\nIngrese el Nombre(s) del Paciente: \n");
            getchar();
            fgets(NewHuman.Nombre, 100, stdin);

            printf("\nIngrese los apellidos del Paciente:\n");
            fflush(stdin);
            fgets(NewHuman.Apellidos, 100, stdin);

            printf("Ingrese La edad del paciete (Numero Entero)\n");
            scanf("%d", &NewHuman.Edad);

            printf("Ingrese El sexo del paciete (1) Masculino o (2) Femenino\n");

            scanf("%d", &opcion);
            if (opcion == 1)
            {
                printf("El paciente es Masculino");
                NewHuman.Sexo = false;
                pausa();
            }
            else
            {
                printf("El paciente es Femenino");
                NewHuman.Sexo = true;
                pausa();
            }

            limpiar();

            printf("\nIngrese la colonia del Paciente:\n");
            getchar();
            fgets(NewHuman.colonia, 30, stdin);

            printf("\nIngrese la calle de la direccion del Paciente: \n");
            fflush(stdin);
            fgets(NewHuman.Calle, 30, stdin);

            printf("Ingrese el Numero de la calle (Numero Entero)\n");
            scanf("%d", &NewHuman.NumCalle);

            limpiar();
            do
            {
                printf("Numero de Seguridad Social: %d", NewHuman.NumSS);
                printf("\nNombre: %s\t    %s", NewHuman.Nombre, NewHuman.Apellidos);
                printf("Edad: %d Sexo: ", NewHuman.Edad);
                if (NewHuman.Sexo)
                {
                    printf("Femenino\n");
                }
                else
                    printf("Masculino\n");
                printf("\nDireccion del Paciente:");
                printf("\nColonia: %s Calle: %s#%d \n", NewHuman.colonia, NewHuman.Calle, NewHuman.NumCalle);
                linea();

                printf("Desea guardar estos datos?\n");
                printf("1) Si\n");
                printf("2) Volver a ingresar datos\n");
                printf("3) Cancelar \n\n");
                scanf("%d", &opcion);

                limpiar();

                switch (opcion)
                {
                case 1:
                    NewHuman.Existe = true;

                    fwrite(&NewHuman, sizeof(Humans), 1, ArchHuman);
                    printf("Paciente Agregado");

                    resultado = fclose(ArchHuman);

                    if (resultado == EOF)
                    {
                        printf("\nEl archivo no se pudo cerrar");
                    }
                    return 0;

                case 2:
                    printf("Ingrese de nuevo los datos que se solicitan:\n\n");
                    break;

                case 3:
                    printf("Se cancelo el registro del nuevo paciente, volviendo al menu\n");
                    return 0;
                    break;

                default:
                    ("Seleccione una opcion que este disponible");
                    pausa();
                    break;
                }

            } while (opcion != 2);
        } while (1);
    }
}

int BuscarHumano(FILE *p, int IDBuscado, int *encontrado)
{

    Humans HumBuscado;
    int registro = 0;

    *encontrado = 0;

    fread(&HumBuscado, sizeof(Humans), 1, p);

    while (!feof(p))
    {
        if (HumBuscado.NumSS == IDBuscado && HumBuscado.Existe == true)
        {
            *encontrado = 1;
            break;
        }
        else
        {
            registro++;
            fread(&HumBuscado, sizeof(Humans), 1, p);
        }
    }
    return registro;
}

int ModificaPaciente()
{
    FILE *ArchHuman;
    int resultado, registro, SSBuscado, encontrado, opcion;
    Humans PacienteModificado;

    //Abre para escritura/lectura (binario)
    ArchHuman = fopen("Humanos.dat", "r+b");

    if (ArchHuman == NULL)
    {
        printf("No fue posible abrir el archivo");
    }
    else
    {
        printf("Cual es el Numero de seguridad social del paciente? ");
        scanf("%d", &SSBuscado);

        registro = BuscarHumano(ArchHuman, SSBuscado, &encontrado);

        if (encontrado == 1)
        {

            //Localiza el registro (inicia en 0)
            fseek(ArchHuman, registro * sizeof(Humans), SEEK_SET);
            //Lee el contenido del registro
            fread(&PacienteModificado, sizeof(Humans), 1, ArchHuman);

            do
            {
                printf("\nDatos Actuales:\n\n");
                linea();
                printf("Numero de Seguridad Social: %d", PacienteModificado.NumSS);
                printf("\nNombre: %sApellidos: %s", PacienteModificado.Nombre, PacienteModificado.Apellidos);
                printf("\nEdad: %d Sexo: ", PacienteModificado.Edad);
                if (PacienteModificado.Sexo)
                {
                    printf("Femenino\n");
                }
                else
                    printf("Masculino\n");

                printf("\nDireccion del Paciente:\n");
                printf("Colonia: %sCalle:%s#%d\n", PacienteModificado.colonia, PacienteModificado.Calle, PacienteModificado.NumCalle);
                linea();

                //Hacer Menu
                printf("\n\tQue datos del paciente desea modificar?\n");
                printf("\t1. Nombre \n");
                printf("\t2. Edad \n");
                printf("\t3. Sexo\n");
                printf("\t4. Direccion \n");
                linea();
                printf("\t5. Finalizar Edicion\n\nOpcion: ");

                scanf("%d", &opcion);

                switch (opcion)
                {
                case 1:
                    printf("\nIngrese el Nombre(s) del Paciente: \n");
                    getchar();
                    fgets(PacienteModificado.Nombre, 100, stdin);
                    printf("\nIngrese los apellidos del Paciente:\n");
                    fflush(stdin);
                    fgets(PacienteModificado.Apellidos, 100, stdin);
                    printf("\nDatos obtenidos, para guardarlos inserte la opcion 6\n");
                    break;
                case 2:
                    printf("Ingrese La edad del paciete (Numero Entero)\n");
                    scanf("%d", &PacienteModificado.Edad);
                    printf("\nDatos obtenidos, para guardarlos inserte la opcion 6\n");
                    break;
                case 3:
                    printf("Ingrese El sexo del paciete (1) Masculino o (2) Femenino\n");
                    scanf("%d", &opcion);
                    if (opcion == 1)
                    {
                        printf("El paciente es Masculino");
                        PacienteModificado.Sexo = false;
                        pausa();
                    }
                    else
                    {
                        printf("El paciente es Femenino");
                        PacienteModificado.Sexo = true;
                        pausa();
                    }

                    printf("\nDatos obtenidos, para guardarlos inserte la opcion 6\n");
                    break;
                case 4:
                    printf("\nIngrese la colonia del Paciente:\n");
                    fflush(stdin);
                    fgets(PacienteModificado.colonia, 30, stdin);
                    printf("\nIngrese la calle de la direccion del Paciente: \n");
                    getchar();
                    fgets(PacienteModificado.Calle, 30, stdin);
                    printf("Ingrese el Numero de la calle (Numero Entero)\n");
                    scanf("%d", &PacienteModificado.NumCalle);
                    printf("\nDatos obtenidos, para guardarlos inserte la opcion 6\n");
                    break;

                case 5:
                    //Vuelve a posicionar el cursor ya que la lectura lo hab?a movido
                    fseek(ArchHuman, registro * sizeof(Humans), SEEK_SET);
                    //Sobreescribe el contenido de la memoria en el archivo
                    fwrite(&PacienteModificado, sizeof(Humans), 1, ArchHuman);

                    printf("\nSe actualizaron los datos del Paciente");
                    return 0;
                    break;

                default:
                    printf("Seleccione una opcion valida :D\n");
                    pausa();
                    break;
                }

                pausa();
                limpiar();
            } while (opcion != 5);
        }
        else
        {
            printf("\nNo se encontraron los datos del Paciente");
            pausa();
        }

        resultado = fclose(ArchHuman);

        if (resultado == EOF)
        {
            printf("\nEl archivo no se pudo cerrar");
        }
    }
}

int BorrarPaciente()
{
    FILE *ArchHum;
    int resultado, registro, IDBuscado, encontrado, opcion;

    Humans PacienteBorrar;

    //Abre para escritura/lectura (binario)
    ArchHum = fopen("Humanos.dat", "r+b");

    if (ArchHum == NULL)
    {
        printf("No fue posible abrir el archivo");
    }
    else
    {
        printf("\nCual es el Numero de seguro social del paciente que desea borrar? \n");
        scanf("%d", &IDBuscado);

        registro = BuscarHumano(ArchHum, IDBuscado, &encontrado);

        if (encontrado == 1)
        {
            //Localiza el registro (inicia en 0)
            fseek(ArchHum, registro * sizeof(Humans), SEEK_SET);
            //Lee el contenido del registro
            fread(&PacienteBorrar, sizeof(Humans), 1, ArchHum);

            printf("\nDatos Del Paciente:\n\n");
            linea();
            printf("Numero de Seguridad Social: %d", PacienteBorrar.NumSS);
            printf("\nNombre: %s\t    %s", PacienteBorrar.Nombre, PacienteBorrar.Apellidos);
            printf("Edad: %d Sexo: ", PacienteBorrar.Edad);
            if (PacienteBorrar.Sexo)
            {
                printf("Femenino\n");
            }
            else
                printf("Masculino\n");
            printf("\nDireccion del Paciente:");
            printf("\nColonia: %s Calle:%s#%d \n", PacienteBorrar.colonia, PacienteBorrar.Calle, PacienteBorrar.NumCalle);
            linea();

            printf("\nSeguro que desea borrar el paciente?\n");
            printf("1: Si\n");
            printf("2: No\n");
            scanf("%d", &opcion);

            limpiar();

            if (opcion == 1)
            {
                PacienteBorrar.Existe = false;

                //Vuelve a posicionar el cursor ya que la lectura lo hab?a movido
                fseek(ArchHum, registro * sizeof(Humans), SEEK_SET);
                //Sobreescribe el contenido de la memoria en el archivo
                fwrite(&PacienteBorrar, sizeof(Humans), 1, ArchHum);

                printf("\nSe borro los datos del paciente");
            }
            else
            {
                printf("\nEl Paciente no fue eliminado");
            }
        }
        else
        {
            printf("\nNo se encontraron los datos del Paciente");
            pausa();
        }

        resultado = fclose(ArchHum);

        if (resultado == EOF)
        {
            printf("\nEl archivo no se pudo cerrar");
        }
    }
}

int Fecha(struct Document *Registro)
{
    char Fecha[20];

    time_t tiempo = 1577836800 + (86400 * (Registro->FechaInt));
    struct tm *tlocal = localtime(&tiempo);
    strftime(Fecha, 128, "%d/%m/%y", tlocal);

    strcpy(Registro->Fecha, Fecha);
}

int NuevoRegistro()
{
    Document NewRegistro;
    FILE *ArchRegistro, *ArchEstados, *ArchHumanos;
    int opcion, resultado[3], encontrado;

    ArchRegistro = fopen("Registro.dat", "ab");
    ArchEstados = fopen("Estados.dat", "rb");
    ArchHumanos = fopen("Humanos.dat", "rb");

    if (ArchRegistro == NULL || ArchEstados == NULL || ArchHumanos == NULL)
    {
        printf("No fue posible abrir uno o varios archivos");
    }
    else
    {
        do
        {
            do
            {
                printf("Ingrese el ID del Estado donde se realizo la prueba\n");
                scanf("%d", &NewRegistro.IDEstado);

                BuscarEstado(ArchEstados, NewRegistro.IDEstado, &encontrado);
                rewind(ArchEstados);
                if (encontrado == 0)
                {
                    limpiar();
                    printf("Ese ID no esta registrado, porfavor ingrese uno nuevo\n\n");
                }
            } while (encontrado == 0);
            limpiar();
            do
            {

                printf("\nIngrese el NSS del paciente atendiro\n");
                scanf("%d", &NewRegistro.NumSS);
                BuscarHumano(ArchHumanos, NewRegistro.NumSS, &encontrado);
                rewind(ArchHumanos);
                if (encontrado == 0)
                {
                    limpiar();
                    printf("Ese Numero de Seguro no ha sido registrado, porfavor ingrese uno nuevo\n\n");
                }

            } while (encontrado == 0);

            printf("\nIngrese el numero del dia del año en que fue realizada la prueba\n");
            scanf("%d", &NewRegistro.FechaInt);

            Fecha(&NewRegistro);

            printf("\nEl paciente dio positivo?\n");
            printf("1) Si\n");
            printf("2) No\n");
            scanf("%d", &opcion);

            if (opcion == 1)
            {
                NewRegistro.Covid19 = true;
            }
            else
                NewRegistro.Covid19 = false;

            do
            {
                limpiar();
                printf("Datos Obtenidos:\n");
                printf("NSS del paciente: %d\n", NewRegistro.NumSS);
                printf("IDE del Estado donde se realizo la prueba %d\n", NewRegistro.IDEstado);
                printf("Dia del registro: %s\n", NewRegistro.Fecha);
                printf("Covid19: ");
                if (NewRegistro.Covid19)
                {
                    printf("Positivo\n");
                }
                else
                    printf("Negativo\n");
                linea();

                printf("Desea guardar estos datos?\n");
                printf("1) Si\n");
                printf("2) Volver a ingresar datos\n");
                printf("3) Cancelar \n\n");
                scanf("%d", &opcion);

                limpiar();

                switch (opcion)
                {
                case 1:
                    fwrite(&NewRegistro, sizeof(Document), 1, ArchRegistro);
                    printf("Registro Agregado");

                    resultado[0] = fclose(ArchRegistro);
                    resultado[1] = fclose(ArchEstados);
                    resultado[2] = fclose(ArchHumanos);

                    if (resultado[0] == EOF || resultado[1] == EOF || resultado[2] == EOF)
                    {
                        printf("\nUno o varios archivos no se purieron cerrar");
                    }
                    return 0;

                case 2:
                    printf("Ingrese de nuevo los datos que se solicitan:\n\n");
                    break;

                case 3:
                    printf("Se cancelo el registro, volviendo al menu\n");
                    return 0;
                    break;

                default:
                    ("Seleccione una opcion que este disponible");
                    pausa();
                    break;
                }
            } while (opcion != 2);
        } while (1);
    }
}

//Listas

int ListaEstados()
{

    FILE *Estados;
    int resultado;
    Estado country;
    Estados = fopen("Estados.dat", "rb");
    if (Estados == NULL)
    {
        printf("El archivo no se ha encontrado");
    }
    else
    {
        fread(&country, sizeof(Estado), 1, Estados);
        while (!feof(Estados))
        {
            if (country.Existe)
            {
                printf("\nID de Estado:%d", country.IDEstado);
                printf("\nNombre: %s", country.Nombre);
                printf("Descripcion: %s\n", country.Descripcion);
                linea();
            }
            fread(&country, sizeof(Estado), 1, Estados);
        }

        resultado = fclose(Estados);

        if (resultado == EOF)
        {
            printf("\nEl archivo no se pudo cerrar");
        }
    }
}

int ListaPaciente()
{
    FILE *ArchHum;
    int resultado, registro;
    Humans Paciente;

    ArchHum = fopen("Humanos.dat", "r+b");
    if (ArchHum == NULL)
    {
        printf("No fue posible abrir el archivo");
    }
    else
    {
        //Lee el contenido del registro
        fread(&Paciente, sizeof(Humans), 1, ArchHum);

        while (!feof(ArchHum))
        {
            if (Paciente.Existe)
            {
                printf("Numero de Seguridad Social: %d", Paciente.NumSS);
                printf("\nNombre: %s %s", Paciente.Nombre, Paciente.Apellidos);
                printf("Edad: %d Sexo: ", Paciente.Edad);
                if (Paciente.Sexo)
                {
                    printf("Femenino\n");
                }
                else
                    printf("Masculino\n");

                printf("\n\tDireccion del Paciente:");
                printf("\nColonia: %sCalle:%s#%d \n", Paciente.colonia, Paciente.Calle, Paciente.NumCalle);
                linea();
            }
            fread(&Paciente, sizeof(Humans), 1, ArchHum);
        }
        resultado = fclose(ArchHum);

        if (resultado == EOF)
        {
            printf("\nEl archivo no se pudo cerrar");
        }
    }
}

int ListaRegistros()
{
    FILE *Aregistro;
    int resultado, casoN = 1;
    Document registrar;
    Aregistro = fopen("Registro.dat", "rb");
    if (Aregistro == NULL)
    {
        printf("El archivo no se ha encontrado");
    }

    else
    {
        fread(&registrar, sizeof(Document), 1, Aregistro);
        while (!feof(Aregistro))
        {
            printf("Caso %d", casoN++);
            printf("\nID: %d", registrar.IDEstado);
            printf("\nNSS: %d", registrar.NumSS);
            printf("\nFecha: %s", registrar.Fecha);
            printf("\nCovid19: ");
            if (registrar.Covid19 == true)
            {
                printf("Positivo\n");
            }
            else
                printf("Negativo\n");
            linea();

            fread(&registrar, sizeof(Document), 1, Aregistro);
        }
        resultado = fclose(Aregistro);

        if (resultado == EOF)
        {
            printf("\nEl archivo no se pudo cerrar");
        }
    }
}

// Acciones de Graficos
int PastelCovid19()
{
    FILE *Aregistro, *ArchPaciente;
    int resultado, pacienteEncontrado, Positivo = 0, Negativo = 0;
    Document registrar;
    Aregistro = fopen("Registro.dat", "rb");
    ArchPaciente = fopen("Humanos.dat", "rb");
    if (Aregistro == NULL || ArchPaciente == NULL)
    {
        printf("Uno o mas archivos no se han encontrado/abierto");
    }

    else
    {
        fread(&registrar, sizeof(Document), 1, Aregistro);
        while (!feof(Aregistro))
        {
            BuscarHumano(ArchPaciente, registrar.NumSS, &pacienteEncontrado);
            if (pacienteEncontrado == 1)
            {
                if (registrar.Covid19)
                {
                    Positivo++;
                }
                else
                    Negativo++;
            }
            rewind(ArchPaciente);

            fread(&registrar, sizeof(Document), 1, Aregistro);
        }

        VentanaPastel("Casos Positivos/Negativos Total");
        GraficaPastel(Positivo, Negativo, Positivo + Negativo);

        resultado = fclose(Aregistro);

        if (resultado == EOF)
        {
            printf("\nEl archivo no se pudo cerrar\n");
        }
        resultado = fclose(ArchPaciente);

        if (resultado == EOF)
        {
            printf("\nEl archivo no se pudo cerrar\n");
        }
    }
}

int PastelCovid19Genero()
{
    FILE *Aregistro, *ArchPaciente;
    int resultado, pacienteEncontrado, Positivo = 0, Negativo = 0,opcion,registro;
    bool genero;
    Document registrar;
    Humans HumComprobar;

    Aregistro = fopen("Registro.dat", "rb");
    ArchPaciente = fopen("Humanos.dat", "rb");
    if (Aregistro == NULL || ArchPaciente == NULL)
    {
        printf("Uno o mas archivos no se han encontrado/abierto");
    }
    else
    {
        printf("Ingresa el genero que deseas ver:\n");
        printf("1) Masculino\n2) Femenino\n");
        scanf("%d",&opcion);

        if(opcion == 1){
            genero = false;
            VentanaPastel("Casos Positivos/Negativos Masculino");
        }
        else {
            genero = true;
            VentanaPastel("Casos Positivos/Negativos Femenino");
        }

        fread(&registrar, sizeof(Document), 1, Aregistro);
        while (!feof(Aregistro))
        {
            registro = BuscarHumano(ArchPaciente, registrar.NumSS, &pacienteEncontrado);
            if (pacienteEncontrado == 1)
            {
                //Localiza el registro (inicia en 0)
                fseek(ArchPaciente, registro * sizeof(Humans), SEEK_SET);
                //Lee el contenido del registro
                fread(&HumComprobar, sizeof(Humans), 1, ArchPaciente);

                if (HumComprobar.Sexo == genero){
                    if (registrar.Covid19)
                    {
                        Positivo++;
                    }
                    else
                        Negativo++;
                }
            }
            rewind(ArchPaciente);

            fread(&registrar, sizeof(Document), 1, Aregistro);
        }

        GraficaPastel(Positivo, Negativo, Positivo + Negativo);

        resultado = fclose(Aregistro);

        if (resultado == EOF)
        {
            printf("\nEl archivo no se pudo cerrar\n");
        }
        resultado = fclose(ArchPaciente);

        if (resultado == EOF)
        {
            printf("\nEl archivo no se pudo cerrar\n");
        }
    }
}

int PastelCovid19Edad()
{
    FILE *Aregistro, *ArchPaciente;
    int resultado, pacienteEncontrado, Positivo = 0, Negativo = 0,EdadMin,EdadMax,registro;
    bool genero;
    Document registrar;
    Humans HumComprobar;

    Aregistro = fopen("Registro.dat", "rb");
    ArchPaciente = fopen("Humanos.dat", "rb");
    if (Aregistro == NULL || ArchPaciente == NULL)
    {
        printf("Uno o mas archivos no se han encontrado/abierto");
    }
    else
    {
        printf("Ingresa la edad minima\n");
        scanf("%d",&EdadMin);
        printf("Ingresa la edad maxima\n");
        scanf("%d",&EdadMax);

        VentanaPastel("Casos Positivos/Negativos Por Edad");

        fread(&registrar, sizeof(Document), 1, Aregistro);
        while (!feof(Aregistro))
        {
            registro = BuscarHumano(ArchPaciente, registrar.NumSS, &pacienteEncontrado);
            if (pacienteEncontrado == 1)
            {
                //Localiza el registro (inicia en 0)
                fseek(ArchPaciente, registro * sizeof(Humans), SEEK_SET);
                //Lee el contenido del registro
                fread(&HumComprobar, sizeof(Humans), 1, ArchPaciente);

                if (HumComprobar.Edad >= EdadMin && HumComprobar.Edad <= EdadMax){
                    if (registrar.Covid19)
                    {
                        Positivo++;
                    }
                    else
                        Negativo++;
                }
            }
            rewind(ArchPaciente);

            fread(&registrar, sizeof(Document), 1, Aregistro);
        }

        GraficaPastel(Positivo, Negativo, Positivo + Negativo);

        resultado = fclose(Aregistro);

        if (resultado == EOF)
        {
            printf("\nEl archivo no se pudo cerrar\n");
        }
        resultado = fclose(ArchPaciente);

        if (resultado == EOF)
        {
            printf("\nEl archivo no se pudo cerrar\n");
        }
    }
}

int EstadoEvolucion()
{
    FILE *Aregistro, *ArchEstado, *ArchPaciente;
    int resultado, posicion = 100, IDEStado, ubicacion, encontrado, pacienteEncontrado, MaxRegistros = 0, ndias = 0, casos, SiRegistro;
    Document registrar;
    Estado EstadoGraf;

    Aregistro = fopen("Registro.dat", "rb");
    ArchEstado = fopen("Estados.dat", "rb");
    ArchPaciente = fopen("Humanos.dat", "rb");
    if (Aregistro == NULL || ArchEstado == NULL || ArchPaciente == NULL)
    {
        printf("Uno o mas archivos no se han encontrado/abierto");
    }

    else
    {
        printf("Ingrese el ID del Estado que desea ver:\n");
        scanf("%d", &IDEStado);

        ubicacion = BuscarEstado(ArchEstado, IDEStado, &encontrado);
        if (encontrado == 1)
        {
            //Localiza el registro (inicia en 0)
            fseek(ArchEstado, ubicacion * sizeof(Estado), SEEK_SET);
            //Lee el contenido del registro
            fread(&EstadoGraf, sizeof(Estado), 1, ArchEstado);

            fread(&registrar, sizeof(Document), 1, Aregistro);

            rewind(Aregistro);

            for (int dia = 0; dia < 367; dia++)
            {
                SiRegistro = 0;
                casos = 0;

                fread(&registrar, sizeof(Document), 1, Aregistro);
                while (!feof(Aregistro))
                {
                    if (registrar.IDEstado == IDEStado && registrar.Covid19 == true && registrar.FechaInt == dia)
                    {
                        BuscarHumano(ArchPaciente, registrar.NumSS, &pacienteEncontrado);
                        if (pacienteEncontrado == 1)
                        {
                            casos++;
                            SiRegistro++;
                        }
                        rewind(ArchPaciente);
                    }
                    fread(&registrar, sizeof(Document), 1, Aregistro);
                }

                if (SiRegistro > 0)
                {
                    ndias++;
                }

                if (casos > MaxRegistros)
                {
                    MaxRegistros = casos;
                }

                rewind(Aregistro);
            }

            rewind(Aregistro);

            pantalla("Evolucion Estado", EstadoGraf.Nombre);

            for (int dia = 1; dia < 367; dia++)
            {
                casos = 0;

                fread(&registrar, sizeof(Document), 1, Aregistro);
                while (!feof(Aregistro))
                {

                    if (registrar.IDEstado == IDEStado && registrar.Covid19 == true && registrar.FechaInt == dia)
                    {
                        BuscarHumano(ArchPaciente, registrar.NumSS, &pacienteEncontrado);
                        if (pacienteEncontrado == 1)
                        {
                            casos++;
                        }
                        rewind(ArchPaciente);
                    }

                    fread(&registrar, sizeof(Document), 1, Aregistro);
                }

                if (casos > 0)
                {
                    rectangulo(casos, MaxRegistros, ndias, dia, &posicion);
                }

                rewind(Aregistro);
            }
            printf("\n");
        }

        resultado = fclose(Aregistro);

        if (resultado == EOF)
        {
            printf("\nEl archivo no se pudo cerrar");
        }
        resultado = fclose(ArchEstado);

        if (resultado == EOF)
        {
            printf("\nEl archivo no se pudo cerrar");
        }
        resultado = fclose(ArchPaciente);

        if (resultado == EOF)
        {
            printf("\nEl archivo no se pudo cerrar");
        }
    }
}

int EstadoTotal()
{
    FILE *Aregistro, *ArchEstado, *ArchPaciente;
    int resultado, posicion = 100, IDEStado, ubicacion, encontrado, pacienteEncontrado, MaxRegistros = 0, ndias = 0, casos, SiRegistro, grafica;
    Document registrar;
    Estado EstadoGraf;

    Aregistro = fopen("Registro.dat", "rb");
    ArchEstado = fopen("Estados.dat", "rb");
    ArchPaciente = fopen("Humanos.dat", "rb");
    if (Aregistro == NULL || ArchEstado == NULL || ArchPaciente == NULL)
    {
        printf("Uno o mas archivos no se han encontrado/abierto");
    }

    else
    {
        printf("Ingrese el ID del Estado que desea ver:\n");
        scanf("%d", &IDEStado);

        ubicacion = BuscarEstado(ArchEstado, IDEStado, &encontrado);
        if (encontrado == 1)
        {
            //Localiza el registro (inicia en 0)
            fseek(ArchEstado, ubicacion * sizeof(Estado), SEEK_SET);
            //Lee el contenido del registro
            fread(&EstadoGraf, sizeof(Estado), 1, ArchEstado);

            fread(&registrar, sizeof(Document), 1, Aregistro);

            rewind(Aregistro);
            casos = 0;

            for (int dia = 0; dia < 367; dia++)
            {
                SiRegistro = 0;

                fread(&registrar, sizeof(Document), 1, Aregistro);
                while (!feof(Aregistro))
                {

                    if (registrar.IDEstado == IDEStado && registrar.Covid19 == true && registrar.FechaInt == dia)
                    {
                        BuscarHumano(ArchPaciente, registrar.NumSS, &pacienteEncontrado);
                        if (pacienteEncontrado == 1)
                        {
                            casos++;
                            SiRegistro++;
                        }
                        rewind(ArchPaciente);
                    }

                    fread(&registrar, sizeof(Document), 1, Aregistro);
                }

                if (SiRegistro > 0)
                {
                    ndias++;
                }

                if (casos > MaxRegistros)
                {
                    MaxRegistros = casos;
                }

                rewind(Aregistro);
            }

            rewind(Aregistro);

            pantalla("Evolucion Estado Total", EstadoGraf.Nombre);

            casos = 0;
            for (int dia = 1; dia < 367; dia++)
            {
                grafica = 0;
                fread(&registrar, sizeof(Document), 1, Aregistro);
                while (!feof(Aregistro))
                {

                    if (registrar.IDEstado == IDEStado && registrar.Covid19 == true && registrar.FechaInt == dia)
                    {
                        BuscarHumano(ArchPaciente, registrar.NumSS, &pacienteEncontrado);
                        if (pacienteEncontrado == 1)
                        {
                            casos += 1;
                            grafica = 1;
                        }
                        rewind(ArchPaciente);
                    }

                    fread(&registrar, sizeof(Document), 1, Aregistro);
                }

                if (grafica > 0)
                {
                    rectangulo(casos, MaxRegistros, ndias, dia, &posicion);
                }

                rewind(Aregistro);
            }
        }
        else
        {
            printf("\n\nEstado no Encontrado\n");
        }

        resultado = fclose(Aregistro);

        if (resultado == EOF)
        {
            printf("\nEl archivo no se pudo cerrar");
        }
        resultado = fclose(ArchEstado);

        if (resultado == EOF)
        {
            printf("\nEl archivo no se pudo cerrar");
        }
        resultado = fclose(ArchPaciente);

        if (resultado == EOF)
        {
            printf("\nEl archivo no se pudo cerrar");
        }
    }
}

int GeneralEvolucion()
{
    FILE *Aregistro, *ArchPaciente;
    int resultado, posicion = 100, pacienteEncontrado, MaxRegistros = 0, ndias = 0, casos, SiRegistro;
    Document registrar;

    Aregistro = fopen("Registro.dat", "rb");
    ArchPaciente = fopen("Humanos.dat", "rb");

    if (Aregistro == NULL || ArchPaciente == NULL)
    {
        printf("Uno o mas archivos no se han encontrado/abierto");
    }

    else
    {

        fread(&registrar, sizeof(Document), 1, Aregistro);
        rewind(Aregistro);

        for (int dia = 0; dia < 367; dia++)
        {
            SiRegistro = 0;
            casos = 0;

            fread(&registrar, sizeof(Document), 1, Aregistro);
            while (!feof(Aregistro))
            {

                if (registrar.Covid19 == true && registrar.FechaInt == dia)
                {
                    BuscarHumano(ArchPaciente, registrar.NumSS, &pacienteEncontrado);
                    if (pacienteEncontrado == 1)
                    {
                        casos++;
                        SiRegistro++;
                    }
                    rewind(ArchPaciente);
                }

                fread(&registrar, sizeof(Document), 1, Aregistro);
            }

            if (SiRegistro > 0)
            {
                ndias++;
            }

            if (casos > MaxRegistros)
            {
                MaxRegistros = casos;
            }

            rewind(Aregistro);
        }

        rewind(Aregistro);
        pantalla("Evolucion General", " General");

        for (int dia = 1; dia < 367; dia++)
        {
            casos = 0;

            fread(&registrar, sizeof(Document), 1, Aregistro);
            while (!feof(Aregistro))
            {

                if (registrar.Covid19 == true && registrar.FechaInt == dia)
                {
                    BuscarHumano(ArchPaciente, registrar.NumSS, &pacienteEncontrado);
                    if (pacienteEncontrado == 1)
                    {
                        casos += 1;
                    }
                    rewind(ArchPaciente);
                }

                fread(&registrar, sizeof(Document), 1, Aregistro);
            }

            if (casos > 0)
            {
                rectangulo(casos, MaxRegistros, ndias, dia, &posicion);
            }

            rewind(Aregistro);
        }

        resultado = fclose(Aregistro);

        if (resultado == EOF)
        {
            printf("\nEl archivo no se pudo cerrar");
        }
        resultado = fclose(ArchPaciente);

        if (resultado == EOF)
        {
            printf("\nEl archivo no se pudo cerrar");
        }
    }
}

int GeneralTotal()
{
    FILE *Aregistro, *ArchPaciente;
    int resultado, posicion = 100, pacienteEncontrado, MaxRegistros = 0, ndias = 0, casos, SiRegistro, grafica;
    Document registrar;

    Aregistro = fopen("Registro.dat", "rb");
    ArchPaciente = fopen("Humanos.dat", "rb");

    if (Aregistro == NULL || ArchPaciente == NULL)
    {
        printf("Uno o mas archivos no se han encontrado/abierto");
    }

    else
    {

        fread(&registrar, sizeof(Document), 1, Aregistro);

        rewind(Aregistro);
        casos = 0;

        for (int dia = 0; dia < 367; dia++)
        {
            SiRegistro = 0;

            fread(&registrar, sizeof(Document), 1, Aregistro);
            while (!feof(Aregistro))
            {

                if (registrar.Covid19 == true && registrar.FechaInt == dia)
                {
                    BuscarHumano(ArchPaciente, registrar.NumSS, &pacienteEncontrado);
                    if (pacienteEncontrado == 1)
                    {
                        casos++;
                        SiRegistro++;
                    }
                    rewind(ArchPaciente);
                }

                fread(&registrar, sizeof(Document), 1, Aregistro);
            }

            if (SiRegistro > 0)
            {
                ndias++;
            }

            if (casos > MaxRegistros)
            {
                MaxRegistros = casos;
            }

            rewind(Aregistro);
        }

        rewind(Aregistro);

        pantalla("Evolucion General Total", "General Total");

        casos = 0;
        for (int dia = 1; dia < 367; dia++)
        {
            grafica = 0;
            fread(&registrar, sizeof(Document), 1, Aregistro);
            while (!feof(Aregistro))
            {

                if (registrar.Covid19 == true && registrar.FechaInt == dia)
                {
                    BuscarHumano(ArchPaciente, registrar.NumSS, &pacienteEncontrado);
                    if (pacienteEncontrado == 1)
                    {
                        casos += 1;
                        grafica = 1;
                    }
                    rewind(ArchPaciente);
                }

                fread(&registrar, sizeof(Document), 1, Aregistro);
            }

            if (grafica > 0)
            {
                rectangulo(casos, MaxRegistros, ndias, dia, &posicion);
            }

            rewind(Aregistro);
        }

        resultado = fclose(Aregistro);

        if (resultado == EOF)
        {
            printf("\nEl archivo no se pudo cerrar");
        }
        resultado = fclose(ArchPaciente);

        if (resultado == EOF)
        {
            printf("\nEl archivo no se pudo cerrar");
        }
    }
}

//Graficos

void pantalla(char *Nombre, char *Estado)
{
    initwindow(1100, 800, Nombre);

    setcolor(15);
    setlinestyle(0, 0, 1);
    line(100, 0, 100, 800);
    line(0, 700, 1100, 700);

    setbkcolor(COLOR(0, 0, 0));
    settextstyle(10, 1, 1);
    settextjustify(1, 1);
    outtextxy(50, 400, Estado);
}

void rectangulo(int cantidad, int maxcasos, int maxdias, int ndia, int *posicion)
{
    static int color = 1;
    int largo = (1000 / maxdias) + *posicion;

    int alto = (((cantidad * 700) / maxcasos) - 700) * -1;
    //printf("\n%d\n",alto);

    setlinestyle(0, 0, 5);
    setfillstyle(3, 15);

    if (color % 2 == 0)
    {
        setcolor(COLOR(29, 97, 234));
        setbkcolor(COLOR(29, 97, 234));
    }
    else
    {
        setcolor(COLOR(58, 182, 140));
        setbkcolor(COLOR(58, 182, 140));
    }

    //rectangle (*posicion, alto, largo, 700);
    int lados[10] = {*posicion + 10, alto, *posicion + 10, 700, largo - 10, 700, largo - 10, alto, *posicion + 10, alto};
    fillpoly(5, lados);

    char CantidadChar[5];
    sprintf(CantidadChar, "%d", cantidad);

    setcolor(COLOR(255, 255, 255));
    settextstyle(10, 0, 5);
    outtextxy(*posicion + (largo - *posicion) / 2, alto + 30, CantidadChar);

    setbkcolor(COLOR(0, 0, 0));
    settextstyle(10, 1, 1);
    settextjustify(1, 1);

    char Fecha[20];

    time_t tiempo = 1577836800 + (86400 * (ndia));
    struct tm *tlocal = localtime(&tiempo);
    strftime(Fecha, 128, "%d/%m/%y", tlocal);

    outtextxy(*posicion + 10 + (largo - *posicion) / 2, 750, Fecha);

    *posicion = largo;
    color++;
}

int VentanaPastel(char *Titulo)
{
    initwindow(1000, 800, Titulo);
}

int GraficaPastel(int Positivo, int Negativo, int Total)
{
    int rebanadaPositivo = Positivo * 360 / Total;

    //int porcentajePositivo = Positivo * 100 / Total;
    //int porcentajeNegativo = Negativo * 100 / Total;

    setcolor(COLOR(255, 255, 255));
    setlinestyle(0, 0, 3);
    settextstyle(10, 0, 1);
    settextjustify(2, 1);

    setbkcolor(COLOR(234, 29, 77));
    setfillstyle(11, COLOR(255, 255, 255));
    pieslice(getmaxx() / 2, getmaxy() / 2, 0, rebanadaPositivo, 350);

    setbkcolor(COLOR(15, 191, 255));
    setfillstyle(11, COLOR(255, 255, 255));
    pieslice(getmaxx() / 2, getmaxy() / 2, rebanadaPositivo, 360, 350);

    char PositivoChar[20];
    sprintf(PositivoChar, "Positivos: %d", Positivo);

    char NegativoChar[20];
    sprintf(NegativoChar, "Negativo: %d", Negativo);

    setbkcolor(COLOR(0, 0, 0));
    setcolor(COLOR(255, 93, 93));
    outtextxy(150, 20, PositivoChar);
    setcolor(COLOR(15, 191, 255));
    outtextxy(150, 50, NegativoChar);

    //Rojo COLOR(255, 93, 93)
    //Azul COLOR(15, 191, 255)
}
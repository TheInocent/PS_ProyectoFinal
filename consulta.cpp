#include "consulta.h"
#include <iostream>
#include <fstream>
#include <string>

//Charge data one y charge data all hacen que se llene el array de struct de las citas
void load_one_user(int posicion, string linea)
{
    int tam = linea.size();
    int posi = 0;
    int posf = 0;
    string aux;
    int aux_data_type = 0;

    for (int i = 0; i < tam; i++)
    {
        if (linea[i] == '$')
        {
            posf = i - 1;
            aux = linea.substr(posi, (posf - posi + 1));

            switch (aux_data_type)
            {
            case 0:
                appointment_list[posicion].id_cita = stoi(aux);
                break;
            case 1:
                appointment_list[posicion].id_paciente = stoi(aux);
                break;
            case 2:
                appointment_list[posicion].dia = stoi(aux);
                break;
            case 3:
                appointment_list[posicion].mes = stoi(aux);
                break;
            case 4:
                appointment_list[posicion].anio = stoi(aux);
                break;
            case 5:
                appointment_list[posicion].hora = stoi(aux);
                break;
            case 6:
                appointment_list[posicion].especialidad = aux;
                break;
            case 7:
                appointment_list[posicion].consultorio = stoi(aux);
                break;
            case 8:
                appointment_list[posicion].condicion = stoi(aux);
                break;
            case 9:
                appointment_list[posicion].turno = stoi(aux);
                break;
            default:
                break;
            }
            aux_data_type++;
            posi = i + 1;
        }
    }
}

void appointment_data_load()
{
    ifstream lectura;
    lectura.open("citas.txt", ios::in);

    string texto;

    if (lectura.is_open())
    {
        while (!lectura.eof())
        {
            getline(lectura, texto);
            load_one_user(arr_length_appointment_list, texto);
            arr_length_appointment_list++;
        }
    }
    else
    {
        cout << "No se pudo abrir el archivo o aun no ha sido creado" << endl;
    }

    lectura.close();
}

void users_load_one_user(int posicion, string linea) //Para modificar
{
    int tam = linea.size();
    int posi = 0;
    int posf = 0;
    string aux;
    int aux_data_type = 0;

    for (int i = 0; i < tam; i++)
    {
        if (linea[i] == '&')
        {
            posf = i - 1;
            aux = linea.substr(posi, (posf - posi + 1));

            switch (aux_data_type)
            {
            case 0:
                user_list[posicion].user_id = stoi(aux);
                break;
            case 1:
                user_list[posicion].nombre = aux;
                break;
            case 2:
                user_list[posicion].apellido = aux;
                break;
            case 3:
                user_list[posicion].telefono = aux;
                break;
            case 4:
                user_list[posicion].email = aux;
                break;
            case 5:
                user_list[posicion].direccion = aux;
                break;
            case 6:
                user_list[posicion].username = aux;
                break;
            case 7:
                user_list[posicion].password = aux;
                break;
            case 8:
                user_list[posicion].user_type = stoi(aux);
                break;
            default:
                break;
            }
            aux_data_type++;
            posi = i + 1;
        }
    }
}

void user_data_load()
{
    ifstream lectura;
    lectura.open("datos.txt", ios::in);

    string texto;

    if (lectura.is_open())
    {
        while (!lectura.eof())
        {
            getline(lectura, texto);
            users_load_one_user(arr_length_user_list, texto);
            arr_length_user_list++;
        }
    }
    else
    {
        cout << "No se pudo abrir el archivo o aun no ha sido creado" << endl;
    }

    lectura.close();
}

void login()
{
    //Se llena el array de struct
    //int UserID = 2;

    //ESTRUCTURA DE USUARIOS EN "datos.txt"
    //1&juan&perez&987654321&juan@unsa.edu.pe&CalleCusco&juan&poir&U
    while (true)
    {
        string usuario, clave;
        cout << "\nDigite el nombre de usario: ";
        cin >> usuario;
        cout << "\nDigite su contraseña: ";
        cin >> clave;
        bool encontrado = false;

        for (int i = 0; i < arr_length_user_list; i++)
        {
            if (user_list[i].username == usuario && user_list[i].password == clave)
            {
                UserID = user_list[i].user_id;
                cout << "\nUsuario encontrado";
                //usuario encontrado
                encontrado = true;
                break;
            }
        }
        if (encontrado)
            break;
        //cout << "\nUsuario no encontrado, intentar otro";
        //usuario no encontrado, seguir intentando
    }
}

void select_cita_paciente(int id_paciente)
{
    cout << "======================================================================" << endl;
    for (int i = 0; i < arr_length_appointment_list; i++)
    {
        if (appointment_list[i].id_paciente == id_paciente)
        {
            cout << "\tEl ID de la cita: " << appointment_list[i].id_cita << endl;
            cout << "\tEspecialidad: " << appointment_list[i].especialidad << endl;
            switch (appointment_list[i].condicion)
            { //0 = Pendiente 1 = Aceptada 2 = No acpetada 3 = Concluida
            case 0:
                cout << "\tESTADO: PENDIENTE" << endl;
                break;
            case 1:
                cout << "\tESTADO: ACEPTADA" << endl;
                break;
            case 2:
                cout << "\tESTADO: NO ACEPTADA" << endl;
                break;
            case 3:
                cout << "\tESTADO: NO CONCLUIDA" << endl;
                break;
            }
            cout << "\tFecha: " << appointment_list[i].dia << appointment_list[i].mes << appointment_list[i].anio << endl;
        }
    }
    cout << "======================================================================" << endl;
}

void select_cita_paciente_pendiente(int id_paciente)
{
    cout << "=============================" << endl;
    cout << "CITAS PENDIENTES DE "
         << "USUARIO" << endl;
    for (int i = 0; i < arr_length_appointment_list; i++)
    {
        if (appointment_list[i].id_paciente == id_paciente && appointment_list[i].condicion == 0)
        {
            cout << "El ID de la cita: " << appointment_list[i].id_cita << endl;
            cout << "Especialidad: " << appointment_list[i].especialidad << endl;
            cout << "Fecha: " << appointment_list[i].dia << appointment_list[i].mes << appointment_list[i].anio << endl;
        }
    }
    cout << "=============================" << endl;
}

void basic_user_modify()
{

    int pos_to_modify = -1;
    int menu_aux;
    string input_aux;
    bool realizado = true;

    select_cita_paciente_pendiente(UserID);
    cout << "Seleccione la ID de la cita a modificar (Solo se muestran las citas pendientes)" << endl;
    cin >> pos_to_modify;

    do
    {
        cout << "¿Qué dato desea modificar?" << endl;
        cout << "1. Día" << endl;
        cout << "2. Mes" << endl;
        cout << "3. Hora" << endl;
        cout << "4. Especialidad" << endl;
        cin >> menu_aux;

        switch (menu_aux)
        {
        case 1:
            cout << "Ingrese un nuevo dia: " << endl;
            cin >> input_aux;
            appointment_list[pos_to_modify - 1].dia = stoi(input_aux);
            break;
        case 2:
            cout << "Ingrese un nuevo mes: " << endl;
            cin >> input_aux;
            appointment_list[pos_to_modify - 1].mes = stoi(input_aux);
            break;
        case 3:
            cout << "Ingrese una nueva hora: " << endl;
            cin >> input_aux;
            appointment_list[pos_to_modify - 1].hora = stoi(input_aux);
            break;
        case 4:
            cout << "Ingrese una nueva especilidad: " << endl;
            cin >> input_aux;
            appointment_list[pos_to_modify - 1].especialidad = input_aux;
            break;

        default:
            cout << "Opcion invalida intente de nuevo: " << endl;
            break;
        }

    } while (!realizado);
}
void change_appointment_condition()
{
    int pos_to_modify = -1;
    int menu_aux;
    int input_aux;
    bool realizado = false;
    cout << "\n\tSeleccione el ID de la cita a cambiar condicion" << endl;
    cin >> pos_to_modify;
    do
    {
        cout << "\n\tA que condicion quiere cambiar la cita \n"
             << endl;
        cout << "\t1. Aceptada" << endl;
        cout << "\t2. No aceptada" << endl;
        cout << "\t3. Concluida" << endl;
        cout << "\t4. Salir" << endl;
        cin >> input_aux;
        if (input_aux == 1 || input_aux == 2 || input_aux == 3)
        {
            appointment_list[pos_to_modify - 1].condicion = input_aux;
            cout << "\tCondicion de cita cambiada con exito !!!" << endl;
            system("cls");
            menu_moderator_user();
            break;
        }
        else if (input_aux == 4)
        {
            cout << "\tSaliendo ..." << endl;
            system("cls");
            menu_moderator_user();
            break;
        }
        else
        {
            cout << "\tOpcion invalida intente de nuevo . . . " << endl;
        }
    } while (!realizado);
}
void select_all_citas_pacientes()
{
    for (int i = 0; i < arr_length_user_list; i++)
    {
        cout << "\tPaciente: " << user_list[i].nombre << " " << user_list[i].apellido << endl;
        select_cita_paciente(user_list[i].user_id);
    }
    system("pause");
    system("cls");
    menu_moderator_user();
}
void select_citas_pendientes()
{
    for (int i = 0; i < arr_length_appointment_list; i++)
    {
        if (appointment_list[i].condicion == 0)
        {
            cout << "=====================================================================" << endl;
            cout << "\tEl ID de la cita: " << appointment_list[i].id_cita << endl;
            cout << "\tID Paciente: " << appointment_list[i].id_paciente << endl;
            cout << "\tEspecialidad: " << appointment_list[i].especialidad << endl;
            cout << "\tConsultorio:" << appointment_list[i].consultorio << endl;
            cout << "\tFecha: " << appointment_list[i].dia << " / " << appointment_list[i].mes << " / " << appointment_list[i].anio << " Turno: " << appointment_list[i].turno << endl;
            cout << "\tCondicion: " << appointment_list[i].condicion << endl;
            switch (appointment_list[i].condicion)
            { //0 = Pendiente 1 = Aceptada 2 = No acpetada 3 = Concluida
            case 0:
                cout << "\tCondicion: PENDIENTE" << endl;
                break;
            case 1:
                cout << "\tCondicion: ACEPTADA" << endl;
                break;
            case 2:
                cout << "\tCondicion: NO ACEPTADA" << endl;
                break;
            case 3:
                cout << "\tCondicion:: NO CONCLUIDA" << endl;
                break;
            }
            cout << "=====================================================================" << endl;
        }
    }
    change_appointment_condition();
}

void select_citas()
{
    for (int i = 0; i < arr_length_appointment_list; i++)
    {
        cout << "==================================================================" << endl;
        cout << "\tID Cita: " << appointment_list[i].id_cita << endl;
        cout << "\tID Paciente: " << appointment_list[i].id_paciente << endl;
        cout << "\tFecha: " << appointment_list[i].dia << " / " << appointment_list[i].mes << " / " << appointment_list[i].anio << " Turno: " << appointment_list[i].turno << endl;
        cout << "\tConsultorio:" << appointment_list[i].consultorio << endl;
        cout << "\tCondicion: " << appointment_list[i].condicion << endl;
        switch (appointment_list[i].condicion)
        { //0 = Pendiente 1 = Aceptada 2 = No acpetada 3 = Concluida
        case 0:
            cout << "\tCondicion:: PENDIENTE" << endl;
            break;
        case 1:
            cout << "\tCondicion:: ACEPTADA" << endl;
            break;
        case 2:
            cout << "\tCondicion:: NO ACEPTADA" << endl;
            break;
        case 3:
            cout << "\tCondicion:: NO CONCLUIDA" << endl;
            break;
        }
        cout << "==================================================================" << endl;
    }
}

void moderator_user_modify()
{
    select_citas();
    int pos_to_modify = -1;
    int menu_aux;
    string input_aux;
    bool realizado = true;
    cout << "\tSeleccione el ID de la cita a modificar" << endl;
    cin >> pos_to_modify;
    do
    {
        cout << "\t¿Que dato desea modificar?\n"
             << endl;
        cout << "\t1. Dia" << endl;
        cout << "\t2. Mes" << endl;
        cout << "\t3. Hora" << endl;
        cout << "\t4. Turno" << endl;
        cout << "\t5. Especialidad" << endl;
        cout << "\t6. Consultorio" << endl;
        cout << "\t7. Condicion" << endl;
        cout << "\t8. Salir\n"
             << endl;
        cin >> menu_aux;
        switch (menu_aux)
        {
        case 1:
            cout << "\tIngrese un nuevo dia: " << endl;
            cin >> input_aux;
            appointment_list[pos_to_modify - 1].dia = stoi(input_aux);
            cout << "\tDia de cita modificado con exito !!!" << endl;
            break;
        case 2:
            cout << "\tIngrese un nuevo mes: " << endl;
            cin >> input_aux;
            appointment_list[pos_to_modify - 1].mes = stoi(input_aux);
            cout << "\tMes de cita modificado con exito !!!" << endl;
            break;
        case 3:
            cout << "\tIngrese una nueva hora: " << endl;
            cin >> input_aux;
            appointment_list[pos_to_modify - 1].hora = stoi(input_aux);
            cout << "\tHora de cita modificado con exito !!!" << endl;
            break;
        case 4:
            cout << "I\tngrese una nuevo turno: " << endl;
            cin >> input_aux;
            appointment_list[pos_to_modify - 1].turno = stoi(input_aux);
            cout << "\tTurno de cita modificado con exito !!!" << endl;
            break;
        case 5:
            cout << "\tIngrese una nueva especialidad: " << endl;
            cin >> input_aux;
            appointment_list[pos_to_modify - 1].especialidad = input_aux;
            cout << "\tEspecialidad de cita modificado con exito !!!" << endl;
            break;
        case 6:
            cout << "\tIngrese una nueva consultorio: " << endl;
            cin >> input_aux;
            appointment_list[pos_to_modify - 1].consultorio = stoi(input_aux);
            cout << "\tConsultorio de cita modificado con exito !!!" << endl;
            break;
        case 7:
            cout << "\tIngrese una nueva condicion de cita: " << endl;
            cin >> input_aux;
            //Verificar condicion de cita valida 0 = Pendiente 1 = Aceptada 2 = No acpetada 3 = Concluida
            appointment_list[pos_to_modify - 1].condicion = stoi(input_aux);
            cout << "\tCondicion de cita modificado con exito !!!" << endl;
            break;
        case 8:
            cout << "Saliendo . . ." << endl;
            //system("cls");
            break;
        default:
            cout << "Opcion invalida intente de nuevo: " << endl;
            break;
        }
    } while (!realizado);
    system("cls");
    menu_moderator_user();
}

void modify()
{

    if (user_list[UserID - 1].user_type == 0) //Usuario Normal
    {
        basic_user_modify();
    }
    else
    { //Usuario con privilegios
        moderator_user_modify();
    }
}

void addCita()
{
    appointment_list[arr_length_appointment_list].id_cita = arr_length_appointment_list + 1;
    if (user_list[UserID - 1].user_type != 0)
    { //administrador
        cout << "\tIngrese id del paciente: ";
        cin >> appointment_list[arr_length_appointment_list].id_paciente;
    }
    else //Usuario normal
    {
        appointment_list[arr_length_appointment_list].id_paciente = UserID;
    }

    cout << "\tIngrese dia de la cita: ";
    cin >> appointment_list[arr_length_appointment_list].dia;
    cout << "\tIngrese mes de la cita: ";
    cin >> appointment_list[arr_length_appointment_list].mes;
    cout << "\tIngrese anio de la cita: ";
    cin >> appointment_list[arr_length_appointment_list].anio;
    cout << "\tIngrese hora de la cita: ";
    cin >> appointment_list[arr_length_appointment_list].hora;
    cout << "\tIngrese la especialidad a la que se desea ir: ";
    cin >> appointment_list[arr_length_appointment_list].especialidad;
    cout << "\tIngrese número de consultorio al cual acudir ";
    cin >> appointment_list[arr_length_appointment_list].consultorio;
    if (user_list[UserID - 1].user_type != 0) //administrador
    {
        int cond_cita;
        cout << "Condicion de la cita. Digite: 0 = Pendiente, 1 = Aceptada, 2 = No aceptada ";
        cin >> cond_cita;
        appointment_list[arr_length_appointment_list].condicion = cond_cita;
        if (cond_cita != 0 || cond_cita != 1 || cond_cita != 2)
        {
            cout << "No existen más opciones, se pone cita como pendiente por default ";
            appointment_list[arr_length_appointment_list].condicion = 0;
        }
    }
    else // Usuario normal
    {
        appointment_list[arr_length_appointment_list].condicion = 0;
        cout << "Cita registrada como pendiente. Administrador podra cambiar la cita a Aceptada ";
    }
    arr_length_appointment_list++;
    system("cls");
    menu_moderator_user();
}

void load_program_menus()
{
    cout << "EL usuario es: " << user_list[UserID - 1].nombre << " con " << user_list[UserID - 1].user_type << endl;
    if (user_list[UserID - 1].user_type == 0) //Usuario Normal
    {
        menu_normal_user();
    }
    else
    { //Usuario con privilegios
        menu_moderator_user();
    }
}

void end_session()
{
    ofstream escritura;
    escritura.open("citas.txt", ios::out);
    if (escritura.fail())
    {
        cout << "No se puedo abrir el archivo para guardar" << endl;
        exit(1);
    }

    for (int i = 0; i < arr_length_appointment_list; i++)
    {
        if (i == arr_length_appointment_list - 1)
        {
            escritura << appointment_list[i].id_cita << "$" << appointment_list[i].id_paciente << "$" << appointment_list[i].dia << "$" << appointment_list[i].mes << "$" << appointment_list[i].anio << "$" << appointment_list[i].hora << "$" << appointment_list[i].especialidad << "$" << appointment_list[i].consultorio << "$" << appointment_list[i].condicion << "$";
        }
        else
        {
            escritura << appointment_list[i].id_cita << "$" << appointment_list[i].id_paciente << "$" << appointment_list[i].dia << "$" << appointment_list[i].mes << "$" << appointment_list[i].anio << "$" << appointment_list[i].hora << "$" << appointment_list[i].especialidad << "$" << appointment_list[i].consultorio << "$" << appointment_list[i].condicion << "$" << endl;
        }
    }
    escritura.close();
}

void menu_normal_user()
{
    int menu_aux;
    bool realizado = false;
    do
    {
        cout << "Hola " << user_list[arr_length_user_list].nombre << " " << user_list[arr_length_user_list].apellido << "!" << endl;
        cout << "1. Crear un cita" << endl;
        cout << "2. Modificar una cita pendiente" << endl;
        cout << "3. Ver mis citas pendientes" << endl;
        cout << "4. Ver mi historial de citas" << endl;
        cin >> menu_aux;

        switch (menu_aux)
        {
        case 1:
            cout << "Crear un Cita!: " << endl;
            addCita();
            realizado = true;
            break;
        case 2:
            cout << "Modificar una cita!" << endl;
            modify();
            realizado = true;
            break;
        case 3:
            cout << "Ver mis citas pendientes" << endl;
            select_cita_paciente_pendiente(UserID);
            realizado = true;
            break;
        case 4:
            cout << "Ver mi historial de citas" << endl;
            select_cita_paciente(UserID);
            realizado = true;
            break;

        default:
            cout << "Opcion invalida intente de nuevo: " << endl;
            break;
        }

    } while (!realizado);
}

void menu_moderator_user()
{
    int menu_aux;
    bool realizado = false;
    do
    {
        cout << " \n\tBienvenido " << user_list[UserID - 1].nombre << " " << user_list[UserID - 1].apellido << " !!!" << endl;
        cout << "\n\t1. Crear un cita" << endl;
        cout << "\t2. Modificar una cita" << endl;
        cout << "\t3. Aceptar citas pendienes" << endl;
        cout << "\t4. Crear usuario" << endl; //AUN
        cout << "\t5. Ver citas por paciente" << endl;
        cout << "\t6. Ver todas las citas" << endl;
        cout << "\t7. Ver los usuarios existentes" << endl;
        cout << "\t8. Salir" << endl;
        cin >> menu_aux;

        switch (menu_aux)
        {
        case 1:
            system("cls");
            cout << "\t\tCREAR CITA\n"
                 << endl;
            addCita();
            realizado = true;
            break;
        case 2:
            system("cls");
            cout << "\t\tMODIFICAR UNA CITA\n"
                 << endl;
            modify();
            realizado = true;
            break;
        case 3:
            system("cls");
            cout << "\t\tCITAS PENDIENTES\n"
                 << endl;
            select_citas_pendientes();
            realizado = true;
            break;
        case 4:
            cout << "\t\tCREAR USUARIO\n"
                 << endl;
            realizado = true;
            break;
        case 5:
            system("cls");
            cout << "\t\tCITAS POR PACIENTE\n"
                 << endl;
            select_all_citas_pacientes();
            realizado = true;
            break;
        case 6:
            system("cls");
            cout << "\t\tTODAS LAS CITAS\n " << endl;
            select_citas();
            realizado = true;
            system("pause");
            system("cls");
            menu_moderator_user();
            break;
        case 7:
            cout << "\t\tUSUARIOS EXISTENTES\n"
                 << endl;
            realizado = true;
            break;
        case 8:
            cout << "\tSaliendo . . .\n"
                 << endl;
            realizado = true;
            break;
        default:
            cout << "Opcion invalida intente de nuevo: " << endl;
            break;
        }

    } while (!realizado);
}

void init_program()
{
    appointment_data_load();
    user_data_load();
    login();
    load_program_menus();
    end_session();
}
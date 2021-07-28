#include "consulta.h"

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
    cout << "=============================" << endl;
    for (int i = 0; i < arr_length_appointment_list; i++)
    {
        if (appointment_list[i].id_paciente == id_paciente)
        {
            cout << "El ID de la cita: " << appointment_list[i].id_cita << endl;
            cout << "Especialidad: " << appointment_list[i].especialidad << endl;
            switch (appointment_list[i].condicion)
            { //0 = Pendiente 1 = Aceptada 2 = No acpetada 3 = Concluida
            case 0:
                cout << "ESTADO: PENDIENTE" << endl;
                break;
            case 1:
                cout << "ESTADO: ACEPTADA" << endl;
                break;
            case 2:
                cout << "ESTADO: NO ACEPTADA" << endl;
                break;
            case 3:
                cout << "ESTADO: NO CONCLUIDA" << endl;
                break;
            }
            cout << "Fecha: " << appointment_list[i].dia << appointment_list[i].mes << appointment_list[i].anio << endl;
        }
    }
    cout << "=============================" << endl;
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

void select_citas_pendientes()
{
    cout << "CITAS PENDIENTES DE APROBACION" << endl;
    for (int i = 0; i < arr_length_appointment_list; i++)
    {
        if (appointment_list[i].condicion == 0)
        {
            cout << "==========================================" << endl;
            cout << "El ID de la cita: " << appointment_list[i].id_cita << endl;
            cout << "ID Paciente: " << appointment_list[i].id_paciente << endl;
            cout << "Especialidad: " << appointment_list[i].especialidad << endl;
            cout << "Consultorio:" << appointment_list[i].consultorio << endl;
            cout << "Fecha: " << appointment_list[i].dia << " / " << appointment_list[i].mes << " / " << appointment_list[i].anio << " Turno: " << appointment_list[i].turno << endl;
            cout << "Condicion" << appointment_list[i].condicion << endl;
            cout << "==========================================" << endl;
        }
    }
}

void list_citas()
{
    cout << "LISTA DE TODAS LAS CITAS" << endl;
    for (int i = 0; i < arr_length_appointment_list; i++)
    {
        cout << "==========================================" << endl;
        cout << "ID Cita: " << appointment_list[i].id_cita << endl;
        cout << "ID Paciente: " << appointment_list[i].id_paciente << endl;
        cout << "Fecha: " << appointment_list[i].dia << " / " << appointment_list[i].mes << " / " << appointment_list[i].anio << " Turno: " << appointment_list[i].turno << endl;
        cout << "Consultorio:" << appointment_list[i].consultorio << endl;
        cout << "Condicion" << appointment_list[i].condicion << endl;
        cout << "==========================================" << endl;
    }
}

void moderator_user_modify()
{
    int pos_to_modify = -1;
    int menu_aux;
    string input_aux;
    bool realizado = true;
    //lista todas las citas
    list_citas();
    cout << "Seleccione el ID de la cita a modificar" << endl;
    cin >> pos_to_modify;
    do
    {
        cout << "¿Qué dato desea modificar?" << endl;
        cout << "1. Día" << endl;
        cout << "2. Mes" << endl;
        cout << "3. Hora" << endl;
        cout << "4. Turno" << endl;
        cout << "5. Especialidad" << endl;
        cout << "6. Consultorio" << endl;
        cout << "7. Condicion" << endl;
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
            cout << "Ingrese una nuevo turno: " << endl;
            cin >> input_aux;
            appointment_list[pos_to_modify - 1].turno = stoi(input_aux);
            break;
        case 5:
            cout << "Ingrese una nueva especialidad: " << endl;
            cin >> input_aux;
            appointment_list[pos_to_modify - 1].especialidad = input_aux;
            break;
        case 6:
            cout << "Ingrese una nueva consultorio: " << endl;
            cin >> input_aux;
            appointment_list[pos_to_modify - 1].consultorio = stoi(input_aux);
            break;
        case 7:
            cout << "Ingrese una nueva condicion de cita: " << endl;
            cin >> input_aux;
            //Verificar condicion de cita valida 0 = Pendiente 1 = Aceptada 2 = No acpetada 3 = Concluida
            appointment_list[pos_to_modify - 1].condicion = stoi(input_aux);
            break;
        default:
            cout << "Opcion invalida intente de nuevo: " << endl;
            break;
        }

    } while (!realizado);
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
        cout << "Ingrese id del paciente: ";
        cin >> appointment_list[arr_length_appointment_list].id_paciente;
    }
    else //Usuario normal
    {
        appointment_list[arr_length_appointment_list].id_paciente = UserID;
    }

    cout << "Ingrese dia de la cita: ";
    cin >> appointment_list[arr_length_appointment_list].dia;
    cout << "Ingrese mes de la cita: ";
    cin >> appointment_list[arr_length_appointment_list].mes;
    cout << "Ingrese anio de la cita: ";
    cin >> appointment_list[arr_length_appointment_list].anio;
    cout << "Ingrese hora de la cita: ";
    cin >> appointment_list[arr_length_appointment_list].hora;
    cout << "Ingrese la especialidad a la que se desea ir: ";
    cin >> appointment_list[arr_length_appointment_list].especialidad;
    cout << "Ingrese número de consultorio al cual acudir ";
    cin >> appointment_list[arr_length_appointment_list].consultorio;
    if (user_list[UserID - 1].user_type != 0) //administrador
    {
        int cond_cita;
        cout << "Condicion de la cita. Digite: 0 = Pendiente, 1 = Aceptada, 2 = No acpetada";
        cin >> cond_cita;
        appointment_list[arr_length_appointment_list].condicion = cond_cita;
        if (cond_cita != 0 || cond_cita != 1 || cond_cita != 2)
        {
            cout << "No existen más opciones, se pone cita como pendiente por default";
            appointment_list[arr_length_appointment_list].condicion = 0;
        }
    }
    else // Usuario normal
    {
        appointment_list[arr_length_appointment_list].condicion = 0;
        cout << "Cita registrada como pendiente. Administrador podra cambiar la cita a Aceptada";
    }
    arr_length_appointment_list++;
}

void load_program_menus()
{
     cout << "EL usuario es: " << user_list[UserID-1].nombre << " con "  << user_list[UserID - 1].user_type << endl;
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
        cout << "Bienvenido "
             << "Persona (Por cambiar a hacer referencia) " << endl;
        cout << "1. Crear un cita" << endl;
        cout << "2. Modificar una cita" << endl;
        cout << "3. Aceptar citas pendienes" << endl;
        cout << "4. Crear usuario" << endl; //AUN
        cout << "5. Ver citas por paciente" << endl;
        cout << "6. Ver todas las citas" << endl;
        cout << "7. Ver los usuarios existentes" << endl;
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
            cout << "Ver las citas pendientes por aceptar" << endl;
            select_citas_pendientes();
            realizado = true;
            break;
        case 4:
            cout << "Crear un uusario" << endl;

            realizado = true;
            break;
        case 5:
            cout << "Ver citas por paciente" << endl;
            realizado = true;
            break;
        case 6:
            cout << "Ver citas por paciente" << endl;

            realizado = true;
            break;
        case 7:
            cout << "Ver todas las citas" << endl;

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

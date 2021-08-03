#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <fstream>
#include <stdlib.h> 

using namespace std;

//Variable global de el ID del usuario logeado
int UserID;


//Struct del usuario con un array de struct
struct User{
    int user_id;
    string nombre;
    string apellido;
    string telefono;
    string email;
    string direccion;
    string username;
    string password;
    int user_type;
};
User user_list[100];
int arr_length_user_list = 0;


//Struct del citas con un array de struct
struct Cita
{
    int id_cita;
    int id_paciente;
    int dia;
    int mes;
    int anio;
    int hora;
    string especialidad;
    int consultorio;
    int condicion; //0 = Pendiente 1 = Aceptada 2 = No acpetada 3 = Concluida
    int turno;
};
Cita appointment_list[100];
int arr_length_appointment_list = 0;

void load_one_user(int, string );
void appointment_data_load();
void users_load_one_user(int, string );
void user_data_load();
void login();
void select_cita_paciente(int);
void select_cita_paciente_pendiente (int);
void basic_user_modify();
void select_citas();
void moderator_user_modify();
void modify();
void addCita();
void load_program_menus();
void end_session();
void menu_normal_user();
void menu_moderator_user();
void register_user();
void sign_up(int t);
void init_program();
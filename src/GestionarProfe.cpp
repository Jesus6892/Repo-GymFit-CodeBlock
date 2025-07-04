#include "GestionarProfe.h"
#include <iostream>
#include <iomanip>
#include <ctime>
#include <algorithm>
#include <cctype>
#include "Utilidades.h"
#include "Profe.h"
#include "Validaciones.h"
using namespace std;

GestionarProfesor::GestionarProfesor()
    : archivoProfesores(sizeof(Profe))
{
}

// Metodos Auxiliares
std::string GestionarProfesor::solicitarDniProfesor()
{
    string dniIngresado, dniNormalizado;
    while (true)
    {
        cout << "Ingrese el DNI del profesor: ";
        getline(cin, dniIngresado);

        dniNormalizado = Validaciones::normalizarDNI(dniIngresado);

        if (!Validaciones::esFormatoDniValido(dniNormalizado))
        {
            cout << "Error: El DNI debe contener 7 u 8 dígitos. Intente de nuevo.\n";
            continue;
        }
        if (archivoProfesores.buscarIdPorDni(dniNormalizado) != -1)
        {
            cout << "Error: Ya existe un profesor con ese DNI. Intente de nuevo.\n";
            continue;
        }
        return dniNormalizado;
    }
}

// Métodos Principales
Profe GestionarProfesor::cargarProfesor()
{
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string nombre, apellido, correoElectronico, observaciones, direccion;
    string telefono, CUIT;
    int idProfe;

    cout << "Ingrese el nombre del profesor: ";
    getline(cin, nombre);

    cout << "Ingrese el apellido del profesor: ";
    getline(cin, apellido);

    string dni = solicitarDniProfesor();

    cout << "Ingrese el correo electronico del profesor: ";
    getline(cin, correoElectronico);

    cout << "Ingrese el CUIT del profesor: ";
    getline(cin, CUIT);

    cout << "Ingrese cualquier observacion sobre el profesor: ";
    getline(cin, observaciones);

    cout << "Ingrese la direccion del profesor: ";
    getline(cin, direccion);

    cout << "Ingrese el telefono del profesor: ";
    getline(cin, telefono);

    idProfe = obtenerIdNuevo();

    // Fecha de alta automática
    auto now = time(nullptr);
    auto *local = localtime(&now);
    int diaAlta = local->tm_mday;
    int mesAlta = local->tm_mon + 1;
    int anioAlta = local->tm_year + 1900;

    return Profe(
        nombre, apellido, dni,
        correoElectronico, direccion, telefono,
        CUIT,
        diaAlta, mesAlta, anioAlta,
        observaciones,
        idProfe);
}

void GestionarProfesor::altaProfesor()
{
    Profe nuevoProfesor = cargarProfesor();

    if (archivoProfesores.guardar(nuevoProfesor))
        cout << "Profesor agregado exitosamente.\n";
    else
        cout << "Error al guardar el profesor.\n";
}

void GestionarProfesor::listarProfesores()
{
    cout << "=== GESTION DE PROFESORES ===\n\n";
    cout << "ID | Nombre       | Apellido     | DNI       | Estado\n";
    cout << "-------------------------------------------------------\n";

    int total = archivoProfesores.contarRegistros();
    for (int i = 0; i < total; ++i)
    {
        Profe p = archivoProfesores.leerRegistro(i);
        // Mostrar sólo profesores activos
        if (!p.getEstado())
            continue;

        // Sanitizar DNI: sólo dígitos, truncar a 9 caracteres
        string rawDni = p.getDni();
        rawDni.erase(remove_if(rawDni.begin(), rawDni.end(),
                               [](char c)
                               { return !isdigit((unsigned char)c); }),
                     rawDni.end());
        if (rawDni.length() > 9)
            rawDni = rawDni.substr(0, 9);

        cout << setw(2) << p.getId() << " | "
             << setw(12) << p.getNombre() << " | "
             << setw(12) << p.getApellido() << " | "
             << setw(9) << rawDni << " | "
             << "Activo"
             << "\n";
    }
    cout << "\n";
}

void GestionarProfesor::bajaProfesor()
{
    int id;
    cout << "Ingrese el ID del profesor a dar de baja: ";
    cin >> id;

    int pos = archivoProfesores.buscar(id);
    if (pos >= 0)
    {
        Profe profesor = archivoProfesores.leerRegistro(pos);
        profesor.setEstado(false);
        if (archivoProfesores.modificarRegistro(profesor, pos))
            cout << "Profesor dado de baja exitosamente.\n";
        else
            cout << "Error al dar de baja el profesor.\n";
    }
    else
        cout << "Profesor no encontrado.\n";
}

void GestionarProfesor::buscarProfesor()
{
    int id;
    cout << "Ingrese el ID del profesor a buscar: ";
    cin >> id;

    int pos = archivoProfesores.buscar(id);
    if (pos >= 0)
        archivoProfesores.leerRegistro(pos).mostrar();
    else
        cout << "Profesor no encontrado.\n";
}

int GestionarProfesor::obtenerIdNuevo()
{
    return Utilidades::obtenerIdNuevo<ProfesArchivo, Profe>(archivoProfesores);
}

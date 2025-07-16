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
            cout << "Error: El DNI debe contener 8 digitos. Intente de nuevo.\n";
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

    string nombre, apellido, correoElectronico, observaciones;
    string telefono, CUIT;
    int idProfe;
    // 1) nombre
    do {
        cout << "Ingrese el nombre del profesor: ";
        getline(cin, nombre);
        if (!Validaciones::esSoloLetras(nombre)) {
            cout << "Nombre invalido. Solo letras y espacios.\n";
        }
    } while(!Validaciones::esSoloLetras(nombre));

    // 2) Apellido
    do {
        cout << "Ingrese el apellido del profesor: ";
        getline(cin, apellido);
        if (!Validaciones::esSoloLetras(apellido)) {
            cout << "Apellido invalido. Solo letras y espacios.\n";
        }
    } while(!Validaciones::esSoloLetras(apellido));

    // 3) DNI
    string dni = solicitarDniProfesor();

    // 4) EMAIL
    cout << "Ingrese el correo electronico del profesor: ";
    getline(cin, correoElectronico);
    while(!Validaciones::esEmailValido(correoElectronico)) {
        cout << "Email invalido. Formato: usuario@dominio.ext\n";
        cout << "Ingrese nuevamente: ";
        getline(cin, correoElectronico);
    }

    // 5) CUIT
    do {
        cout << "Ingrese el CUIT del profesor (11 digitos): ";
        getline(cin, CUIT);
        if (!Validaciones::esCUITValido(CUIT)) {
            cout << "CUIT invalido. Debe tener 11 digitos numericos.\n";
        }
    } while (!Validaciones::esCUITValido(CUIT));

    // 6) Observaciones
    do {
        cout << "Ingrese cualquier observacion sobre el profesor: ";
        getline(cin, observaciones);
        if (!Validaciones::esObservacionValida(observaciones)) {
            cout << "Observacion invalida. Debe contener al menos alguna letra.\n";
        }
    } while (!Validaciones::esObservacionValida(observaciones));

    // 7) Telefono
    do {
        cout << "Ingrese el telefono del profesor: ";
        getline(cin, telefono);
        if (!Validaciones::esTelefonoValido(telefono)) {
            cout << "Telefono invalido. Debe ser 10 digitos numericos.\n";
        }
    } while(!Validaciones::esTelefonoValido(telefono));


    idProfe = obtenerIdNuevo();

    // Fecha de alta automática
    auto now = time(nullptr);
    auto *local = localtime(&now);
    int diaAlta = local->tm_mday;
    int mesAlta = local->tm_mon + 1;
    int anioAlta = local->tm_year + 1900;

    return Profe(
        nombre, apellido, dni,
        correoElectronico, telefono,
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
    int total = archivoProfesores.contarRegistros();
    if (total == 0) {
        cout
            << "\n+-----------------------------------------------+\n"
            << "|   No hay profesores registrados.              |\n"
            << "+-----------------------------------------------+\n\n";
        return;
    }

    bool huboActivos = false;
    for (int i = 0; i < total; ++i)
    {
        Profe p = archivoProfesores.leerRegistro(i);
        if (!p.getEstado())
            continue;

        if (!huboActivos) {
            cout << "=== GESTION DE PROFESORES ===\n\n";
            cout << "ID | Nombre       | Apellido     | DNI       | Estado\n";
            cout << "-------------------------------------------------------\n";
            huboActivos = true;
        }

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

    if (!huboActivos) {
        cout
            << "\n+-----------------------------------------------+\n"
            << "| AVISO: No se encontraron profesores activos. |\n"
            << "+-----------------------------------------------+\n\n";
    } else {
        cout << "\n";
    }
}

void GestionarProfesor::bajaProfesor()
{
    std::string dni;
    cout << "Ingrese el DNI del profesor a dar de baja: ";
    cin >> dni;

    int pos = archivoProfesores.buscarPosPorDni(dni);
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
    std::string dni;
    cout << "Ingrese el DNI del profesor a buscar: ";
    cin >> dni;

    int pos = archivoProfesores.buscarPosPorDni(dni);
    if (pos >= 0)
        archivoProfesores.leerRegistro(pos).mostrar();
    else
        cout << "Profesor no encontrado.\n";
}

void GestionarProfesor::modificarProfesor()
{
    std::string dni;
    cout << "Ingrese el DNI del profesor a modificar: ";
    cin >> dni;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    int pos = archivoProfesores.buscarPosPorDni(dni);
    if (pos < 0)
    {
        cout << "No se encontro un profesor con ese DNI." << endl;
        return;
    }

    Profe profe = archivoProfesores.leerRegistro(pos);
    cout << "Datos actuales del profesor:" << endl;
    profe.mostrar();

    int opcion;
    std::string nuevoValor;

    cout << "\nQue campo desea modificar?" << endl;
    cout << "1. Nombre" << endl;
    cout << "2. Apellido" << endl;
    cout << "3. Correo Electronico" << endl;
    cout << "4. Telefono" << endl;
    cout << "5. CUIT" << endl;
    cout << "0. Cancelar" << endl;
    cout << "Seleccione una opcion: ";
    cin >> opcion;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    switch (opcion)
    {
    case 1:
        cout << "Ingrese el nuevo nombre: ";
        getline(cin, nuevoValor);
        profe.setNombre(nuevoValor);
        break;
    case 2:
        cout << "Ingrese el nuevo apellido: ";
        getline(cin, nuevoValor);
        profe.setApellido(nuevoValor);
        break;
    case 3:
        cout << "Ingrese el nuevo correo electronico: ";
        getline(cin, nuevoValor);
        while (!Validaciones::esEmailValido(nuevoValor)) {
            cout << "Email invalido. Ingrese nuevamente: ";
            getline(cin, nuevoValor);
        }
        profe.setCorreoElectronico(nuevoValor);
        break;
    case 4:
        cout << "Ingrese el nuevo telefono: ";
        getline(cin, nuevoValor);
         while (!Validaciones::esTelefonoValido(nuevoValor)) {
            cout << "Telefono invalido. Ingrese nuevamente: ";
            getline(cin, nuevoValor);
        }
        profe.setTelefono(nuevoValor);
        break;
    case 5:
        cout << "Ingrese el nuevo CUIT: ";
        getline(cin, nuevoValor);
        profe.setCUIT(nuevoValor);
        break;
    case 0:
        cout << "Modificacion cancelada." << endl;
        return;
    default:
        cout << "Opcion no valida." << endl;
        return;
    }

    if (archivoProfesores.modificarRegistro(profe, pos))
    {
        cout << "Profesor modificado exitosamente." << endl;
    }
    else
    {
        cout << "Error al modificar el profesor." << endl;
    }
}

int GestionarProfesor::obtenerIdNuevo()
{
    return Utilidades::obtenerIdNuevo<ProfesArchivo, Profe>(archivoProfesores);
}

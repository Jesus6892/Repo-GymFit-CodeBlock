#include "GestionarPago.h"
#include "AlumnosArchivo.h"
#include "Utilidades.h"

#include <iostream>
using namespace std;

GestionarPago::GestionarPago()
    : archivoPagos(sizeof(Pago))
{
}

// --- Carga un Pago: si idAlumno<=0 pide DNI, si es >0 lo usa directamente ---
Pago GestionarPago::cargarPago(int idAlumno)
{
    // 1) Validar o pedir DNI
    if (idAlumno <= 0) {
        string dniAlumno;
        ArchivoAlumnos archivoAlumnos(sizeof(Alumno));
        do {
            cout << "Ingrese DNI del alumno (8 digitos) o 0 para cancelar: ";
            cin >> dniAlumno;
            if (dniAlumno == "0")
                return Pago();
            idAlumno = archivoAlumnos.buscarPorDni(dniAlumno);
            if (idAlumno < 0)
                cout << "ERROR: Alumno no encontrado.\n";
        } while (idAlumno < 0);
    }

    // 2) Seleccionar actividad
    int idActividad;
    do {
        cout << "Ingrese ID de la actividad (>=1) o 0 para cancelar: ";
        cin >> idActividad;
        if (idActividad == 0)
            return Pago();
    } while (idActividad < 1);

    // 3) Fecha y monto
    string fechaPago;
    cout << "Ingrese fecha de pago (YYYY-MM-DD): ";
    cin >> fechaPago;

    float monto;
    cout << "Ingrese monto del pago: ";
    cin >> monto;

    // 4) Generar nuevo ID y devolver Pago
    int nuevoIdPago = Utilidades::obtenerIdNuevo<PagoArchivo, Pago>(archivoPagos);
    return Pago(nuevoIdPago, idAlumno, idActividad, fechaPago, monto, true);
}


bool GestionarPago::guardarPago(const Pago& pago)
{
    return archivoPagos.guardar(pago);
}

void GestionarPago::altaPago()
{
    cout << "--- Registro de Pago ---\n";
    Pago pago = cargarPago();  // idAlumno por defecto = -1
    if (pago.getId() < 0) {
        cout << "Registro de pago cancelado.\n";
        return;
    }
    if (guardarPago(pago))
        cout << "Pago registrado con exito.\n";
    else
        cout << "ERROR: No se pudo guardar el pago.\n";
}

// --- Elimina (anula) un pago existente ---
void GestionarPago::bajaPago()
{
    int idPago;
    cout << "Ingrese ID de pago para anular (o 0 para cancelar): ";
    cin >> idPago;
    if (idPago == 0) {
        cout << "Operacion cancelada.\n";
        return;
    }
    int pos = archivoPagos.buscar(idPago);
    if (pos < 0) {
        cout << "ERROR: Pago no encontrado.\n";
        return;
    }
    Pago pago = archivoPagos.leerRegistro(pos);
    pago.anular();
    if (archivoPagos.modificarRegistro(pago, pos))
        cout << "Pago anulado con exito.\n";
    else
        cout << "ERROR: No se pudo anular el pago.\n";
}

// --- Lista todos los pagos activos ---
void GestionarPago::listarPagos()
{
    int total = archivoPagos.contarRegistros();
    bool seMostro = false;
    for (int i = 0; i < total; ++i) {
        Pago p = archivoPagos.leerRegistro(i);
        if (p.getEstado()) {
            if (!seMostro) {
                cout << "\n--- Listado de Pagos Activos ---\n";
                seMostro = true;
            }
            p.mostrar();
        }
    }
    if (!seMostro)
        cout << "No hay pagos activos registrados.\n";
}

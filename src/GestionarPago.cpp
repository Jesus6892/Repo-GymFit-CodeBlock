#include "GestionarPago.h"
#include "AlumnosArchivo.h"

using namespace std;

GestionarPago::GestionarPago()
    : archivoPagos(sizeof(Pago)) {}

Pago GestionarPago::cargarPago() {
    int idAlumno = -1;
    int idActividad = -1;
    string dniAlumno;
    string fechaPago;
    float monto;

    int idPago = Utilidades::obtenerIdNuevo<PagoArchivo, Pago>(archivoPagos);

    ArchivoAlumnos archivoAlumnos(sizeof(Alumno));
    do {
        cout << "Ingrese DNI del alumno (8 dígitos) o 0 para cancelar: ";
        cin >> dniAlumno;
        if (dniAlumno == "0") return Pago();
        idAlumno = archivoAlumnos.buscarPorDni(dniAlumno);
        if (idAlumno == -1) cout << "ERROR: Alumno no encontrado.\n";
    } while (idAlumno == -1);

    do {
        cout << "Ingrese ID de la actividad (>=1) o 0 para cancelar: ";
        cin >> idActividad;
        if (idActividad == 0) return Pago();
    } while (idActividad < 1);

    cout << "Ingrese fecha de pago (YYYY-MM-DD): ";
    cin >> fechaPago;
    cout << "Ingrese monto del pago: ";
    cin >> monto;

    return Pago(idPago, idAlumno, idActividad, fechaPago, monto, true);
}

void GestionarPago::altaPago() {
    cout << "--- Registro de Pago ---\n";
    Pago pago = cargarPago();
    if (pago.getId() < 0) {
        cout << "Registro de pago cancelado.\n";
        return;
    }
    if (archivoPagos.guardar(pago))
        cout << "Pago registrado con éxito.\n";
    else
        cout << "ERROR: No se pudo guardar el pago.\n";
}

void GestionarPago::bajaPago() {
    int idPago;
    cout << "Ingrese ID de pago para anular (o 0 para cancelar): ";
    cin >> idPago;
    if (idPago == 0) {
        cout << "Operación cancelada.\n";
        return;
    }
    int pos = archivoPagos.buscar(idPago);
    if (pos == -1) {
        cout << "ERROR: Pago no encontrado.\n";
        return;
    }
    Pago pago = archivoPagos.leerRegistro(pos);
    pago.anular();
    if (archivoPagos.modificarRegistro(pago, pos))
        cout << "Pago anulado con éxito.\n";
    else
        cout << "ERROR: No se pudo anular el pago.\n";
}

void GestionarPago::listarPagos() {
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
    if (!seMostro) cout << "No hay pagos activos registrados.\n";
}

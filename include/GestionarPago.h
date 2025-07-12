#pragma once

#include <iostream>
#include <limits>
#include <string>
#include "Pago.h"
#include "PagoArchivo.h"
#include "GestionarAlumno.h"
#include "GestionarActividad.h"
#include "Utilidades.h"

class GestionarPago {
private:
    PagoArchivo archivoPagos;

public:
    GestionarPago();
    Pago cargarPago(int idAlumno = -1);
    bool guardarPago(const Pago& pago);
    void altaPago();
    void bajaPago();
    void listarPagos();
};

#pragma once

#include <fstream>
#include "Pago.h"

class PagoArchivo {
private:
    std::string _nombreArchivo = "pagos.dat";
    int _tamRegistro;

public:
    PagoArchivo(int tamRegistro);

    bool guardar(const Pago& registro);
    Pago leerRegistro(int posicion);
    int contarRegistros();
    bool modificarRegistro(const Pago& registro, int posicion);
    int buscar(int idPago);
};

#include "PagoArchivo.h"
#include <iostream>

PagoArchivo::PagoArchivo(int tamRegistro)
    : _tamRegistro(tamRegistro) {}

bool PagoArchivo::guardar(const Pago& registro) {
    std::ofstream file(_nombreArchivo, std::ios::binary | std::ios::app);
    if (!file) {
        std::cout << "ERROR: No se pudo abrir el archivo de pagos para guardar.\n";
        return false;
    }
    file.write(reinterpret_cast<const char*>(&registro), _tamRegistro);
    file.close();
    return true;
}

Pago PagoArchivo::leerRegistro(int posicion) {
    Pago registro;
    std::ifstream file(_nombreArchivo, std::ios::binary);
    if (!file) {
        std::cout << "ERROR: No se pudo abrir el archivo de pagos para leer.\n";
        return registro;
    }
    file.seekg(posicion * _tamRegistro);
    file.read(reinterpret_cast<char*>(&registro), _tamRegistro);
    file.close();
    return registro;
}

int PagoArchivo::contarRegistros() {
    std::ifstream file(_nombreArchivo, std::ios::binary);
    if (!file) return 0;
    file.seekg(0, std::ios::end);
    int total = static_cast<int>(file.tellg() / _tamRegistro);
    file.close();
    return total;
}

bool PagoArchivo::modificarRegistro(const Pago& registro, int posicion) {
    std::fstream file(_nombreArchivo, std::ios::binary | std::ios::in | std::ios::out);
    if (!file) {
        std::cout << "ERROR: No se pudo abrir el archivo de pagos para modificar.\n";
        return false;
    }
    file.seekp(posicion * _tamRegistro);
    file.write(reinterpret_cast<const char*>(&registro), _tamRegistro);
    file.close();
    return true;
}

int PagoArchivo::buscar(int idPago) {
    int total = contarRegistros();
    for (int i = 0; i < total; ++i) {
        Pago p = leerRegistro(i);
        if (p.getId() == idPago) return i;
    }
    return -1;
}


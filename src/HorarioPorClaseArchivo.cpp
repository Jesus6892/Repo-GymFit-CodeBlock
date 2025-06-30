// HorarioArchivo.cpp
#define _CRT_SECURE_NO_WARNINGS
#include "HorarioPorClaseArchivo.h"

HorarioPorClaseArchivo::HorarioPorClaseArchivo(int tamanioRegistro)
  : ArchivoBinario("HorarioPorClase.dat", tamanioRegistro) {}

HorarioPorClaseArchivo::HorarioPorClaseArchivo()
  : HorarioPorClaseArchivo(sizeof(Horario)) {}

bool HorarioPorClaseArchivo::listarRegistro() const {
    int total = contarRegistros();
    for (int i = 0; i < total; ++i) {
        HorarioPorClase reg = leerRegistro(i);
        reg.mostrar();
    }
    return total > 0;
}

bool HorarioPorClaseArchivo::tieneHorariosAsignados(int idActividad) const {
    int total = contarRegistros();
    for (int i = 0; i < total; ++i) {
        HorarioPorClase reg = leerRegistro(i);
        if (reg.getIdClase() == idActividad)
            return true;
    }
    return false;
}

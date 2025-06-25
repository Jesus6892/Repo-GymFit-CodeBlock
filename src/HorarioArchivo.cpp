// HorarioArchivo.cpp
#define _CRT_SECURE_NO_WARNINGS
#include "HorarioArchivo.h"

HorarioArchivo::HorarioArchivo(int tamanioRegistro)
  : ArchivoBinario("Horario.dat", tamanioRegistro) {}

HorarioArchivo::HorarioArchivo()
  : HorarioArchivo(sizeof(Horario)) {}

bool HorarioArchivo::listarRegistro() const {
    int total = contarRegistros();
    for (int i = 0; i < total; ++i) {
        Horario reg = leerRegistro(i);
        reg.mostrarHorario();
    }
    return total > 0;
}

bool HorarioArchivo::tieneHorariosAsignados(int idActividad) const {
    int total = contarRegistros();
    for (int i = 0; i < total; ++i) {
        Horario reg = leerRegistro(i);
        if (reg.getIdActividad() == idActividad)
            return true;
    }
    return false;
}

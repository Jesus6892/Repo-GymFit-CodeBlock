#define _CRT_SECURE_NO_WARNINGS
#include "ProfesArchivo.h"

// Implementación de constructores
ProfesArchivo::ProfesArchivo(int tamRegistro)
    : ArchivoBinario("profes.dat", tamRegistro)
{
}

ProfesArchivo::ProfesArchivo()
    : ProfesArchivo(sizeof(Profe))
{
}

// Implementación de buscarIdPorDni usando API heredada
int ProfesArchivo::buscarIdPorDni(const std::string& dni) const {
    int total = contarRegistros();
    for (int pos = 0; pos < total; ++pos) {
        Profe reg = leerRegistro(pos);
        if (reg.getDni() == dni && reg.getEstado()) {
            return reg.getId();
        }
    }
    return -1;
}

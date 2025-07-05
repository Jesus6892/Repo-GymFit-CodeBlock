#define _CRT_SECURE_NO_WARNINGS
#include "ProfesArchivo.h"
#include "Validaciones.h"

// Implementacin de constructores
ProfesArchivo::ProfesArchivo(int tamRegistro)
    : ArchivoBinario("profes.dat", tamRegistro)
{
}

ProfesArchivo::ProfesArchivo()
    : ProfesArchivo(sizeof(Profe))
{
}

// Implementaci�n de buscarIdPorDni usando API heredada
int ProfesArchivo::buscarIdPorDni(const std::string& dni) const {
    int pos = buscarPosPorDni(dni);
    if (pos >= 0) {
        return leerRegistro(pos).getId();
    }
    return -1;
}

int ProfesArchivo::buscarPosPorDni(const std::string& dni) const {
    std::string targetDni = Validaciones::normalizarDNI(dni);
    int total = contarRegistros();
    for (int pos = 0; pos < total; ++pos) {
        Profe reg = leerRegistro(pos);
        std::string regDni = Validaciones::normalizarDNI(reg.getDni());
        if (regDni == targetDni && reg.getEstado()) {
            return pos;
        }
    }
    return -1;
}

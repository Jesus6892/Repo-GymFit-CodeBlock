#define _CRT_SECURE_NO_WARNINGS
#include "AlumnosArchivo.h"
#include "Validaciones.h"
#include <cctype>

ArchivoAlumnos::ArchivoAlumnos(int tamanioRegistro)
    : ArchivoBinario("alumnos.dat", tamanioRegistro)
{
}

ArchivoAlumnos::ArchivoAlumnos()
    : ArchivoBinario("alumnos.dat", sizeof(Alumno))
{
}

int ArchivoAlumnos::buscarPorDni(const std::string& dni) const {
    int pos = buscarPosPorDni(dni);
    if (pos >= 0) {
        return leerRegistro(pos).getId();
    }
    return -1;
}

int ArchivoAlumnos::buscarPosPorDni(const std::string& dni) const {
    std::string targetDni = Validaciones::normalizarDNI(dni);
    int total = contarRegistros();
    for (int pos = 0; pos < total; ++pos) {
        Alumno reg = leerRegistro(pos);
        if (!reg.getEstado()) continue;
        std::string regDni = Validaciones::normalizarDNI(reg.getDni());
        if (regDni == targetDni) {
            return pos; // Devuelve la posición
        }
    }
    return -1;
}

#define _CRT_SECURE_NO_WARNINGS
#include "AlumnosArchivo.h"
#include <cctype>

ArchivoAlumnos::ArchivoAlumnos(int tamanioRegistro)
    : ArchivoBinario("alumnos.dat", tamanioRegistro)
{
}

ArchivoAlumnos::ArchivoAlumnos()
    : ArchivoBinario("alumnos.dat", sizeof(Alumno))
{
}

std::string ArchivoAlumnos::sanitizeDni(const std::string& s) {
    std::string out;
    for (char c : s) {
        if (std::isdigit(static_cast<unsigned char>(c)))
            out += c;
    }
    return out;
}

int ArchivoAlumnos::buscarPorDni(const std::string& dni) const {
    std::string target = sanitizeDni(dni);
    int total = contarRegistros();
    for (int pos = 0; pos < total; ++pos) {
        Alumno reg = leerRegistro(pos);
        if (!reg.getEstado()) continue;
        if (sanitizeDni(reg.getDni()) == target) {
            return reg.getId();
        }
    }
    return -1;
}

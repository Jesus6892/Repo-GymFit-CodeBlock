#pragma once
#include <cstdio>
#include <cstring>
#include "IArchivable.h"
#include "Alumno.h"
#include "ArchivoBinario.h"

class ArchivoAlumnos : public ArchivoBinario<Alumno> {
public:
    ArchivoAlumnos();
    ArchivoAlumnos(int tamanioRegistro);

    // Búsqueda adicional por DNI
    int buscarPorDni(const std::string& dni) const;

private:
    static std::string sanitizeDni(const std::string& s);
};

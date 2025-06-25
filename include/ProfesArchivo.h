#pragma once
#include "ArchivoBinario.h"
#include "Profe.h"
#include <string>

class ProfesArchivo : public ArchivoBinario<Profe> {
public:
    // Constructor con tamaño de registro
    ProfesArchivo(int tamRegistro);
    // Constructor por defecto usando sizeof(Profe)
    ProfesArchivo();

    // Búsqueda de ID por DNI
    int buscarIdPorDni(const std::string& dni) const;

    ~ProfesArchivo() override = default;
};

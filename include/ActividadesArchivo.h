#pragma once
#include "ArchivoBinario.h"
#include "Actividad.h"

class ActividadesArchivo : public ArchivoBinario<Actividad> {
public:
    // Constructor que recibe tamaño de registro
    ActividadesArchivo(int tamanioRegistro);
    // Constructor por defecto usando sizeof(Actividad)
    ActividadesArchivo();

    ~ActividadesArchivo() = default;
};

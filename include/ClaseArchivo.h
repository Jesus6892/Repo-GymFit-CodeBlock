#ifndef CLASEARCHIVO_H
#define CLASEARCHIVO_H

#include "ArchivoBinario.h"
#include "Clase.h"

class ClaseArchivo : public ArchivoBinario<Clase> {
public:
    ClaseArchivo();
    ClaseArchivo(int tamanioRegistro);
    ~ClaseArchivo() override = default;
};

#endif // CLASEARCHIVO_H 
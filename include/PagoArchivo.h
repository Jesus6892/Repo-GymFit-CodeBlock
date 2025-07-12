#pragma once

#include "ArchivoBinario.h"
#include "Pago.h"

class PagoArchivo : public ArchivoBinario<Pago> {
public:
    // Constructor que recibe tama�o de registro
    PagoArchivo(int tamRegistro);
    // Constructor por defecto usando sizeof(Pago)
    PagoArchivo();

    ~PagoArchivo() override = default;
};

#pragma once

#include "ArchivoBinario.h"
#include "HorarioPorClase.h"

class HorarioPorClaseArchivo : public ArchivoBinario<HorarioPorClase> {
public:
    HorarioPorClaseArchivo(int tamanioRegistro);
    HorarioPorClaseArchivo();

    // override listar para usar mostrarHorario()
    bool listarRegistro() const override;

    // override tieneHorariosAsignados sin tocar _ruta ni _tamReg
    bool tieneHorariosAsignados(int idActividad) const;

    ~HorarioPorClaseArchivo() override = default;
};

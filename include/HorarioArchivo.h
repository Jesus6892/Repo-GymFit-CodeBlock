#pragma once

#include "ArchivoBinario.h"
#include "Horario.h"

class HorarioArchivo : public ArchivoBinario<Horario> {
public:
    HorarioArchivo(int tamanioRegistro);
    HorarioArchivo();

    // override listar para usar mostrarHorario()
    bool listarRegistro() const override;

    // override tieneHorariosAsignados sin tocar _ruta ni _tamReg
    bool tieneHorariosAsignados(int idActividad) const;

    ~HorarioArchivo() override = default;
};

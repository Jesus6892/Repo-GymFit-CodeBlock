#ifndef INSCRIPCIONARCHIVO_H
#define INSCRIPCIONARCHIVO_H

#include "ArchivoBinario.h"
#include "Inscripcion.h"

class InscripcionArchivo : public ArchivoBinario<Inscripcion> {
public:
    InscripcionArchivo();
    InscripcionArchivo(int tamanioRegistro);

    bool yaEstaInscripto(int idAlumno, int idClase) const;

    ~InscripcionArchivo() override = default;
};

#endif // INSCRIPCIONARCHIVO_H 
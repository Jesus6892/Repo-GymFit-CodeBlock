#include "InscripcionArchivo.h"

InscripcionArchivo::InscripcionArchivo(int tamanioRegistro)
    : ArchivoBinario("inscripciones.dat", tamanioRegistro)
{
}

InscripcionArchivo::InscripcionArchivo()
    : InscripcionArchivo(sizeof(Inscripcion))
{
}

bool InscripcionArchivo::yaEstaInscripto(int idAlumno, int idClase) const {
    int total = contarRegistros();
    for (int i = 0; i < total; ++i) {
        Inscripcion reg = leerRegistro(i);
        if (reg.getIdAlumno() == idAlumno && reg.getIdClase() == idClase && reg.getEstado()) {
            return true;
        }
    }
    return false;
} 
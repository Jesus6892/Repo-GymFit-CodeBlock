#include "InscripcionArchivo.h"

InscripcionArchivo::InscripcionArchivo(int tamanioRegistro)
    : ArchivoBinario("inscripciones.dat", tamanioRegistro)
{
}

InscripcionArchivo::InscripcionArchivo()
    : InscripcionArchivo(sizeof(Inscripcion))
{
} 
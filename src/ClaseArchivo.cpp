#include "ClaseArchivo.h"

ClaseArchivo::ClaseArchivo(int tamanioRegistro)
    : ArchivoBinario("clases.dat", tamanioRegistro)
{
}

ClaseArchivo::ClaseArchivo()
    : ClaseArchivo(sizeof(Clase))
{
} 
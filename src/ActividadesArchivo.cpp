#define _CRT_SECURE_NO_WARNINGS
#include "ActividadesArchivo.h"

ActividadesArchivo::ActividadesArchivo(int tamanioRegistro)
    : ArchivoBinario("actividades.dat", tamanioRegistro)
{
}

ActividadesArchivo::ActividadesArchivo()
    : ActividadesArchivo(sizeof(Actividad))
{
}

#define _CRT_SECURE_NO_WARNINGS
#include "PagoArchivo.h"

PagoArchivo::PagoArchivo(int tamRegistro)
    : ArchivoBinario("pagos.dat", tamRegistro)
{
}

PagoArchivo::PagoArchivo()
    : PagoArchivo(sizeof(Pago))
{
}

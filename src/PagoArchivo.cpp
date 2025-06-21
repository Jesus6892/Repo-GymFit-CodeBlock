#include "PagoArchivo.h"
#include <iostream>

PagoArchivo::PagoArchivo(int tamRegistro){
    _ruta = "pagos.dat";
	_tamReg = tamanioRegistro;
}

bool PagoArchivo::guardar(const Pago& reg) {
    FILE* pPagos;
	pPagos = fopen(_ruta.c_str(), "ab");
	bool result;

	if (pPagos == nullptr) {
		return false;
	}

	result = fwrite(&reg, _tamReg, 1, pPagos) == 1;
	fclose(pPagos);

	return result;
}

Pago PagoArchivo::leerRegistro(int posicion) {
    FILE* pPagos;
	Pago reg;
	pPagos = fopen(_ruta.c_str(), "rb");
	if (pPagos == nullptr) {
		return reg;
	}

	int cantBytes = ubi * _tamReg;
	fseek(pPagos, cantBytes, SEEK_SET);
	fread(&reg, sizeof(Pago), 1, pPagos);
	fclose(pPagos);
	return reg;
}

int PagoArchivo::contarRegistros() {
    FILE* pPagos;
	Pago reg;
	pPagos = fopen(_ruta.c_str(), "rb");
	if (pPagos == nullptr) {
		return 0;
	}

	fseek(pPagos, 0, SEEK_END);
	int total = ftell(pPagos);

	fclose(pPagos);
	return total / _tamReg;
}

bool PagoArchivo::modificarRegistro(const Pago& reg, int posicion) {
    FILE* pPagos;
	pPagos = fopen(_ruta.c_str(), "rb+");
	if (pPagos == nullptr) {
		return false;
	}

	fseek(pPagos, pos * _tamReg, SEEK_SET);
	bool escribio = fwrite(&reg, _tamReg, 1, pPagos);
	fclose(pPagos);
	return escribio;
}

int PagoArchivo::buscar(int idPago) {
    FILE* pPagos;
	Pago reg;
	int pos = 0;
	pPagos = fopen(_ruta.c_str(), "rb");
	if (pPagos == nullptr) {
		return -2;
	}
	while (fread(&reg, _tamReg, 1, pPagos) == 1) {
		if (reg.getId() == id && reg.getEstado()) {
			fclose(pPagos);
			return pos;
		}
		pos++;
	};

	fclose(pPagos);
	return -1;
}


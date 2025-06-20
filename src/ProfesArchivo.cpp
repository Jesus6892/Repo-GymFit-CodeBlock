#define _CRT_SECURE_NO_WARNINGS
#include "ProfesArchivo.h"

ProfesArchivo::ProfesArchivo(int tamanioRegistro) {
	_ruta = "profes.dat";
	_tamReg = tamanioRegistro;
}

bool ProfesArchivo::comprobarArchivo() const {
	FILE* pProfes;
	bool lecturaExitosa = true;


	pProfes = fopen(_ruta.c_str(), "rb");
	if (pProfes == nullptr) {
		lecturaExitosa = false;
		// devuelve -2 si no puede abrir el archivo
	}
	else {
		fclose(pProfes);
	}
	return lecturaExitosa;
}

int ProfesArchivo::buscarIdPorDni(const std::string& dni) const {
    FILE* p;
    p = fopen(_ruta.c_str(), "rb");
    if (p == nullptr) {
        return -1;
    }

    Profe reg;
    while (fread(&reg, sizeof(Profe), 1, p) == 1) {
       if (reg.getDni() == dni && reg.getEstado()) {
            fclose(p);
            return reg.getId(); 
        }
    }

    fclose(p);
    return -1;
}

bool ProfesArchivo::listarRegistro() const {
	Profe reg;
	FILE* pProfes;

	pProfes = fopen(_ruta.c_str(), "rb");
	if (pProfes == nullptr) {
		return false;
	}

	while (fread(&reg, _tamReg, 1, pProfes) == 1) {
		reg.mostrar();
	}

	fclose(pProfes);
	return true;
}

bool ProfesArchivo::guardar(const Profe& reg) const {
	FILE* pProfes;
	pProfes = fopen(_ruta.c_str(), "ab");
	bool result;

	if (pProfes == nullptr) {
		return false;
	}

	result = fwrite(&reg, _tamReg, 1, pProfes) == 1;
	fclose(pProfes);

	return result;
}

int ProfesArchivo::buscar(int id) const {
    FILE* pProfes;
    Profe reg;
    int pos = 0;
    pProfes = fopen(_ruta.c_str(), "rb");
    if (pProfes == nullptr) {
        return -2;
    }

    while (fread(&reg, _tamReg, 1, pProfes) == 1) {
        if (reg.getId() == id) {
            fclose(pProfes);
            return pos;
        }
        pos++;
    }

    fclose(pProfes);
    return -1;
}
int ProfesArchivo::contarRegistros() const {
	FILE* pProfes;
	Profe reg;
	pProfes = fopen(_ruta.c_str(), "rb");
	if (pProfes == nullptr) {
		return 0;
	}

	fseek(pProfes, 0, SEEK_END);
	int total = ftell(pProfes);

	fclose(pProfes);
	return total / _tamReg;
}

bool ProfesArchivo::modificarRegistro(const Profe& reg, int pos) const {
	FILE* pProfes;
	pProfes = fopen(_ruta.c_str(), "rb+");
	if (pProfes == nullptr) {
		return false;
	}

	fseek(pProfes, pos * _tamReg, SEEK_SET);
	bool escribio = fwrite(&reg, _tamReg, 1, pProfes);
	fclose(pProfes);
	return escribio;
}

Profe ProfesArchivo::leerRegistro(int ubi) const {
	FILE* pProfes;
	Profe reg;
	pProfes = fopen(_ruta.c_str(), "rb");
	if (pProfes == nullptr) {
		return reg;
	}

	int cantBytes = ubi * _tamReg;
	fseek(pProfes, cantBytes, SEEK_SET);
	fread(&reg, sizeof(Profe), 1, pProfes);
	fclose(pProfes);
	return reg;
}

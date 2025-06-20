#define _CRT_SECURE_NO_WARNINGS
#include "AlumnosArchivo.h"

ArchivoAlumnos::ArchivoAlumnos(int tamanioRegistro) {
	_ruta = "alumnos.dat";
	_tamReg = tamanioRegistro;
}

bool ArchivoAlumnos::comprobarArchivo() const {
	FILE* pAlumno;
	bool lecturaExitosa = true;


	pAlumno = fopen(_ruta.c_str(), "rb");
	if (pAlumno == nullptr) {
		lecturaExitosa = false;
		// devuelve -2 si no puede abrir el archivo
	}
	else {
		fclose(pAlumno);
	}
	return lecturaExitosa;
}
bool ArchivoAlumnos::listarRegistro() const {
	Alumno reg;
	FILE* pAlumno;

	pAlumno = fopen(_ruta.c_str(), "rb");
	if (pAlumno == nullptr) {
		return false;
	}

	while (fread(&reg, _tamReg, 1, pAlumno) == 1) {
		reg.mostrar();
	};

	fclose(pAlumno);
	return true;
}

bool ArchivoAlumnos::guardar(const Alumno& reg) const {
	FILE* pAlumno;
	pAlumno = fopen(_ruta.c_str(), "ab");
	bool result;

	if (pAlumno == nullptr) {
		return false;
	}

	result = fwrite(&reg, _tamReg, 1, pAlumno) == 1;
	fclose(pAlumno);

	return result;
}

int ArchivoAlumnos::buscar(int id) const {
	FILE* pAlumno;
	Alumno reg;
	int pos = 0;
	pAlumno = fopen(_ruta.c_str(), "rb");
	if (pAlumno == nullptr) {
		return -2;
	}
	while (fread(&reg, _tamReg, 1, pAlumno) == 1) {
		if (reg.getId() == id && reg.getEstado()) {
			fclose(pAlumno);
			return pos;
		}
		pos++;
	};

	fclose(pAlumno);
	return -1;
}
int ArchivoAlumnos::contarRegistros() const {
	FILE* pAlumno;
	Alumno reg;
	pAlumno = fopen(_ruta.c_str(), "rb");
	if (pAlumno == nullptr) {
		return 0;
	}

	fseek(pAlumno, 0, SEEK_END);
	int total = ftell(pAlumno);

	fclose(pAlumno);
	return total / _tamReg;
}
bool ArchivoAlumnos::modificarRegistro(const Alumno& reg, int pos) const {
	FILE* pAlumno;
	pAlumno = fopen(_ruta.c_str(), "rb+");
	if (pAlumno == nullptr) {
		return false;
	}

	fseek(pAlumno, pos * _tamReg, SEEK_SET);
	bool escribio = fwrite(&reg, _tamReg, 1, pAlumno);
	fclose(pAlumno);
	return escribio;
}

int ArchivoAlumnos::buscarPorDni(const std::string& dni) const {
	FILE* pAlumno;
	Alumno reg;
	pAlumno = fopen(_ruta.c_str(), "rb");
	if (pAlumno == nullptr) {
		// No se pudo abrir el archivo
		return -1;
	}

	while (fread(&reg, _tamReg, 1, pAlumno) == 1) {
		if (reg.getDni() == dni && reg.getEstado()) { // Compara DNI y estado
			fclose(pAlumno);
			return reg.getId(); // Devuelve el ID del alumno
		}
	}

	fclose(pAlumno);
	return -1; // No se encontró el alumno o no está activo
}

Alumno ArchivoAlumnos::leerRegistro(int ubi) const {
	FILE* pAlumno;
	Alumno reg;
	pAlumno = fopen(_ruta.c_str(), "rb");
	if (pAlumno == nullptr) {
		return reg;
	}

	int cantBytes = ubi * _tamReg;
	fseek(pAlumno, cantBytes, SEEK_SET);
	fread(&reg, sizeof(Alumno), 1, pAlumno);
	fclose(pAlumno);
	return reg;
}


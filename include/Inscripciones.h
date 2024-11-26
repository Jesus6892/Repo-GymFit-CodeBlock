#pragma once
#include <iostream>

class Inscripciones
{
private:
	int _idHorario;
	int _idAlumno;
	bool _estado;
public:
	Inscripciones();
	Inscripciones(int idHorario, int idAlumno);

	// getters
	int getIdAlumno();
	int getIdHorario();
    bool getEstado() const;

	// setters
	void setIdAlumno(int idAlumno);
	void setIdHorario(int idHorario);
    void setEstado(bool estado);


	// interfaz
	void mostrar();
};


















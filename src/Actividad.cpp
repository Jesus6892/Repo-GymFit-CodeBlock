#include <cstring>
#include <iostream>
#include "Actividad.h"

const std::string Actividad::defaultValue = "no hay datos";


Actividad::Actividad()
{
    _idActividad = -1;
    _idProfe = -1;
    _cantMax = -1;
    _costo = 0.0f;
    _estado = false;
    _nombreActividad[sizeof(_nombreActividad) - 1] = '\0';
    _descripcion[sizeof(_descripcion) - 1] = '\0';
}
Actividad::Actividad(int idActividad, std::string nombreActividad, int idProfe, int cantMax,float costo, std::string descripcion, bool estado) // Removed idLugarDeDesarrollo
{
    _idActividad = idActividad;
    _idProfe = idProfe;
    _cantMax = cantMax;
    _costo = costo;
    _estado = estado;
     strncpy(_nombreActividad, nombreActividad.c_str(), sizeof(_nombreActividad) - 1);
    _nombreActividad[sizeof(_nombreActividad) - 1] = '\0';
      strncpy(_descripcion, descripcion.c_str(), sizeof(_descripcion) - 1);
    _descripcion[sizeof(_descripcion) - 1] = '\0';
}

// getters
int Actividad::getId() const { return _idActividad; }
int Actividad::getIdProfe() const { return _idProfe; }
int Actividad::getCantMax() const { return _cantMax; }
bool Actividad::getEstado() const { return _estado; }
float Actividad::getCosto() const {return _costo; }
std::string Actividad::getNombreActividad() const { return _nombreActividad; }
std::string Actividad::getDescripcion() const { return _descripcion; }


// setters
void Actividad::setId(int idActividad) {
	if (idActividad < 0) throw std::invalid_argument("El ID de la Actividad debe ser un numero positivo");
	_idActividad = idActividad;
}
void Actividad::setCosto(float costo) {
	if (costo < 0) throw std::invalid_argument("El costo no puede ser negativo");
	_costo = costo;
}
void Actividad::setIdProfe(int idProfe) {
	if (idProfe < 0) throw std::invalid_argument("El ID del Profesor debe ser un numero positivo");
	_idProfe = idProfe;
}
void Actividad::setCantMax(int cantMax) {
    if (cantMax <= 0) throw std::invalid_argument("La Cantidad Maxima debe ser un nmero positivo");
    _cantMax = cantMax;
}
void Actividad::setEstado(bool estado) {
	_estado = estado;
}
void Actividad::setNombreActividad(std::string actividad) {
	if (actividad.size() >= sizeof(_nombreActividad)) {
        actividad = actividad.substr(0, sizeof(_nombreActividad) - 2);
    }
	strncpy(_nombreActividad, actividad.c_str(), sizeof(_nombreActividad) - 1);
	_nombreActividad[sizeof(_nombreActividad) - 1] = '\0';
}

void Actividad::setDescripcion(std::string descripcion) {
	if (descripcion.size() >= sizeof(_descripcion)) {
        descripcion = descripcion.substr(0, sizeof(_descripcion) - 2);
    }
	strncpy(_descripcion, descripcion.c_str(), sizeof(_descripcion) - 1);
	_descripcion[sizeof(_descripcion) - 1] = '\0';
}


// interfaz
void Actividad::mostrar() const {
	std::string claseActiva;
	claseActiva = getEstado() ? "Activa" : "Dada de baja";

	std::cout << "Clase: " << getId() << std::endl;
	std::cout << "Nombre: " << getNombreActividad() << std::endl;
    std::cout << "Profe: " << getIdProfe() << std::endl;
    std::cout << "Costo: $" << getCosto() << std::endl; // --> AÑADIDO
	std::cout << "Cant Maxima alumnos: " << getCantMax() << std::endl;
	std::cout << "Descripcion: " << getDescripcion() << std::endl;
	std::cout << "Estado: " << claseActiva << std::endl;
}

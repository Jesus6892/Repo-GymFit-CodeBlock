#include "Profe.h"
#include <iostream>
#include <stdexcept>

// Constructor por defecto
Profe::Profe()
    : Empleado(), _idProfe(-1), _estado(false) {}

// Constructor parametrizado
Profe::Profe(const std::string nombre, const std::string apellido, const std::string dni,
             int diaNasc, int mesNasc, int anioNasc,
             const std::string correoElectronico, const std::string direccion, const std::string telefono,
             const std::string CUIT,
             int diaAlta, int mesAlta, int anioAlta,
             const std::string& observaciones,
             int idProfe,
             bool estado)
    : Empleado(nombre, apellido, dni, diaNasc, mesNasc, anioNasc,
               correoElectronico, direccion, telefono,
               CUIT, diaAlta, mesAlta, anioAlta),
      _idProfe(idProfe),
      _estado(estado)
{
    if (idProfe < 0)
        throw std::invalid_argument("El ID del Profesor debe ser un número positivo");
}

// Setters
void Profe::setId(int idProfe) {
    if (idProfe < 0)
        throw std::invalid_argument("El ID del Profesor debe ser un número positivo");
    _idProfe = idProfe;
}

void Profe::setEstado(bool estado) {
    _estado = estado;
}

// Getters
int Profe::getId() const {
    return _idProfe;
}

bool Profe::getEstado() const {
    return _estado;
}

// Mostrar
void Profe::mostrar() const {
    Empleado::mostrar();
    std::cout << "ID Profe: " << getId() << std::endl;
    std::cout << "Estado: " << (getEstado() ? "Activo" : "Inactivo") << std::endl;
}

// Destructor
Profe::~Profe() {}

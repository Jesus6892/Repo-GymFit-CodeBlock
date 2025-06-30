#include "Profe.h"

// Constructor por defecto
Profe::Profe() : Empleado(), _idProfe(-1) {}

// Constructor parametrizado
Profe::Profe(const string nombre, const string apellido, const string dni,
          int diaNasc, int mesNasc, int anioNasc,
          const string correoElectronico, const string direccion, const string telefono,
          const string CUIT,
          int diaAlta, int mesAlta, int anioAlta,
          const std::string& observaciones,
          int idProfe)
    : Empleado(nombre, apellido, dni, diaNasc, mesNasc, anioNasc,
               correoElectronico, direccion, telefono,
               CUIT, diaAlta, mesAlta, anioAlta),
      _idProfe(idProfe)
{}

void Profe::setId(int idProfe) {
    if (idProfe < 0) throw std::invalid_argument("El ID del Profesor debe ser un número positivo");
    else _idProfe = idProfe;
}

// Getters
int Profe::getId() const {
    return _idProfe;
}

// Mostrar
void Profe::mostrar() const {
    Empleado::mostrar();
    std::cout << "ID Profe: " << getId() << std::endl;
}

// Destructor
Profe::~Profe() {}

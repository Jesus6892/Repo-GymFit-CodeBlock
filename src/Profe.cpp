#include "Profe.h"

// Constructor por defecto
Profe::Profe() : Empleado(), _idProfe(-1), _estado(false) {}

// Constructor parametrizado
Profe::Profe(const string nombre, const string apellido, const string dni,
          int diaNasc, int mesNasc, int anioNasc,
          const string correoElectronico, const string direccion, const string telefono,
          const string CUIT,
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
    if (salarioHora < 0)
        throw std::invalid_argument("El Salario por Hora debe ser un número positivo");
    if (idProfe < 0)
        throw std::invalid_argument("El ID del Profesor debe ser un número positivo");
}

// Setters
void Profe::setSalarioHora(float salarioHora) {
    if (salarioHora < 0)
        throw std::invalid_argument("El Salario por Hora debe ser un número positivo");
    _salarioHora = salarioHora;
}

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

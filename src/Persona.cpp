#include "Persona.h"

Persona::Persona() {
    strcpy(_nombre, "SIN NOMBRE");
    strcpy(_apellido, "SIN APELLIDO");
    strcpy(_dni, "00000000");
    strcpy(_correoElectronico, "SIN EMAIL");
    strcpy(_telefono, "0000000000");
    strcpy(_domicilio, "SIN DOMICILIO");
    _estado = true;
}

Persona::Persona(const string& nombre,
                 const string& apellido,
                 const string& dni,
                 const string& correo,
                 const string& domicilio,
                 const string& telefono)
{
    strcpy(_nombre, nombre.c_str());
    strcpy(_apellido, apellido.c_str());
    strcpy(_dni, dni.c_str());
    strcpy(_correoElectronico, correo.c_str());
    strcpy(_telefono, telefono.c_str());
    strcpy(_domicilio, domicilio.c_str());
    _estado = true;
}

// Getters
std::string Persona::getNombre() const { return _nombre; }
std::string Persona::getApellido() const { return _apellido; }
std::string Persona::getDni() const { return _dni; }
std::string Persona::getCorreoElectronico() const { return _correoElectronico; }
std::string Persona::getTelefono() const { return _telefono; }
std::string Persona::getDomicilio() const { return _domicilio; }
bool Persona::getEstado() const { return _estado; }

// Setters
void Persona::setNombre(const string nombre) {
    strcpy(_nombre, nombre.c_str());
}

void Persona::setApellido(const string apellido) {
    strcpy(_apellido, apellido.c_str());
}

void Persona::setDni(const string dni) {
    strcpy(_dni, dni.c_str());
}

void Persona::setCorreoElectronico(const string correo) {
    strcpy(_correoElectronico, correo.c_str());
}

void Persona::setTelefono(const string telefono) {
    strcpy(_telefono, telefono.c_str());
}

void Persona::setDomicilio(const string domicilio) {
    strcpy(_domicilio, domicilio.c_str());
}

void Persona::setEstado(bool estado) {
    _estado = estado;
}

// Interfaz
void Persona::mostrarPersona() const {
    cout << "Nombre: " << _nombre << endl;
    cout << "Apellido: " << _apellido << endl;
    cout << "DNI: " << _dni << endl;
    cout << "Correo electrónico: " << _correoElectronico << endl;
    cout << "Teléfono: " << _telefono << endl;
    cout << "Domicilio: " << _domicilio << endl;
    cout << "Estado: " << (_estado ? "Activo" : "Inactivo") << endl;
}

Persona::~Persona() {}

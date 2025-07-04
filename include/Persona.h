#pragma once
#include <cstring>
#include <string>
#include <iostream>
using namespace std;

class Persona
{
private:
    char _nombre[50];
    char _apellido[50];
    char _dni[8];
    char _correoElectronico[50];
    char _telefono[10];
    char _domicilio[50];
    bool _estado;

public:
    // Constructores
    Persona();
    Persona(const string& nombre,
        const string& apellido,
        const string& dni,
        const string& correoElectronico,
        const string& domicilio,
        const string& telefono);

    // Getters
    std::string getNombre() const;
    std::string getApellido() const;
    std::string getDni() const;
    std::string getCorreoElectronico() const;
    std::string getTelefono() const;
    std::string getDomicilio() const;
    bool getEstado() const;

    // Setters
    void setNombre(const string nombre);
    void setApellido(const string apellido);
    void setDni(const string dni);
    void setCorreoElectronico(const string correo);
    void setTelefono(const string telefono);
    void setDomicilio(const string domicilio);
    void setEstado(bool estado);

    // Interfaz
    void mostrarPersona() const;

    // Destructor
    ~Persona();
};

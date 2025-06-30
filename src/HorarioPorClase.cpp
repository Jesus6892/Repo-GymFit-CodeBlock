#include "HorarioPorClase.h"
#include <iostream>

// Constructor por defecto
HorarioPorClase::HorarioPorClase()
{
    _idHorarioPorClase = 0;
    _idClase = 0;
    _horario = Horario();
    _estado = false;
}

// Constructor con parámetros
HorarioPorClase::HorarioPorClase(int idHorarioPorClase, int idClase, std::string& diaSemana, int horaInicio, int horaFin, bool estado)
{
    _idHorarioPorClase = idHorarioPorClase;
    _idClase = idClase;
    _horario = Horario(diaSemana, horaInicio, horaFin); // Se crea el objeto Horario con esos datos
    _estado = estado;
}

// Setters
void HorarioPorClase::setId(int idHorarioPorClase) { _idHorarioPorClase = idHorarioPorClase; }
void HorarioPorClase::setHorario(Horario horario) { _horario = horario; }
void HorarioPorClase::setIdClase(int idClase) { _idClase = idClase; }
void HorarioPorClase::setEstado(bool estado) { _estado = estado; }

// Getters
int HorarioPorClase::getId() const { return _idHorarioPorClase; }
Horario HorarioPorClase::getHorario() const { return _horario; }
int HorarioPorClase::getIdClase() const { return _idClase; }
bool HorarioPorClase::getEstado() const { return _estado; }

// Mostrar (para depuración o visualización por consola)
void HorarioPorClase::mostrar()
{
    std::cout << "ID Clase: " << _idClase << std::endl;
    std::cout << "Horario: ";
    _horario.mostrar();  // Suponiendo que Horario tiene un método mostrar()
    std::cout << "Estado: " << (_estado ? "Activo" : "Inactivo") << std::endl;
}

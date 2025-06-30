#pragma once
#include <string>
#include <algorithm>
#include <cctype>
#include <stdexcept>
#include <iostream>

class Horario
{
private:
    enum DiaSemana { lunes, martes, miercoles, jueves, viernes, sabado, domingo };

    DiaSemana _diaSemana;
    int _horaInicio;
    int _horaFin;

    static DiaSemana convertirStringADia(const std::string& diaStr);
    std::string convertirDiaAString(const DiaSemana& dia) const;
    static void convertirAMinusculas(std::string& dia);
public:
    Horario();
    Horario(std::string& diaSemana, int horaInicio, int horaFin);

    // getters
    std::string getDiaSemana() const;
    int getHoraInicio() const;
    int getHoraFin() const;

    // setters
    void setDiaSemana(const std::string& diaSemana);
    void setHoraInicio(int horaInicio);
    void setHoraFin(int horaFin);

    // interfaz
    void mostrar() const;

    // destructor
    ~Horario();
};

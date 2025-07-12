#pragma once
#include <iostream>
#include <string>
#include <stdexcept>

class Fecha {
private:
    int _dia;
    int _mes;
    int _anio;

    bool esDiaValido(int dia, int mes, int anio) const;
    bool esMesValido(int mes) const;
    bool esAnioValido(int anio) const;
    bool esAnioBisiesto(int anio) const;

    int getCantidadDiasDelMes(int mes, int anio) const;
    void setFechaDefault();
    void validarIngreso(int dia, int mes, int anio);

public:
    Fecha();
    Fecha(int dia, int mes, int anio);

    // inspector
    std::string toString() const;

    // getters
    int getDia() const;
    int getMes() const;
    int getAnio() const;

    // modificadores
    void aumentarDia();
    void restarDia();

    // destructor trivial
    ~Fecha() = default;

    friend std::ostream& operator<<(std::ostream& os, const Fecha& fecha);
};

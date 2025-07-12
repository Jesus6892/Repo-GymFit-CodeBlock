#include "Fecha.h"

// constructores
Fecha::Fecha() {
    setFechaDefault();
}

Fecha::Fecha(int dia, int mes, int anio)
    : _dia(dia), _mes(mes), _anio(anio)
{
    validarIngreso(dia, mes, anio);
}

// getters
int Fecha::getDia() const       { return _dia; }
int Fecha::getMes() const       { return _mes; }
int Fecha::getAnio() const      { return _anio; }

int Fecha::getCantidadDiasDelMes(int mes, int anio) const {
    int diasDelMes[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
    if (esAnioBisiesto(anio)) diasDelMes[1] = 29;
    return diasDelMes[mes-1];
}

// validadores
void Fecha::setFechaDefault() {
    _dia = 1; _mes = 1; _anio = 2023;
}

void Fecha::validarIngreso(int dia, int mes, int anio) {
    if (!esDiaValido(dia,mes,anio) || !esMesValido(mes) || !esAnioValido(anio)) {
        setFechaDefault();
        throw std::invalid_argument("Fecha inválida, aplicando valor por defecto");
    }
}

bool Fecha::esAnioValido(int anio) const {
    return anio >= 1;
}

bool Fecha::esMesValido(int mes) const {
    return mes >= 1 && mes <= 12;
}

bool Fecha::esDiaValido(int dia, int mes, int anio) const {
    int maxDias = getCantidadDiasDelMes(mes, anio);
    return dia >= 1 && dia <= maxDias;
}

bool Fecha::esAnioBisiesto(int anio) const {
    return (anio%4==0 && anio%100!=0) || (anio%400==0);
}

// conversión a cadena
std::string Fecha::toString() const {
    auto pad = [](int v){
        std::string s = std::to_string(v);
        return std::string(2 - s.length(), '0') + s;
    };
    return pad(_dia) + "/" + pad(_mes) + "/" + std::to_string(_anio);
}

// modificadores de día
void Fecha::aumentarDia() {
    int maxDias = getCantidadDiasDelMes(_mes, _anio);
    if (_dia == maxDias && _mes == 12) {
        _dia = 1; _mes = 1;  _anio++;
    }
    else if (_dia == maxDias) {
        _dia = 1; _mes++;
    }
    else {
        _dia++;
    }
}

void Fecha::restarDia() {
    if (_dia > 1) {
        _dia--;
    }
    else {
        if (_mes == 1) {
            _mes = 12; _anio = (_anio>1? _anio-1 : 2023);
        }
        else {
            _mes--;
        }
        _dia = getCantidadDiasDelMes(_mes, _anio);
    }
}

// operador <<
std::ostream& operator<<(std::ostream& os, const Fecha& fecha) {
    os << fecha.toString();
    return os;
}

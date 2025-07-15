#pragma once
#include <cstring>
#include <string>
#include <iostream>
#include "Fecha.h"

class Pago {
private:
    int _id;
    int _idAlumno;
    int _idActividad;
    Fecha _fechaPago;  // formato "YYYY-MM-DD"
    float _monto;
    bool _estado;  // true = activo, false = anulado

public:
    Pago();
    Pago(int id, int idAlumno, int idActividad, int dia, int mes, int anio, float monto, bool estado = true);

    // Getters
    int getId() const;
    int getIdAlumno() const;
    int getIdActividad() const;
    std::string getFechaPago() const;
    float getMonto() const;
    bool getEstado() const;

    // Setters
    void setEstado(bool estado);

    // Métodos
    void mostrar() const;
    void anular();
};

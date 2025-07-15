#pragma once
#include <cstring>
#include <string>
#include <iostream>

class Pago {
private:
    int _id;
    int _idAlumno;
    int _idActividad;
    char _fechaPago[10];  // formato "YYYY-MM-DD"
    float _monto;
    bool _estado;  // true = activo, false = anulado

public:
    Pago();
    Pago(int id, int idAlumno, int idActividad, const std::string& fechaPago, float monto, bool estado = true);

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

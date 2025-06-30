#ifndef HORARIOSPORCLASE_H
#define HORARIOSPORCLASE_H
#include "Horario.h"


class HorarioPorClase
{
private:
    int _idHorarioPorClase;
    int _idClase;
    Horario _horario;
    bool _estado;

public:
    // Constructor por defecto
    HorarioPorClase();

    // Constructor con parámetros
    HorarioPorClase(int idHorarioPorClase, int idClase, std::string& diaSemana, int horaInicio, int horaFin, bool estado = true);

    // Setters
    void setId(int idHorarioPorClase);
    void setHorario(Horario horario);
    void setIdClase(int idClase);
    void setEstado(bool est);

    // Getters
    int getId() const;
    Horario getHorario() const;
    int getIdClase() const;
    bool getEstado() const;

    //Visual
    void mostrar();
};

#endif // HORARIOSPORCLASE_H

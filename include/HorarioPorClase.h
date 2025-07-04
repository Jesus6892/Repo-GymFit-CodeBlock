#ifndef HORARIOSPORCLASE_H
#define HORARIOSPORCLASE_H
#include "Horario.h"


class HorarioPorClase
{
private:
    int _id;
    int _idClase;
    Horario _horario;
    bool _estado;

public:
    // Constructor por defecto
    HorarioPorClase();

    // Constructor con parmetros
    HorarioPorClase(int id, int idClase, std::string& diaSemana, int horaInicio, int horaFin, bool estado = true);

    // Setters
    void setId(int id);
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

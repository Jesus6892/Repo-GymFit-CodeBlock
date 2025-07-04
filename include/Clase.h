#ifndef CLASE_H
#define CLASE_H

class Clase {
private:
    int _id;
    int _idHorario;
    int _idActividad;
    int _idProfe;
    bool _estado;

public:
    Clase();
    Clase(const int id,
          const int idHorario,
          const int idActividad,
          const int idProfe,
          const bool estado);

    void setEstado(const bool estado);
    bool getEstado() const;

    // Getters
    int getId() const;
    int getIdHorario() const;
    int getIdActividad() const;
    int getIdProfe() const;

    // Setters
    void setId(int id);
    void setIdHorario(int idHorario);
    void setIdActividad(int idActividad);
    void setIdProfe(int idProfe);
};

#endif // CLASE_H

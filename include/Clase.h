#ifndef CLASE_H
#define CLASE_H

class Clase {
private:
    int _id;
    int _idActividad;
    int _idProfe;
    bool _estado;

public:
    Clase();
    Clase(const int id,
          const int idActividad,
          const int idProfe,
          const bool estado);

    void setEstado(const bool estado);
    bool getEstado() const;

    int getId() const;
    int getIdActividad() const;
    int getIdProfe() const;

    void setId(int id);
    void setIdActividad(int idActividad);
    void setIdProfe(int idProfe);

    // Interfaz para compatibilidad
    void mostrar() const;
};

#endif // CLASE_H

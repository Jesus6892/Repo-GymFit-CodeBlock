#ifndef CLASE_H
#define CLASE_H

class Clase {
private:
    int _idClase;
    int _idHorario;
    int _idProfe;
    bool _estado;

public:
    Clase();
    Clase(const int idClase,
          const int idHorario,
          const int idProfe,
          const bool estado);

    void setEstado(const bool estado);
    bool getEstado() const;

    // Getters opcionales si los necesitás
    int getIdClase() const;
    int getIdHorario() const;
    int getIdProfe() const;

    // Setters opcionales si necesitás modificarlos
    void setIdClase(int idClase);
    void setIdHorario(int idHorario);
    void setIdProfe(int idProfe);
};

#endif // CLASE_H

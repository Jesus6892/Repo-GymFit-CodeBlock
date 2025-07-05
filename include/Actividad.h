#ifndef ACTIVIDAD_H
#define ACTIVIDAD_H
#include <cstring>
#include <string>

class Actividad
{
    private:
        static const std::string defaultValue;
        int _id;
        char _nombreActividad[150];
        char _descripcion[150];
        int _cantMax;
        float _costo;
        bool _estado;
    public:
        Actividad();
        Actividad(int id, std::string nombreActividad, int cantMax,float costo,std::string descripcion);

	// getters
	int getId() const;
	std::string getNombreActividad() const;
	int getCantMax() const;
    float getCosto() const;
	std::string getDescripcion() const;
	bool getEstado() const;

	void setId(int id);
	void setCantMax(int cantMax);
    void setCosto(float costo);
	void setEstado(bool estado);
	void setNombreActividad(std::string actividad);
	void setDescripcion(std::string descripcion);

	// interfaz
	void mostrar() const;

};

#endif // ACTIVIDAD_H

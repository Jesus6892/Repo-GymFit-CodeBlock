#ifndef ACTIVIDAD_H
#define ACTIVIDAD_H
#include <cstring>
#include <string>

class Actividad
{
    private:
        static const std::string defaultValue;
        int _idActividad;
        int _idProfe;
        int _cantMax;
        float _costo;
        bool _estado;
        char _descripcion[150];
        char _nombreActividad[150];
    public:
        Actividad();
        Actividad(int idActividad, std::string nombreActividad, int idProfe, int cantMax,float costo,std::string descripcion, bool estado);

	// getters
	int getId() const;
	int getIdProfe() const;
	std::string getNombreActividad() const;
	int getCantMax() const;
    float getCosto() const;
	std::string getDescripcion() const;
	bool getEstado() const;

	void setId(int idActividad);
	void setIdProfe(int idProfe);
	void setCantMax(int cantMax);
    void setCosto(float costo);
	void setEstado(bool estado);
	void setNombreActividad(std::string actividad);
	void setDescripcion(std::string descripcion);

	// interfaz
	void mostrar() const;

};

#endif // ACTIVIDAD_H

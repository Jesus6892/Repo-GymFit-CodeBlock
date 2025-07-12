#include "Horario.h"

//constructores
Horario::Horario() {
	_diaSemana = lunes;
	_horaInicio = 0;
	_horaFin = 0;
}
Horario::Horario(std::string& diaSemana, int horaInicio, int horaFin) {
	_diaSemana = convertirStringADia(diaSemana);
	_horaInicio = horaInicio;
	_horaFin = horaFin;
}

std::string Horario::getDiaSemana() const {
	std::string dia = convertirDiaAString(_diaSemana);
	return dia;
}
int Horario::getHoraInicio() const {
	return _horaInicio;
}
int Horario::getHoraFin() const {
	return _horaFin;
}

// setters
void Horario::setDiaSemana(const std::string& diaSemana) {
	if (diaSemana.empty()) throw std::invalid_argument("El dia de la Semana no puede estar vacio");
	_diaSemana = convertirStringADia(diaSemana);
}
void Horario::setHoraInicio(int horaInicio) {
	if (horaInicio < 0 || horaInicio  > 23) throw std::invalid_argument("La hora de inicio debe estar entre las 0 y 23 horas");
	_horaInicio = horaInicio;
}
void Horario::setHoraFin(int horaFin) {
	if (horaFin < 0 || horaFin > 23) throw std::invalid_argument("La hora de fin debe estar entre las 0 y 23 horas");
	_horaFin = horaFin;
}

// conversores
Horario::DiaSemana Horario::convertirStringADia(const std::string& diaStr) {
	std::string lowerStr = diaStr;

	convertirAMinusculas(lowerStr);

	// Compara y retorna el valor del enum
	if (lowerStr == "lunes") return lunes;
	else if (lowerStr == "martes") return martes;
	else if (lowerStr == "miercoles") return miercoles;
	else if (lowerStr == "jueves") return jueves;
	else if (lowerStr == "viernes") return viernes;
	else if (lowerStr == "sabado") return sabado;
	else if (lowerStr == "domingo") return domingo;
	else throw std::invalid_argument("Día inválido."); // excepción
}
std::string Horario::convertirDiaAString(const DiaSemana& dia) const {
	switch (dia) {
	case lunes:     return "lunes";
	case martes:    return "martes";
	case miercoles: return "miercoles";
	case jueves:    return "jueves";
	case viernes:   return "viernes";
	case sabado:    return "sabado";
	case domingo:   return "domingo";
	default:        return "Día desconocido";
	}
}
void Horario::convertirAMinusculas(std::string& dia) {
	for (int i = 0; i < dia.size(); i++) {
		dia[i] = std::tolower(dia[i]);
	}
}

// Visual
void Horario::mostrar() const {
	std::cout << "Dia : " << getDiaSemana() << std::endl;
	std::cout << "Hora Comienzo: " << getHoraInicio() << std::endl;
	std::cout << "Hora Fin: " << getHoraFin() << std::endl;
}

// destructor
Horario::~Horario() {}

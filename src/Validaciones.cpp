#include "Validaciones.h"
#include <cctype>
#include <regex>
#include <ctime>

Validaciones::Validaciones()
{
    //ctor
}
Validaciones::~Validaciones()
{
    //dtor
}


bool Validaciones::esSoloLetras(const std::string& s) {
    for (char c : s)
        if (!std::isalpha(c) && c!=' ')
            return false;
    return !s.empty();
}

std::string Validaciones::normalizarDNI(const std::string& dni) {
    std::string normalizado = dni;
    normalizado.erase(
        std::remove_if(normalizado.begin(), normalizado.end(),
            [](unsigned char c) { return !std::isdigit(c); }
        ),
        normalizado.end()
    );

    return normalizado;
}

bool Validaciones::esFormatoDniValido(const std::string& dni) {
    if (dni.length() >= 7 && dni.length() <= 8) {
        return true;
    }
    return false;
}



bool Validaciones::esSoloNumeros(const std::string& s) {
    for (char c : s)
        if (!std::isdigit(c))
            return false;
    return !s.empty();
}


bool Validaciones::tieneLongitud(const std::string& s, int len) {
    return static_cast<int>(s.size()) == len;
}

bool Validaciones::esDNIValido(const std::string& dni) {
    return esSoloNumeros(dni) && tieneLongitud(dni, 8);
}

bool Validaciones::esTelefonoValido(const std::string& tel) {
    return esSoloNumeros(tel) && tieneLongitud(tel, 10);
}

bool Validaciones::esEmailValido(const std::string& email) {
    static const std::regex pat(R"(^[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\.[A-Za-z]{2,}$)");
    return std::regex_match(email, pat);
}

bool Validaciones::esFechaNacimientoValida(int d, int m, int a) {
    if (a < 1900 || m<1 || m>12 || d<1 || d>31) return false;
    static const int mdays[] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
    bool bisiesto = (a%4==0 && a%100!=0) || (a%400==0);
    int maxd = mdays[m] + (m==2 && bisiesto);
    if (d>maxd) return false;
    std::time_t t = std::time(nullptr);
    std::tm* hoy = std::localtime(&t);
    if (a > hoy->tm_year+1900) return false;
    if (a == hoy->tm_year+1900 && m > hoy->tm_mon+1) return false;
    if (a == hoy->tm_year+1900 && m == hoy->tm_mon+1 && d > hoy->tm_mday) return false;
    return true;
}

bool Validaciones::esCostoValido(float costo) {
    return costo >= 0;
}

bool Validaciones::esObservacionValida(const std::string& obs)
{
    //Revisar me ayudo botsito
    if (obs.empty()) return false;

    bool tieneLetra = std::any_of(obs.begin(), obs.end(), [](char c) {
        return std::isalpha(static_cast<unsigned char>(c));
    });

    return tieneLetra;
}

bool Validaciones::esCUITValido(const std::string& cuit)
{
    if (cuit.length() != 11) return false;

    return std::all_of(cuit.begin(), cuit.end(), ::isdigit);
}



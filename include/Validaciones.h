#ifndef VALIDACIONES_H
#define VALIDACIONES_H
#pragma once
#include <string>


class Validaciones
{
    public:
        Validaciones();
        virtual ~Validaciones();

        //Validaciones básicas
        static bool esSoloLetras(const std::string& s);
        static bool esSoloNumeros(const std::string& s);
        static bool tieneLongitud(const std::string& s, int len);
        static bool esCostoValido(float costo);
        static int pedirEntero(const std::string& mensaje, int min = INT_MIN, int max = INT_MAX);


        //Validaciones especificas
        static bool esDNIValido(const std::string& dni);          // 8 dígitos numéricos
        static bool esTelefonoValido(const std::string& tel);     // 10 dígitos numéricos
        static bool esEmailValido(const std::string& email);      // formato básico xx@yy.zz
        static bool esFechaNacimientoValida(int d, int m, int a);
        static std::string normalizarDNI(const std::string& dni);
        static bool esFormatoDniValido(const std::string& dni);
        static bool esObservacionValida(const std::string& obs);
        static bool esCUITValido(const std::string& cuit);
        static bool estaEnBlanco(const std::string& s);
    protected:


    private:
};

#endif // VALIDACIONES_H

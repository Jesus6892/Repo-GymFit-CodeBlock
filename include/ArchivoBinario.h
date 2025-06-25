#pragma once
#include "IArchivable.h"
#include <string>
#include <cstdio>

template<typename T>
class ArchivoBinario : public IArchivable<T> {
public:
    ArchivoBinario(const std::string& ruta, int tamReg)
        : _ruta(ruta), _tamReg(tamReg) {}

    bool comprobarArchivo() const override {
        FILE* f = fopen(_ruta.c_str(), "rb");
        if (!f) return false;
        fclose(f);
        return true;
    }

    bool listarRegistro() const override {
        FILE* f = fopen(_ruta.c_str(), "rb");
        if (!f) return false;
        T reg;
        while (fread(&reg, _tamReg, 1, f) == 1) {
            reg.mostrar();
        }
        fclose(f);
        return true;
    }

    bool guardar(const T& reg) const override {
        FILE* f = fopen(_ruta.c_str(), "ab");
        if (!f) return false;
        bool ok = fwrite(&reg, _tamReg, 1, f) == 1;
        fclose(f);
        return ok;
    }

    int buscar(int id) const override {
        FILE* f = fopen(_ruta.c_str(), "rb");
        if (!f) return -2;
        T reg;
        int pos = 0;
        while (fread(&reg, _tamReg, 1, f) == 1) {
            if (reg.getId() == id && reg.getEstado()) {
                fclose(f);
                return pos;
            }
            pos++;
        }
        fclose(f);
        return -1;
    }

    T leerRegistro(int pos) const override {
        FILE* f = fopen(_ruta.c_str(), "rb");
        T reg{};
        if (!f) return reg;
        fseek(f, pos * _tamReg, SEEK_SET);
        fread(&reg, _tamReg, 1, f);
        fclose(f);
        return reg;
    }

    int contarRegistros() const override {
        FILE* f = fopen(_ruta.c_str(), "rb");
        if (!f) return 0;
        fseek(f, 0, SEEK_END);
        int bytes = ftell(f);
        fclose(f);
        return bytes / _tamReg;
    }

    bool modificarRegistro(const T& reg, int pos) const override {
        FILE* f = fopen(_ruta.c_str(), "rb+");
        if (!f) return false;
        fseek(f, pos * _tamReg, SEEK_SET);
        bool ok = fwrite(&reg, _tamReg, 1, f) == 1;
        fclose(f);
        return ok;
    }

private:
    std::string _ruta;
    int         _tamReg;
};

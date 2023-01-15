#include "Menu_Opciones.h"

MenuOpciones::MenuOpciones(std::string label, MenuOpcionesCallback callback) {
    this->label = label;
    this->callback = callback;
}


MenuOpciones::MenuOpciones(std::string label, MenuOpcionesCallback callback, bool wait_after_exec) {
    this->label = label;
    this->callback = callback;
    this->wait_after_exec = wait_after_exec;
}

MenuOpciones::MenuOpciones(std::string label, MenuOpcionesCallback callback, MenuOpcionesArgumentos argumento) {
    this->label = label;
    this->callback = callback;
    this->argumento = argumento;
}

MenuOpciones::MenuOpciones(std::string label, MenuOpcionesCallback callback, MenuOpcionesArgumentos argumento, bool wait_after_exec) {
    this->label = label;
    this->callback = callback;
    this->argumento = argumento;
    this->wait_after_exec = wait_after_exec;
}



fecha
#pragma once
#include <string>

class Fecha
{
public:
    Fecha();
    Fecha(int dia, int mes, int anio);

    int getDia() const;
    void setDia(int dia);
    int getMes() const;
    void setMes(int mes);
    int getAnio() const;
    void setAnio(int anio);

    static Fecha actual();
    static Fecha leer(std::string mensaje);
    static bool valida(int dia, int mes, int anio);
    static bool valida(Fecha fecha);

private:
    int dia = 0;
    int mes = 0;
    int anio = 0;
};

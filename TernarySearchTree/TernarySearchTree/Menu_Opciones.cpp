#include "Menu_Opciones.h"

MenuOpciones::MenuOpciones(std::string etiqueta, MenuOpcionesCallback regresar) {
    this->etiqueta = etiqueta;
    this->regresar = regresar;
}


MenuOpciones::MenuOpciones(std::string etiqueta, MenuOpcionesCallback regresar, bool esperar_despues_ejecucion) {
    this->etiqueta = etiqueta;
    this->regresar = regresar;
    this->esperar_despues_ejecucion = esperar_despues_ejecucion;
}

MenuOpciones::MenuOpciones(std::string etiqueta, MenuOpcionesCallback regresar, MenuOpcionesArgumentos argumentos) {
    this->etiqueta = etiqueta;
    this->regresar = regresar;
    this->argumentos = argumentos;
}

MenuOpciones::MenuOpciones(std::string etiqueta, MenuOpcionesCallback regresar, MenuOpcionesArgumentos argumentos, bool esperar_despues_ejecucion) {
    this->etiqueta = etiqueta;
    this->regresar = regresar;
    this->argumentos = argumentos;
    this->esperar_despues_ejecucion = esperar_despues_ejecucion;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

MenuOpciones::MenuOpciones(std::string etiqueta, MenuOpcionesCallback2 regresar) {
    this->etiqueta = etiqueta;
    this->regresar2 = regresar;
}

MenuOpciones::MenuOpciones(std::string etiqueta, MenuOpcionesCallback2 regresar, bool esperar_despues_ejecucion) {
    this->etiqueta = etiqueta;
    this->regresar2 = regresar;
    this->esperar_despues_ejecucion = esperar_despues_ejecucion;
}

MenuOpciones::MenuOpciones(std::string etiqueta, MenuOpcionesCallback2 regresar, MenuOpcionesArgumentos argumentos) {
    this->etiqueta = etiqueta;
    this->regresar2 = regresar;
    this->argumentos = argumentos;
}

MenuOpciones::MenuOpciones(std::string etiqueta, MenuOpcionesCallback2 regresar, MenuOpcionesArgumentos argumentos, bool esperar_despues_ejecucion) {
    this->etiqueta = etiqueta;
    this->regresar2 = regresar;
    this->argumentos = argumentos;
	this->esperar_despues_ejecucion = esperar_despues_ejecucion;
}

bool MenuOpciones::visible() {
    return regreso_visible_();
}

void MenuOpciones::visible(bool visible) {
    regreso_visible_ = [=]() { return visible; };
}

void MenuOpciones::visible(std::function<bool()> regresar) {
    regreso_visible_ = regresar;
}

std::string MenuOpciones::get_etiqueta() {
    return etiqueta;
}

void MenuOpciones::ejecutar() {
    if (regresar.has_value()) {
        regresar.value()(argumentos);
    }
    else {
        regresar2.value()();
    }
}

bool MenuOpciones::should_wait() {
    return esperar_despues_ejecucion;
}

MenuOpcionesArgumentos& MenuOpciones::get_args() {
    return argumentos;
}



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

MenuOpciones::MenuOpciones(std::string etiqueta, MenuOpcionesCallback regresar, MenuOpcionesArgumentos argumento) {
    this->etiqueta = etiqueta;
    this->regresar = regresar;
    this->argumento = argumento;
}

MenuOpciones::MenuOpciones(std::string etiqueta, MenuOpcionesCallback regresar, MenuOpcionesArgumentos argumento, bool esperar_despues_ejecucion) {
    this->etiqueta = etiqueta;
    this->regresar = regresar;
    this->argumento = argumento;
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

MenuOpciones::MenuOpciones(std::string etiqueta, MenuOpcionesCallback2 regresar, MenuOpcionesArgumentos argumento) {
    this->etiqueta = etiqueta;
    this->regresar2 = regresar;
    this->argumento = argumento;
}

MenuOpciones::MenuOpciones(std::string etiqueta, MenuOpcionesCallback2 regresar, MenuOpcionesArgumentos argumento, bool esperar_despues_ejecucion) {
    this->etiqueta = etiqueta;
    this->regresar2 = regresar;
    this->argumento = argumento;
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
        regresar.value()(argumento);
    }
    else {
        regresar2.value()();
    }
}

bool MenuOpciones::should_wait() {
    return esperar_despues_ejecucion;
}

MenuOpcionesArgumentos& MenuOpciones::get_args() {
    return argumento;
}



#include "Menu_Opciones.h"

MenuOpciones::MenuOpciones(std::string label, MenuOpcionesCallback regresar) {
    this->label = label;
    this->regresar = regresar;
}


MenuOpciones::MenuOpciones(std::string label, MenuOpcionesCallback regresar, bool esperar_despues_ejecucion) {
    this->label = label;
    this->regresar = regresar;
    this->esperar_despues_ejecucion = esperar_despues_ejecucion;
}

MenuOpciones::MenuOpciones(std::string label, MenuOpcionesCallback regresar, MenuOpcionesArgumentos argumento) {
    this->label = label;
    this->regresar = regresar;
    this->argumento = argumento;
}

MenuOpciones::MenuOpciones(std::string label, MenuOpcionesCallback regresar, MenuOpcionesArgumentos argumento, bool esperar_despues_ejecucion) {
    this->label = label;
    this->regresar = regresar;
    this->argumento = argumento;
    this->esperar_despues_ejecucion = esperar_despues_ejecucion;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

MenuOpciones::MenuOpciones(std::string label, MenuOpcionesCallback2 regresar) {
    this->label = label;
    this->regresar2 = regresar;
}

MenuOpciones::MenuOpciones(std::string label, MenuOpcionesCallback2 regresar, bool esperar_despues_ejecucion) {
    this->label = label;
    this->regresar2 = regresar;
    this->esperar_despues_ejecucion = esperar_despues_ejecucion;
}

MenuOpciones::MenuOpciones(std::string label, MenuOpcionesCallback2 regresar, MenuOpcionesArgumentos argumento) {
    this->label = label;
    this->regresar2 = regresar;
    this->argumento = argumento;
}

MenuOpciones::MenuOpciones(std::string label, MenuOpcionesCallback2 regresar, MenuOpcionesArgumentos argumento, bool esperar_despues_ejecucion) {
    this->label = label;
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

std::string MenuOpciones::get_label() {
    return label;
}

void MenuOpciones::execute() {
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



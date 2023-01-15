#include "Menu_opciones.h"

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
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




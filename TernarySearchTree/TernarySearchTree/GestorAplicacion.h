#pragma once
#include "ArbolTernarioBusqueda.h"

class GestorAplicacion {
public:
    GestorAplicacion() {
        arbol = new ArbolTernarioBusqueda();
    }
    
    static int iniciar();
    void correr();
    void menu_opcion_arbol();
    
private:
    ArbolTernarioBusqueda* arbol;
};

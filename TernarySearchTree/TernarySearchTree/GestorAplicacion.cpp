/*
/*                                  Universidad de las Fuerzas Armadas "ESPE"
* ArbolBinario
* ALumno: Leon William, Obando Leonardo, Quintana Wendy
* 20 / 01 / 2023
* 20 / 01 / 2023
* 7999 Estructura de datos
*/

#include "GestorAplicacion.h"
#include "menu.h"
#include "Validaciones.h"
#include <Windows.h>
#include <filesystem>
#pragma execution_character_set( "utf-8" )

int GestorAplicacion::iniciar() {
    SetConsoleOutputCP(65001);
    GestorAplicacion app;
    app.correr();
    
    return 0;
}

void GestorAplicacion::correr() {
    Menu menu("Menu principal");
    menu.add_option(MenuOption("Arbol Ternario", [&]() {
        menu_opcion_arbol();
    }, false));    
    
    menu.add_option(menu.opcion_salir("Salir"));
    menu.display();
}

void GestorAplicacion::menu_opcion_arbol()
{
    Menu menu("Arbol Ternario");

    menu.add_option(MenuOption("insertar", [&]() {
        std::string valor = Validaciones::leer_con_formato("ingrese un valor: ", "[a-z]+");
        arbol->insert(valor);

        std::cout << std::endl;
        arbol->print();
    }));

    menu.add_option(MenuOption("buscar", [&]() {
        std::string valor = Validaciones::leer_con_formato("ingrese un valor: ", "[a-z]+");
        NodoTernario* encontrado = arbol->find(valor);
        
        if (encontrado != nullptr) {
            std::cout << "el valor '" << valor << "' fue encontrado" << std::endl << std::endl;
            arbol->print();
        } else {
            std::cout << "el valor '" << valor << "' no fue encontrado" << std::endl << std::endl;
        }
    }));

    menu.add_option(MenuOption("eliminar", [&]() {
        std::string valor = Validaciones::leer_con_formato("ingrese un valor: ", "[a-z]+");
        NodoTernario* encontrado = arbol->find(valor);

        if (encontrado != nullptr) {
            arbol->remove(valor);
            std::cout << "El valor '" << valor << " ' Eliminado Correctamente " << std::endl << std::endl;
            arbol->print();
        } else {
            std::cout << "el valor '" << valor << "' no fue encontrado" << std::endl << std::endl;
        }
    }));

    menu.add_option(MenuOption("imprimir inorden", [&]() {
        arbol->traverse([](char v) {
            std::cout << v << " -> ";
        });
    }));

    menu.add_option(MenuOption("imprimir", [&]() {
        arbol->print();
    }));

    menu.add_option(menu.opcion_salir("Salir"));
    menu.display();
}

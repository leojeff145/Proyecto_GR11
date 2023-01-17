#pragma once
#include "Menu_Opciones.h"
#include <iostream>
#include <vector>
#include <windows.h>

#define LLAVE_ARRIBA 72
#define LLAVE_ABAJO 80
#define LLAVE_IZQUIERDA 77
#define LLAVE_DERECHA 75
#define LLAVE_ENTER 13
#define LLAVE_ESCAPE 27


class Consola
{
public:
    Consola(Consola const&) = delete;
    Consola& operator=(Consola const&) = delete;
    static Consola& obtener();

    void print(std::string text, COORD coord);
    void limpiar_linea(short y);
    void limpiar_pantalla();
    void limpiar_area(SMALL_RECT area);
    void set_cursor_posicion(COORD coord);
    COORD get_tamano_consola();

private:
    Consola();
};

class Menu {
public:
    Menu();
    Menu(std::string titulo);

    /**
     * @brief agrega una opcion al menu
     * @param option
     */
    void add_opciones(MenuOpciones opciones);

    /**
     * @brief remueve una opcion del menu
     * @param index indice de la opcion a eliminar
     */
    void eliminar_opciones(int indice);

    /**
     * @brief muestra el menu
     */
    void mostrar();

    /**
     * @brief detiene el menu
     */
    void parar();

    /**
     * @brief verifica si el menu esta detenido.
     * @return true si esta corriendo, caso contrario devuelve true
    */
    bool corriendo();

    MenuOpciones opciones_salir(std::string etiqueta = "Salir", bool pausar = false) {
        return MenuOpciones(etiqueta, [&]() {
            parar();
            }, pausar);
    }

private:
    std::string titulo;
    std::vector<MenuOpciones> opciones;
    HANDLE etfdr;
    bool correr = false;
};

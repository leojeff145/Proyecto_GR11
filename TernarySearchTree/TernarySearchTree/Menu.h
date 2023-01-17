#pragma once
#include "Menu_Opciones.h"
#include <iostream>
#include <vector>
#include <windows.h>

#define LLAVE_UP 72
#define LLAVE_DOWN 80
#define LLAVE_LEFT 77
#define LLAVE_RIGHT 75
#define LLAVE_ENTER 13
#define LLAVE_ESCAPE 27


class Consola
{
public:
    Consola(Consola const&) = delete;
    Consola& operator=(Consola const&) = delete;
    static Consola& get();

    void print(std::string text, COORD coord);
    void clear_line(short y);
    void clear_screen();
    void clear_area(SMALL_RECT area);
    void set_cursor_position(COORD coord);
    COORD get_consola_size();

private:
    Consola();
};

class Menu {
public:
    Menu();
    Menu(std::string title);

    /**
     * @brief agrega una opcion al menu
     * @param option
     */
    void add_opciones(MenuOpciones opciones);

    /**
     * @brief remueve una opcion del menu
     * @param index indice de la opcion a eliminar
     */
    void eliminar_opciones(int index);

    /**
     * @brief muestra el menu
     */
    void display();

    /**
     * @brief detiene el menu
     */
    void stop();

    /**
     * @brief verifica si el menu esta detenido.
     * @return true si esta corriendo, caso contrario devuelve true
    */
    bool is_running();

    MenuOpciones opciones_salir(std::string label = "Salir", bool pausar = false) {
        return MenuOpciones(label, [&]() {
            stop();
            }, pausar);
    }

private:
    std::string title;
    std::vector<MenuOpciones> opciones;
    HANDLE conhandler;
    bool running = false;
};

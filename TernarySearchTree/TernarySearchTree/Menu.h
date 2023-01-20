#pragma once
#include "MenuOpciones.h"
#include <iostream>
#include <vector>
#include <windows.h>

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 77
#define KEY_RIGHT 75
#define KEY_ENTER 13
#define KEY_ESCAPE 27


class Console
{
public:
    Console(Console const&) = delete;
    Console& operator=(Console const&) = delete;
    static Console& get();

    void print(std::string text, COORD coord);
    void clear_line(short y);
    void clear_screen();
    void clear_area(SMALL_RECT area);
    void set_cursor_position(COORD coord);
    COORD get_console_size();

private:
    Console();
};

class Menu {
public:
    Menu();
    Menu(std::string title);

    /**
     * @brief agrega una opcion al menu
     * @param option 
     */
    void add_option(MenuOption option);

    /**
     * @brief remueve una opcion del menu
     * @param index indice de la opcion a eliminar
     */
    void remove_option(int index);

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

    MenuOption opcion_salir(std::string label = "Salir", bool pausar = false) {
        return MenuOption(label, [&]() {
            stop();
        }, pausar);
    }

private:
    std::string title;
    std::vector<MenuOption> options;
    HANDLE conhandler;
    bool running = false;
};

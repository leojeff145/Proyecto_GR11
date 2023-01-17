#include "Menu.h"
#include <conio.h>
#include <vector>

Menu::Menu() {
    etfdr = GetStdHandle(STD_OUTPUT_HANDLE);
}

Menu::Menu(std::string ti) {
    this->titulo = ti;
    etfdr = GetStdHandle(STD_OUTPUT_HANDLE);
}

void Menu::add_opciones(MenuOpciones opcion) {
    opciones.push_back(opcion);
}

void Menu::eliminar_opciones(int indice) {
    if (indice < 0 || indice > opciones.size()) {
        return;
    }

    std::vector<MenuOpciones>::iterator it = opciones.begin();
    std::advance(it, indice);
    opciones.erase(it);
}

void Menu::mostrar() {
    int seleccionar = 1;

    if (opciones.empty()) {
        return;
    }

    CONSOLE_SCREEN_BUFFER_INFO csbi;
    WORD csbi_defaults;

    GetConsoleScreenBufferInfo(etfdr, &csbi);
    csbi_defaults = csbi.wAttributes;

    correr = true;

    Consola& consola = Consola::obtener();

    consola.limpiar_area({ 0, 2, consola.get_tamano_consola().X, consola.get_tamano_consola().Y });
    consola.set_cursor_posicion({ 0, 2 });
    
    while (correr) {
        int posicion = 1;

        consola.limpiar_area({ 0, 2, consola.get_tamano_consola().X, consola.get_tamano_consola().Y });
        consola.set_cursor_posicion({ 0, 2 });

        std::vector<MenuOpciones> visible_opciones;

        std::cout << std::endl << titulo << std::endl << std::endl;

        for (MenuOpciones opcion : opciones) {
            if (opcion.visible()) {
                visible_opciones.push_back(opcion);
            }
        }

        for (MenuOpciones opcion : visible_opciones) {
            if (opcion.get_args().has("__index")) {
                opcion.get_args().set("__index", posicion - 1);
            }
            else {
                opcion.get_args().add("__index", posicion - 1);
            }

            if (posicion++ == seleccionar) {
                SetConsoleTextAttribute(etfdr, 23);
            }

            std::cout << " " << opcion.get_etiqueta() << " " << std::endl;
            SetConsoleTextAttribute(etfdr, csbi_defaults);
        }

        int llave;

        do {
#ifdef _MSC_VER
            llave = _getch();

            if (llave == 0) {
                llave = _getch();
            }
#else
            llave = getch();

            if (llave == 0) {
                llave = getch();
            }
#endif
        } while (llave != LLAVE_ARRIBA && llave != LLAVE_ABAJO && llave != LLAVE_ENTER);

        switch (llave) {
        case LLAVE_ARRIBA: {
            seleccionar--;

            if (seleccionar < 1) {
                seleccionar = visible_opciones.size();
            }
        }
                   break;
        case LLAVE_ABAJO: {
            seleccionar++;

            if (seleccionar > visible_opciones.size()) {
                seleccionar = 1;
            }
        }
                     break;
        case LLAVE_ENTER: {
            MenuOpciones opciones = visible_opciones.at(seleccionar - 1);
            std::cout << std::endl << std::endl;
            opciones.ejecutar();

            if (opciones.should_wait()) {
                std::cout << std::endl << std::endl;
                system("pause");
            }

            system("cls");
        }
        }
    }
}

void Menu::parar() {
    correr = false;
}

bool Menu::corriendo() {
    return correr;
}

Consola::Consola() {}

Consola& Consola::obtener() {
    static Consola instancia;
    return instancia;
}

void Consola::print(std::string texto, COORD coord) {
    CHAR_INFO* buffer = (CHAR_INFO*)calloc(texto.size(), sizeof(CHAR_INFO));

    if (buffer == 0) {
        return;
    }

    COORD consola_size = get_tamano_consola();
    SMALL_RECT posicion = {
        coord.X, // left
        coord.Y, // top
        coord.X + texto.length(), // right
        coord.Y + 1 // bottom
    };
    HANDLE manejo_consola = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD tamanio_buffer = { texto.size(), 1 };

    int i = 0;

    for (const char c : texto) {
        buffer[i].Char.AsciiChar = c;
        buffer[i].Attributes = 15;
        i++;
    }

    WriteConsoleOutputA(manejo_consola, buffer, tamanio_buffer, { 0, 0 }, &posicion);
    free(buffer);
}

void Consola::limpiar_linea(short y) {
    COORD tamanio_consola = get_tamano_consola();

    if (y < 0 || y > tamanio_consola.Y) return;

    std::string vacio(tamanio_consola.X, ' ');
    print(vacio, { 0, y });
}

void Consola::limpiar_pantalla() {
    COORD tamanio_consola = get_tamano_consola();
    limpiar_area({ 0, 0, tamanio_consola.X, tamanio_consola.Y });
}

void Consola::set_cursor_posicion(COORD coord) {
    HANDLE manejo_consola = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(manejo_consola, coord);
}

void Consola::limpiar_area(SMALL_RECT area) {
    int x = area.Left;
    int y = area.Top;
    int ancho = area.Right - area.Left;
    int altura = area.Bottom - area.Top;

    std::string espacios = std::string(ancho * altura, ' ');
    CHAR_INFO* buffer = (CHAR_INFO*)calloc(espacios.size(), sizeof(CHAR_INFO));

    if (buffer == 0) {
        return;
    }

    SMALL_RECT posicion = {
        x, // left
        y, // top
        x + ancho, // right
        y + altura // bottom
    };
    COORD tamanio_buffer = { ancho, altura };
    HANDLE manejo_consola = GetStdHandle(STD_OUTPUT_HANDLE);
    int i = 0;

    for (const char c : espacios) {
        buffer[i].Char.AsciiChar = c;
        buffer[i].Attributes = 15;
        i++;
    }

    WriteConsoleOutputA(manejo_consola, buffer, tamanio_buffer, { 0, 0 }, &posicion);
    free(buffer);
}

COORD Consola::get_tamano_consola() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int columnas, filas;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    columnas = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    filas = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

    COORD tamanio = { columnas, filas };

    return tamanio;
}
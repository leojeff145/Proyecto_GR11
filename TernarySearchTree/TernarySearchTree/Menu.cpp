#include "Menu.h"
#include <conio.h>
#include <vector>

Menu::Menu() {
    conhandler = GetStdHandle(STD_OUTPUT_HANDLE);
}

Menu::Menu(std::string ti) {
    this->title = title;
    conhandler = GetStdHandle(STD_OUTPUT_HANDLE);
}

void Menu::add_opciones(MenuOpciones opciones) {
    opciones.push_back(opciones);
}

void Menu::remove_opciones(int index) {
    if (index < 0 || index > opciones.size()) {
        return;
    }

    std::vector<MenuOpciones>::iterator it = opciones.begin();
    std::advance(it, index);
    opciones.erase(it);
}

void Menu::display() {
    int selected = 1;

    if (opciones.empty()) {
        return;
    }

    CONSOLE_SCREEN_BUFFER_INFO csbi;
    WORD csbi_defaults;

    GetConsoleScreenBufferInfo(conhandler, &csbi);
    csbi_defaults = csbi.wAttributes;

    running = true;

    Consola& consola = Consola::get();

    consola.clear_area({ 0, 2, consola.get_consola_size().X, consola.get_consola_size().Y });
    consola.set_cursor_position({ 0, 2 });

    while (running) {
        int position = 1;

        consola.clear_area({ 0, 2, consola.get_consola_size().X, consola.get_consola_size().Y });
        consola.set_cursor_position({ 0, 2 });

        std::vector<MenuOpciones> visible_opciones;

        std::cout << std::endl << title << std::endl << std::endl;

        for (MenuOpciones option : opciones) {
            if (opciones.visible()) {
                visible_opciones.push_back(opciones);
            }
        }

        for (MenuOpciones option : visible_opciones) {
            if (option.get_args().has("__index")) {
                option.get_args().set("__index", position - 1);
            }
            else {
                option.get_args().add("__index", position - 1);
            }

            if (position++ == selected) {
                SetConsoleTextAttribute(conhandler, 23);
            }

            std::cout << " " << option.get_label() << " " << std::endl;
            SetConsoleTextAttribute(conhandler, csbi_defaults);
        }

        int key;

        do {
#ifdef _MSC_VER
            key = _getch();

            if (key == 0) {
                key = _getch();
            }
#else
            key = getch();

            if (key == 0) {
                key = getch();
            }
#endif
        } while (key != LLAVE_UP && key != LLAVE_DOWN && key != LLAVE_ENTER);

        switch (key) {
        case LLAVE_UP: {
            selected--;

            if (selected < 1) {
                selected = visible_opciones.size();
            }
        }
                   break;
        case LLAVE_DOWN: {
            selected++;

            if (selected > visible_opciones.size()) {
                selected = 1;
            }
        }
                     break;
        case LLAVE_ENTER: {
            MenuOpciones opciones = visible_opciones.at(selected - 1);
            std::cout << std::endl << std::endl;
            opciones.execute();

            if (opciones.should_wait()) {
                std::cout << std::endl << std::endl;
                system("pause");
            }

            system("cls");
        }
        }
    }
}

void Menu::stop() {
    running = false;
}

bool Menu::is_running() {
    return running;
}

Consola::Consola() {}

Consola& Consola::get() {
    static Consola instance;
    return instance;
}

void Consola::print(std::string text, COORD coord) {
    CHAR_INFO* buffer = (CHAR_INFO*)calloc(text.size(), sizeof(CHAR_INFO));

    if (buffer == 0) {
        return;
    }

    COORD console_size = get_consola_size();
    SMALL_RECT position = {
        coord.X, // left
        coord.Y, // top
        coord.X + text.length(), // right
        coord.Y + 1 // bottom
    };
    HANDLE consola_handler = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD buffer_size = { text.size(), 1 };

    int i = 0;

    for (const char c : text) {
        buffer[i].Char.AsciiChar = c;
        buffer[i].Attributes = 15;
        i++;
    }

    WriteConsoleOutputA(consola_handler, buffer, buffer_size, { 0, 0 }, &position);
    free(buffer);
}

void Consola::clear_line(short y) {
    COORD console_size = get_consola_size();

    if (y < 0 || y > console_size.Y) return;

    std::string empty(console_size.X, ' ');
    print(empty, { 0, y });
}

void Consola::clear_screen() {
    COORD consola_size = get_consola_size();
    clear_area({ 0, 0, consola_size.X, consola_size.Y });
}

void Consola::set_cursor_position(COORD coord) {
    HANDLE console_handler = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(console_handler, coord);
}

void Consola::clear_area(SMALL_RECT area) {
    int x = area.Left;
    int y = area.Top;
    int width = area.Right - area.Left;
    int height = area.Bottom - area.Top;

    std::string spaces = std::string(width * height, ' ');
    CHAR_INFO* buffer = (CHAR_INFO*)calloc(spaces.size(), sizeof(CHAR_INFO));

    if (buffer == 0) {
        return;
    }

    SMALL_RECT position = {
        x, // left
        y, // top
        x + width, // right
        y + height // bottom
    };
    COORD buffer_size = { width, height };
    HANDLE console_handler = GetStdHandle(STD_OUTPUT_HANDLE);
    int i = 0;

    for (const char c : spaces) {
        buffer[i].Char.AsciiChar = c;
        buffer[i].Attributes = 15;
        i++;
    }

    WriteConsoleOutputA(console_handler, buffer, buffer_size, { 0, 0 }, &position);
    free(buffer);
}

COORD Consola::get_consola_size() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int columns, rows;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

    COORD size = { columns, rows };

    return size;
}
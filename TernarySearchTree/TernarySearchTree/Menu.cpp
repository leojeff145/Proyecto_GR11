/*
/*                                  Universidad de las Fuerzas Armadas "ESPE"
* ArbolBinario
* ALumno: Leon William, Obando Leonardo, Quintana Wendy
* 20 / 01 / 2023
* 20 / 01 / 2023
* 7999 Estructura de datos
*/
#include "Menu.h"
#include <conio.h>

Menu::Menu() {
    conhandler = GetStdHandle(STD_OUTPUT_HANDLE);
}

Menu::Menu(std::string title) {
    this->title = title;
    conhandler = GetStdHandle(STD_OUTPUT_HANDLE);
}

void Menu::add_option(MenuOption option) {
    options.push_back(option);
}

void Menu::remove_option(int index) {
    if (index < 0 || index > options.size()) {
        return;
    }

    std::vector<MenuOption>::iterator it = options.begin();
    std::advance(it, index);
    options.erase(it);
}

void Menu::display() {
    int selected = 1;

    if (options.empty()) {
        return;
    }

    CONSOLE_SCREEN_BUFFER_INFO csbi;
    WORD csbi_defaults;

    GetConsoleScreenBufferInfo(conhandler, &csbi);
    csbi_defaults = csbi.wAttributes;

    running = true;
        
    Console &console = Console::get();

    console.clear_area({ 0, 2, console.get_console_size().X, console.get_console_size().Y });
    console.set_cursor_position({0, 2});

    while (running) {
        int position = 1;

        console.clear_area({ 0, 2, console.get_console_size().X, console.get_console_size().Y });
        console.set_cursor_position({0, 2});

        std::vector<MenuOption> visible_options;

        std::cout << std::endl << title << std::endl << std::endl;

        for (MenuOption option : options) {
            if (option.visible()) {
                visible_options.push_back(option);
            }
        }

        for (MenuOption option : visible_options) {
            if (option.get_args().has("__index")) {
                option.get_args().set("__index", position - 1);
            } else {
                option.get_args().add("__index", position - 1);
            }

            if (position++ == selected) {
                SetConsoleTextAttribute (conhandler, 23);
            }

            std::cout << " " << option.get_label() << " " << std::endl;
            SetConsoleTextAttribute (conhandler, csbi_defaults);
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
        } while (key != KEY_UP && key != KEY_DOWN && key != KEY_ENTER);
        
        switch (key) {
            case KEY_UP: {
                selected--;

                if (selected < 1) {
                    selected = visible_options.size();
                }
            }
            break;
            case KEY_DOWN: {
                selected++;

                if (selected > visible_options.size()) {
                    selected = 1;
                }
            }
            break;
            case KEY_ENTER: {
                MenuOption option = visible_options.at(selected - 1);
                std::cout << std::endl << std::endl;
                option.execute();

                if (option.should_wait()) {
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

Console::Console() {}

Console& Console::get() {
    static Console instance;
    return instance;
}

void Console::print(std::string text, COORD coord) {
    CHAR_INFO* buffer = (CHAR_INFO*)calloc(text.size(), sizeof(CHAR_INFO));

    if (buffer == 0) {
        return;
    }

    COORD console_size = get_console_size();
    SMALL_RECT position = {
        coord.X, // left
        coord.Y, // top
        coord.X + text.length(), // right
        coord.Y + 1 // bottom
    };
    HANDLE console_handler = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD buffer_size = { text.size(), 1 };

    int i = 0;

    for (const char c : text) {
        buffer[i].Char.AsciiChar = c;
        buffer[i].Attributes = 15;
        i++;
    }

    WriteConsoleOutputA(console_handler, buffer, buffer_size, { 0, 0 }, &position);
    free(buffer);
}

void Console::clear_line(short y) {
    COORD console_size = get_console_size();

    if (y < 0 || y > console_size.Y) return;

    std::string empty(console_size.X, ' ');
    print(empty, { 0, y });
}

void Console::clear_screen() {
    COORD console_size = get_console_size();
    clear_area({ 0, 0, console_size.X, console_size.Y });
}

void Console::set_cursor_position(COORD coord) {
    HANDLE console_handler = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(console_handler, coord);
}

void Console::clear_area(SMALL_RECT area) {
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

COORD Console::get_console_size() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int columns, rows;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

    COORD size = { columns, rows };

    return size;
}

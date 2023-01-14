#pragma once
#define _USE_MATH_DEFINES
#include <iostream>
#include <string>
#include <cctype>
#include <algorithm>
#include <conio.h>
#include <cmath>
#include <vector>
#include <sstream>
#include <fstream>
#include <regex>
#include <windows.h>

#ifndef _MSC_VER
#define _getch getch
#endif

class Validaciones
{
public:
    static inline int es_numero(std::string str) {
        return !str.empty() && std::find_if(str.begin(),
            str.end(), [](unsigned char c) {
                return !std::isdigit(c);
            }) == str.end();
    }

    inline static std::vector<std::string> splitstr(std::string str, char delimitador) {
        std::vector<std::string> values;
        std::stringstream ss(str);
        std::string tok;

        while (std::getline(ss, tok, delimitador)) {
            values.push_back(tok);
        }

        return values;
    }

    inline static std::string trim(const std::string& str) {
        std::string trimmed(str);
        trimmed = trimmed.erase(trimmed.find_last_not_of(" \t\n\r\f\v") + 1);
        trimmed = trimmed.erase(0, trimmed.find_first_not_of(" \t\n\r\f\v"));

        return trimmed;
    }

    inline static std::string strtolower(const std::string& str) {
        std::string output(str);

        std::transform(output.begin(), output.end(), output.begin(),
            [](unsigned char c) { return std::tolower(c); });

        return output;
    }

    inline static bool confirmar(const std::string question) {
        std::string input;
        bool answer;

        do {
            input = leer_cadena(question + " (s/n): ");

            if (input.empty()) {
                continue;
            }

            if (input.length() != 1) {
                continue;
            }

            char c = std::tolower(input.at(0));

            if (c != 's' && c != 'n') {
                continue;
            }

            answer = (c == 's');

            break;
        } while (true);

        return answer;
    }

    inline static std::string leer_password(std::string label) {
        std::string password;
        int ch = 0;

        std::cout << label;

        while (true) {
            ch = _getch();

            if (ch == 0x00) {
                ch = _getch();
            }

            if (ch == 13) {
                break;
            }

            if (ch == 8) {
                if (password.length() != 0) {
                    std::cout << "\b \b";
                    password.resize(password.length() - 1);
                }
                else {
                    Beep(523, 100);
                }
            }
            else {
                password += ch;
                std::cout << '*';
            }
        }

        std::cout << std::endl;

        return password;
    }

    static inline int convertirEnEntero(std::string cadena)
    {
        int numero = 0;
        int multiplo = 1;
        std::string cadenaReversa = cadena;

        if (cadena.find(".") != std::string::npos) {
            cadenaReversa = cadena.substr(0, cadena.find("."));
        }

        std::reverse(cadenaReversa.begin(), cadenaReversa.end());

        for (const char c : cadenaReversa) {
            if ((c < '0' || c > '9') && c != '-') {
                if (numero)
                    break;
                else
                    continue;
            }

            if (c == '-') {
                if (numero) {
                    numero = -numero;
                    break;
                }
            }
            else {
                numero += (c - '0') * multiplo;
                multiplo *= 10;
            }
        }

        return numero;
    }

    static inline double convertirEnReal(std::string cadena)
    {
        double rez = 0, fact = 1;

        if (cadena.at(0) == '-') {
            fact = -1;
            cadena = cadena.substr(1, cadena.length() - 1);
        }

        bool punto = false;
        int indice = 0;

        for (const char c : cadena) {
            int ascii = (int)c;

            if (c == '.' || c == ',') {
                if (punto || (!punto && indice == 0)) {
                    throw std::runtime_error("numero real incorrecto");
                }

                punto = true;
                indice++;
                continue;
            }

            if (!isdigit(c)) {
                throw std::runtime_error("numero real incorrecto");
            }

            int d = c - '0';

            if (d >= 0 && d <= 9) {
                if (punto) fact /= 10.0f;
                rez = rez * 10.0f + static_cast<double>(d);
            }

            indice++;
        }

        double resultado = rez * fact;

        return resultado;
    }

    static inline std::string leerCadenaNumerica(const std::string mensaje) {
        std::string resultado = "";
        int longitud = 0;

        std::cout << mensaje;

        while (true) {
            int ascii = _getch();

            if (ascii == 0) {
                ascii = _getch();
            }

            if (ascii == 8) {
                if (longitud == 0) {
                    continue;
                }

                std::cout << "\b \b";
                resultado.pop_back();
                longitud--;
                continue;
            }
            else if (ascii == 13) {
                if (trim(resultado).length() == 0 || resultado.at(resultado.length() - 1) == '.') {
                    continue;
                }

                break;
            }

            if ((ascii >= 48 && ascii <= 57) || ascii == 45 || ascii == 46 || ascii == 127) {
                if (ascii == 46 && resultado.find(".") != std::string::npos) {
                    continue;
                }

                if (ascii == 46 && longitud == 0) {
                    continue;
                }

                if (ascii == 45 && longitud != 0) {
                    continue;
                }

                resultado.push_back(static_cast<char>(ascii));
                longitud++;
                std::cout << static_cast<char>(ascii);
            }
        }

        return resultado;
    }

    static inline int leer_entero(std::string mensaje, int minimo = INT_MIN, int maximo = INT_MAX) {
        int leido;

        do {
            std::string input = trim(leerCadenaNumerica(mensaje));

            if (input.empty()) continue;

            leido = convertirEnEntero(input);
            std::cout << std::endl;
        } while (leido < minimo || leido > maximo);

        return leido;
    }

    static inline float leer_flotante(std::string mensaje, float minimo = FLT_MIN, float maximo = FLT_MAX) {
        float leido;

        do {
            std::string input = trim(leerCadenaNumerica(mensaje));

            if (input.empty()) continue;

            leido = convertirEnReal(input);
            std::cout << std::endl;
        } while (leido < minimo || leido > maximo);

        return leido;
    }

    static bool cedula_valida(const std::string cedula) {
        if (cedula.length() != 10) {
            return false;
        }

        int sum_par = 0;
        int sum_impar = 0;
        int sum;
        int i = 1;

        std::string digits = cedula.substr(0, cedula.size() - 1);

        for (char& c : digits) {
            int digit = c - '0';
            if (i % 2 == 0) {
                sum_par += digit;
            }
            else {
                if ((digit * 2) > 9) {
                    sum_impar += (digit * 2) - 9;
                }
                else {
                    sum_impar += (digit * 2);
                }
            }
            i++;
        }

        sum = sum_par + sum_impar;

        int verifier = cedula.at(cedula.size() - 1) - '0';
        int higher = (10 - (sum % 10)) + sum;

        if (sum % 10 == 0) {
            return verifier == 0;
        }

        return (higher - sum) == verifier;
    }

    static inline bool email_valido(std::string email) {
        std::regex pattern("^[a-zA-Z0-9.!#$%&'*+/=?^_`{|}~-]+@[a-zA-Z0-9](?:[a-zA-Z0-9-]{0,61}[a-zA-Z0-9])?(?:\\.[a-zA-Z0-9](?:[a-zA-Z0-9-]{0,61}[a-zA-Z0-9])?)*$");
        return std::regex_match(email, pattern);
    }

    static std::string leer_con_formato(std::string mensaje, std::string formato) {
        std::string output;
        bool invalido;

        do {
            std::cout << mensaje;
            std::getline(std::cin, output);
            output = recortar_cadena(output);
            invalido = !std::regex_match(output, std::regex(formato));

            if (invalido) {
                std::cout << "\n[Formato invalido]" << std::endl;
            }
        } while (invalido);

        return output;
    }

    static std::string leer_cadena(std::string mensaje) {
        std::string output;

        do {
            std::cout << mensaje;
            std::getline(std::cin, output);
            output = recortar_cadena(output);
        } while (output.empty());

        return output;
    }

    static std::string recortar_cadena(std::string str) {
        std::string output(str);
        std::string::size_type pos = output.find_first_not_of(' ');

        if (pos != std::string::npos) {
            output.erase(0, pos);
        }

        pos = output.find_last_not_of(' ');

        if (pos != std::string::npos) {
            output.erase(pos + 1);
        }

        return output;
    }

    static std::vector<std::vector<std::string>> leer_archivo_datos(std::string archivo) {
        std::ifstream file(archivo);
        std::string line;
        std::vector<std::vector<std::string>> resultado;

        while (std::getline(file, line)) {
            std::istringstream ss(line);
            std::string token;
            std::vector<std::string> columnas;

            while (std::getline(ss, token, ',')) {
                columnas.push_back(token);
            }

            resultado.push_back(columnas);
        }

        return resultado;
    }

    static void guardar_archivo_datos(std::string archivo, std::vector<std::string> lineas, bool overwrite = true) {
        std::ofstream file(archivo, overwrite ? std::ios::trunc : std::ios::app);

        for (std::string linea : lineas) {
            file << linea << std::endl;
        }

        std::string linea;
    }

    static inline void mostrar_archivo(std::string archivo) {
        std::ifstream file(archivo);
        std::string line;

        while (std::getline(file, line)) {
            std::cout << line << std::endl;
        }

        file.close();
    }
};

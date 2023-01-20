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
    static inline int es_numerico(std::string str) {
        return !str.empty() && std::find_if(str.begin(),
            str.end(), [](unsigned char c) {
                return !std::isdigit(c);
        }) == str.end();
    }

    inline static std::vector<std::string> dividirStr(std::string str, char delimitador) {
        std::vector<std::string> valores;
        std::stringstream ss(str);
        std::string pla;

        while (std::getline(ss, pla, delimitador)) {
            valores.push_back(pla);
        }

        return valores;
    }

    inline static std::string recortar(const std::string& str) {
        std::string recortadoPla(str);
        recortadoPla = recortadoPla.erase(recortadoPla.find_last_not_of(" \t\n\r\f\v") + 1);
        recortadoPla = recortadoPla.erase(0, recortadoPla.find_first_not_of(" \t\n\r\f\v"));

        return recortadoPla;
    }

    inline static std::string reducirstr(const std::string& str) {
        std::string salida(str);

        std::transform(salida.begin(), salida.end(), salida.begin(),
            [](unsigned char c) { return std::tolower(c); });

        return salida;
    }

    inline static bool confirmar(const std::string pregunta) {
        std::string entrada;
        bool respuesta;

        do {
            entrada = leer_cadena(pregunta + " (s/n): ");

            if (entrada.empty()) {
                continue;
            }

            if (entrada.length() != 1) {
                continue;
            }

            char c = std::tolower(entrada.at(0));

            if (c != 's' && c != 'n') {
                continue;
            }

            respuesta = (c == 's');

            break;
        } while (true);

        return respuesta;
    }

    inline static std::string leer_contraseña(std::string etique) {
        std::string contraseña;
        int ch = 0;

        std::cout << etique;

        while (true) {
            ch = _getch();

            if (ch == 0x00) {
                ch = _getch();
            }

            if (ch == 13) {
                break;
            }

            if (ch == 8) {
                if (contraseña.length() != 0) {
                    std::cout << "\b \b";
                    contraseña.resize(contraseña.length() - 1);
                } else {
                    Beep(523, 100);
                }
            } else {
                contraseña += ch;
                std::cout << '*';
            }
        }

        std::cout << std::endl;
        
        return contraseña;
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
        double rez = 0, fct = 1;

        if (cadena.at(0) == '-') {
            fct = -1;
            cadena = cadena.substr(1, cadena.length() - 1);
        }

        bool punto = false;
        int indice = 0;

        for (const char c : cadena) {
            int ascii = (int) c;

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
                if (punto) fct /= 10.0f;
                rez = rez * 10.0f + static_cast<double>(d);
            }

            indice++;
        }

        double resultado = rez * fct;

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
                if (recortar(resultado).length() == 0 || resultado.at(resultado.length() - 1) == '.') {
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
            std::string input = recortar(leerCadenaNumerica(mensaje));

            if (input.empty()) continue;

            leido = convertirEnEntero(input);
            std::cout << std::endl;
        } while (leido < minimo || leido > maximo);

        return leido;
    }

    static inline float leer_flotante(std::string mensaje, float minimo = FLT_MIN, float maximo = FLT_MAX) {
        float leido;

        do {
            std::string entrada = recortar(leerCadenaNumerica(mensaje));

            if (entrada.empty()) continue;

            leido = convertirEnReal(entrada);
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

        int verificador = cedula.at(cedula.size() - 1) - '0';
        int mAlto = (10 - (sum % 10)) + sum;

        if (sum % 10 == 0) {
            return verificador == 0;
        }

        return (mAlto - sum) == verificador;
    }

    static inline bool email_valido(std::string email) {
        std::regex patron("^[a-zA-Z0-9.!#$%&'*+/=?^_`{|}~-]+@[a-zA-Z0-9](?:[a-zA-Z0-9-]{0,61}[a-zA-Z0-9])?(?:\\.[a-zA-Z0-9](?:[a-zA-Z0-9-]{0,61}[a-zA-Z0-9])?)*$");
        return std::regex_match(email, patron);
    }

    static std::string leer_con_formato(std::string mensaje, std::string formato) {
        std::string salida;
        bool invalido;
        
        do {
            std::cout << mensaje;
            std::getline(std::cin, salida);
            salida = recortar_cadena(salida);
            invalido = !std::regex_match(salida, std::regex(formato));

            if (invalido) {
                std::cout << "\n[Formato invalido]" << std::endl;
            }
        } while (invalido);

        return salida;
    }

    static std::string leer_cadena(std::string mensaje) {
        std::string salida;

        do {
            std::cout << mensaje;
            std::getline(std::cin, salida);
            salida = recortar_cadena(salida);
        } while (salida.empty());

        return salida;
    }

    static std::string recortar_cadena(std::string str) {
        std::string salida(str);
        std::string::size_type pos = salida.find_first_not_of(' ');
        
        if (pos != std::string::npos) {
            salida.erase(0, pos);
        }

        pos = salida.find_last_not_of(' ');
        
        if (pos != std::string::npos) {
            salida.erase(pos + 1);
        }

        return salida;
    }

    static std::vector<std::vector<std::string>> leer_archivo_datos(std::string archivo) {
        std::ifstream documento(archivo);
        std::string linea;
        std::vector<std::vector<std::string>> resultado;
        
        while (std::getline(documento, linea)) {
            std::istringstream ss(linea);
            std::string fich;
            std::vector<std::string> columnas;
            
            while (std::getline(ss, fich, ',')) {
                columnas.push_back(fich);
            }

            resultado.push_back(columnas);
        }

        return resultado;
    }

    static void guardar_archivo_datos(std::string archivo, std::vector<std::string> lineas, bool sobreescribir = true) {
        std::ofstream documento(archivo, sobreescribir ? std::ios::trunc : std::ios::app);
        
        for (std::string linea : lineas) {
            documento << linea << std::endl;
        }
        
        std::string linea;
    }

    static inline void mostrar_archivo(std::string archivo) {
        std::ifstream documento(archivo);
        std::string linea;

        while (std::getline(documento, linea)) {
            std::cout << linea << std::endl;
        }

        documento.close();
    }
};

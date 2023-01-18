#pragma once
/*#include "Fecha.h"
#include <iostream>
#include <chrono>
#include <ctime> 
#include <cstdlib>
#include <regex>
#include "Validaciones.h"



Fecha::Fecha()
{
}

Fecha::Fecha(int dia, int mes, int anio)
{
    this->dia = dia;
    this->mes = mes;
    this->anio = anio;

    if (!Fecha::valida(*this)) {
        std::time_t t = std::time(0);
        std::tm* now = std::localtime(&t);
  
        this->dia = (now->tm_mday);
        this->mes = (now->tm_mon + 1);
        this->anio = (now->tm_year + 1900);
    }
}


int Fecha::getDia() const
{
    return dia;
}

void Fecha::setDia(int dia)
{
    this->dia = dia;
}

int Fecha::getMes() const
{
    return mes;
}

void Fecha::setMes(int mes)
{
    this->mes = mes;
}

int Fecha::getAnio() const
{
    return anio;
}

void Fecha::setAnio(int anio)
{
    this->anio = anio;
}

Fecha Fecha::actual()
{
    std::time_t t = std::time(0);
    std::tm* now = std::localtime(&t);

    int dia = (now->tm_mday);
    int mes = (now->tm_mon + 1);
    int anio = (now->tm_year + 1900);

    return Fecha(dia, mes, anio);
}

Fecha Fecha::leer(std::string mensaje)
{
    Fecha fecha;

    do {
        int dia, mes, anio;

        std::string linea;
        std::regex pattern("^[0-9]{1,2}-[0-9]{1,2}-[0-9]{4}$");

        do {
            linea = Validaciones::leer_cadena(mensaje);
        } while (!std::regex_match(linea, pattern));


        auto partes = Validaciones::splitstr(linea, '-');
        dia = std::stoi(partes[0]);
        mes = std::stoi(partes[1]);
        anio = std::stoi(partes[2]);

        if (!Fecha::valida(dia, mes, anio)) {
            printf("\n(Fecha incorrecta)\n");
            continue;
        }

        fecha.setDia(dia);
        fecha.setMes(mes);
        fecha.setAnio(anio);

        break;
    } while (true);

    return fecha;
}

bool Fecha::valida(Fecha fecha)
{
    return valida(fecha.getDia(), fecha.getMes(), fecha.getAnio());
}

bool Fecha::valida(int dia, int mes, int anio)
{
    struct tm tm;

    if (mes < 1 || mes > 12)
        return false;

    if (dia < 1 || dia > 31)
        return false;

    memset(&tm, 0, sizeof(tm));

    tm.tm_mday = dia;
    tm.tm_mon = (mes - 1);
    tm.tm_year = (anio - 1900);

    time_t resultado = mktime(&tm);

    if (resultado == (time_t)-1) {
        return false;
    }

    bool bisiesto = (((anio % 4 == 0) &&
        (anio % 100 != 0)) ||
        (anio % 400 == 0));

    if (mes == 2)
    {
        if (bisiesto)
            return (dia <= 29);
        else
            return (dia <= 28);
    }

    if (mes == 4 || mes == 6 ||
        mes == 9 || mes == 11)
        return (dia <= 30);

    return true;
}*/

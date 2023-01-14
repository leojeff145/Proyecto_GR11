#pragma once
#include <string>
#include "modelo.h"
class Usuario: public Modelo
{
private:
    std::string _nombre;
	std::string _contrasenia;

public:
    Usuario() = default;
    Usuario(std::string nombre, std::string contrasenia);

    std::string getNombre();
    std::string getContrasenia();

    void setNombre(std::string nombre);
    void setContrasenia(std::string contrasenia);

    virtual std::string toCSV();
};


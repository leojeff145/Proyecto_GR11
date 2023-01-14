#include "Usuario.h"
Usuario::Usuario(std::string nombre, std::string contrasenia)
{
    _nombre = nombre;
    _contrasenia = contrasenia;
}

std::string Usuario::getNombre()
{
    return _nombre;
}

std::string Usuario::getContrasenia()
{
    return _contrasenia;
}

void Usuario::setNombre(std::string nombre)
{
    _nombre = nombre;
}

void Usuario::setContrasenia(std::string contrasenia)
{
    _contrasenia = contrasenia;
}

std::string Usuario::toCSV()
{
    return _nombre + "," + _contrasenia;
}

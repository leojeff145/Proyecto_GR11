#pragma once
#include <functional>
#include "CDLlist.h"
#include "Usuario.h"
class GestorConfirmacion
{
public:
    GestorConfirmacion() = default;
    void iniciar();
    void alIngresar(std::function<void()> retrollamada);

    void autentificar();
    void registro();
    CDLlist<Usuario> obtener_usuarios();
    void guardar_usuarios(CDLlist<Usuario> usuarios);
    void guardar_usuario(Usuario usuario);
private:

    std::function<void()> _callback_ingreso;

};

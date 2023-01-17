#include "Gestor_Confirmacion.h"
#include "Menu.h"
#include "Validaciones.h"
#include "md5.h"

void GestorConfirmacion::iniciar()
{
    Menu menu("Autentificacion");

    _callback_ingreso = [&]() {
        menu.parar();
    };

    menu.add_opciones(MenuOpciones("Ingresar", [&]() { autentificar(); }));
    menu.add_opciones(MenuOpciones("Registrar nuevo usuario", [this]() { registro(); }));
    menu.add_opciones(MenuOpciones("Salir", []() { exit(0); }));
    menu.mostrar();
}

void GestorConfirmacion::alIngresar(std::function<void()> callback)
{
    _callback_ingreso = callback;
}

void GestorConfirmacion::autentificar()
{

    std::string nombre = Validaciones::leer_con_formato("Ingresa el usuario: ", "^[a-zA-Z0-9_]{4,}$");
    std::string contrasena = Validaciones::leer_contrasenia("Ingresa la contrasena: ");
    MD5 md5;

    auto usuarios = obtener_usuarios();
    auto encontrado = usuarios.buscar([&](Usuario u) {
        return u.getNombre() == nombre;
        });

    if (!encontrado.has_value()) {
        std::cout << "\n[Nombre de usuario incorrecto]" << std::endl;
        return;
    }

    Usuario usuario = encontrado.value();

    if (usuario.getContrasenia() != md5(contrasena)) {
        std::cout << "\n[Contrasena incorrecta]" << std::endl;
        return;
    }

    if (_callback_ingreso) {
        _callback_ingreso();
    }
}

void GestorConfirmacion::registro()
{
    std::string nombre = Validaciones::leer_con_formato("Ingresa el usuario: ", "^[a-zA-Z0-9_]{4,}$");
    std::string contrasena, contrasena2;

    do {
        contrasena = Validaciones::leer_contrasenia("Ingresa la contrasena: ");
        contrasena2 = Validaciones::leer_contrasenia("Confirma la contrasena: ");

        if (contrasena != contrasena2) {
            std::cout << "\n[Las contrasenas no coinciden]" << std::endl;
        }
    } while (contrasena != contrasena2);

    MD5 md5;

    auto usuarios = obtener_usuarios();
    auto encontrado = usuarios.buscar([&](Usuario u) {
        return u.getNombre() == nombre;
        });

    if (encontrado.has_value()) {
        std::cout << "\n[Nombre de usuario en uso]" << std::endl;
        return;
    }

    guardar_usuario(Usuario(nombre, md5(contrasena)));
    std::cout << "\n[Usuario registrado]" << std::endl;
}

CDLlist<Usuario> GestorConfirmacion::obtener_usuarios()
{
    CDLlist<Usuario> usuarios;
    auto csv = Validaciones::leer_archivo_datos("Usuarios.txt");

    for (auto registro : csv) {
        std::string nombre = registro[0];
        std::string contrasena = registro[1];
        usuarios.retroceder(Usuario(nombre, contrasena));
    }

    return usuarios;
}

void GestorConfirmacion::guardar_usuarios(CDLlist<Usuario> usuarios)
{
    std::vector<std::string> csv;

    usuarios.paraCada([&](Usuario usuario) {
        csv.push_back(usuario.toCSV());
        });

    Validaciones::guardar_archivo_datos("usuarios.txt", csv);
}

void GestorConfirmacion::guardar_usuario(Usuario usuario)
{
    auto usuarios = obtener_usuarios();
    usuarios.retroceder(usuario);
    guardar_usuarios(usuarios);
}

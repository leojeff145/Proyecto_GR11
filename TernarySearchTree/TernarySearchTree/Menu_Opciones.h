#pragma once
#include <string>
#include <functional>
#include <vector>
#include <map>
#include <memory>
#include <optional>

#ifndef __MENU_CLASSES_
#define __MENU_CLASSES_
class MenuOpcionesArgumentoBase
{
public:
    virtual ~MenuOpcionesArgumentoBase() = 0;
};
inline MenuOpcionesArgumentoBase::~MenuOpcionesArgumentoBase() {}

///////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
class MenuOpcionesArgumento : public MenuOpcionesArgumentoBase {
public:
    typedef T Type;
    explicit MenuOpcionesArgumento(const Type& valor);
    Type get_valor();
    void set_valor(Type valor);
private:
    Type valor;
};

template <typename T>
MenuOpcionesArgumento<T>::MenuOpcionesArgumento(const T& valor) : valor(valor) {}

template <typename T>
T MenuOpcionesArgumento<T>::get_valor() {
    return valor;
}

template <typename T>
void MenuOpcionesArgumento<T>::set_valor(T valor) {
    this->valor = valor;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

class MenuOpcionesArgumentos {
public:
    MenuOpcionesArgumentos();

    /**
     * @brief agrega un argumento con clave
     * @tparam T tipo del argumento
     * @param llave
     * @param argument
    */
    template <typename T>
    void add(std::string llave, MenuOpcionesArgumento<T>* argumento);

    /**
     * @brief Agrega un argumento con clave y un valor
     * @tparam T tipo de dato del argumento
     * @param llave clave del argumento
     * @param valor
    */
    template <typename T>
    void add(std::string llave, T valor);

    /**
     * @brief obtiene un argumento por clave
     * @tparam T tipo de dato del argumento
     * @param llave clave del argumento a obtener
     * @return
    */
    template <typename T>
    T get(std::string llave);

    /**
     * @brief define un argumento por clave y valor
     * @tparam T tipo de dato del argumento
     * @param llave clave del argumento
     * @param valor valor del argumento
    */
    template <typename T>
    void set(std::string llave, T valor);

    bool has(std::string llave);
private:
    std::map<std::string, std::unique_ptr<MenuOpcionesArgumentoBase>>* argumento;
};

inline MenuOpcionesArgumentos::MenuOpcionesArgumentos() {
    argumento = new std::map<std::string, std::unique_ptr<MenuOpcionesArgumentoBase>>();
}

template <typename T>
void MenuOpcionesArgumentos::add(std::string llave, MenuOpcionesArgumento<T>* argumento) {
    (*argumento)[llave] = std::unique_ptr<MenuOpcionesArgumentoBase>(argumento);
}

template <typename T>
void MenuOpcionesArgumentos::add(std::string llave, T valor) {
    add(llave, new MenuOpcionesArgumento<T>(valor));
}

template <typename T>
T MenuOpcionesArgumentos::get(std::string llave) {
    auto arg = dynamic_cast<MenuOpcionesArgumento<T>&>(*((*argumento)[llave]));
    return arg.get_valor();
}

template <typename T>
void MenuOpcionesArgumentos::set(std::string llave, T valor) {
    auto arg = dynamic_cast<MenuOpcionesArgumento<T>&>(*((*argumento)[llave]));
    arg.set_valor(valor);
}

inline bool MenuOpcionesArgumentos::has(std::string llave) {
    return !(argumento->find(llave) == argumento->end());
}

#endif

///////////////////////////////////////////////////////////////////////////////////////////////////

typedef std::function<void(MenuOpcionesArgumentos args)> MenuOpcionesCallback;
typedef std::function<void()> MenuOpcionesCallback2;

class MenuOpciones {
public:
    MenuOpciones(std::string label, MenuOpcionesCallback regresar);
    MenuOpciones(std::string label, MenuOpcionesCallback regresar, bool esperar_despues_ejecucion);
    MenuOpciones(std::string label, MenuOpcionesCallback regresar, MenuOpcionesArgumentos argumento);
    MenuOpciones(std::string label, MenuOpcionesCallback regresar, MenuOpcionesArgumentos argumento, bool esperar_despues_ejecucion);

    MenuOpciones(std::string label, MenuOpcionesCallback2 regresar);
    MenuOpciones(std::string label, MenuOpcionesCallback2 regresar, bool esperar_despues_ejecucion);
    MenuOpciones(std::string label, MenuOpcionesCallback2 regresar, MenuOpcionesArgumentos argumento);
    MenuOpciones(std::string label, MenuOpcionesCallback2 regresar, MenuOpcionesArgumentos argumento, bool esperar_despues_ejecucion);

    bool visible();
    void visible(bool visible);
    void visible(std::function<bool()> visible_cb);

    /**
     * @brief obtiene la etiqueta de la opcion del menu
     * @return
    */
    std::string get_label();

    /**
     * @brief ejecuta la accion de esta opcion del menu
    */
    void execute();

    /**
     * @brief verifica si esta opcion deberia esperar al usuario
     * @return true si deberia esperar, caso contrario devuelve false
    */
    bool should_wait();

    /**
     * @brief obtiene todos los argumentos de esta opcion
     * @return
    */
    MenuOpcionesArgumentos& get_args();

private:
    std::string label;
    std::optional<MenuOpcionesCallback> regresar;
    std::optional<MenuOpcionesCallback2> regresar2;
    bool esperar_despues_ejecucion = true;
    MenuOpcionesArgumentos argumento;
    std::function<bool()> regrso_visible_ = []() { return true; };
};




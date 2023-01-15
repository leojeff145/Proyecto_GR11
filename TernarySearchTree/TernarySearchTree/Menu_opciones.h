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
    explicit MenuOpcionesArgumento(const Type& value);
    Type get_value();
    void set_value(Type value);
private:
    Type value;
};

template <typename T>
MenuOpcionesArgumento<T>::MenuOpcionesArgumento(const T& value) : value(value) {}

template <typename T>
T MenuOpcionesArgumento<T>::get_value() {
    return value;
}

template <typename T>
void MenuOpcionesArgumento<T>::set_value(T value) {
    this->value = value;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

class MenuOpcionesArgumentos {
public:
    MenuOpcionesArgumentos();

    /**
     * @brief agrega un argumento con clave
     * @tparam T tipo del argumento
     * @param key
     * @param argument
    */
    template <typename T>
    void add(std::string key, MenuOpcionesArgumento<T> *argumento);

    /**
     * @brief Agrega un argumento con clave y un valor
     * @tparam T tipo de dato del argumento
     * @param key clave del argumento
     * @param value
    */
    template <typename T>
    void add(std::string key, T value);

    /**
     * @brief obtiene un argumento por clave
     * @tparam T tipo de dato del argumento
     * @param key clave del argumento a obtener
     * @return
    */
    template <typename T>
    T get(std::string key);

    /**
     * @brief define un argumento por clave y valor
     * @tparam T tipo de dato del argumento
     * @param key clave del argumento
     * @param value valor del argumento
    */
    template <typename T>
    void set(std::string key, T value);

    bool has(std::string key);
private:
    std::map<std::string, std::unique_ptr<MenuOpcionesArgumentoBase>> *argumento;
};

inline MenuOpcionesArgumentos::MenuOpcionesArgumentos() {
    argumento = new std::map<std::string, std::unique_ptr<MenuOpcionesArgumentoBase>>();
}

template <typename T>
void MenuOpcionesArgumentos::add(std::string key, MenuOpcionesArgumento<T> *argumento) {
    (*argumento)[key] = std::unique_ptr<MenuOpcionesArgumentoBase>(argumento);
}

template <typename T>
void MenuOpcionesArgumentos::add(std::string key, T value) {
    add(key, new MenuOpcionesArgumento<T>(value));
}

template <typename T>
T MenuOpcionesArgumentos::get(std::string key) {
    auto arg = dynamic_cast<MenuOpcionesArgumento<T>&>(*((*argumento)[key]));
    return arg.get_value();
}

template <typename T>
void MenuOpcionesArgumentos::set(std::string key, T value) {
    auto arg = dynamic_cast<MenuOpcionesArgumento<T>&>(*((*argumento)[key]));
    arg.set_value(value);
}

inline bool MenuOpcionesArgumentos::has(std::string key) {
    return !(argumento->find(key) == argumento->end());
}

#endif

///////////////////////////////////////////////////////////////////////////////////////////////////

typedef std::function<void(MenuOpcionesArgumentos args)> MenuOpcionesCallback;
typedef std::function<void()> MenuOpcionesCallback2;

class MenuOpciones {
public:
    MenuOpciones(std::string label, MenuOpcionesCallback callback);
    MenuOpciones(std::string label, MenuOpcionesCallback callback, bool wait_after_exec);
    MenuOpciones(std::string label, MenuOpcionesCallback callback, MenuOpcionesArgumentos argumento);
    MenuOpciones(std::string label, MenuOpcionesCallback callback, MenuOpcionesArgumentos argumento, bool wait_after_exec);

    MenuOpciones(std::string label, MenuOpcionesCallback2 callback);
    MenuOpciones(std::string label, MenuOpcionesCallback2 callback, bool wait_after_exec);
    MenuOpciones(std::string label, MenuOpcionesCallback2 callback, MenuOpcionesArgumentos argumento);
    MenuOpciones(std::string label, MenuOpcionesCallback2 callback, MenuOpcionesArgumentos argumento, bool wait_after_exec);

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
    std::optional<MenuOpcionesCallback> callback;
    std::optional<MenuOpcionesCallback2> callback2;
    bool wait_after_exec = true;
    MenuOpcionesArgumentos argumento;
    std::function<bool()> visible_callback_ = []() { return true; };
};



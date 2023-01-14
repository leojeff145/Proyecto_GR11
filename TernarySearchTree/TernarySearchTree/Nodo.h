#pragma once

template<typename T>
class Nodo
{
public:
    Nodo(T dato);
    Nodo(T dato, Nodo<T>* siguiente);
    Nodo(T dato, Nodo<T>* siguiente, Nodo<T>* anterior);

    void set_siguiente(Nodo<T>* siguiente);
    Nodo<T>* get_siguiente();

    void set_anterior(Nodo<T>* siguiente);
    Nodo<T>* get_anterior();

    void set_dato(T dato);
    T get_dato();

private:
    T dato;
    Nodo<T>* siguiente = nullptr;
    Nodo<T>* anterior = nullptr;
};
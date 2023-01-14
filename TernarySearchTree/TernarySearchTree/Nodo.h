#pragma once

template<typename T>
class Nodo
{
public:
    Nodo(T dato);
    Nodo(T dato, Nodo<T> *siguiente);
    Nodo(T dato, Nodo<T> *siguiente, Nodo<T> *anterior);

    void set_siguiente(Nodo<T> *siguiente);
    Nodo<T> *get_siguiente();

    void set_anterior(Nodo<T> *siguiente);
    Nodo<T> *get_anterior();

    void set_dato(T dato);
    T get_dato();

private:
    T dato;
    Nodo<T> *siguiente = nullptr;
    Nodo<T> *anterior = nullptr;
};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T>
Nodo<T>::Nodo(T dato) {
    this->dato = dato;
    this->siguiente = nullptr;
    this->anterior = nullptr;
}

template<typename T>
Nodo<T>::Nodo(T dato, Nodo<T> *siguiente) {
    this->dato = dato;
    this->siguiente = siguiente;
    this->anterior = nullptr;
}

template<typename T>
Nodo<T>::Nodo(T dato, Nodo<T> *siguiente, Nodo<T> *anterior) {
    this->dato = dato;
    this->siguiente = siguiente;
    this->anterior = anterior;
}

template<typename T>
void Nodo<T>::set_dato(T dato) {
    this->dato = dato;
}

template<typename T>
T Nodo<T>::get_dato() {
    return dato;
}

template<typename T>
void Nodo<T>::set_siguiente(Nodo<T> *siguiente) {
    this->siguiente = siguiente;
}

template<typename T>
Nodo<T>* Nodo<T>::get_siguiente() {
    return siguiente;
}

template<typename T>
void Nodo<T>::set_anterior(Nodo<T> *anterior) {
    this->anterior = anterior;
}

template<typename T>
Nodo<T>* Nodo<T>::get_anterior() {
    return anterior;
}
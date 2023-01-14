#include "NodoBasico.h"

NodoBasico::NodoBasico() {
	_padre = nullptr;
}

NodoBasico::NodoBasico(std::string dato) {
	_padre = nullptr;
	_dato = dato;
}

NodoBasico::~NodoBasico() {
	for (auto it = _hijos.begin(); it != _hijos.end(); ++it) {
		delete (*it);
	}
}

void NodoBasico::nodosHijos(NodoBasico* nd) {
	_hijos.push_back(nd);
	nd->setPadre(this);
}

std::list<NodoBasico*> NodoBasico::getHijos() {
	return _hijos;
}

std::string NodoBasico::getDato() {
	return _dato;
}

void NodoBasico::setDato(std::string dato) {
	_dato = dato;
}

void NodoBasico::setPadre(NodoBasico* nd) {
	_padre = nd;
}
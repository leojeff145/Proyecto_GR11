#include "NodoBasico.h"

NodoBasico::NodoBasico() {
	_padre = nullptr;
}

NodoBasico::NodoBasico(std::string data) {
	_padre = nullptr;
	_dato = data;
}

NodoBasico::~NodoBasico() {
	for (auto it = _hijo.begin(); it != _hijo.end(); ++it) {
		delete (*it);
	}
}

void NodoBasico::agregarHijo(NodoBasico* nd) {
	_hijo.push_back(nd);
	nd->setPadre(this);
}

std::list<NodoBasico*> NodoBasico::getHijo() {
	return _hijo;
}

std::string NodoBasico::getDato() {
	return _dato;
}

void NodoBasico::setDato(std::string data) {
	_dato = data;
}

void NodoBasico::setPadre(NodoBasico* nd) {
	_padre = nd;
}

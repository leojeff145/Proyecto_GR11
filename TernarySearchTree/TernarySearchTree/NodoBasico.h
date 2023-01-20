#pragma once
#include <string>
#include <list>

class NodoBasico {
public:
	NodoBasico();
	NodoBasico(std::string dato);

	virtual ~NodoBasico();

	void agregarHijo(NodoBasico* nd);
	std::list<NodoBasico*> getHijo();

	std::string getDato();
	void setDato(std::string data);

protected:
	void setPadre(NodoBasico* nd);

	std::string _dato;

	std::list<NodoBasico*> _hijo;
	NodoBasico* _padre;
};


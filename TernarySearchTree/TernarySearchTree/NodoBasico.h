#pragma once
#include <string>
#include <list>

class NodoBasico {
public:
	NodoBasico();
	NodoBasico(std::string dato);

	virtual ~NodoBasico();

	void nodosHijos(NodoBasico* nd);
	std::list<NodoBasico*> getHijos();

	std::string getDato();
	void setDato(std::string dato);

protected:
	void setPadre(NodoBasico* nd);

	std::string _dato;

	std::list<NodoBasico*> _hijos;
	NodoBasico* _padre;
};
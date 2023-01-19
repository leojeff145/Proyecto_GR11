#pragma once
#include <string>

class NodoTernario
{
public:
	char val;
	NodoTernario* izq = nullptr;
	NodoTernario* der = nullptr;
	NodoTernario* med = nullptr;
	NodoTernario* pad = nullptr;
	bool esPalabra = false;
public:
	NodoTernario(char valor);

	char valor();
	NodoTernario*& izquierda();
	NodoTernario*& medio();
	NodoTernario*& derecha();
	NodoTernario*& padre();
	bool es_Palabra();

	void valor(char valor);
	void izquierda(NodoTernario* izquierda);
	void medio(NodoTernario* medio);
	void derecha(NodoTernario* derecha);
	void padre(NodoTernario* padre);
	void es_Palabra(bool valor);
};


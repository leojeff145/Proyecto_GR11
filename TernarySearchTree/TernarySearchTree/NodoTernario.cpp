#include "NodoTernario.h"

NodoTernario::NodoTernario(char valor)
{
	val = valor;
}

char NodoTernario::valor()
{
	return val;
}

NodoTernario*& NodoTernario::izquierda()
{
	return izq;
}

NodoTernario*& NodoTernario::medio()
{
	return med;
}

NodoTernario*& NodoTernario::derecha()
{
	return der;
}

NodoTernario*& NodoTernario::padre()
{
	return pad;
}

bool NodoTernario::es_Palabra()
{
	return esPalabra;
}

void NodoTernario::valor(char valor)
{
	val = valor;
}

void NodoTernario::izquierda(NodoTernario* izquierda)
{
	izq = izquierda;
}

void NodoTernario::medio(NodoTernario* medio)
{
	med = medio;
}

void NodoTernario::derecha(NodoTernario* derecha)
{
	der = derecha;
}

void NodoTernario::padre(NodoTernario* padre)
{
	pad = padre;
}

void NodoTernario::es_Palabra(bool valor)
{
	esPalabra = valor;
}


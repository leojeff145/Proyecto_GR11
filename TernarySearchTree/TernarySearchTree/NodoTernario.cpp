/*
/*                                  Universidad de las Fuerzas Armadas "ESPE"
* ArbolBinario
* ALumno: Leon William, Obando Leonardo, Quintana Wendy
* 20 / 01 / 2023
* 20 / 01 / 2023
* 7999 Estructura de datos
*/
#include "NodoTernario.h"

NodoTernario::NodoTernario(char valor) {
	valor_ = valor;
}

char NodoTernario::value() {
	return valor_;
}

NodoTernario*& NodoTernario::left() {
	return izquierda_;
}

NodoTernario*& NodoTernario::middle() {
	return medio_;
}

NodoTernario*& NodoTernario::right() {
	return derecha_;
}

NodoTernario*& NodoTernario::parent() {
	return padre_;
}

bool NodoTernario::is_word() {
	return es_palabra_;
}

void NodoTernario::value(char valor) {
	valor_ = valor;
}

void NodoTernario::left(NodoTernario* izquierda) {
	izquierda_ = izquierda;
}

void NodoTernario::middle(NodoTernario* medio) {
	medio_ = medio;
}

void NodoTernario::right(NodoTernario* derecha) {
	derecha_ = derecha;
}

void NodoTernario::parent(NodoTernario* padre) {
	padre_ = padre;
}

void NodoTernario::is_word(bool valor) {
	es_palabra_ = valor;
}

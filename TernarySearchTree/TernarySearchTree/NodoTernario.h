#pragma once
#include <string>

class NodoTernario {
public:
	NodoTernario(char value);

	char value();
	NodoTernario*& left();
	NodoTernario*& middle();
	NodoTernario*& right();
	NodoTernario*& parent();
	bool is_word();

	void value(char valor);
	void left(NodoTernario* izquierda);
	void middle(NodoTernario* medio);
	void right(NodoTernario* derecha);
	void parent(NodoTernario* padre);
	void is_word(bool valor);

private:
	char valor_;
	NodoTernario* izquierda_ = nullptr;
	NodoTernario* medio_ = nullptr;
	NodoTernario* derecha_ = nullptr;
	NodoTernario* padre_ = nullptr;
	bool es_palabra_ = false;
};
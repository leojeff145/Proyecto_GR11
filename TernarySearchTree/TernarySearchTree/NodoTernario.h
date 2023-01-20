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

	void value(char value);
	void left(NodoTernario* left);
	void middle(NodoTernario* middle);
	void right(NodoTernario* right);
	void parent(NodoTernario* parent);
	void is_word(bool value);

private:
	char value_;
	NodoTernario* left_ = nullptr;
	NodoTernario* middle_ = nullptr;
	NodoTernario* right_ = nullptr;
	NodoTernario* parent_ = nullptr;
	bool is_word_ = false;
};
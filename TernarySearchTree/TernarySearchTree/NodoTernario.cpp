#include "NodoTernario.h"

NodoTernario::NodoTernario(char value) {
	value_ = value;
}

char NodoTernario::value() {
	return value_;
}

NodoTernario*& NodoTernario::left() {
	return left_;
}

NodoTernario*& NodoTernario::middle() {
	return middle_;
}

NodoTernario*& NodoTernario::right() {
	return right_;
}

NodoTernario*& NodoTernario::parent() {
	return parent_;
}

bool NodoTernario::is_word() {
	return is_word_;
}

void NodoTernario::value(char value) {
	value_ = value;
}

void NodoTernario::left(NodoTernario* left) {
	left_ = left;
}

void NodoTernario::middle(NodoTernario* middle) {
	middle_ = middle;
}

void NodoTernario::right(NodoTernario* right) {
	right_ = right;
}

void NodoTernario::parent(NodoTernario* parent) {
	parent_ = parent;
}

void NodoTernario::is_word(bool value) {
	is_word_ = value;
}

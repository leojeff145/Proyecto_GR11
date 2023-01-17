#pragma once
#include "NodoTernario.h"
#include "ayudas.h"
#include "NodoAB.h"
#include "NodoBasico.h"
#include <regex>
#include <string>
#include <iostream>
#include <functional>
#include <fstream>

class ArbolBT {
public:
	void insertar(std::string valor);
	void remover(std::string valor);
	NodoTernario* encontrar(std::string valor);
	void imprimir();
	void atravesar(std::function<void(char valor)>cb);
	void escribir(std::ostream& out);
	NodoTernario* leer(std::string nombre_archivo);

private:
	void escribir_recursivo(NodoTernario* p, std::ostream& out);
	int leer_recursivo(NodoTernario*& raiz, std::istream& in);
	void atravesar_recursivo(NodoTernario* raiz, std::function<void(char valor)>cb);
	void insertar_recursivo(NodoTernario* arbol, std::string valor);
	NodoTernario* encontrar_recursivo(NodoTernario* arbol, std::string valor);
	NodoTernario* remover_recursivo(NodoTernario* nodo, std::string palabra,int posicion);
	
	void limpieza_eliminacion(NodoTernario* nodo);
	NodoTernario* crear_si_no_existe(NodoTernario* arbol, NodoTernario*& hijo, std::string label);
	void imprimir_ayuda(NodoTernario* raiz, char* buffer, int profundidad,NodoBasico* cabeza);
	
	int contar_hermanos(NodoTernario* nodo) {
		int contador = 0;
		
		if (nodo->izquierda() != nullptr) {
			contador++;
		}
		if (nodo->derecha() != nullptr) {
			contador++;
		}
		if (nodo->medio() != nullptr) {
			contador++;
		}
		return contador;
	}
	NodoTernario* raiz_ = nullptr;
};

inline void ArbolBT::atravesar(std::function<void(char valor)>cb) {
	atravesar_recursivo(raiz_, cb);
}

inline void ArbolBT::escribir(std::ostream& out) {
	escribir_recursivo(raiz_, out);
}




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
	int leer_recursivo(NodoTernario*& raiz, std::ifstream& in);
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

inline NodoTernario* ArbolBT::leer(std::string nombre_archivo) {
	NodoTernario* raiz;
	std::ifstream archivo(nombre_archivo.c_str());
	leer_recursivo(raiz, archivo);
	raiz_ = raiz;
	return raiz;
}

inline void ArbolBT::escribir_recursivo(NodoTernario* raiz, std::ostream& out) {
	if (raiz == nullptr) {
		out << "Vacio" << std::endl;
		return;
	}
	
	out << raiz->valor() << std::endl;
	escribir_recursivo(raiz->izquierda(), out);
	escribir_recursivo(raiz->medio(), out);
	escribir_recursivo(raiz->derecha(), out);
}

inline int ArbolBT::leer_recursivo(NodoTernario*& raiz, std::ifstream& in) {
	std::string linea;
	getline(in, linea);
	
	if (linea == "Vacio") {
		raiz = nullptr;
		return 0;
	}
	
	raiz = new NodoTernario(linea[0]);
	leer_recursivo(raiz->izquierda(),in);
	leer_recursivo(raiz->medio(), in);
	leer_recursivo(raiz->derecha(), in);
	return 0;
}

inline void ArbolBT::atravesar_recursivo(NodoTernario* raiz, std::function<void(char valor)> cb) {
	if (raiz != nullptr) {		
		atravesar_recursivo(raiz->izquierda(), cb);
		cb(raiz->valor());
		atravesar_recursivo(raiz->medio(), cb);
		atravesar_recursivo(raiz->derecha(), cb);
	}
}

inline void ArbolBT::insertar(std::string valor) {
	std::string insertar_valor = Ayudas::uppercase(valor);
	std::regex padre("[^a-z]");
	std::smatch sm;
	
	std::regex_replace(insertar_valor, padre, "");
	
	if (insertar_valor.empty()) {
		return;
	}
	
	if (raiz_ == nullptr) {
		raiz_ = new NodoTernario(insertar_valor[0]);
	}
	
	insertar_recursivo(raiz_, Ayudas::uppercase(valor));
}

inline NodoTernario* ArbolBT::encontrar(std::string valor) {
	valor = Ayudas::uppercase(valor);
	std::regex padre("[^a-z]");
	std::regex_replace(valor, padre, "");
	return encontrar_recursivo(raiz_, valor);
}

inline NodoTernario* ArbolBT::encontrar_recursivo(NodoTernario* arbol, std::string valor) {
	if (arbol == nullptr){
		return nullptr;
	}
	
	if (valor.length() == 0) {
		if (arbol->es_Palabra() == true) {
			return arbol;
		}else {
			return nullptr;
		}
	} else{
		NodoTernario* hijo = nullptr;
		
		if (arbol->valor() == ' ') {
			return nullptr;
		}
		
		if (arbol->valor() == valor.at(0)) {
			valor = valor.substr(1);
			hijo = arbol->medio();
		}
		else if (arbol->valor() > valor.at(0)) {
			hijo = arbol->izquierda();
		}
		else {
			hijo = arbol->derecha();
		}

		if (hijo != nullptr) {
			// ...
		}
		else {
			// ...
		}

		return encontrar_recursivo(hijo, valor);
	}			
}

inline void ArbolBT::limpieza_eliminacion(NodoTernario* arbol) {
	if (arbol == nullptr) {
		return;
	}
	else if (arbol->medio() == nullptr) {
		return;
	}
	else if (arbol->medio() == nullptr && arbol->derecha() == nullptr && arbol->izquierda() == nullptr && arbol->es_Palabra() == true) {
		return;
	}
	else if (arbol->medio() == nullptr && arbol->izquierda() == nullptr && arbol->derecha() == nullptr) {
		if (arbol->padre() == nullptr) {
			raiz_ = nullptr;
		}
		else if (arbol->padre()->izquierda() == arbol) {
			arbol->padre()->izquierda(nullptr);
		}
		else if (arbol->padre()->derecha() == arbol) {
			arbol->padre()->derecha(nullptr);
		}
		else if (arbol->padre()->medio() == arbol) {
			arbol->padre()->medio(nullptr);
		}

		limpieza_eliminacion(arbol->padre());
	}
	else if ((arbol->izquierda() == nullptr && arbol->medio() == nullptr) || (arbol->derecha() == nullptr && arbol->medio() == nullptr)) {
		NodoTernario* hijo = nullptr;

		if (arbol->izquierda() != nullptr) {
			hijo = arbol->izquierda();
		}
		else {
			hijo = arbol->derecha();
		}

		if (arbol->padre() == nullptr) {
			raiz_ = hijo;
		}
		else if (arbol->padre()->izquierda() == arbol) {
			arbol->padre()->izquierda(hijo);
			hijo->padre(arbol->padre());
		}
		else if (arbol->padre()->derecha() == arbol) {
			arbol->padre()->derecha(hijo);
			hijo->padre(arbol->padre());
		}
		else if (arbol->padre()->medio() == arbol) {
			hijo->padre(arbol->padre());
			arbol->padre()->medio(hijo);
		}
		else {
			// ...
		}
	}
	else if (arbol->derecha() != nullptr && arbol->medio() != nullptr && arbol->derecha() != nullptr) {
		NodoTernario* nodo = arbol->izquierda();
		NodoTernario* nodo = arbol->padre();

		while (nodo->derecha() != nullptr) {
			nodo = nodo->derecha();
		}

		if (arbol->izquierda() != nodo) {
			nodo->padre()->derecha(nodo->izquierda());

			if (nodo->izquierda() != nullptr) {
				nodo->izquierda()->padre(nodo->padre());
			}

			nodo->derecha(arbol->derecha());
			nodo->izquierda(arbol->izquierda());
			arbol->derecha()->padre(nodo);
			arbol->izquierda()->padre(nodo);
		}
		else {
			nodo->derecha(arbol->derecha());
			nodo->derecha()->padre(nodo);
		}

		nodo->padre(arbol->padre());

		if (nodo->padre() == nullptr) {
			raiz_ = nodo;
		}
		else {
			if (arbol->padre()->izquierda() == arbol) {
				arbol->padre()->izquierda(nodo);
				nodo->padre(arbol->padre());
			}
			else if (arbol->padre()->derecha() == arbol) {
				arbol->padre()->derecha(nodo);
				nodo->padre(arbol->padre());
			}
			else if (arbol->padre()->medio() == arbol) {
				arbol->padre()->medio(nodo);
				nodo->padre(arbol->padre());
			}
		}
	}
}

inline void ArbolBT::remover(std::string valor) {
	remover_recursivo(raiz_, valor, 0);
}

inline NodoTernario* ArbolBT::remover_recursivo(NodoTernario* nodo, std::string palabra, int posicion) {
	if (nodo == nullptr) {
		return nullptr;
	}

	int child = this->contar_hermanos(nodo);

	if (palabra[posicion] < nodo->valor()) {
		nodo->izquierda(this->remover_recursivo(nodo->izquierda(), palabra, posicion));
	}
	else if (palabra[posicion] > nodo->valor()) {
		nodo->right(this->remover_recursivo(nodo->derecha(), palabra, posicion));
	}
	else {
		if ((posicion + 1) < palabra.length()) {
			// When word not empty
			nodo->medio(this->remover_recursivo(nodo->medio(), palabra, posicion + 1));
		}
		else if (nodo->es_Palabra() == true) {
			if (child > 0) {
				// In case child node exist of deleted word
				nodo->es_Palabra(false);
			}
			else {
				delete nodo;
				return nullptr;
			}
		}
	}
	if (child != this->contar_hermanos(nodo) && child == 1 && nodo->es_Palabra() == false) {
		delete nodo;
		return nullptr;
	}

	return nodo;
}
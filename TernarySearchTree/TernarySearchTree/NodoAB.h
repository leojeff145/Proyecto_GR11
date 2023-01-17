#pragma once

#include <string>
#include <list>
#include <vector>
#include <memory>
#include <climits>
#include <iostream>

#define CALL_MEMBER_FN(object, ptrToMember) ((object).*(ptrToMember))

template <class T>
class NodoAB
{
public:
	typedef std::list<T*>(T::* hijosGetterF)(void);
	typedef std::string(T::* datoGetterF)    (void);
	static void inicioClase(hijosGetterF f1, datoGetterF f2);

private:
	static hijosGetterF hijosGetter;
	static datoGetterF	 datoGetter;

	std::list<T*> getHijos();
	std::string    getDato();

public:
	NodoAB(T* node);

	virtual ~NodoAB();

	void imprimirArbol(std::shared_ptr<NodoAB<T>> cabeza);

private:
	T* _nd;
	std::list<std::shared_ptr<NodoAB>> _hijos;
	std::size_t _profunidad;

	std::size_t _wself;
	std::size_t _whijo;
	std::size_t _wbloc;

	std::size_t _fcp;
	std::size_t _lcp;
	std::size_t _mcp;
	std::size_t _fbp;
	std::size_t _lbp;

	void calcProfundidad(std::size_t inicioProfundidad);
	std::size_t calcAncho();

	void gruposNodosProfundidad(std::vector<std::unique_ptr<std::list<std::shared_ptr<NodoAB>>>>& niveles, std::shared_ptr<NodoAB<T>> cabeza);
	std::size_t asignarPosicionNodos(std::size_t inicioBloque);

	void imprimirLinea(std::size_t ln, std::vector<std::unique_ptr<std::list<std::shared_ptr<NodoAB>>>>& niveles);
	void imprimirPrelinea(std::size_t ln, std::vector<std::unique_ptr<std::list<std::shared_ptr<NodoAB>>>>& niveles);

	std::size_t imprimirInicioNodoAT(std::size_t c, std::unique_ptr<std::list<std::shared_ptr<NodoAB>>>& nivel);
	std::size_t imprimirDatoNodo();

	bool CisPrimerCaracterPadre(std::size_t c, std::unique_ptr<std::list<std::shared_ptr<NodoAB>>>& nivel);
	bool CisEntreHijosyPadres(std::size_t c, std::unique_ptr<std::list<std::shared_ptr<NodoAB>>>& padre);
	bool CisCentroHijo(std::size_t c, std::unique_ptr<std::list<std::shared_ptr<NodoAB>>>& hijos);
	int posicionPadreDeHijo(std::size_t c, std::unique_ptr<std::list<std::shared_ptr<NodoAB>>>& padre, std::unique_ptr<std::list<std::shared_ptr<NodoAB>>>& hijos);


	void imprimirEspacio();
	void imprimirSubrayar();
	void imprimirHijosIzq();
	void imprimirHijosDer();
	void imprimirHijosVertical();

};

template <class T>
class ArbolBin
{
public:
	typedef std::list<T*>(T::* hijosGetterF)(void);
	typedef std::string(T::* datoGetterF)    (void);
	ArbolBin(T* cabeza, hijosGetterF f1, datoGetterF f2);
	void print();

private:
	std::shared_ptr<NodoAB<T>> _cabeza;
};

template <class T>
typename NodoAB<T>::hijosGetterF NodoAB<T>::hijosGetter = nullptr;

template <class T>
typename NodoAB<T>::datoGetterF NodoAB<T>::datoGetter = nullptr;

template <class T>
void NodoAB<T>::inicioClase(hijosGetterF f1, datoGetterF f2) {
	hijosGetter = f1;
	datoGetter = f2;
}

template <class T>
std::list<T*> NodoAB<T>::getHijos() {
	return CALL_MEMBER_FN(*_nd, hijosGetter)();
}

template <class T>
std::string NodoAB<T>::getDato() {
	return CALL_MEMBER_FN(*_nd, datoGetter)();
}


template <class T>
NodoAB<T>::NodoAB(T* node) {
	_nd = node;
	_profundidad = 0;

	_fcp = 0;
	_lcp = 0;
	_mcp = 0;

	_fbp = 0;
	_lbp = 0;

	_wself = getDato().length();
	_whijo = 0;
	_wbloc = 0;

	std::list<T*> ls = getHijos();
	for (auto& hijos : ls) {
		std::shared_ptr<NodoAB> newHijos(new NodoAB(hijos));
		_hijos.push_back(std::move(newHijos));
	}
}

template <class T>
NodoAB<T>::~NodoAB() {
}

template <class T>
void NodoAB<T>::imprimirArbol(std::shared_ptr<NodoAB<T>> cabeza) {

	calcProfundidad(0);
	calcAncho();

	std::vector<std::unique_ptr<std::list<std::shared_ptr<NodoAB>>>> niveles;
	gruposNodosProfundidad(niveles, cabeza);
	asignarPosicionNodos(0);
	imprimirLinea(0, niveles);

	for (std::size_t i = 1; i < niveles.size(); i++) {
		imprimirPrelinea(i, niveles);
		imprimirLinea(i, niveles);
	}
}

template <class T>
void NodoAB<T>::calcProfundidad(std::size_t inicioProfundidad) {
	_profundidad = inicioProfundidad;
	for (auto& hijo : _hijos) {
		hijo->calcProfundidad(inicioProfundidad + 1);
	}
}

template <class T>
std::size_t NodoAB<T>::calcAncho() {
	if (_hijos.empty()) {
		_whijo = 0;
	}
	else {
		_whijo += _hijos.front()->calcAncho();

		auto it = ++_hijos.begin();
		for (; it != _hijos.end(); ++it) {
			_whijo += 1;
			_whijo += (*it)->calcAncho();
		}
	}
	_wbloc = std::max(_wself, _whijo);
	return _wbloc;
}

template <class T>
void NodoAB<T>::gruposNodosProfundidad(std::vector<std::unique_ptr<std::list<std::shared_ptr<NodoAB>>>>& niveles, std::shared_ptr<NodoAB<T>> cabeza) {
	std::list<std::shared_ptr<NodoAB>> queue;
	std::shared_ptr<NodoAB> nd;

	queue.push_back(cabeza);

	while (!queue.empty()) {
		nd = queue.front();
		queue.pop_front();
		for (auto& hijo : nd->_hijos) {
			queue.push_back(hijo);
		}
		while (niveles.size() <= nd->_profundidad) {
			std::unique_ptr<std::list<std::shared_ptr<NodoAB>>> layer(new std::list<std::shared_ptr<NodoAB>>());
			niveles.push_back(std::move(layer));
		}
		niveles[nd->_profundidad]->push_back(nd);
	}
}

template <class T>
std::size_t NodoAB<T>::asignarPosicionNodos(std::size_t inicioBloque) {
	_fbp = inicioBloque;
	_lbp = inicioBloque + _wbloc - 1;

	if (_wself >= _whijo) {
		_fcp = inicioBloque + (_wbloc - _wself) / 2;
		_lcp = _fcp + _wself - 1;
		_mcp = (_fcp + _lcp) / 2;

		std::size_t inicioBloqueHijos = inicioBloque + (_wbloc - _whijo) / 2;
		for (std::shared_ptr<NodoAB>& nd : _hijos) {
			inicioBloqueHijos = nd->asignarPosicionNodos(inicioBloqueHijos);
		}
	}
	else {
		std::size_t inicioBloqueHijos = inicioBloque + (_wbloc - _whijo) / 2;
		for (std::shared_ptr<NodoAB>& nd : _hijos) {
			inicioBloqueHijos = nd->asignarPosicionNodos(inicioBloqueHijos);
		}

		_mcp = (_hijos.front()->_mcp + _hijos.back()->_mcp) / 2;
		_fcp = _mcp - (_wself - 1) / 2; // left aligning;
		_lcp = _fcp + _wself - 1;
	}

	return inicioBloque + _wbloc + 1;
}

template <class T>
void NodoAB<T>::imprimirLinea(std::size_t ln, std::vector<std::unique_ptr<std::list<std::shared_ptr<NodoAB>>>>& niveles) {
	for (std::size_t c = 0; c < _wbloc; c++) {
		if (CisPrimerCaracterPadre(c, niveles[ln])) {
			c += imprimirInicioNodoAT(c, niveles[ln]) - 1;
		}
		else if (CisEntreHijosyPadres(c, niveles[ln])) {
			imprimirSubrayar();
		}
		else {
			imprimirEspacio();
		}
	}
	std::cout << std::endl;
}

template <class T>
void NodoAB<T>::imprimirPrelinea(std::size_t ln, std::vector<std::unique_ptr<std::list<std::shared_ptr<NodoAB>>>>& niveles) {
	for (std::size_t c = 0; c < _wbloc; c++) {
		if (CisCentroHijo(c, niveles[ln])) {
			switch (posicionPadreDeHijo(c, niveles[ln - 1], niveles[ln])) {
			case -1:
				imprimirHijosIzq();
				break;
			case 0:
				imprimirHijosVertical();
				break;
			case 1:
				imprimirHijosDer();
				break;
			}
		}
		else {
			imprimirEspacio();
		}
	}
	std::cout << std::endl;
}

template <class T>
bool NodoAB<T>::CisPrimerCaracterPadre(std::size_t c, std::unique_ptr<std::list<std::shared_ptr<NodoAB>>>& nivel) {
	for (std::shared_ptr<NodoAB>& nd : *nivel) {
		if (nd->_fcp == c)
			return true;
	}
	return false;
}

template <class T>
std::size_t NodoAB<T>::imprimirInicioNodoAT(std::size_t c, std::unique_ptr<std::list<std::shared_ptr<NodoAB>>>& nivel) {
	for (std::shared_ptr<NodoAB>& nd : *nivel) {
		if (nd->_fcp == c) {
			return nd->imprimirDatoNodo();
		}
	}
	return 0;
}

template <class T>
bool NodoAB<T>::CisEntreHijosyPadres(std::size_t c, std::unique_ptr<std::list<std::shared_ptr<NodoAB>>>& padre) {
	for (std::shared_ptr<NodoAB>& nd : *padre) {
		if (nd->_hijos.empty()) {
			continue;
		}
		std::size_t minCp = nd->_hijos.front()->_mcp;
		std::size_t maxCp = nd->_hijos.back()->_mcp;
		if (c > minCp && c < maxCp)
			return true;
	}
	return false;
}

template <class T>
bool NodoAB<T>::CisCentroHijo(std::size_t c, std::unique_ptr<std::list<std::shared_ptr<NodoAB>>>& hijos) {
	for (std::shared_ptr<NodoAB>& nd : *hijos) {
		if (nd->_mcp == c)
			return true;
	}
	return false;
}

template <class T>
int NodoAB<T>::posicionPadreDeHijo(std::size_t c, std::unique_ptr<std::list<std::shared_ptr<NodoAB>>>& padre, std::unique_ptr<std::list<std::shared_ptr<NodoAB>>>& hijos) {
	std::shared_ptr<NodoAB> pa = nullptr;
	std::shared_ptr<NodoAB> hij = nullptr;
	for (std::shared_ptr<NodoAB>& nd : *padre) {
		if ((c >= nd->_fbp) && (c <= nd->_lbp)) {
			pa = nd;
		}
	}
	for (auto& nd : *hijos) {
		if ((c >= nd->_fbp) && (c <= nd->_lbp)) {
			hij = nd;
		}
	}

	if (hij->_mcp < pa->_mcp)
		return -1;
	else if (hij->_mcp == pa->_mcp)
		return 0;
	else
		return 1;
}

template <class T>
std::size_t NodoAB<T>::imprimirDatoNodo() {
	std::cout << getDato();
	return _wself;
}

template <class T>
void NodoAB<T>::imprimirEspacio() {
	std::cout << " ";
}

template <class T>
void NodoAB<T>::imprimirSubrayar() {
	std::cout << "_";
}

template <class T>
void NodoAB<T>::imprimirHijosIzq() {
	std::cout << "/";
}

template <class T>
void NodoAB<T>::imprimirHijosDer() {
	std::cout << "\\";
}

template <class T>
void NodoAB<T>::imprimirHijosVertical() {
	std::cout << "|";
}

template <class T>
ArbolBin<T>::ArbolBin(T* cabeza, hijosGetterF f1, datoGetterF f2) {
	NodoAB<T>::inicioClase(f1, f2);
	_cabeza = std::shared_ptr<NodoAB<T>>(new NodoAB<T>(cabeza));
}

template <class T>
void ArbolBin<T>::print() {
	_cabeza->imprimirArbol(_cabeza);
}

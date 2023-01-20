#pragma once

#include <string>
#include <list>
#include <vector>
#include <memory>
#include <climits>
#include <iostream>

#define CALL_MEMBER_FN(object, ptrToMember) ((object).*(ptrToMember))

template <class T>
class NodoArbolBinario
{
  public:
	typedef std::list<T*> (T::*hijoGetterFcn)( void);
	typedef std::string   (T::*datoGetterFcn)    ( void);
	static void inicializarClase(hijoGetterFcn f1, datoGetterFcn f2);

  private:
	static hijoGetterFcn hijoGetter;
	static datoGetterFcn	 datoGetter;

	std::list<T *> getHijo();
	std::string    getDato();
    
  public:
	NodoArbolBinario(T* node);

	virtual ~NodoArbolBinario();

	void printTree(std::shared_ptr<NodoArbolBinario<T>> thisHead);

  private:
	T * _nd;
	std::list<std::shared_ptr<NodoArbolBinario>> _hijo;
	std::size_t _profundidad;

	std::size_t _wser;
	std::size_t _wchijo;
	std::size_t _wbloque;

	std::size_t _fcp;
	std::size_t _lcp;
	std::size_t _mcp;
	std::size_t _fbp;
	std::size_t _lbp;

	void calcProfundidad(std::size_t profundidadInicial);
	std::size_t calcAncho();

	void agruparNodosPorProfundidad(std::vector<std::unique_ptr<std::list<std::shared_ptr<NodoArbolBinario>>>> & niveles, std::shared_ptr<NodoArbolBinario<T>> estaCabeza);
	std::size_t cambiarPosicionesNodos(std::size_t blockStart);
	
	void imprimirLinea(std::size_t ln,    std::vector<std::unique_ptr<std::list<std::shared_ptr<NodoArbolBinario>>>> & niveles);
	void printPreline(std::size_t ln, std::vector<std::unique_ptr<std::list<std::shared_ptr<NodoArbolBinario>>>> & niveles);
	
	std::size_t printNodeStartingAt(std::size_t c, std::unique_ptr<std::list<std::shared_ptr<NodoArbolBinario>>> & niveles);
	std::size_t printNodeData();
	
	bool CisParentFirstCharacter(std::size_t c, std::unique_ptr<std::list<std::shared_ptr<NodoArbolBinario>>> & nivel);
	bool CisBetweenChildrenAndParent(std::size_t c, std::unique_ptr<std::list<std::shared_ptr<NodoArbolBinario>>> & padre);
	bool CisCenterChildren(std::size_t c, std::unique_ptr<std::list<std::shared_ptr<NodoArbolBinario>>> & hijo);
	int parentPositionRelToChildren(std::size_t c, std::unique_ptr<std::list<std::shared_ptr<NodoArbolBinario>>> & padre, std::unique_ptr<std::list<std::shared_ptr<NodoArbolBinario>>> & hijo);
	
	
	void printSpace();
	void printUnderscore();
	void printLeftChildren();
	void printRightChildren();
	void printVerticalChildren();

};

template <class T>
class BTTree
{
  public:
	typedef std::list<T*> (T::*hijoGetterFcn)( void);
	typedef std::string   (T::*datoGetterFcn)    ( void);
	BTTree(T* head, hijoGetterFcn f1, datoGetterFcn f2);
	void print();

  private:
	std::shared_ptr<NodoArbolBinario<T>> _head;
};

template <class T>
typename NodoArbolBinario<T>::hijoGetterFcn NodoArbolBinario<T>::hijoGetter = nullptr;

template <class T>
typename NodoArbolBinario<T>::datoGetterFcn NodoArbolBinario<T>::datoGetter = nullptr;

template <class T>
void NodoArbolBinario<T>::inicializarClase(hijoGetterFcn f1, datoGetterFcn f2) {
	hijoGetter = f1;
	datoGetter = f2;
}

template <class T>
std::list<T*> NodoArbolBinario<T>::getHijo() {
	return CALL_MEMBER_FN(*_nd, hijoGetter)();
}

template <class T>
std::string NodoArbolBinario<T>::getDato() {
	return CALL_MEMBER_FN(*_nd, datoGetter)();
}


template <class T>
NodoArbolBinario<T>::NodoArbolBinario(T* node) {
	_nd = node;
	_profundidad = 0;

	_fcp = 0;
	_lcp = 0;
	_mcp = 0;

	_fbp = 0;
	_lbp = 0;

	_wser = getDato().length();
	_wchijo = 0;
	_wbloque = 0;

	std::list<T*> ls = getHijo();
	for (auto& child : ls) {
		std::shared_ptr<NodoArbolBinario> newChild(new NodoArbolBinario(child));
		_hijo.push_back(std::move(newChild));
	}
}

template <class T>
NodoArbolBinario<T>::~NodoArbolBinario() {
}

template <class T>
void NodoArbolBinario<T>::printTree(std::shared_ptr<NodoArbolBinario<T>> thisHead) {

	calcProfundidad(0);
	calcAncho();

	std::vector<std::unique_ptr<std::list<std::shared_ptr<NodoArbolBinario>>>> levels;
	agruparNodosPorProfundidad(levels, thisHead);
	cambiarPosicionesNodos(0);
	imprimirLinea(0, levels);

	for (std::size_t i = 1; i < levels.size(); i++) {
		printPreline(i, levels);
		imprimirLinea(i, levels);
	}
}

template <class T>
void NodoArbolBinario<T>::calcProfundidad(std::size_t initialDepth) {
	_profundidad = initialDepth;
	for (auto& child : _hijo) {
		child->calcProfundidad(initialDepth + 1);
	}
}

template <class T>
std::size_t NodoArbolBinario<T>::calcAncho() {
	if (_hijo.empty()) {
		_wchijo = 0;
	} else {
		_wchijo += _hijo.front()->calcAncho();

		auto it = ++_hijo.begin();
		for (; it != _hijo.end(); ++it) {
			_wchijo += 1;
			_wchijo += (*it)->calcAncho();
		}
	}
	_wbloque = std::max(_wser, _wchijo);
	return _wbloque;
}

template <class T>
void NodoArbolBinario<T>::agruparNodosPorProfundidad(std::vector<std::unique_ptr<std::list<std::shared_ptr<NodoArbolBinario>>>>& levels, std::shared_ptr<NodoArbolBinario<T>> thisHead) {
	std::list<std::shared_ptr<NodoArbolBinario>> queue;
	std::shared_ptr<NodoArbolBinario> nd;

	queue.push_back(thisHead);

	while (!queue.empty()) {
		nd = queue.front();
		queue.pop_front();
		for (auto& child : nd->_hijo) {
			queue.push_back(child);
		}
		while (levels.size() <= nd->_profundidad) {
			std::unique_ptr<std::list<std::shared_ptr<NodoArbolBinario>>> layer(new std::list<std::shared_ptr<NodoArbolBinario>>());
			levels.push_back(std::move(layer));
		}
		levels[nd->_profundidad]->push_back(nd);
	}
}

template <class T>
std::size_t NodoArbolBinario<T>::cambiarPosicionesNodos(std::size_t blockStart) {
	_fbp = blockStart;
	_lbp = blockStart + _wbloque - 1;

	if (_wser >= _wchijo) {
		_fcp = blockStart + (_wbloque - _wser) / 2;
		_lcp = _fcp + _wser - 1;
		_mcp = (_fcp + _lcp) / 2; // left aligning;

		std::size_t childrenBlockStart = blockStart + (_wbloque - _wchijo) / 2;
		for (std::shared_ptr<NodoArbolBinario>& nd : _hijo) {
			childrenBlockStart = nd->cambiarPosicionesNodos(childrenBlockStart);
		}
	} else {
		std::size_t childrenBlockStart = blockStart + (_wbloque - _wchijo) / 2;
		for (std::shared_ptr<NodoArbolBinario>& nd : _hijo) {
			childrenBlockStart = nd->cambiarPosicionesNodos(childrenBlockStart);
		}

		_mcp = (_hijo.front()->_mcp + _hijo.back()->_mcp) / 2;
		_fcp = _mcp - (_wser - 1) / 2; // left aligning;
		_lcp = _fcp + _wser - 1;
	}

	return blockStart + _wbloque + 1;
}

template <class T>
void NodoArbolBinario<T>::imprimirLinea(std::size_t ln, std::vector<std::unique_ptr<std::list<std::shared_ptr<NodoArbolBinario>>>>& levels) {
	for (std::size_t c = 0; c < _wbloque; c++) {
		if (CisParentFirstCharacter(c, levels[ln])) {
			c += printNodeStartingAt(c, levels[ln]) - 1;
		} else if (CisBetweenChildrenAndParent(c, levels[ln])) {
			printUnderscore();
		} else {
			printSpace();
		}
	}
	std::cout << std::endl;
}

template <class T>
void NodoArbolBinario<T>::printPreline(std::size_t ln, std::vector<std::unique_ptr<std::list<std::shared_ptr<NodoArbolBinario>>>>& levels) {
	for (std::size_t c = 0; c < _wbloque; c++) {
		if (CisCenterChildren(c, levels[ln])) {
			switch (parentPositionRelToChildren(c, levels[ln - 1], levels[ln])) {
			case -1:
				printLeftChildren();
				break;
			case 0:
				printVerticalChildren();
				break;
			case 1:
				printRightChildren();
				break;
			}
		} else {
			printSpace();
		}
	}
	std::cout << std::endl;
}

template <class T>
bool NodoArbolBinario<T>::CisParentFirstCharacter(std::size_t c, std::unique_ptr<std::list<std::shared_ptr<NodoArbolBinario>>>& level) {
	for (std::shared_ptr<NodoArbolBinario>& nd : *level) {
		if (nd->_fcp == c)
			return true;
	}
	return false;
}

template <class T>
std::size_t NodoArbolBinario<T>::printNodeStartingAt(std::size_t c, std::unique_ptr<std::list<std::shared_ptr<NodoArbolBinario>>>& level) {
	for (std::shared_ptr<NodoArbolBinario>& nd : *level) {
		if (nd->_fcp == c) {
			return nd->printNodeData();
		}
	}
	return 0;
}

template <class T>
bool NodoArbolBinario<T>::CisBetweenChildrenAndParent(std::size_t c, std::unique_ptr<std::list<std::shared_ptr<NodoArbolBinario>>>& parent) {
	for (std::shared_ptr<NodoArbolBinario>& nd : *parent) {
		if (nd->_hijo.empty()) {
			continue;
		}
		std::size_t minCp = nd->_hijo.front()->_mcp;
		std::size_t maxCp = nd->_hijo.back()->_mcp;
		if (c > minCp && c < maxCp)
			return true;
	}
	return false;
}

template <class T>
bool NodoArbolBinario<T>::CisCenterChildren(std::size_t c, std::unique_ptr<std::list<std::shared_ptr<NodoArbolBinario>>>& children) {
	for (std::shared_ptr<NodoArbolBinario>& nd : *children) {
		if (nd->_mcp == c)
			return true;
	}
	return false;
}

template <class T>
int NodoArbolBinario<T>::parentPositionRelToChildren(std::size_t c, std::unique_ptr<std::list<std::shared_ptr<NodoArbolBinario>>>& parent, std::unique_ptr<std::list<std::shared_ptr<NodoArbolBinario>>>& children) {
	std::shared_ptr<NodoArbolBinario> dad = nullptr;
	std::shared_ptr<NodoArbolBinario> kid = nullptr;
	for (std::shared_ptr<NodoArbolBinario>& nd : *parent) {
		if ((c >= nd->_fbp) && (c <= nd->_lbp)) {
			dad = nd;
		}
	}
	for (auto& nd : *children) {
		if ((c >= nd->_fbp) && (c <= nd->_lbp)) {
			kid = nd;
		}
	}

	if (kid->_mcp < dad->_mcp)
		return -1;
	else if (kid->_mcp == dad->_mcp)
		return 0;
	else
		return 1;
}

template <class T>
std::size_t NodoArbolBinario<T>::printNodeData() {
	std::cout << getDato();
	return _wser;
}

template <class T>
void NodoArbolBinario<T>::printSpace() {
	std::cout << " ";
}

template <class T>
void NodoArbolBinario<T>::printUnderscore() {
	std::cout << "_";
}

template <class T>
void NodoArbolBinario<T>::printLeftChildren() {
	std::cout << "/";
}

template <class T>
void NodoArbolBinario<T>::printRightChildren() {
	std::cout << "\\";
}

template <class T>
void NodoArbolBinario<T>::printVerticalChildren() {
	std::cout << "|";
}

template <class T>
BTTree<T>::BTTree(T* head, hijoGetterFcn f1, datoGetterFcn f2) {
	NodoArbolBinario<T>::inicializarClase(f1, f2);
	_head = std::shared_ptr<NodoArbolBinario<T>>(new NodoArbolBinario<T>(head));
}

template <class T>
void BTTree<T>::print() {
	_head->printTree(_head);
}

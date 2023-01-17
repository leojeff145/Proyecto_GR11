#pragma once
#include "Nodo.h"
#include <functional>
#include <optional>
#include <stdexcept>
#include <exception>

template<typename T>
class CDLlist {
public:
	CDLlist() = default;

	Nodo<T>* nAct(int actual);
	void retroceder(const T& valor);
	void adelantar(const T& valor);
	void posicion_actual(int actual, const T& valor);
	void eliminar_actual(int actual);
	void eliminar(std::function<bool(T)> devolver);
	void eliminar_todo(std::function<bool(T)> devolver);
	bool contener(const T& valor);

	void paraCada(std::function<void(Nodo<T>*, int)> devolver);
	void paraCada(std::function<void(Nodo<T>*)> devolver);
	void paraCada(std::function<void(T, int)> devolver);
	void paraCada(std::function<void(T)> devolver);

	void hasta(std::function<bool(Nodo<T>*)> devolver);
	void hasta(std::function<bool(T)> devolver);

	std::optional<T> buscar(std::function<bool(Nodo<T>*, int)> devolver);
	std::optional<T> buscar(std::function<bool(Nodo<T>*)> devolver);
	std::optional<T> buscar(std::function<bool(T, int)> devolver);
	std::optional<T> buscar(std::function<bool(T)> devolver);

	void limpiar();
	int tamano();
	bool vacio();

private:
	Nodo<T>* cola();
	Nodo<T>* cabeza = nullptr;
	int _tamano = 0;
};

template <typename T>
void CDLlist<T>::retroceder(const T& valor) {
	if (cabeza == nullptr) {
		cabeza = new Nodo<T>(valor);
		cabeza->set_siguiente(cabeza);
		cabeza->set_anterior(cabeza);
		_tamano++;
		return;
	}

	Nodo<T>* anterior_nodo = cola();
	Nodo<T>* nodo = new Nodo<T>(valor);

	anterior_nodo->set_siguiente(nodo);
	nodo->set_anterior(anterior_nodo);
	nodo->set_siguiente(cabeza);
	cabeza->set_anterior(nodo);
	_tamano++;
}

template <typename T>
void CDLlist<T>::adelantar(const T& valor) {
	if (cabeza == nullptr) {
		return retroceder(valor);
	}

	Nodo<T>* nodo = new Nodo<T>(valor);
	Nodo<T>* temp = cabeza;

	cabeza = nodo;
	cabeza->set_siguiente(temp);
	cabeza->set_anterior(temp->get_anterior());
	temp->get_anterior()->set_siguiente(cabeza);
	temp->set_anterior(cabeza);
	_tamano++;
}

template <typename T>
void CDLlist<T>::posicion_actual(int actual, const T& valor) {
	if (actual < 0 || actual > _tamano) {
		throw std::invalid_argument("Índice fuera de los límites");
	}

	if (actual == 0 || _tamano == 0) {
		return adelantar(valor);
	}
	else if (actual == _tamano) {
		return retroceder(valor);
	}

	Nodo<T>* seleccion = nAct(actual);
	Nodo<T>* anterior = seleccion->get_anterior();
	Nodo<T>* siguiente = seleccion->get_siguiente();
	Nodo<T>* nodo = new Nodo<T>(valor);

	anterior->set_siguiente(nodo);
	nodo->set_siguiente(seleccion);
	nodo->set_anterior(anterior);
	seleccion->set_anterior(nodo);
	_tamano++;
}

template <typename T>
void CDLlist<T>::eliminar_actual(int actual) {
	if (actual < 0 || actual >= _tamano) {
		throw std::invalid_argument("Índice fuera de los límites");
	}
	if (actual == 0) {
		Nodo<T>* temp = cabeza;
		cabeza = cabeza->get_siguiente();
		cabeza->set_anterior(temp->get_anterior());
		temp->get_anterior()->set_siguiente(cabeza);
		delete temp;
	}
	else if (actual == _tamano - 1) {
		Nodo<T>* nodo = cola();
		Nodo<T>* anterior = nodo->get_anterior();
		anterior->set_siguiente(cabeza);
		cabeza->set_anterior(anterior);
		delete nodo;
	}
	else {
		Nodo<T>* seleccion = nAct(actual);
		Nodo<T>* anterior = seleccion->get_anterior();
		Nodo<T>* siguiente = seleccion->get_siguiente();

		anterior->set_siguiente(siguiente);
		siguiente->set_anterior(anterior);
		delete seleccion;
	}

	_tamano--;
}

template <typename T>
inline void CDLlist<T>::eliminar(std::function<bool(T)> devolver) {
	Nodo<T>* act = cabeza;
	int actual = 0;

	if (act == nullptr) {
		return;
	}
	while (true) {
		if (actual > 0 && act == cabeza) {
			break;
		}
		if (devolver(act->get_dato()) {
			eliminar_actual(actual);
				break;
		}
		act = act->get_siguiente();
			actual++;
	}
}

template <typename T>
inline void CDLlist<T>::eliminar_todo(std::function<bool(T)> devolver) {
	while (find(devolver).has_value()) {
		eliminar(devolver);
	}
}

template <typename T>
inline bool CDLlist<T>::contener(const T& valor) {
	return find([valor](int n) {return n == valor; }).has_value();
}

template <typename T>
void CDLlist<T>::paraCada(std::function<void(Nodo<T>*, int)> devolver) {
	Nodo<T>* act = cabeza;
	int actual = 0;

	if (actual == nullptr) {
		return;
	}do {
		devolver(act, actual);
		act = act->get_siguiente();
		actual++;
	} while (act != cabeza);
}

template <typename T>
void CDLlist<T>::paraCada(std::function<void(T, int)> devolver) {
	paraCada([&](Nodo<T>* nodo, int actual) {
		devolver(nodo->get_dato(), actual);
		});
}

template <typename T>
void CDLlist<T>::paraCada(std::function<void(T)> devolver) {
	paraCada([&](Nodo<T>* nodo, int actual) {
		devolver(nodo->get_dato());
		});
}

template <typename T>
void CDLlist<T>::paraCada(std::function<void(Nodo<T>*)> devolver) {
	paraCada([&](Nodo<T>* nodo, int actual) {
		devolver(nodo->get_dato());
		});
}

template <typename T>
void CDLlist<T>::hasta(std::function<bool(Nodo<T>*)> devolver) {
	Nodo<T>* act = cabeza;
	int actual = 0;

	if (act == nullptr) {
		return;
	}
	while (true) {
		if (actual > 0 && act == cabeza) {
			break;
		}
		if (!devolver(act))
			break;
		act = act->get_siguiente();
		actual++;
	}

}

template <typename T>
void CDLlist<T>::hasta(std::function<bool(T)> devolver) {
	hasta([&](Nodo<T>* nodo) {
		return devolver(nodo->get_dato());
		});
}

template <typename T>
std::optional<T> CDLlist<T>::buscar(std::function<bool(Nodo<T>*, int)> devolver) {
	Nodo<T>* act = cabeza;
	int actual = 0;

	if (act == nullptr) {
		return std::nullopt;
	}
	while (true) {
		if (actual > 0 && act == cabeza) {
			break;
		}
		if (devolver(act, actual++)) {
			return act->get_dato();
		}
		act = act->get_siguiente();
	}
	return std::nullopt;
}

template <typename T>
std::optional<T> CDLlist<T>::buscar(std::function<bool(Nodo<T>*)> devolver) {
	return buscar([&](Nodo<T>* nodo, int actual) -> bool {
		return devolver(nodo->get_dato());
		});
}

template <typename T>
std::optional<T> CDLlist<T>::buscar(std::function<bool(T, int)> devolver) {
	return buscar([&](Nodo<T>* nodo, int actual) -> bool {
		return devolver(nodo->get_dato(), actual);
		});
}

template <typename T>
std::optional<T> CDLlist<T>::buscar(std::function<bool(T)> devolver) {
	return buscar([&](Nodo<T>* nodo, int actual) -> bool {
		return devolver(nodo->get_dato());
		});
}

template <typename T>
void CDLlist<T>::limpiar() {
	while (!vacio()) {
		eliminar_actual(0);
	}
}

template <typename T>
int CDLlist<T>::tamano() {
	return _tamano;
}

template <typename T>
bool CDLlist<T>::vacio() {
	return _tamano == 0;
}

template <typename T>
Nodo<T>* CDLlist<T>::cola() {
	if (_tamano == 0) {
		return nullptr;
	}
	return nAct(_tamano - 1);
}

template <typename T>
Nodo<T>* CDLlist<T>::nAct(int actual) {
	if (actual < 0 || actual >= _tamano) {
		throw std::invalid_argument("Indice fuera de rango");
	}
	if (actual == 0) {
		return cabeza;
	}

	int actual_indice = 0;
	Nodo<T>* act = cabeza;
	while (true) {
		if (actual_indice > 0 && actual == cabeza) {
			break;
		}
		if (actual_indice == actual) {
			return act;
		}
		actual_indice++;
		act = act->get_siguiente();
	}
	return act;
}
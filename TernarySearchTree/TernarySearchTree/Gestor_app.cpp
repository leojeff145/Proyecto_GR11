#include "Gestor_app.h"
#include "Menu.h"
#include "Titulo.h"
#include "Gestor_Confirmacion.h"
#include "Validaciones.h"
#include <Windows.h>
#include <filesystem>
#pragma execution_character_set( "utf-8" )

int Gestor_app::iniciar() {
    SetConsoleOutputCP(65001);

}

void Gestor_app::correr() {
	Menu menu("Menu principal");
	menu.add_opciones(MenuOpciones("Arbol Ternario", [&]() {
		menu_opArbol();
		}, false));
	menu.add_opciones(MenuOpciones("Generar PDF", [&]() {
		generarPDF();
		}));
	menu.add_opciones(MenuOpciones("Ayuda", [&]() {
		ShellExecuteA(NULL, "open", "manual.chm", NULL, NULL, SW_SHOW);
		}));
	menu.add_opciones(menu.opciones_salir("Salir"));
	menu.mostrar();
}

void Gestor_app::generarPDF() {
	time_t tiempo = time(0);
	struct tm* nuevo = localtime(&tiempo);
	std::string tiempot = std::to_string(nuevo->tm_year + 1900) + std::to_string(nuevo->tm_mon + 1) + std::to_string(nuevo->tm_mday) + std::to_string(nuevo->tm_hour) + std::to_string(nuevo->tm_min) + std::to_string(nuevo->tm_sec);
	std::stringstream ss;
	
	ss  << std::setfill('0') << std::setw(2) << nuevo->tm_mday << "-"
		<< std::setfill('0') << std::setw(2) << nuevo->tm_mon + 1 << "-"
		<< std::setfill('0') << std::setw(4) << nuevo->tm_year + 1900 << "-"
		<< std::setfill('0') << std::setw(2) << nuevo->tm_hour + 1 << ":" << std::setw(2) << nuevo->tm_min;
	
	std::string subfijo = tiempot;
	std::string insertar = "doc_" + subfijo + ".html";
	std::string extraer = "reporte_" + subfijo + ".pdf";
	std::ofstream enArchivo(insertar);
	std::stringstream enBusca;

	enBusca << "<html><body><h1 style=\"text-align: center\">Universidad de las fuerzas armadas ESPE</h1><br><h2>Arbol ternario - Reporte</h2><br>";
	enBusca << "<strong>Fecha:  </strong>" << ss.str() << "<br><br><br>";
	enBusca	<< "<strong>Ternary search tree inorder: </strong> ";

	arbol->atravesar([&enBusca](char c) {
		enBusca << "<strong style=\"background:#ddd; padding: 4px; margin-right: 5px\">" << c << "</strong>";
		});
	
	enBusca << "</body><html>";
	enArchivo << enBusca.str();
	enArchivo.close();

	system((std::string("pdf ./") + insertar + "./" +extraer).c_str());
}

void Gestor_app::menu_opArbol() {
	Menu menu("Arbol Ternario");

	menu.add_opciones(MenuOpciones("insertar", [&]() {
		std::string valor = Validaciones::leer_con_formato("ingrese un valor: ", "[a-z]+");
	arbol->insertar(valor);

	std::cout << std::endl;
	arbol->imprimir();
		}));
	menu.add_opciones(MenuOpciones("buscar", [&]() {
		std::string valor = Validaciones::leer_con_formato("ingrese un valor: ", "[a-z]+");
	NodoTernario* encontrado = arbol->encontrar(valor);

	if (encontrado != nullptr) {
		std::cout << "el valor '" << valor << "' fue encontrado" << std::endl << std::endl;
		arbol->imprimir();
	}
	else {
		std::cout << "el valor '" << valor << "' no fue encontrado" << std::endl << std::endl;
	}
		}));

	menu.add_opciones(MenuOpciones("eliminar", [&]() {
			std::string valor = Validaciones::leer_con_formato("ingrese un valor: ", "[a-z]+");
		NodoTernario* encontrado = arbol->encontrar(valor);

		if (encontrado != nullptr) {
			arbol->remover(valor);
			arbol->imprimir();
		}
		else {
			std::cout << "el valor '" << valor << "' no fue encontrado" << std::endl << std::endl;
		}
		}));

	menu.add_opciones(MenuOpciones("Imprimir inorden", [&]() {
			arbol->atravesar([](char v) {
				std::cout << v << " -> ";
				});
		}));

	menu.add_opciones(MenuOpciones("Imprimir", [&]() {
			arbol->imprimir();
		}));

	menu.add_opciones(menu.opciones_salir("Salir"));
	menu.mostrar();
}
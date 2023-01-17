#pragma once
#include "CDLlist.h"
#include "ArbolBT.h"

class Gestor_app{
	public:
        Gestor_app() {
            arbol = new ArbolBT();
        }

        static int iniciar();
        void correr();
        void generarPDF();
        void pixelar_imagen();
        void guardar_copia();
        void cargar_copia();
        void menu_opcion_arbol();

      private:
        ArbolBT* arbol;
};


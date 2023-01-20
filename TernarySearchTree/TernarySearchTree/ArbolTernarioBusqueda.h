#pragma once
#include "NodoTernario.h"
#include "Ayuda.h"
#include "NodoArbolBinario.h"
#include "NodoBasico.h"
#include <regex>
#include <string>
#include <iostream>
#include <functional>
#include <fstream>

class ArbolTernarioBusqueda {
public:
	void insert(std::string valor);
	void remove(std::string valor);
	NodoTernario* find(std::string valor);
	void print();
	void traverse(std::function<void(char value)> cb);
	void write(std::ostream& out);
	NodoTernario* read(std::string filename);

private:
	void write_recursive(NodoTernario* p, std::ostream& out);
	int read_recursive(NodoTernario*& root, std::ifstream& in);
	void traverse_recursive(NodoTernario* root, std::function<void(char value)> cb);
	void insert_recursive(NodoTernario* tree, std::string value);
	NodoTernario* find_recursive(NodoTernario*& tree, std::string value);
	NodoTernario* remove_recursive(NodoTernario* node, std::string word, int position);

	void cleanup_delete(NodoTernario* node);
	NodoTernario* create_if_not_extant(NodoTernario* tree, NodoTernario*& child, std::string label);
	void print_util(NodoTernario* root, char* buffer, int depth, NodoBasico* head);

	int count_siblings(NodoTernario* node) {
		int count = 0;

		if (node->left() != nullptr) {
			count++;
		}
		if (node->right() != nullptr) {
			count++;
		}
		if (node->middle() != nullptr) {
			count++;
		}
		return count;
	}

	NodoTernario* raiz_ = nullptr;
};

inline void ArbolTernarioBusqueda::traverse(std::function<void(char value)> cb) {
	traverse_recursive(raiz_, cb);
}

inline void ArbolTernarioBusqueda::write(std::ostream& out) {
	write_recursive(raiz_, out);
}

inline NodoTernario* ArbolTernarioBusqueda::read(std::string filename) {
	NodoTernario* root;
	std::ifstream file(filename.c_str());
	read_recursive(root, file);
	raiz_ = root;
	return root;
}

inline void ArbolTernarioBusqueda::write_recursive(NodoTernario* root, std::ostream& out) {
	if (root == nullptr) {
		out << "null" << std::endl;
		return;
	}

	out << root->value() << std::endl;
	write_recursive(root->left(), out);
	write_recursive(root->middle(), out);
	write_recursive(root->right(), out);
}

inline int ArbolTernarioBusqueda::read_recursive(NodoTernario*& root, std::ifstream& in) {
	std::string line;
	getline(in, line);

	if (line == "null") {
		root = nullptr;
		return 0;
	}

	root = new NodoTernario(line[0]);
	read_recursive(root->left(), in);
	read_recursive(root->middle(), in);
	read_recursive(root->right(), in);

	return 0;
}

inline void ArbolTernarioBusqueda::traverse_recursive(NodoTernario* root, std::function<void(char value)> cb) {
	if (root != nullptr) {
		traverse_recursive(root->left(), cb);
		cb(root->value());
		traverse_recursive(root->middle(), cb);
		traverse_recursive(root->right(), cb);
	}
}

inline void ArbolTernarioBusqueda::insert(std::string value) {
	std::string inserted_value = Ayuda::uppercase(value);
	std::regex pattern("[^a-z]");
	std::smatch sm;

	std::regex_replace(inserted_value, pattern, "");

	if (inserted_value.empty()) {
		return;
	}

	if (raiz_ == nullptr) {
		raiz_ = new NodoTernario(' ');
	}

	insert_recursive(raiz_, Ayuda::uppercase(value));
}

inline NodoTernario* ArbolTernarioBusqueda::find(std::string value) {
	value = Ayuda::uppercase(value);
	std::regex pattern("[^a-z]");
	std::regex_replace(value, pattern, "");
	return find_recursive(raiz_, value);
}

inline NodoTernario* ArbolTernarioBusqueda::find_recursive(NodoTernario*& tree, std::string value) {
	if (tree == nullptr) {
		return nullptr;
	}

	if (value.length() == 0) {
		if (tree->is_word() == true) {
			return tree;
		} else {
			return nullptr;
		}
	} else {
		NodoTernario* child = nullptr;

		if (tree->value() == ' ') {
			return nullptr;
		}

		if (tree->value() == value.at(0)) {
			value = value.substr(1);
			child = tree->middle();
		} else if (tree->value() > value.at(0)) {
			child = tree->left();
		} else {
			child = tree->right();
		}

		if (child != nullptr) {
			// ...
		} else {
			// ...
		}

		return find_recursive(child, value);
	}
}

inline void ArbolTernarioBusqueda::cleanup_delete(NodoTernario* tree) {
	if (tree == nullptr) {
		return;
	} else if (tree->middle() == nullptr) {
		return;
	} else if (tree->middle() == nullptr && tree->right() == nullptr && tree->left() == nullptr && tree->is_word() == true) {
		return;
	} else if (tree->middle() == nullptr && tree->left() == nullptr && tree->right() == nullptr) {
		if (tree->parent() == nullptr) {
			raiz_ = nullptr;
		} else if (tree->parent()->left() == tree) {
			tree->parent()->left(nullptr);
		} else if (tree->parent()->right() == tree) {
			tree->parent()->right(nullptr);
		} else if (tree->parent()->middle() == tree) {
			tree->parent()->middle(nullptr);
			//tree->parent()->value(' ');
		}

		cleanup_delete(tree->parent());
	} else if ((tree->left() == nullptr && tree->middle() == nullptr) || (tree->right() == nullptr && tree->middle() == nullptr)) {
		NodoTernario* child = nullptr;

		if (tree->left() != nullptr) {
			child = tree->left();
		} else {
			child = tree->right();
		}

		if (tree->parent() == nullptr) {
			raiz_ = child;
		} else if (tree->parent()->left() == tree) {
			tree->parent()->left(child);
			child->parent(tree->parent());
		} else if (tree->parent()->right() == tree) {
			tree->parent()->right(child);
			child->parent(tree->parent());
		} else if (tree->parent()->middle() == tree) {
			child->parent(tree->parent());
			tree->parent()->middle(child);
		} else {
			// ...
		}
	} else if (tree->right() != nullptr && tree->middle() != nullptr && tree->right() != nullptr) {
		NodoTernario* node = tree->left();
		NodoTernario* parent = tree->parent();

		while (node->right() != nullptr) {
			node = node->right();
		}

		if (tree->left() != node) {
			node->parent()->right(node->left());

			if (node->left() != nullptr) {
				node->left()->parent(node->parent());
			}

			node->right(tree->right());
			node->left(tree->left());
			tree->right()->parent(node);
			tree->left()->parent(node);
		} else {
			node->right(tree->right());
			node->right()->parent(node);
		}

		node->parent(tree->parent());

		if (node->parent() == nullptr) {
			raiz_ = node;
		} else {
			if (tree->parent()->left() == tree) {
				tree->parent()->left(node);
				node->parent(tree->parent());
			} else if (tree->parent()->right() == tree) {
				tree->parent()->right(node);
				node->parent(tree->parent());
			} else if (tree->parent()->middle() == tree) {
				tree->parent()->middle(node);
				node->parent(tree->parent());
			}
		}
	}
}

inline void ArbolTernarioBusqueda::remove(std::string value) {
	NodoTernario* node = find(value);

	if (node != nullptr) {
		node->is_word(false);
		cleanup_delete(node);
	}

	//remove_recursive(raiz_, value, 0);
}

inline NodoTernario* ArbolTernarioBusqueda::remove_recursive(NodoTernario* node, std::string word, int position) {
	if (node == nullptr) {
		return nullptr;
	}

	int child = this->count_siblings(node);

	if (word[position] < node->value()) {
		node->left(this->remove_recursive(node->left(), word, position));
	} else if (word[position] > node->value()) {
		node->right(this->remove_recursive(node->right(), word, position));
	} else {
		if ((position + 1) < word.length()) {
			// When word not empty
			node->middle(this->remove_recursive(node->middle(), word, position + 1));
		} else if (node->is_word() == true) {
			if (child > 0) {
				// In case child node exist of deleted word
				node->is_word(false);
			} else {
				delete node;
				return nullptr;
			}
		}
	}
	if (child != this->count_siblings(node) && child == 1 && node->is_word() == false) {
		delete node;
		return nullptr;
	}

	return node;
}

inline void ArbolTernarioBusqueda::print() {
	char buffer[1000];
	NodoBasico* head = new NodoBasico();
	print_util(raiz_, buffer, 0, head);

	ArbolBT<NodoBasico> printer(head->getHijo().front(), &NodoBasico::getHijo, &NodoBasico::getDato);
	printer.print();
}

inline NodoTernario* ArbolTernarioBusqueda::create_if_not_extant(NodoTernario* tree, NodoTernario*& child, std::string label) {
	if (child == nullptr) {
		child = new NodoTernario(' ');
	}

	return child;
}

inline void ArbolTernarioBusqueda::print_util(NodoTernario* root, char* buffer, int depth, NodoBasico* head) {
	if (root != nullptr) {
		NodoBasico* node = new NodoBasico("[ " + std::string(1, root->value()) + " ]");
		print_util(root->left(), buffer, depth, node);
		head->agregarHijo(node);
		print_util(root->middle(), buffer, depth + 1, node);
		print_util(root->right(), buffer, depth, node);
	}
}

inline void ArbolTernarioBusqueda::insert_recursive(NodoTernario* tree, std::string value) {
	if (value.length() == 0) {
		tree->is_word(true);
		return;
	} else {
		if (tree->value() == ' ') {
			tree->value(value.at(0));

			if (tree->middle() == nullptr) {
				std::string label = "=" + std::string(1, value.at(0));
				NodoTernario* node = tree->middle();

				if (node == nullptr) {
					node = new NodoTernario(' ');
				}

				tree->middle(node);
				tree->middle()->parent(tree);
			}

			insert_recursive(tree->middle(), value.substr(1));
		} else if (tree->value() == value.at(0)) {
			insert_recursive(tree->middle(), value.substr(1));
		} else {
			NodoTernario* child = nullptr;
			std::string label;

			if (tree->value() > value.at(0)) {
				label = "<" + tree->value();
				NodoTernario* node = tree->left();

				if (node == nullptr) {
					node = new NodoTernario(' ');
				}

				tree->left(node);
				tree->left()->parent(tree);
				child = tree->left();
			} else {
				label = ">" + tree->value();
				NodoTernario* node = tree->right();

				if (node == nullptr) {
					node = new NodoTernario(' ');
				}

				tree->right(node);
				tree->right()->parent(tree);
				child = tree->right();
			}

			insert_recursive(child, value);
		}
	}
}

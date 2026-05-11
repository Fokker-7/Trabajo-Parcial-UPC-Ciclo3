// Serie.h
#pragma once
#include <iostream>
using namespace std;
#include "Multimedia.h"

class Serie : public Multimedia {
public:
	Serie() = default;
	Serie(
		int id,
		const std::string& title,
		const std::string& genre,
		int year,
		int duration,
		Persona* director,
		const std::vector<Persona*>& actors
	)
	: Multimedia(
		id,
		title,
		genre,
		year,
		duration,
		director,
		actors
	)
	{}

	virtual ~Serie() = default;

	// Implementaciones vacías (stubs) dejadas para otros desarrolladores
	void play() const override {}
	void printInfo() const override {
		    cout << "Serie: " << title << "(" << year << ")"<<" Favs: "<< countFavorites << endl; //esta parte si quieren mas la pueden cambiar

	}
	void printDetail() const override {
		std::cout << "\n===== DETALLE SERIE =====\n";
		std::cout << "Titulo: " << title << "\n";
		std::cout << "Genero: " << genre << "\n";
		std::cout << "Año: " << year << "\n";
		std::cout << "Duracion total: " << duration << " min\n";
		std::cout << "Favoritos: " << countFavorites << "\n";

		if (director)
			std::cout << "Director: " << director->getUsername() << "\n";

		std::cout << "Actores:\n";
		for (auto* a : actors) {
			std::cout << " - " << a->getUsername() << "\n";
		}

		std::cout << "========================\n";
	}
	Multimedia* clone() const override { return new Serie(*this); }
};


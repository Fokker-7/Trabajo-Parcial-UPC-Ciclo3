// Pelicula.h
#pragma once

#include <string>
#include <iostream>
#include "Multimedia.h"

class Pelicula : public Multimedia {
public:
	Pelicula() = default;
	Pelicula(
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

	virtual ~Pelicula() = default;

	// Implementaciones vacías (stubs) dejadas para otros desarrolladores
	void play() const override {}
	void printInfo() const override {
		    std::cout << "Pelicula: " << title 
              << " (" << year << ") "
              << "Favs: " << countFavorites << "\n"; // no lo puse para el otro pero si quieren copien y peguen este en series 
	}
	void printDetail() const override {
		std::cout << "\n===== DETALLE PELICULA =====\n";
		std::cout << "Titulo: " << title << "\n";
		std::cout << "Genero: " << genre << "\n";
		std::cout << "Año: " << year << "\n";
		std::cout << "Duracion: " << duration << " min\n";
		std::cout << "Favoritos: " << countFavorites << "\n";

		if (director)
			std::cout << "Director: " << director->getUsername() << "\n";

		std::cout << "Reparto:\n";
		for (auto* a : actors) {
			std::cout << " - " << a->getUsername() << "\n";
		}

		std::cout << "===========================\n";
	}
	Multimedia* clone() const override { return new Pelicula(*this); }
};
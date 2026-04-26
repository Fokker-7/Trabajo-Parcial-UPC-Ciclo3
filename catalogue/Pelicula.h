// Pelicula.h
#pragma once
#include <iostream>
using namespace std;
#include "Multimedia.h"

class Pelicula : public Multimedia {
public:
	Pelicula() = default;
	Pelicula(const std::string& title, const std::string& genre, int year, int duration)
		: Multimedia(title, genre, year, duration) {}

	virtual ~Pelicula() = default;

	// Implementaciones vacías (stubs) dejadas para otros desarrolladores
	void play() const override {}
	void printInfo() const override {
		    cout << "Pelicula: " << title 
              << " (" << year << ") "
              << "Favs: " << countFavorites << "\n"; // no lo puse para el otro pero si quieren copien y peguen este en series 
	}
	Multimedia* clone() const override { return new Pelicula(*this); }
};


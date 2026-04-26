// Serie.h
#pragma once
#include <iostream>
using namespace std;
#include "Multimedia.h"

class Serie : public Multimedia {
public:
	Serie() = default;
	Serie(const std::string& title, const std::string& genre, int year, int duration)
		: Multimedia(title, genre, year, duration) {}

	virtual ~Serie() = default;

	// Implementaciones vacías (stubs) dejadas para otros desarrolladores
	void play() const override {}
	void printInfo() const override {
		    cout << "-" << title << endl; //esta parte si quieren mas la pueden cambiar

	}
	Multimedia* clone() const override { return new Serie(*this); }
};


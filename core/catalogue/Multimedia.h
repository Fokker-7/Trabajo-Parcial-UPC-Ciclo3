#pragma once
#include <string>
#include <vector>
#include "users/Persona.h"

class Multimedia {
public:
	Multimedia() = default;

	Multimedia(
		int id,
		const std::string& title,
		const std::string& genre,
		int year,
		int duration,
		Persona* director,
		const std::vector<Persona*>& actors
	)
	: id(id),
	title(title),
	genre(genre),
	countFavorites(0),
	year(year),
	duration(duration),
	director(director),
	actors(actors)
	{}

	virtual ~Multimedia() = default;

	// ===== getters =====
	int getId() const { return id; }
	const std::string& getTitle() const { return title; }
	const std::string& getGenre() const { return genre; }
	int getYear() const { return year; }
	int getDuration() const { return duration; }
	int getCountFavorites() const { return countFavorites; }

	// ===== favorites =====
	void addFavorite() { countFavorites++; }

	// ===== cast system =====
	void setDirector(Persona* d) { director = d; }
	void addActor(Persona* a) { actors.push_back(a); }

	const Persona* getDirector() const { return director; }
	const std::vector<Persona*>& getActors() const { return actors; }

	// ===== abstract =====
	virtual void play() const = 0;
	virtual void printInfo() const = 0;
	virtual Multimedia* clone() const = 0;
	virtual void printDetail() const = 0;

protected:
	int id;
	std::string title;
	std::string genre;
	int countFavorites = 0;
	int year;
	int duration;

	Persona* director = nullptr;
	std::vector<Persona*> actors;
};
#pragma once
#include <string>

class Multimedia {
public:
	Multimedia() = default;
	Multimedia(
		int id,
		const std::string& title,
		const std::string& genre,
		int year,
		int duration
	)
		: id(id), title(title), genre(genre), year(year), duration(duration) {
            this->countFavorites = 0;
        }

	virtual ~Multimedia() = default;

	// Getters
	int getId() const { return id; }
	const std::string& getTitle() const { return title; }
	const std::string& getGenre() const { return genre; }
	int getYear() const { return year; }
	int getDuration() const { return duration; }
    int getCountFavorites() const { return countFavorites; };

	// Setters
	void setTitle(const std::string& t) { title = t; }
	void setGenre(const std::string& g) { genre = g; }
	void setYear(int y) { year = y; }
	void setDuration(int d) { duration = d; }

	// Métodos abstractos que deben implementar las subclases
	virtual void play() const = 0;
	virtual void printInfo() const = 0;
	virtual Multimedia* clone() const = 0;
	void addFavorite() { countFavorites++; } //hacer un contador de favoritos

protected:
    int id;
    std::string title;
    std::string genre;
    int countFavorites;
    int year;
    int duration;
};



# Compilador
CXX = clang++
# Flags
CXXFLAGS = -std=c++14 -Wall -Wextra -g -I./core -I./ui -I./helpers -I./infra -I./app

# Ejecutable
TARGET = app/main

# Archivos fuente
SRC = app/main.cpp \
	core/catalogue/Catalogo.cpp \
	core/reproductor/Reproductor.cpp \
	infra/input/Keyboard.cpp \
	infra/utils/Console.cpp \
	ui/CatalogoUI.cpp \
	helpers/ConvertList.cpp \
	core/users/UserManager.cpp \
	core/favorites/FavoritesManager.cpp \
	infra/logs/LogHandler.cpp \
	infra/logs/Log.cpp \
	core/users/Admin.cpp \
	core/users/Persona.cpp \
	core/users/Usuario.cpp

# Objetos (.o)
OBJ = $(SRC:.cpp=.o)

# Regla principal
$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $(TARGET)

# Regla para compilar cada .cpp → .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Limpiar
clean:
	rm -f $(OBJ) $(TARGET)

# Ejecutar
run: $(TARGET)
	./$(TARGET)
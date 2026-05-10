# Detección del Sistema Operativo
ifeq ($(OS),Windows_NT)
    CXX = g++
    TARGET = app/main.exe
    COMANDO_RUN = .\app\main.exe
    CLEAN_CMD = del /Q /F $(subst /,\,$(OBJ)) $(subst /,\,$(TARGET))
else
    CXX = clang++
    TARGET = app/main
    COMANDO_RUN = ./$(TARGET)
    CLEAN_CMD = rm -f $(OBJ) $(TARGET)
endif

# Flags
CXXFLAGS = -std=c++14 -Wall -Wextra -g -I./core -I./ui -I./helpers -I./infra -I./app

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
	-$(CLEAN_CMD)

# Ejecutar
run: $(TARGET)
	$(COMANDO_RUN)
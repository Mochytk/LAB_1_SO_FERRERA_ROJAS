# Variables
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17
TARGET = LAB1_Rojas_Ferrera

# Compilar el programa
all: $(TARGET)

$(TARGET): LAB1_Rojas_Ferrera.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

# Limpiar archivos generados
clean:
	rm -f $(TARGET)

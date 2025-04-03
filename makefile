# Variables
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17
TARGET = main

# Compilar el programa
all: $(TARGET)

$(TARGET): main.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

# Limpiar archivos generados
clean:
	rm -f $(TARGET)

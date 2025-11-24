# Compilador
CXX = g++
CXXFLAGS = -std=c++17 -I./src -O2 -g

# Encontrar todos los .cpp en src y subcarpetas
SOURCES = $(wildcard src/*.cpp) \
          $(wildcard src/domain/*.cpp) \
          $(wildcard src/service/*.cpp) \
          $(wildcard src/ui/*.cpp)

OBJECTS = $(SOURCES:.cpp=.o)

TARGET = course_console.exe

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	del /q $(OBJECTS) $(TARGET) 2>nul || true

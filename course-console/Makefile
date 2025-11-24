CXX = g++
CXXFLAGS = -std=c++17 -I./src -O2 -g

# Directorios con código fuente
SRCDIRS = src src/domain src/service src/ui

# Todos los .cpp de los directorios
SOURCES = $(foreach dir,$(SRCDIRS),$(wildcard $(dir)/*.cpp))
OBJECTS = $(SOURCES:.cpp=.o)

# Tests
TEST_SOURCES = $(wildcard tests/*.cpp)
TEST_OBJECTS = $(TEST_SOURCES:.cpp=.o)

# Targets
TARGET = course_console.exe
TEST_TARGET = run_tests.exe

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compilar tests (excepto main.o)
tests: $(TEST_OBJECTS) $(filter-out src/main.o,$(OBJECTS))
	$(CXX) $(CXXFLAGS) -o $(TEST_TARGET) $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	del /Q $(subst /,\,$(OBJECTS)) $(subst /,\,$(TEST_OBJECTS)) $(TARGET) $(TEST_TARGET) 2>nul || true

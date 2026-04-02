CXX ?= g++
CXXFLAGS = -O2 $(shell pkg-config --cflags raylib)
LDFLAGS = $(shell pkg-config --libs raylib)
TARGET = 3d-cube

all: $(TARGET)

$(TARGET): main.cpp
	$(CXX) $(CXXFLAGS) -o $(TARGET) main.cpp $(LDFLAGS)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)

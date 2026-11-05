CXX := g++

CXXFLAGS := -std=c++20 -Wall -Wextra -Iinclude

LDFLAGS := -lncurses -lncursesw
LDLIBS := 

TARGET := game.out

SOURCE := $(shell find src -type f -name '*.cpp')
OBJECTS := $(SOURCE:.cpp=.o)

.PHONY: all clean run delete

all: $(TARGET)

$(TARGET) : $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET) $(LDFLAGS) $(LDLIBS)

src/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

delete:
	rm -rf $(OBJECTS) $(TARGET)

clean:
	rm -rf $(OBJECTS)
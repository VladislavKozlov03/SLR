CXX = g++
CXXFLAGS = -Wall -std=c++11 -Iinclude

INCLUDE_DIR = include
TARGET = test_runner

all: $(TARGET)

lexer.c: lexer.l
	flex -o lexer.c lexer.l

lexer.o: lexer.c $(INCLUDE_DIR)/lexer.h
	$(CXX) $(CXXFLAGS) -c lexer.c -o lexer.o

parser.o: parser.cpp $(INCLUDE_DIR)/parser.h $(INCLUDE_DIR)/lexer.h
	$(CXX) $(CXXFLAGS) -c parser.cpp -o parser.o

test_runner.o: test_runner.cpp $(INCLUDE_DIR)/lexer.h $(INCLUDE_DIR)/parser.h tests.h
	$(CXX) $(CXXFLAGS) -c test_runner.cpp -o test_runner.o

$(TARGET): lexer.o parser.o test_runner.o
	$(CXX) -o $(TARGET) lexer.o parser.o test_runner.o

test: $(TARGET)
	./$(TARGET)

clean:
	rm -f lexer.c *.o $(TARGET) temp_test_input.txt

.PHONY: all clean test
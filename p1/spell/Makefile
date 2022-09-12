CPP_FILES=$(wildcard *.cpp)
OBJECTS=$(CPP_FILES:.cpp=.o)

.PHONY: all
all: $(OBJECTS)

%.o: %.cpp %.h
	g++ -c -g $<

.PHONY: clean
clean:
	rm -f *.o

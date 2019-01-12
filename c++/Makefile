CXX = c++

SRC = src/BinaryTree.cc
OBJ = $(SRC:.cc=.o)

all: BinaryTree.so

BinaryTree.so: $(OBJ)
	$(CXX) -shared -o $@ $^

%.o:%.cc
	$(CXX) -fpic -D$(LANG) -o $@ -c $< -Iinclude

src/BinaryTree.o: include/BinaryTree.h

format: $(SRC) include/BinaryTree.h
	@clang-format -i $^ 2>/dev/null || echo "Please install clang-format to run this commands"

clean:
	@rm -f *~ */*~ BinaryTree.so src/*.o

.PHONY: clean all format

CXX = c++
SRC = benchmark/Performance_test.cpp
INCLUDE = include/BinaryTreeRec.cpp
TESTINC = include/private/TestFunction.h 
TEST = test/BTtests.cpp  

all: bench unitTest

bench: $(SRC) $(INCLUDE)
	$(CXX) -O3 -o $@ $^ -Iinclude -Wall -Wextra

unitTest: $(TEST) $(INCLUDE) $(TESTINC)
	$(CXX) -o $@  $^  -Itest -Iinclude/private -Iinclude -Wall -Wextra

format: $(SRC) include/BinaryTree.h
	@clang-format -i $^ 2>/dev/null || echo "Please install clang-format to run this commands"

clean:
	@rm -f *~ */*~ benchmark uniTtest


.PHONY: clean all format

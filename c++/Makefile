CXX = c++
SRC = benchmark/Performance_test.cpp
INCLUDE = include/BinaryTreeRec.h
TESTINC = include/private/TestFunction.h 
TEST = test/BTtests.cpp  

all: bench unitTest

bench: $(SRC) $(INCLUDE)
	$(CXX) -O3 -o $@ $^ -Iinclude -Wall -Wextra

unitTest: $(TEST) $(INCLUDE) $(TESTINC)
	$(CXX) -o $@  $^  -Itest -Iinclude/private -Iinclude -Wall -Wextra

format: $(SRC) include/BinaryTree.h
	@clang-format -i $^ 2>/dev/null || echo "Please install clang-format to run this commands"

document: 
	@cd documentation; doxygen Doxyfile

clean:
	@rm -rf *~ */*~ bench unitTest documentation/html


.PHONY: clean all format document

#define CATCH_CONFIG_MAIN

#include "BinaryTree.h"
#include <iostream>
#include <vector>
#include <string>
#include "catch.hpp"




TEST_CASE("Testing methos of class BT", "[BinaryTree]")
{
	std::cout << "Initializing objects" << std::cend;
	BinaryTree<int,std::string> bt{};
	BinaryTree<std::string,std::vector<double>> bt2{};
	int keys[10]{1,2,3,4,5,6,7,8,9,10};
    std::string values[10]{"a","b","c","d","e","f","g","h","i","l"};
	for (int i = 0; i < 10; ++i)
	{
		bt.insert(keys[i], values[i]);
		bt2.insert(values[i], std::vector<double>(10, i));
	}

	SCENARIO("Testing clear and find method")
	{
		REQUIRE((*(bt.find(1)).)second == "a");
		REQUIRE((*(bt2.find("a")).)second == std::vector<double>(10, 1))
		bt.clear();
		bt2.clear();
		REQUIRE(bt.find(1) == nullptr);
		REQUIRE(bt2.find("a") == nullptr)
	}

	SCENARIO("Testing copy constructor")
	{
		BinaryTree<int,std::string> bt3{bt};
		BinaryTree<std::string,std::vector<double>> bt4{bt2};
		REQUIRE((*(bt.find(1)).second == (*(bt3.find(1)).second)
		REQUIRE((*(bt2.find("a")).second == (*(bt4.find("a")).second)
		CHECK(&(*(bt.find(1)) != &(*(bt3.find(1)))
		CHECK(&(*(bt2.find("a")) != &(*(bt4.find("a")))
		bt.clear();
		bt3.clear();
		REQUIRE((*(bt3.find(1)).)second == "a");
		REQUIRE((*(bt4.find("a")).)second == std::vector<double>(10, 1))
	}
}


/*

int main()
{
    int keys[10]{1,2,3,4,5,6,7,8,9,10};
    std::string values[10]{"a","b","c","d","e","f","g","h","i","l"};
	
	{
		BinaryTree<int,std::string> bt{};
		bt.insert(3,"three");
		bt.insert(1,"one");
		bt.insert(2,"two");
		bt.insert(4,"four");

		//should find all this things if really copied
		BinaryTree<int,std::string> copy{bt};
		assert(*(copy.find(1))=="one");
		assert(*(copy.find(2))=="two");
		assert(*(copy.find(3))=="three");
		assert(*(copy.find(4))=="four");	
		assert(copy.find(1972)==nullptr);
			
		//should find nothing if really cleared
		bt.clear();
		assert(bt.find(1)==nullptr);	

		//should not be cleared if really deep-copied
		assert(*(copy.find(1))=="one");
		assert(*(copy.find(2))=="two");
		assert(*(copy.find(3))=="three");
		assert(*(copy.find(4))=="four");

		//copy assignment should work
		bt = copy;
		assert(*(bt.find(1))=="one");
		assert(*(bt.find(2))=="two");
		assert(*(bt.find(3))=="three");
		assert(*(bt.find(4))=="four");

		//should still work if really deep-copied
		copy.clear();
		assert(*(bt.find(1))=="one");
		assert(*(bt.find(2))=="two");
		assert(*(bt.find(3))=="three");
		assert(*(bt.find(4))=="four");
		
		
	}


	return 0;
}

*/
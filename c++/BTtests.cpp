#define CATCH_CONFIG_MAIN

#include "BinaryTree.cpp"
#include <iostream>
#include <vector>
#include <string>
#include "catch.hpp"


typedef std::pair<const int, std::string> pair_is;
typedef std::pair<const std::string, double> pair_sd;

TEST_CASE("Testing methos of class BT", "[BinaryTree]")
{
	std::cout << "Initializing objects" << std::endl;
	BinaryTree<int,std::string> bt{};
	BinaryTree<std::string,double> bt2{};
	int keys[10]{1,2,3,4,5,6,7,8,9,10};
    std::string values[10]{"a","b","c","d","e","f","g","h","i","l"};
	for (int i = 0; i < 10; ++i)
	{
		bt.insert(keys[i], values[i]);
		bt2.insert(values[i], keys[i] + 0.1 );
	}

	SECTION("Testing clear and find method")
	{
		pair_is p1{1, "a"};
		pair_sd p2{"a", 1.1};
		REQUIRE(*bt.find(1) == p1);
		REQUIRE(*bt2.find("a") == p2);
		bt.clear();
		bt2.clear();
		REQUIRE(bt.find(1) == bt.end());
		REQUIRE(bt2.find("a") == bt2.end());
	}

	SECTION("Testing copy constructor")
	{
		pair_is p1{1, "a"};
		pair_sd p2{"a", 1.1};
		BinaryTree<int,std::string> bt3{bt};
		BinaryTree<std::string,double> bt4{bt2};
		REQUIRE(*bt.find(2) == *bt3.find(2));
		REQUIRE(*bt2.find("a") == *bt4.find("a"));
		CHECK(&(*bt.find(1)) != &(*bt3.find(1)));
		CHECK(&(*bt2.find("a")) != &(*bt4.find("a")));
		bt.clear();
		bt2.clear();
		REQUIRE(*bt3.find(1) == p1 );
		REQUIRE(*bt4.find("a") == p2);
	}
	SECTION("Test move constructor, move assignment and copy assignment")
	{
		pair_is p1(2,"b");
		pair_sd p2("b",2.1);
		BinaryTree<int,std::string> bt_copy;
		BinaryTree<std::string,double> bt2_copy;
		bt_copy = bt;
		bt2_copy = bt2;
		REQUIRE(*bt_copy.find(2) == p1);
		REQUIRE(*bt2_copy.find("b") == p2);
		CHECK(&(*bt.find(2)) != &(*bt_copy.find(2)));
		CHECK(&(*bt2.find("b")) != &(*bt2_copy.find("b")));
		BinaryTree<int,std::string> bt3 = std::move(bt);
		BinaryTree<std::string,double> bt4 = std::move(bt2);
		CHECK(bt.find(1) == bt.end());
		REQUIRE(*bt3.find(2) == *bt_copy.find(2));
		REQUIRE(*bt4.find("b") == *bt2_copy.find("b"));

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
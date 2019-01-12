#include <BinaryTree.h>
#include <iostream>
#include <vector>
#include <string>


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

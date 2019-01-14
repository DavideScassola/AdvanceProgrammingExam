#include <iostream>
#include <memory>
#include <algorithm>
#include <string>
#include <vector>
#include <map>
#include <chrono>
#include "BinaryTree.cpp"

int main(int arcv, char * argv [])
{

    //this data structure simulate an object stored in memory
    struct Load
    {
        std::unique_ptr<double[]> p;
        Load(const size_t s) : p{new double[s]} {}
        ~Load() = default;
    };
	
	//non piace parametrizzato con Load
	//copy constr non mi funziona

	std::srand(0);
	const size_t N = (arcv<2) ? 10000 : atoi(argv[1]);
	const size_t load_size = 2; //how many byte for each data

	BinaryTree<const int, int> linked_list_tree;
	BinaryTree<const int, int> balanced_tree;
	BinaryTree<const int, int> random_tree;
	std::map<const int, int> map;
	

	
	//////////// Initializing trees ////////////
	std::cout << "size = "<< N << std::endl;
	std::cout << "initializing trees . . ." << std::endl;
	for(int i = 0; i<N; i++)
	{
		linked_list_tree.insert(i,777);
		
		map.insert(std::make_pair(i,111));
	}
	
	balanced_tree = linked_list_tree;
	// building a vector of random ordered numbers
	std::vector<int> random_permutation_vector;
	for(int i = 0; i<N; i++)
		random_permutation_vector.push_back(i);
	std::random_shuffle ( random_permutation_vector.begin(), random_permutation_vector.end() );

	// initializing random tree
	std::cout << "initializing random tree . . ." << std::endl;
	for(auto e : random_permutation_vector)
	{
		random_tree.insert(e,777);
	}

	// balancing one of the trees
	std::cout << "balancing tree . . ." << std::endl;
	balanced_tree.balance();

	//////////////////////////////////////////////////////////////////////////////////////




	//////////// Performance measuring ////////////

	// reshuffling for random access
	std::random_shuffle ( random_permutation_vector.begin(), random_permutation_vector.begin());

	std::cout << "accessing all the elements . . ." << std::endl;


	//LINKED LIST TREE
	auto begin = std::chrono::high_resolution_clock::now();
	for(auto e : random_permutation_vector)
	{
		linked_list_tree.find(e);
	}
	auto end = std::chrono::high_resolution_clock::now();
	auto total = std::chrono::duration_cast<std::chrono::microseconds>(end-begin).count();
	std::cout << "LINKED_LIST_TREE: " << total << "ms, average = " << total/N << "us" << std::endl;

	//RANDOM TREE
	begin = std::chrono::high_resolution_clock::now();
	for(auto e : random_permutation_vector)
	{
		random_tree.find(e);
	}
	end = std::chrono::high_resolution_clock::now();
	total = std::chrono::duration_cast<std::chrono::microseconds>(end-begin).count();
	std::cout << "RANDOM_TREE: " << total << "us, average = " << total/double(N) << "us" << std::endl;

	//BALANCED TREE
	begin = std::chrono::high_resolution_clock::now();
	for(auto e : random_permutation_vector)
	{
		balanced_tree.find(e);
	}
	end = std::chrono::high_resolution_clock::now();
	total = std::chrono::duration_cast<std::chrono::microseconds>(end-begin).count();
	std::cout << "BALANCED_TREE: " << total << "us, average = " << total/double(N) << "us" << std::endl;

	//MAP PERFORMANCES
	begin = std::chrono::high_resolution_clock::now();
	for(auto e : random_permutation_vector)
	{
		map.find(e);
	}
	end = std::chrono::high_resolution_clock::now();
	total = std::chrono::duration_cast<std::chrono::microseconds>(end-begin).count();
	std::cout << "MAP: " << total << "us, average = " << total/double(N) << "us" << std::endl;

    return 0;
}

#include <iostream>
#include <memory>
#include <algorithm>
#include <string>
#include <vector>
#include <map>
#include <chrono>
#include "BinaryTree.cpp"

int main(int arcv, char *argv[])
{

	std::srand(0);
	const size_t N = (arcv<2) ? 10000 : atoi(argv[1]);
	const bool full_test = (arcv<3) ? true : false;
	//const size_t load_size = 2; //how many byte for each data

	BinaryTree<const int, double> linked_list_tree;
	BinaryTree<const int, double> balanced_tree;
	BinaryTree<const int, double> random_tree;
	std::map<const int, double> map;

	
	//////////// Initializing trees ////////////
	std::cout << "size = "<< N << std::endl;
	

	if(full_test)
	{
		std::cout << "initializing linked_list_tree . . ." << std::endl;
		for(int i = 0; i<N; i++)
		{
			linked_list_tree.insert(i,i);
		}
	}

	std::cout << "initializing std::map  . . ." << std::endl;
	for(int i = 0; i<N; i++)
	{
		map.insert(std::make_pair(i,i));
	}


	// building a vector of random ordered numbers
	std::vector<double> random_permutation_vector;
	for(int i = 0; i<N; i++)
		random_permutation_vector.push_back(i);
	std::random_shuffle ( random_permutation_vector.begin(), random_permutation_vector.end() );

	
	// initializing random tree
	std::cout << "initializing random tree . . ." << std::endl;
	for(auto e : random_permutation_vector)
	{
		random_tree.insert(e,e);
	}

	// balancing one of the trees
	std::cout << "balancing tree . . ." << std::endl;
	balanced_tree = random_tree;
	balanced_tree.balance();

	
	//////////////////////////////////////////////////////////////////////////////////////




	//////////// Performance measuring ////////////

	// reshuffling for random access
	std::random_shuffle ( random_permutation_vector.begin(), random_permutation_vector.begin());

	// just for initializing them
	auto begin = std::chrono::high_resolution_clock::now();
	auto end = std::chrono::high_resolution_clock::now();
	auto total = std::chrono::duration_cast<std::chrono::microseconds>(end-begin).count();



	std::cout << "accessing all the elements . . ." << std::endl;

	//LINKED LIST TREE
	if(full_test)
	{
		begin = std::chrono::high_resolution_clock::now();
		for(auto e : random_permutation_vector)
		{
			linked_list_tree.find(e);
		}
		end = std::chrono::high_resolution_clock::now();
		total = std::chrono::duration_cast<std::chrono::microseconds>(end-begin).count();
		std::cout << "LINKED_LIST_TREE: " << total << "us, average = " << total/N << "us" << std::endl;
	}

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

	//MAP
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


#include <vector>
#include <iostream>
#include <thread>
#include <ctime>
#include <cmath>

const unsigned int NUM = 10000000;

void func1()
{
	std::vector<int*> vec;	
	for (unsigned int i=0; i<NUM; i++)
	{	
		vec.push_back(new int(i));
	}
	
	clock_t begin = clock();
	size_t size = vec.size();
	for(size_t i=0; i<size; i++)
	{
		*vec[i] = 1;
	}
	clock_t end = clock();
	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
	std::cout<<"func1 elapsed_secs="<<elapsed_secs<<std::endl;
}

void func2()
{
	std::vector<int*> vec;	
	for (unsigned int i=0; i<NUM; i++)
	{	
		vec.push_back(new int(i));
	}
	
	clock_t begin = clock();
	for(unsigned int i=0; i<vec.size(); i++)
	{
		*vec[i] = 1;
    }
	clock_t end = clock();
	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
	std::cout<<"func2 elapsed_secs="<<elapsed_secs<<std::endl;
}

void func3()
{
	std::vector<int*> vec;	
	for (unsigned int i=0; i<NUM; i++)
	{
		vec.push_back(new int(i));
	}
	
	clock_t begin = clock();
	for(auto it=vec.begin(); it != vec.end(); it++)
	{
		**it = 1;
	}
	clock_t end = clock();
	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
	std::cout<<"func3 elapsed_secs="<<elapsed_secs<<std::endl;
}

void func4()
{
	std::vector<int*> vec;	
	for (unsigned int i=0; i<NUM; i++)
	{
		vec.push_back(new int(i));
	}
	
	clock_t begin = clock();
	for(int* &element : vec)
	{
		*element = 1;
	}
	clock_t end = clock();
	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
	std::cout<<"func4 elapsed_secs="<<elapsed_secs<<std::endl;
}


void runMultithread()
{
	std::thread thr1(func1);
	std::thread thr2(func2);
	std::thread thr3(func3);
	std::thread thr4(func4);
		
	thr1.join();
	thr2.join();
	thr3.join();
	thr4.join();
}

void runSinglethread()
{
	func1();
	func2();
	func3();
	func4();
}

void runThreadTest()
{
	clock_t begin = clock();
	runMultithread();
	clock_t end = clock();
	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
	std::cout<<"total elapsed_secs="<<elapsed_secs<<std::endl;
		
	exit(0);
}
	

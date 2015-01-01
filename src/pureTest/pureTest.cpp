
#include <vector>
#include <iostream>
#include "items/equipment/RadarEquipment.hpp"
#include <meti/RandUtils.hpp>
//#include <ceti/StringUtils.hpp>

void pureTest1()
{
    std::vector<int> int_vec;
    for (int i=0; i<20; i++)
    {
        int_vec.push_back(i);
    }
            
    for (std::vector<int>::iterator it = int_vec.begin(); it < int_vec.end(); ++it)
    {
        if ((*it == 4) or (*it == 19))
        {
            it = int_vec.erase(it);
        }
    }
    
    for (unsigned int i=0; i<int_vec.size(); i++)
    {
            std::cout<<" "<<int_vec[i];
    }
    std::cout<<std::endl;

    exit(0);          
}


void pureTest2()
{
	RadarEquipment* radar = new RadarEquipment(1);
	delete radar;

	Base* base = new RadarEquipment(2);
	delete base;	
	
    for (unsigned int i=0; i<100; i++)
        std::cout<<meti::getRandInt(0,2)<<std::endl;
	
	exit(0);
		
}

void pureTest3()
{	
	//unsigned long int uli = 5286255174080033224;
	//std::cout<<uli<<std::endl;
	//std::cout<<str(uli)<<std::endl;
	
	exit(0);		
}

void pureTest4()
{	
    int a = 2;
    //int b = 3;
    
    const int* const p = &a;
    //*p = 4;
    //p = &b;
    std::cout<<*p<<std::endl;
    
	exit(0);		
}

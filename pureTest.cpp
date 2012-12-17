
#include <vector>
#include <iostream>
#include "src/items/equipment/RadarEquipment.hpp"
#include "src/common/gameStruct.hpp"
#include "src/common/rand.hpp"

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
	
	for (unsigned int i=0; i<100; i++) std::cout<<getRandInt(0,2)<<std::endl;
	
	exit(0);
		
}

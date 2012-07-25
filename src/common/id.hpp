/*
Copyright (C) ColdStars, Aleksandr Pivovarov <<coldstars8@gmail.com>>

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/

#ifndef ID_H
#define ID_H

#include <string>
#include <vector>


struct IdInfoData
{
	unsigned long int id;
	std::string str;
};


//class DetaliedIdGenerator
//{
    	//public:
		//static DetaliedIdGenerator& Instance();

        	//unsigned long int getNextId(const std::string&);
        	//std::string getStrByTypeId(unsigned long int);
        	
        //private:
                //DetaliedIdGenerator():last_id(0) {};
        	//~DetaliedIdGenerator() {};
                	
        	//DetaliedIdGenerator(DetaliedIdGenerator&) = delete;
        	//DetaliedIdGenerator& operator=(DetaliedIdGenerator&) = delete;
        	
                //unsigned long int last_id;
                //std::vector<IdInfoData> id_data_vec;        
//};



class SimpleIdGenerator
{
    	public:
		static SimpleIdGenerator& Instance();
        	
        	unsigned long int GetNextId();
        	
        private:
        	SimpleIdGenerator():last_id(0) {};
        	~SimpleIdGenerator() {};
        	
        	SimpleIdGenerator(SimpleIdGenerator&) = delete;
        	SimpleIdGenerator& operator=(SimpleIdGenerator&) = delete;
        	        
                unsigned long int last_id;
        	std::vector<unsigned long int> id_vec; 
};


class TextureIdGenerator
{
    	public:
		static TextureIdGenerator& Instance();
        	
        	unsigned long int GetNextId();
        	
        private:
        	TextureIdGenerator():last_id(0) {};
        	~TextureIdGenerator() {};
        	
        	TextureIdGenerator(TextureIdGenerator&) = delete;
        	TextureIdGenerator& operator=(TextureIdGenerator&) = delete;
        	        
                unsigned long int last_id;
        	std::vector<unsigned long int> id_vec; 
};

#endif

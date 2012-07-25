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

#include "../common/id.hpp"

//DetaliedIdGenerator& DetaliedIdGenerator::Instance()
//{
	//static DetaliedIdGenerator instance;
	//return instance;
//}

//unsigned long int DetaliedIdGenerator::getNextId(const std::string& id_string)
//{  
	//last_id++;
	
	//IdInfoData id_data;
	//id_data.id = last_id;
	//id_data.str = id_string;
	
	//id_data_vec.push_back(id_data);
        
        //return last_id;
//}  

//std::string DetaliedIdGenerator::getStrByTypeId(unsigned long int _id)
//{
        //for(unsigned int i=0; i<id_data_vec.size(); i++)
        //{
		//if(_id == id_data_vec[i].id)
		//{
                 	//return id_data_vec[i].str; 
                //}                 
        //}  
        
        //return "___";
//}



SimpleIdGenerator& SimpleIdGenerator::Instance()
{
	static SimpleIdGenerator instance;
	return instance;
}

unsigned long int SimpleIdGenerator::GetNextId()
{  
	last_id++;
        id_vec.push_back(last_id);
        
        return last_id;
}  


TextureIdGenerator& TextureIdGenerator::Instance()
{
	static TextureIdGenerator instance;
	return instance;
}

unsigned long int TextureIdGenerator::GetNextId()
{  
	last_id++;
        id_vec.push_back(last_id);
        
        return last_id;
}  



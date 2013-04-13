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

#ifndef IDGENERATOR_H
#define IDGENERATOR_H

#include <string>
#include <vector>

class EntityIdGenerator
{
    	public:
		static EntityIdGenerator& Instance();
        	
        	unsigned long int GetNextId();
        	void AddFreeId(unsigned long int free_id) { free_ids.push_back(free_id); };
        	
        private:
        	EntityIdGenerator():last_incremented_id(0) {};
        	~EntityIdGenerator() {};
        	
        	EntityIdGenerator(EntityIdGenerator&) = delete;
        	EntityIdGenerator& operator=(EntityIdGenerator&) = delete;
        	        
                unsigned long int last_incremented_id;
        	std::vector<unsigned long int> free_ids; 
};


class TextureIdGenerator
{
    	public:
		static TextureIdGenerator& Instance();
        	
        	unsigned long int GetNextId();
        	
        private:
        	TextureIdGenerator():last_incremented_id(0) {};
        	~TextureIdGenerator() {};
        	
        	TextureIdGenerator(TextureIdGenerator&) = delete;
        	TextureIdGenerator& operator=(TextureIdGenerator&) = delete;
        	        
                unsigned long int last_incremented_id;
};

#endif

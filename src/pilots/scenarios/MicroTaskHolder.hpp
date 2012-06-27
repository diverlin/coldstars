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


#ifndef MICROTASKHOLDER_H
#define MICROTASKHOLDER_H


class MicroTaskHolder
{
	public:
		MicroTaskHolder();
		~MicroTaskHolder();
		
		void Set(BaseScenario*, BaseGameEntity*);
		void SetResult(int result)  { this->result = result; }
				
		int GetResult() const { return result; };
		
		BaseGameEntity* GetTarget() const { return target; };	
		BaseScenario* GetScenario() const { return scenario; };				
				
	protected:
		int result;
				
		BaseGameEntity* target;	
		BaseScenario* scenario;
		
		void Reset();
};


#endif 
     

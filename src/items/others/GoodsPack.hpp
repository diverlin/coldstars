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



#ifndef GOODSPACK_H
#define GOODSPACK_H


class GoodsPack : public BaseItem
{
    	public:                  
        	GoodsPack(int);
        	virtual ~GoodsPack();
        	
        	void Increase(unsigned int);       
                void Decrease(unsigned int);

                virtual void UpdateOwnerAbilities();
        	
        	virtual void SaveData(boost::property_tree::ptree&) const;
		virtual void LoadData(boost::property_tree::ptree&);
		virtual void ResolveData();
		
        private:
        	unsigned int mineral;
        	unsigned int food;
        	unsigned int medicine;
        	unsigned int military;
        	unsigned int drug;
        	
        	virtual void AddCommonInfo();
 		virtual void AddUniqueInfo();   
};

GoodsPack* GetNewGoodsPack(unsigned int);

#endif 

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


#ifndef VERTICALFLOWTEXT_HPP
#define VERTICALFLOWTEXT_HPP

#include <string>
#include <math/Vec2.hpp>
#include <math/Color4.hpp>


class VerticalFlowText
{
	public:
		VerticalFlowText(const std::string&, int, const Vec2<float>&, const Color4<int>&, float);                                   
		~VerticalFlowText();
		
		bool GetAlive() const { return m_IsAlive; }
		
		const Vec2<float>& GetCenter() const { return m_Center; }
		
		void Update();
		void Render(const Vec2<float>&, float) const;
	
	private:
		bool m_IsAlive;
		int m_LiveTime;
		
		int m_FontSize;
		
		std::string m_Text;
		Color4<int> m_Color;
		
		Vec2<float> m_Center;
		
		float m_Speed;
};

#endif 

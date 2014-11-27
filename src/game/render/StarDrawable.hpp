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

#pragma once

#include <render/BasePlanetDrawable.hpp>

class StarDrawable : public BasePlanetDrawable
{
    public:
        StarDrawable(jeti::TextureOb*, jeti::Mesh*);
        virtual ~StarDrawable() final override;

        //alpitodorender
//        int GetColorId() const;
//        float GetBrightThreshold() const;
        float GetDeltaColor() const { return m_DeltaColor; }
        
        void InitiateSpark();
        

       // alpitodorender void CalcColor(); 
        void UpdateInSpace(int, bool);
                
    private:
        float m_DeltaColor;
        
        bool m_SparkActive;
        bool m_SparkGrows;
        
        int m_TurnSinceLastSparkCounter;
        int m_TurnSparkThreshold;
        
        //virtual void UpdateInfo() override final;
}; 



        


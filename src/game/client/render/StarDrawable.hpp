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

#include <jeti/BaseDrawable.hpp>

namespace model {
class Star;
} // namespace model

namespace view {

class Star : public jeti::BaseDrawable
{
    public:
        Star(model::Star*);
        virtual ~Star() final override;

        //alpitodorender
//        int GetColorId() const;
//        float GetBrightThreshold() const;
        float GetDeltaColor() const { return m_DeltaColor; }
        
        void InitiateSpark();
        

       // alpitodorender void CalcColor(); 
        void UpdateInSpace(int, bool);
                
    private:
        model::Star* m_model_star = nullptr;
        model::Star* model() const { return m_model_star; }

        float m_DeltaColor;
        
        bool m_SparkActive;
        bool m_SparkGrows;
        
        int m_TurnSinceLastSparkCounter;
        int m_TurnSparkThreshold;
        
        //virtual void UpdateInfo() override final;
}; 

} // namespace view

        



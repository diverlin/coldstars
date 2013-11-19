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


#ifndef STAR_HPP
#define STAR_HPP

#include <spaceobjects/BasePlanet.hpp>
#include <render/Render.hpp>

class Star : public BasePlanet
{
    public:
        Star(int);
        virtual ~Star();
        
        int GetColorId() const;
        float GetBrightThreshold() const;
        float GetDeltaColor() const { return m_DeltaColor; }
        
        void Hit(int, bool) {};
        void InitiateSpark();
        
        void CalcColor();        
        void UpdateInSpaceInStatic();    
        void UpdateInSpace(int, bool);
        
        void Render_NEW(const Renderer&);
        void Render_OLD(const Renderer&);
        
        virtual void Save(boost::property_tree::ptree&) const override final;
        virtual void Load(const boost::property_tree::ptree&) override final;
        virtual void Load() override final;
                
    private:
        float m_TextureOffset;
         
        float m_DeltaColor;
        
        bool m_SparkActive;
        bool m_SparkGrows;
        
        int m_TurnSinceLastSparkCounter;
        int m_TurnSparkThreshold;
        
        virtual void UpdateInfo() override final;
        virtual void PostDeathUniqueEvent(bool) override final;
        
        void Save(boost::property_tree::ptree&, const std::string&) const;        
        void Load(const boost::property_tree::ptree&);
        void Resolve();
}; 


#endif 
    

        



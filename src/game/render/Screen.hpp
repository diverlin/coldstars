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

#ifndef SCREEN_HPP
#define SCREEN_HPP

#include <GL/glew.h>

#include "../math/myVector.hpp"
#include "../render/Fbo.hpp"
#include "../render/Bloom.hpp"
#include "../common/rect.hpp"

#include <render/Render.hpp>
#include <render/Camera.hpp>

#include "SFML_Wrapper.hpp"


class Screen : public SFML_Wrapper
{
    public:
        static Screen& Instance();
        void InitBasic(int width, int height, int bpp, bool vert_sync, const std::string&);
        void InitPostEffects(int, int);
        
        //Rect& GetRect() { return rect; };
        //glm::vec2 GetBottomLeftScreenWC()    { return rect.GetBottomLeft()*scale; }
        //glm::vec2 GetTopRightScreenWC()    { return rect.GetTopRight()*scale; }
        Renderer& GetRender() { return m_Render; }
        Camera& GetCamera() { return m_Camera; }
        
        void SetBottomLeftScreenWC(const glm::vec2& bl)    { rect.SetBottomLeft(bl); }
        
        glm::vec2 GetBottomLeftScreenWC()    { return rect.GetBottomLeft(); }
        glm::vec2 GetTopRightScreenWC()    { return (rect.GetBottomLeft()+glm::vec2(rect.GetWidth()*scale, rect.GetHeight()*scale)); }
        
        const glm::vec2& GetBottomLeft() const    { return rect.GetBottomLeft(); }
        const glm::vec2& GetTopRight()    const    { return rect.GetTopRight(); }
                        
        Fbo& GetFbo0() { return fbo0; };
        Fbo& GetFbo1() { return fbo1; };
        Fbo& GetFbo2() { return fbo2; };
        Fbo& GetFbo3() { return fbo3; }
        Fbo& GetFbo4() { return fbo4; }
        BloomEffect& GetBloom() { return bloom; };    
        
        void MovingBy(const glm::vec2&);
        void InitiateScrollTo(const glm::vec2& scroll_coord) { target_center = scroll_coord; auto_scroll = true; };
        void UpdateInSpace();
        
        void Resize(int, int);   
        void Draw();
        
        int GetFramesCounter() const { return frames_counter; }
        
        float GetScale() const { return scale; }
        void IncreaseScale();
        void DecreaseScale();

        void ResizePostEffects(int, int);
                    
    private:
        Screen();
        ~Screen();
        Screen(const Screen&) = delete;
        Screen& operator=(const Screen&) = delete;
        
        Renderer m_Render;
        Camera m_Camera;
        
        bool auto_scroll;
        
        int fps;
        int frames_counter;        
        float last_time;
        
        Fbo fbo0;
        Fbo fbo1;
        Fbo fbo2;
        Fbo fbo3;
        Fbo fbo4;
        
        BloomEffect bloom;
        
        float scale;
        float d_scale;
        Rect rect;
        glm::vec2 target_center;
        
        void DrawFps();
};


#endif


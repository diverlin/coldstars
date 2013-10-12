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


#include "Bloom.hpp"
#include "Render.hpp"


BloomEffect::BloomEffect()
{
    pass_max = 3;           
    fbo_max_per_pass = 4; 
}

                
BloomEffect::~BloomEffect()
{
    for (unsigned int i=0; i<vec_vec_fbo.size(); i++)
    {
        for (unsigned int j=0; j<vec_vec_fbo[i].size(); j++)
        {
            delete (vec_vec_fbo[i])[j];
        }
    }
}

void BloomEffect::Create(GLuint program_blur, GLuint program_extractBright, GLuint program_combine)
{
    this->program_blur          = program_blur;
    this->program_extractBright = program_extractBright;
    this->program_combine       = program_combine;
    
    for (int pass_num = 0; pass_num < pass_max; pass_num++) 
    {   
        std::vector<Fbo*> vec_fbo;
        for(int fbo_num = 0; fbo_num < fbo_max_per_pass; fbo_num++)
        {
            Fbo* fbo = new Fbo(); 
            fbo->Create();
            vec_fbo.push_back(fbo);
        }
        vec_vec_fbo.push_back(vec_fbo);
    }

    fbo_final.Create();
}
                
void BloomEffect::Resize(int width, int height)
{
    for (unsigned int i=0; i<vec_vec_fbo.size(); i++) 
        {   
            int div = 1;    
        for(unsigned int j=0; j<vec_vec_fbo[i].size(); j++)
        {
                    (vec_vec_fbo[i])[j]->Resize(width/div, height/div);
            div *= 2;
        }
    }

    fbo_final.Resize(width, height);
}
                
void BloomEffect::Proceed(const Renderer& render, int width, int height, GLuint texture, float brightness_threshold)
{
    Pass0(render, width, height, texture, brightness_threshold);
    RestPasses(render, width, height);
    Combine(render, width, height, texture);
}
                
void BloomEffect::Pass0(const Renderer& render, int width, int height, GLuint _orig_scene_texture, float brightThreshold)
{
    // RENDER TO FBO0
    (vec_vec_fbo[0])[0]->Activate(width, height);

    // render background
    glUseProgram(program_extractBright);
    glActiveTexture(GL_TEXTURE0);                                
    glBindTexture(GL_TEXTURE_2D, _orig_scene_texture);
    glUniform1i(glGetUniformLocation(program_extractBright, "source"), 0);

    glUniform1f(glGetUniformLocation(program_extractBright, "threshold"), brightThreshold);
    
    render.DrawFullScreenQuad(width, height, -499.0);
    glUseProgram(0);

    (vec_vec_fbo[0])[0]->Deactivate();
        
    int div = 2;    
    for(int fbo_num = 1; fbo_num < fbo_max_per_pass; fbo_num++)
    {
        (vec_vec_fbo[0])[fbo_num]->Activate(width, height);
        render.DrawFullScreenTexturedQuad((vec_vec_fbo[0])[0]->GetTexture(), width/div, height/div, -499.0);
        (vec_vec_fbo[0])[fbo_num]->Deactivate();
         
        div *= 2;
    }                
}       
                
void BloomEffect::RestPasses(const Renderer& render, int width, int height)
{
    for (int pass_num = 1; pass_num < pass_max; pass_num++) 
    {   
        int div = 1;    
        for(int fbo_num = 0; fbo_num < fbo_max_per_pass; fbo_num++)
        {
            (vec_vec_fbo[pass_num])[fbo_num]->Activate(width, height);
            render.DrawFullScreenTexturedQuadBlurred((vec_vec_fbo[pass_num-1])[fbo_num]->GetTexture(), width/div, height/div, -499.0);
            (vec_vec_fbo[pass_num])[fbo_num]->Deactivate();
          
            div *= 2;
        }
    }    
}



void BloomEffect::Combine(const Renderer& render, int width, int height, GLuint _orig_scene_texture)
{
      // RENDER TO final FBO
      fbo_final.Activate(width, height);

      glUseProgram(program_combine);

      glActiveTexture(GL_TEXTURE0);                                
      glBindTexture(GL_TEXTURE_2D, _orig_scene_texture);
      glUniform1i(glGetUniformLocation(program_combine, "u_TextureScene"), 0);


      glActiveTexture(GL_TEXTURE1);                                
      glBindTexture(GL_TEXTURE_2D, (vec_vec_fbo[0])[0]->GetTexture());
      glUniform1i(glGetUniformLocation(program_combine, "u_Pass0_tex1"), 1);

      glActiveTexture(GL_TEXTURE2);        
      glBindTexture(GL_TEXTURE_2D, (vec_vec_fbo[0])[1]->GetTexture());
      glUniform1i(glGetUniformLocation(program_combine, "u_Pass0_tex2"), 2);

      glActiveTexture(GL_TEXTURE3);                                
      glBindTexture(GL_TEXTURE_2D, (vec_vec_fbo[0])[2]->GetTexture());
      glUniform1i(glGetUniformLocation(program_combine, "u_Pass0_tex3"), 3);

      glActiveTexture(GL_TEXTURE4);                                
      glBindTexture(GL_TEXTURE_2D, (vec_vec_fbo[0])[3]->GetTexture());
      glUniform1i(glGetUniformLocation(program_combine, "u_Pass0_tex4"), 4);


      glActiveTexture(GL_TEXTURE5);                                
      glBindTexture(GL_TEXTURE_2D, (vec_vec_fbo[1])[0]->GetTexture());
      glUniform1i(glGetUniformLocation(program_combine, "u_Pass1_tex1"), 5);

      glActiveTexture(GL_TEXTURE6);                                
      glBindTexture(GL_TEXTURE_2D, (vec_vec_fbo[1])[1]->GetTexture());
      glUniform1i(glGetUniformLocation(program_combine, "u_Pass1_tex2"), 6);

      glActiveTexture(GL_TEXTURE7);                                
      glBindTexture(GL_TEXTURE_2D, (vec_vec_fbo[1])[2]->GetTexture());
      glUniform1i(glGetUniformLocation(program_combine, "u_Pass1_tex3"), 7);

      glActiveTexture(GL_TEXTURE8);                                
      glBindTexture(GL_TEXTURE_2D, (vec_vec_fbo[1])[3]->GetTexture());
      glUniform1i(glGetUniformLocation(program_combine, "u_Pass1_tex4"), 8);


      glActiveTexture(GL_TEXTURE9);                                
      glBindTexture(GL_TEXTURE_2D, (vec_vec_fbo[2])[0]->GetTexture());
      glUniform1i(glGetUniformLocation(program_combine, "u_Pass2_tex1"), 9);

      glActiveTexture(GL_TEXTURE10);                                
      glBindTexture(GL_TEXTURE_2D, (vec_vec_fbo[2])[1]->GetTexture());
      glUniform1i(glGetUniformLocation(program_combine, "u_Pass2_tex2"), 10);

      glActiveTexture(GL_TEXTURE11);                                
      glBindTexture(GL_TEXTURE_2D, (vec_vec_fbo[2])[2]->GetTexture());
      glUniform1i(glGetUniformLocation(program_combine, "u_Pass2_tex3"), 11);

      glActiveTexture(GL_TEXTURE12);                                
      glBindTexture(GL_TEXTURE_2D, (vec_vec_fbo[2])[3]->GetTexture());
      glUniform1i(glGetUniformLocation(program_combine, "u_Pass2_tex4"), 12);

      render.DrawFullScreenQuad(width, height, -499.0);

      fbo_final.Deactivate();
      //texture_blured = fbo_final->texture; //(vec_vec_fbo[pass_num])[fbo_num]->texture; // improove, blured texture is needed for volumetric shader
      texture_blured = (vec_vec_fbo[2])[3]->GetTexture(); // improove, blured texture is needed for volumetric shader
}










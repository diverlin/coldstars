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


#include "bloom.hpp"

BloomEffect :: BloomEffect(int _screen_w, 
			   int _screen_h, 
			   GLuint _program_blur, 
			   GLuint _program_extractBright, 
			   GLuint _program_combine, 
			   int _pass_max, 
			   int _fbo_max_per_pass)
{
	pass_max = 3; 	      //_pass_max;
	fbo_max_per_pass = 4; //_fbo_max_per_pass;
            
	screen_w = _screen_w;
	screen_h = _screen_h;
            
        for (int pass_num = 0; pass_num < pass_max; pass_num++) 
        {   
        	VEC_pFBO_type fbo_pList;
        	int div = 1;    
		for(int fbo_num = 0; fbo_num < fbo_max_per_pass; fbo_num++)
		{
                	FBO* pTo_fbo = new FBO(screen_w/div, screen_h/div); 
			fbo_pList.push_back(pTo_fbo);
			div *= 2;
		}
		pTo_fbo_pass_pList.push_back(fbo_pList);
	}

        pTo_fbo_final = new FBO(screen_w, screen_h);

	program_blur =          _program_blur;
	program_extractBright = _program_extractBright;
	program_combine =       _program_combine;
}


void BloomEffect :: pass0(GLuint _orig_scene_texture, float brightThreshold)
{
	// RENDER TO FBO0
        (pTo_fbo_pass_pList[0])[0]->activate();

	// render background
	glUseProgram(program_extractBright);
	glActiveTexture(GL_TEXTURE0);                                
	glBindTexture(GL_TEXTURE_2D, _orig_scene_texture);
	glUniform1i(glGetUniformLocation(program_extractBright, "source"), 0);

	glUniform1f(glGetUniformLocation(program_extractBright, "threshold"), brightThreshold);
	
	drawFullScreenQuad(screen_w, screen_h, -999.0);
	glUseProgram(0);

        (pTo_fbo_pass_pList[0])[0]->deactivate();
        
        int div = 2;    
	for(int fbo_num = 1; fbo_num < fbo_max_per_pass; fbo_num++)
	{
	        (pTo_fbo_pass_pList[0])[fbo_num]->activate();
        	drawFullScreenTexturedQuad((pTo_fbo_pass_pList[0])[0]->getTexture(), screen_w/div, screen_h/div, -999.0);
		(pTo_fbo_pass_pList[0])[fbo_num]->deactivate();
         
		div *= 2;
	}
		
        
}       
                
void BloomEffect :: restPasses()
{
	for (int pass_num = 1; pass_num < pass_max; pass_num++) 
        {   
        	int div = 1;    
		for(int fbo_num = 0; fbo_num < fbo_max_per_pass; fbo_num++)
		{
		        (pTo_fbo_pass_pList[pass_num])[fbo_num]->activate();
          		drawFullScreenTexturedQuadBlurred((pTo_fbo_pass_pList[pass_num-1])[fbo_num]->getTexture(), screen_w/div, screen_h/div, -999.0, program_blur);
          		(pTo_fbo_pass_pList[pass_num])[fbo_num]->deactivate();
          
			div *= 2;
		}
	}	
}



void BloomEffect :: combine(GLuint _orig_scene_texture)
{
          // RENDER TO final FBO
          pTo_fbo_final->activate();

          glUseProgram(program_combine);

          glActiveTexture(GL_TEXTURE0);                                
          glBindTexture(GL_TEXTURE_2D, _orig_scene_texture);
          glUniform1i(glGetUniformLocation(program_combine, "Scene"), 0);


          glActiveTexture(GL_TEXTURE1);                                
          glBindTexture(GL_TEXTURE_2D, (pTo_fbo_pass_pList[0])[0]->getTexture());
          glUniform1i(glGetUniformLocation(program_combine, "Pass0_tex1"), 1);

          glActiveTexture(GL_TEXTURE2);        
          glBindTexture(GL_TEXTURE_2D, (pTo_fbo_pass_pList[0])[1]->getTexture());
          glUniform1i(glGetUniformLocation(program_combine, "Pass0_tex2"), 2);

          glActiveTexture(GL_TEXTURE3);                                
          glBindTexture(GL_TEXTURE_2D, (pTo_fbo_pass_pList[0])[2]->getTexture());
          glUniform1i(glGetUniformLocation(program_combine, "Pass0_tex3"), 3);

          glActiveTexture(GL_TEXTURE4);                                
          glBindTexture(GL_TEXTURE_2D, (pTo_fbo_pass_pList[0])[3]->getTexture());
          glUniform1i(glGetUniformLocation(program_combine, "Pass0_tex4"), 4);


          glActiveTexture(GL_TEXTURE5);                                
          glBindTexture(GL_TEXTURE_2D, (pTo_fbo_pass_pList[1])[0]->getTexture());
          glUniform1i(glGetUniformLocation(program_combine, "Pass1_tex1"), 5);

          glActiveTexture(GL_TEXTURE6);                                
          glBindTexture(GL_TEXTURE_2D, (pTo_fbo_pass_pList[1])[1]->getTexture());
          glUniform1i(glGetUniformLocation(program_combine, "Pass1_tex2"), 6);

          glActiveTexture(GL_TEXTURE7);                                
          glBindTexture(GL_TEXTURE_2D, (pTo_fbo_pass_pList[1])[2]->getTexture());
          glUniform1i(glGetUniformLocation(program_combine, "Pass1_tex3"), 7);

          glActiveTexture(GL_TEXTURE8);                                
          glBindTexture(GL_TEXTURE_2D, (pTo_fbo_pass_pList[1])[3]->getTexture());
          glUniform1i(glGetUniformLocation(program_combine, "Pass1_tex4"), 8);


          glActiveTexture(GL_TEXTURE9);                                
          glBindTexture(GL_TEXTURE_2D, (pTo_fbo_pass_pList[2])[0]->getTexture());
          glUniform1i(glGetUniformLocation(program_combine, "Pass2_tex1"), 9);

          glActiveTexture(GL_TEXTURE10);                                
          glBindTexture(GL_TEXTURE_2D, (pTo_fbo_pass_pList[2])[1]->getTexture());
          glUniform1i(glGetUniformLocation(program_combine, "Pass2_tex2"), 10);

          glActiveTexture(GL_TEXTURE11);                                
          glBindTexture(GL_TEXTURE_2D, (pTo_fbo_pass_pList[2])[2]->getTexture());
          glUniform1i(glGetUniformLocation(program_combine, "Pass2_tex3"), 11);

          glActiveTexture(GL_TEXTURE12);                                
          glBindTexture(GL_TEXTURE_2D, (pTo_fbo_pass_pList[2])[3]->getTexture());
          glUniform1i(glGetUniformLocation(program_combine, "Pass2_tex4"), 12);

          drawFullScreenQuad(screen_w, screen_h, -999.0);

          pTo_fbo_final->deactivate();
          //texture_blured = pTo_fbo_final->texture; //(pTo_fbo_pass_pList[pass_num])[fbo_num]->texture; // improove, blured texture is needed for volumetric shader
          texture_blured = (pTo_fbo_pass_pList[2])[3]->getTexture(); // improove, blured texture is needed for volumetric shader
}










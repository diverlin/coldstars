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


ExplosionEffect :: ExplosionEffect()
{  
	//subtype_id = EXPLOSION_EFFECT_ID;
}
 
/* virtual */
ExplosionEffect :: ~ExplosionEffect()
{}


void ExplosionEffect :: createParticles()
{
	for(int i = 0; i< num_particles; i++)
    	{  
                Particle* particle = new Particle(data_particle);
                particle->setPosition(center);
       		particle->setVelocity(getRandomVelocity());
       		particles_vec.push_back(particle);
    	}
}



void ExplosionEffect :: update()
{
    	is_alive = false;
    	for (unsigned int i = 0; i < num_particles; i++)
    	{
        	if (particles_vec[i]->GetAlive() == true)
        	{
           		particles_vec[i]->update();
           		is_alive = true;
        	}
    	}  
}     
    

void ExplosionEffect :: Render()
{
	glBindTexture(GL_TEXTURE_2D, texOb->texture);
    	for(unsigned int i = 0; i < num_particles; i++)
    	{
		particles_vec[i]->Render();
    	}            
}  

                 


void  createExplosion(StarSystem* _starsystem, vec2f _center_pos, int obSize)
{
	//obSize = getRandInt(1,9); // DEBUG
	ExplosionEffect* explosion;
	
	TextureOb* texOb_particle; 
	ParticleData  data_particle;
	int particles_num;

	//data_particle.velocity_start = getRandInt(13,17) * 0.1;   
	data_particle.velocity_start = (float)obSize*0.1f + getRandInt(40,90) * 0.01;
	data_particle.velocity_end   = data_particle.velocity_start;
	data_particle.d_velocity     = 0;

	data_particle.color_start.r    = 1.0;
	data_particle.color_start.g    = 1.0;
	data_particle.color_start.b    = 1.0;
        data_particle.color_start.a    = 1.0;

	data_particle.color_end.r    = 0.0;
	data_particle.color_end.g    = 0.0;
	data_particle.color_end.b    = 0.0;
        data_particle.color_end.a    = 0.0;

	data_particle.color_delta.r    = 0.0;
	data_particle.color_delta.g    = 0.0;
	data_particle.color_delta.b    = 0.0;
        data_particle.color_delta.a    = getRandInt(5,8) * 0.001;

	
	//data_particle.size_start
	data_particle.size_end 	     = 0.1;		
	data_particle.d_size 	     = (float)obSize*0.1f + getRandInt(30,50) * 0.01;  
	//data_particle.d_size 	     = getRandInt(60,80) * 0.01 * obSize/3;  
        
	if (obSize < 4)
	{
		particles_num = getRandInt(10 * obSize, 15 * obSize);    
		data_particle.size_start  = 25 * obSize;                                 

                texOb_particle = g_TEXTURE_MANAGER.getTexObByColorId(TEXTURE::PARTICLE_EFFECT_ID, COLOR::RED_ID);

		explosion = new ExplosionEffect();
                explosion->setTextureOb(texOb_particle);
                explosion->setPosition(_center_pos);
                explosion->setParticleData(data_particle);
                explosion->setParticlesNum(particles_num);
                
                explosion->createParticles();
                
		_starsystem->Add(explosion);
	}
    	else    
	{
                {
		particles_num = 40;
		data_particle.size_start  = 25 * obSize;

                texOb_particle = g_TEXTURE_MANAGER.getTexObByColorId(TEXTURE::PARTICLE_EFFECT_ID, COLOR::RED_ID);
		
		explosion = new ExplosionEffect();
                explosion->setTextureOb(texOb_particle);
                explosion->setPosition(_center_pos);
                explosion->setParticleData(data_particle);
                explosion->setParticlesNum(particles_num);
                
                explosion->createParticles();
                
		_starsystem->Add(explosion);
                }

                {
		particles_num = 50;
		data_particle.size_start  = 25 * (obSize-1);

                texOb_particle = g_TEXTURE_MANAGER.getTexObByColorId(TEXTURE::PARTICLE_EFFECT_ID, COLOR::YELLOW_ID);

		explosion = new ExplosionEffect();
                explosion->setTextureOb(texOb_particle);
                explosion->setPosition(_center_pos);
                explosion->setParticleData(data_particle);
                explosion->setParticlesNum(particles_num);
                
                explosion->createParticles();
                
		_starsystem->Add(explosion);
                }
        
                {
		particles_num = 100;                              
		data_particle.size_start  = 25 * (obSize-2);

                texOb_particle = g_TEXTURE_MANAGER.getTexObByColorId(TEXTURE::PARTICLE_EFFECT_ID, COLOR::RED_ID);
		
		explosion = new ExplosionEffect();
                explosion->setTextureOb(texOb_particle);
                explosion->setPosition(_center_pos);
                explosion->setParticleData(data_particle);
                explosion->setParticlesNum(particles_num);
                
                explosion->createParticles();
                
		_starsystem->Add(explosion);
                }
	} 	       
 
 	if ( (obSize > 3) && (_starsystem->GetShockWaveNum() < 10) )
	{
		createShockWave(_starsystem, _center_pos, obSize);
	}
	//explosion.play()
} 

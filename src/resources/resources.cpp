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

#include "resources.h"



void loadResources()
{
pTo_SPHERE_MESH = new ObjMeshInstance("data/obj/sphere/planet.obj");

pTo_DEFORMED_SPHERE_MESH = new ObjMeshInstance("data/obj/sphere_deformed/planet.obj");

//g_model.import("data/obj/sphere/planet.obj");
//g_model.normalize();



if (USE_MODERN_HW == true)
{
//static const char * pTo_lightVertexSource = {
//"/* vertex */"
//"    void main() {"
//"        gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;"
//"    }"
//};   

//static const char * pTo_lightFragSource = {
//"/* fragment */"
//"    void main() {"
//"        gl_FragColor = vec4(0.0, 1.0, 0.0, 0.0);"
//"    }"
//};       

static const char * pTo_blackToAlphaVertexSource = {
"/* vertex */"
"void main()" 
"{"
"  gl_Position = ftransform();"
"  gl_TexCoord[0] = gl_MultiTexCoord0;"
"}"
};   

static const char * pTo_blackToAlphaFragSource = {
"/* fragment */"
"uniform sampler2D sceneTex;     /* texture unit 0 */"
"void main()"
"{"
"    vec4 c = texture2D(sceneTex, gl_TexCoord[0].st);"
"    float rgb = c.r + c.g + c.b;"
"    if (c.g > 0.6)"
"       gl_FragColor = vec4(0.0, 0.0, 0.0, 0.0);"
"    else"
"       gl_FragColor = c;"
"}"
};       

g_BLACK2ALPHA_PROGRAM = glCreateProgram();
compile_program(pTo_blackToAlphaVertexSource, pTo_blackToAlphaFragSource, &g_BLACK2ALPHA_PROGRAM);





// shaders are taken from http://www.geeks3d.com/20091116/shader-library-2d-shockwave-post-processing-filter-glsl/
static const GLchar * pTo_shockWaveVertexSource = {
"/* Vertex program */"
" "
"void main(void)"
"{"
"  gl_Position = ftransform();"
"  gl_TexCoord[0] = gl_MultiTexCoord0;"
"}"
};


static const GLchar * pTo_shockWaveFragSource = {
"/* Fragment program */"
" "
"uniform sampler2D sceneTex;     /* texture unit 0 */"
"uniform vec2 center[10];"        
"uniform vec3 shockParams[10];   /* 10.0, 0.8, 0.1 */" 
"uniform float time[10];         /* effect elapsed time */"
"uniform int imax;               /* how many shaders */"
" "
"void main()"
"{"
"  vec2 uv = gl_TexCoord[0].xy;"
"  vec2 texCoord = uv;"
"  for(int i=0; i<imax; i++)"
"  {"
"      float distance = distance(uv, center[i]);"
"      /* if ( (distance <= (time[i] + shockParams[i].z)) && (distance >= (time[i] - shockParams[i].z)) ) */"
"      if (distance <= (time[i] + shockParams[i].z))"
"         if (distance >= (time[i] - shockParams[i].z))"
"         {"
"              float diff = (distance - time[i]);"
"              float powDiff = 1.0 - pow(abs(diff*shockParams[i].x), shockParams[i].y);"
"              float diffTime = diff  * powDiff;"
"              vec2 diffUV = normalize(uv - center[i]);"
"              texCoord = uv + (diffUV * diffTime);"
"         }"
"  }"
" "
"  gl_FragColor = texture2D(sceneTex, texCoord);"
"}"
};

g_SHOCKWAVE_PROGRAM = glCreateProgram();
compile_program(pTo_shockWaveVertexSource, pTo_shockWaveFragSource, &g_SHOCKWAVE_PROGRAM);





static const GLchar * pTo_volumetricLightVertexSource = {
"/* Vertex program */"
" "
"void main(void)"
"{"
"  gl_Position = ftransform();"
"  gl_TexCoord[0] = gl_MultiTexCoord0;"
"}"
};


static const GLchar * pTo_volumetricLightFragSource = {
"/* Fragment program */"
" "
"uniform sampler2D FullSampler;"
"uniform sampler2D BlurSampler;"
"uniform vec4 sun_pos;"
" "
"const vec4 ShaftParams	= vec4(0.05, 1.0, 0.05, 1.0);"
"const vec4 sunColor	= vec4(0.9, 0.8, 0.6, 1.0);"
" "
"float saturate(float val)"
"{"
"	return clamp(val,0.0,1.0);"
"}"
" "
"void main(void)"
"{ "
"	vec2  sunPosProj = sun_pos.xy;"
"	float sign = sun_pos.w;"
" "
"	vec2  tc = gl_TexCoord[0].xy;"
" "
"	vec2  sunVec = sunPosProj.xy - tc; /* + vec2(0.5,0.5); */"
"	float sunDist = saturate(sign) * (1.0 - saturate(dot(sunVec,sunVec) * ShaftParams.y));"
" "
"	sunVec *= ShaftParams.x * sign;"
" "
"	tc += sunVec;"
"	vec4 accum = texture2D(BlurSampler, tc);"
"	tc += sunVec;"
"	accum += texture2D(BlurSampler, tc) * 0.875;"
"	tc += sunVec;"
"	accum += texture2D(BlurSampler, tc) * 0.75;"
"	tc += sunVec;"
"	accum += texture2D(BlurSampler, tc) * 0.625;"
"	tc += sunVec;"
"	accum += texture2D(BlurSampler, tc) * 0.5;"
"	tc += sunVec;"
"	accum += texture2D(BlurSampler, tc) * 0.375;"
"	tc += sunVec;"
"	accum += texture2D(BlurSampler, tc) * 0.25;"
"	tc += sunVec;"
"	accum += texture2D(BlurSampler, tc) * 0.125;"
" "
"	accum  *= 1.65 * sunDist;"
" "
"	vec4 cScreen = texture2D(FullSampler, gl_TexCoord[0].xy);"
"	accum = cScreen + accum * ShaftParams.w * sunColor * ( 1.0 - cScreen );"
" "
"	gl_FragColor = accum;"
"}"
};

g_VOLUMETRICLIGHT_PROGRAM = glCreateProgram();
compile_program(pTo_volumetricLightVertexSource, pTo_volumetricLightFragSource, &g_VOLUMETRICLIGHT_PROGRAM);


















//http://www.gamedev.ru/code/forum/?id=90743
static const GLchar * pTo_lightVertexSource = {
"/* Vertex program */"
" "
"uniform vec4 lightPos, eyePos;"
"varying vec3 l, v, n;"
" "
"void main(void)"
"{"
"    vec3 p = vec3(gl_ModelViewMatrix * gl_Vertex);      /* transformed point to world space */ "
"    l = normalize(vec3(lightPos) - p);                  /* vector to light source */           "
"    v = normalize(vec3(eyePos)   - p);                  /* vector to the eye */                "
"    n = normalize(gl_NormalMatrix * gl_Normal);         /* transformed n */                    "
"    gl_TexCoord[0] = gl_MultiTexCoord0;                                                        " 
" "
"    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;                                    "
"}"
};   

//http://www.gamedev.ru/code/forum/?id=90743
static const GLchar * pTo_lightFragSource = {
"/* Fragment program */"
" "
"uniform sampler2D Texture_0;"
"varying vec3 l, v, n;"
" "
"void main (void)"
"{"
"    const vec4  diffColor = vec4(1.0, 1.0, 1.0, 1.0);"
"    const vec4  ambientColor = vec4(0.1, 0.1, 0.1, 1.0);"
"    const vec4  specColor = vec4(0.7, 0.7, 0.0, 0.0);"
"    const float specPower = 30.0;"
" "
"    vec3 n2   = normalize(n);"
"    vec3 l2   = normalize(l);"
"    vec3 v2   = normalize(v);"
"    vec3 r    = reflect(-v2, n2);"
"    vec4 diff = diffColor * max(dot(n2, l2), 0.0);"
"    vec4 spec = specColor * pow(max(dot(l2, r), 0.0), specPower);"
"    vec2 texCoord0 = gl_TexCoord[0].xy;"
"    vec4 texColor0 = texture2D(Texture_0, texCoord0);"
" "
"    gl_FragColor = (diff + ambientColor) * texColor0;"
"}"
};       

g_LIGHT_PROGRAM = glCreateProgram();
compile_program(pTo_lightVertexSource, pTo_lightFragSource, &g_LIGHT_PROGRAM);








static const GLchar * pTo_blurVertexSource = {
"/* Vertex program */"
" "
"void main(void)"
"{"
"  gl_Position = ftransform();"
"  gl_TexCoord[0] = gl_MultiTexCoord0;"
"}"
};     

static const GLchar * pTo_blurFragmentSource = {
"/* Fragment program */"
"uniform sampler2D sceneTex;  /* 0 */"
" "
"uniform float rt_w;    /* render target width  */"
"uniform float rt_h;    /* render target height */"
"uniform float vx_offset;"
" "
"float offset[3] = float[]( 0.0, 1.3846153846, 3.2307692308 );"
"float weight[3] = float[]( 0.2270270270, 0.3162162162, 0.0702702703 );"
" "
"void main()"
"{"
"  vec3 tc = vec3(0.0, 0.0, 0.0);"
"  if (gl_TexCoord[0].x<(vx_offset-0.01))"
"  {"
"    vec2 uv = gl_TexCoord[0].xy;"
"    tc = texture2D(sceneTex, uv).rgb * weight[0];"
" "
"    for (int i=1; i<3; i++)"
"    {"
"      tc += texture2D(sceneTex, uv + vec2(offset[i])/rt_w, 0.0).rgb * weight[i];"
"      tc += texture2D(sceneTex, uv - vec2(offset[i])/rt_w, 0.0).rgb * weight[i];"
"    }"
"  }"
"  else if (gl_TexCoord[0].x>=(vx_offset+0.01))"
"  {"
"    tc = texture2D(sceneTex, gl_TexCoord[0].xy).rgb;"
"  }"
"  gl_FragColor = vec4(tc, 1.0);"
"}"
};  

g_BLUR_PROGRAM = glCreateProgram();
compile_program(pTo_blurVertexSource, pTo_blurFragmentSource, &g_BLUR_PROGRAM);





static const GLchar * pTo_extractBrightVertexSource = {
"/* Vertex program */"
" "
"void main(void)"
"{"
"  gl_Position = ftransform();"
"  gl_TexCoord[0] = gl_MultiTexCoord0;"
"}"
};  


static const GLchar * pTo_extractBrightFragmentSource = {
"/* Fragment program */"
"uniform sampler2D source;"
"uniform float threshold;"
" "
"void main(void)"
"{"
"    vec4 c = texture2D(source, gl_TexCoord[0].st);"
"    float rgb = c.r + c.g + c.b;"
"    if (rgb > threshold)   /* threshold ~ 1.9 */ "
"       gl_FragColor = c;"
"    else"
"       gl_FragColor = vec4(0.0, 0.0, 0.0, 0.0);"
"}"
};  

g_EXTRACT_BRIGHT_PROGRAM = glCreateProgram();
compile_program(pTo_extractBrightVertexSource, pTo_extractBrightFragmentSource, &g_EXTRACT_BRIGHT_PROGRAM);







static const GLchar * pTo_combineVertexSource = {
"/* Vertex program */"
" "
"void main(void)"
"{"
"  gl_Position = ftransform();   /* This transforms the input vertex the same way the fixed-function pipeline would */"
"  gl_TexCoord[0] = gl_MultiTexCoord0;"
"}"
};  


static const GLchar * pTo_combineFragmentSource = {
"/* Fragment program */"
"uniform sampler2D Scene;"
" "
"uniform sampler2D Pass0_tex1;"
"uniform sampler2D Pass0_tex2;"
"uniform sampler2D Pass0_tex3;"
"uniform sampler2D Pass0_tex4;"
" "
"uniform sampler2D Pass1_tex1;"
"uniform sampler2D Pass1_tex2;"
"uniform sampler2D Pass1_tex3;"
"uniform sampler2D Pass1_tex4;"
" "
"uniform sampler2D Pass2_tex1;"
"uniform sampler2D Pass2_tex2;"
"uniform sampler2D Pass2_tex3;"
"uniform sampler2D Pass2_tex4;"
" "
"void main(void)"
"{"
"    vec4 t0 = texture2D(Scene, gl_TexCoord[0].st);"
" "
"    vec4 p0t1 = texture2D(Pass0_tex1, gl_TexCoord[0].st);"
"    vec4 p0t2 = texture2D(Pass0_tex2, gl_TexCoord[0].st);"
"    vec4 p0t3 = texture2D(Pass0_tex3, gl_TexCoord[0].st);"
"    vec4 p0t4 = texture2D(Pass0_tex4, gl_TexCoord[0].st);"
" "
"    vec4 p1t1 = texture2D(Pass1_tex1, gl_TexCoord[0].st);"
"    vec4 p1t2 = texture2D(Pass1_tex2, gl_TexCoord[0].st);"
"    vec4 p1t3 = texture2D(Pass1_tex3, gl_TexCoord[0].st);"
"    vec4 p1t4 = texture2D(Pass1_tex4, gl_TexCoord[0].st);"
" "
"    vec4 p2t1 = texture2D(Pass2_tex1, gl_TexCoord[0].st);"
"    vec4 p2t2 = texture2D(Pass2_tex2, gl_TexCoord[0].st);"
"    vec4 p2t3 = texture2D(Pass2_tex3, gl_TexCoord[0].st);"
"    vec4 p2t4 = texture2D(Pass2_tex4, gl_TexCoord[0].st);"
" "
" "
"    gl_FragColor = t0 + p0t1 + p0t2 + p0t3 + p0t4 + p1t1 + p1t2 + p1t3 + p1t4 + p2t1 + p2t2 + p2t3 + p2t4;"
"}"
};  

g_COMBINE_PROGRAM = glCreateProgram();
compile_program(pTo_combineVertexSource, pTo_combineFragmentSource, &g_COMBINE_PROGRAM);









static const GLchar * pTo_multitexVertexSource = {
"/* Vertex program */"
" "
"void main(void)"
"{"
"  gl_Position = ftransform();"
"  gl_TexCoord[0] = gl_MultiTexCoord0;"
"}"
};


static const GLchar * pTo_multitexFragmentSource = {
"/* Fragment program */"
"uniform sampler2D Texture_0;     /* texture unit 0 */"
"uniform sampler2D Texture_1;"
" "
"uniform vec2 displ;"
" "
"void main() {"
"  vec2 uv = gl_TexCoord[0].xy;"
"  vec2 texCoord0 = uv - displ;"
"  vec2 texCoord1 = uv + displ;"
" "
"  vec4 color0 = texture2D(Texture_0, texCoord0);"
"  vec4 color1 = texture2D(Texture_1, texCoord1);"
"  /*vec4 color3 = vec4(1.0, 1.0, 0.0, 1.0); */"
"  vec4 tmp = mix(color0, color1, 0.5);"
" "
"  /*gl_FragColor = mix(tmp, color3, 0.4); */"
"  gl_FragColor = tmp;"
"}"
};

    
g_MULTITEX_PROGRAM = glCreateProgram();
compile_program(pTo_multitexVertexSource, pTo_multitexFragmentSource, &g_MULTITEX_PROGRAM);


}






//####################################### TURREL_TEXTURE ###################################
VEC_int_type turrel_arg_00;   
turrel_arg_00.push_back(RACE_0_ID);
g_TEXTURE_MANAGER.manage( new TextureOb(TURREL_TEXTURE_ID, "data/turrel/lazer.png", true, &turrel_arg_00) );

//####################################### SLOT_TEXTURE ###################################
VEC_int_type slot_arg_00;   
slot_arg_00.push_back(RACE_0_ID);
g_TEXTURE_MANAGER.manage( new TextureOb(SLOT_TEXTURE_ID, "data/other/slot.png", true, &slot_arg_00) );

//####################################### FACE_TEXTURE_ID ################################
//RACE_0_ID
VEC_int_type face_race0_00_arg; 
face_race0_00_arg.push_back(RACE_0_ID);
g_TEXTURE_MANAGER.manage_face( new TextureOb(FACE_TEXTURE_ID, "data/race/0000.png", false, &face_race0_00_arg) );

VEC_int_type face_race0_01_arg; 
face_race0_01_arg.push_back(RACE_0_ID);
g_TEXTURE_MANAGER.manage_face( new TextureOb(FACE_TEXTURE_ID, "data/race/0001.png", false, &face_race0_01_arg) );

//RACE_1_ID
VEC_int_type face_race1_00_arg; 
face_race1_00_arg.push_back(RACE_1_ID);
g_TEXTURE_MANAGER.manage_face( new TextureOb(FACE_TEXTURE_ID, "data/race/1000.png", false, &face_race1_00_arg) );

VEC_int_type face_race1_01_arg; 
face_race1_01_arg.push_back(RACE_1_ID);
g_TEXTURE_MANAGER.manage_face( new TextureOb(FACE_TEXTURE_ID, "data/race/1001.png", false, &face_race1_01_arg) );

//RACE_2_ID
VEC_int_type face_race2_00_arg; 
face_race2_00_arg.push_back(RACE_2_ID);
g_TEXTURE_MANAGER.manage_face( new TextureOb(FACE_TEXTURE_ID, "data/race/2000.png", false, &face_race2_00_arg) );

VEC_int_type face_race2_01_arg; 
face_race2_01_arg.push_back(RACE_2_ID);
g_TEXTURE_MANAGER.manage_face( new TextureOb(FACE_TEXTURE_ID, "data/race/2001.png", false, &face_race2_01_arg) );

//RACE_3_ID
VEC_int_type face_race3_00_arg; 
face_race3_00_arg.push_back(RACE_3_ID);
g_TEXTURE_MANAGER.manage_face( new TextureOb(FACE_TEXTURE_ID, "data/race/3000.png", false, &face_race3_00_arg) );

VEC_int_type face_race3_01_arg; 
face_race3_01_arg.push_back(RACE_3_ID);
g_TEXTURE_MANAGER.manage_face( new TextureOb(FACE_TEXTURE_ID, "data/race/3001.png", false, &face_race3_01_arg) );

//RACE_4_ID
VEC_int_type face_race4_00_arg; 
face_race4_00_arg.push_back(RACE_4_ID);
g_TEXTURE_MANAGER.manage_face( new TextureOb(FACE_TEXTURE_ID, "data/race/4000.png", false, &face_race4_00_arg) );

VEC_int_type face_race4_01_arg; 
face_race4_01_arg.push_back(RACE_4_ID);
g_TEXTURE_MANAGER.manage_face( new TextureOb(FACE_TEXTURE_ID, "data/race/4001.png", false, &face_race4_01_arg) );


//RACE_6_ID
VEC_int_type face_race6_00_arg; 
face_race6_00_arg.push_back(RACE_6_ID);
g_TEXTURE_MANAGER.manage_face( new TextureOb(FACE_TEXTURE_ID, "data/race/6000.png", false, &face_race6_00_arg) );

VEC_int_type face_race6_01_arg; 
face_race6_01_arg.push_back(RACE_6_ID);
g_TEXTURE_MANAGER.manage_face( new TextureOb(FACE_TEXTURE_ID, "data/race/6001.png", false, &face_race6_01_arg) );


//RACE_7_ID
VEC_int_type face_race7_00_arg; 
face_race7_00_arg.push_back(RACE_7_ID);
g_TEXTURE_MANAGER.manage_face( new TextureOb(FACE_TEXTURE_ID, "data/race/7000.png", false, &face_race7_00_arg) );

VEC_int_type face_race7_01_arg; 
face_race7_01_arg.push_back(RACE_7_ID);
g_TEXTURE_MANAGER.manage_face( new TextureOb(FACE_TEXTURE_ID, "data/race/7001.png", false, &face_race7_01_arg) );




//####################################### ASTEROID_TEXTURE ################################
VEC_int_type aArg1; 
g_TEXTURE_MANAGER.manage( new TextureOb(ASTEROID_TEXTURE_ID, "data/asteroid/a_000.png", true, &aArg1) );

VEC_int_type aArg2; 
g_TEXTURE_MANAGER.manage( new TextureOb(ASTEROID_TEXTURE_ID, "data/asteroid/a_001.png", true, &aArg2) );

VEC_int_type aArg3; 
g_TEXTURE_MANAGER.manage( new TextureOb(ASTEROID_TEXTURE_ID, "data/asteroid/a_002.png", true, &aArg3) );


//####################################### MINERAL_TEXTURE ################################
VEC_int_type mArg0; 
g_TEXTURE_MANAGER.manage( new TextureOb(MINERAL_TEXTURE_ID, "data/asteroid/m_000.png", true, &mArg0) );

VEC_int_type mArg1; 
g_TEXTURE_MANAGER.manage( new TextureOb(MINERAL_TEXTURE_ID, "data/asteroid/m_001.png", true, &mArg1) );

VEC_int_type mArg2; 
g_TEXTURE_MANAGER.manage( new TextureOb(MINERAL_TEXTURE_ID, "data/asteroid/m_002.png", true, &mArg2) );


VEC_int_type container_arg; 
g_TEXTURE_MANAGER.manage( new TextureOb(CONTAINER_TEXTURE_ID, "data/item/container.png", true, &container_arg) );

VEC_int_type bomb_arg; 
g_TEXTURE_MANAGER.manage( new TextureOb(BOMB_TEXTURE_ID, "data/item/bomb_item.png", true, &bomb_arg) );




//####################################### SPUTNIK_TEXTURE_ID ################################
//TEXTURE_MANAGER.manage( textureOb(SPUTNIK_TEXTURE_ID, 'data/satellite/sa_001.png', True, [], 48, 49) )
//TEXTURE_MANAGER.manage( textureOb(SPUTNIK_TEXTURE_ID, 'data/satellite/sa_002.png', True, [], 24, 23) )
//TEXTURE_MANAGER.manage( textureOb(SPUTNIK_TEXTURE_ID, 'data/satellite/sa_003.png', True, [], 48, 49) )
//TEXTURE_MANAGER.manage( textureOb(SPUTNIK_TEXTURE_ID, 'data/satellite/sa_004.png', True, []) )
//TEXTURE_MANAGER.manage( textureOb(SPUTNIK_TEXTURE_ID, 'data/satellite/sa_005.png', True, [], 24, 24) )
//TEXTURE_MANAGER.manage( textureOb(SPUTNIK_TEXTURE_ID, 'data/satellite/sa_006.png', True, [], 24, 21) )
//TEXTURE_MANAGER.manage( textureOb(SPUTNIK_TEXTURE_ID, 'data/satellite/sa_007.png', True, [], 24, 20) )



//####################################### SHIP_TEXTURE ####################################
//################################ race texnologi
VEC_int_type k_arg_00_0_0;   
k_arg_00_0_0.push_back(RACE_0_ID); k_arg_00_0_0.push_back(RANGER_ID); k_arg_00_0_0.push_back(256); k_arg_00_0_0.push_back(256); k_arg_00_0_0.push_back(256);   //COLOR_VIOLET
g_TEXTURE_MANAGER.manage( new TextureOb(SHIP_TEXTURE_ID, "data/ship/k_00_0_0.png", true, &k_arg_00_0_0) );

VEC_int_type k_arg_01_0_0;   
k_arg_01_0_0.push_back(RACE_0_ID); k_arg_01_0_0.push_back(WARRIOR_ID); k_arg_01_0_0.push_back(256); k_arg_01_0_0.push_back(256); k_arg_01_0_0.push_back(256);   //COLOR_VIOLET
g_TEXTURE_MANAGER.manage( new TextureOb(SHIP_TEXTURE_ID, "data/ship/k_01_0_0.png", true, &k_arg_01_0_0) );

VEC_int_type k_arg_01_0_1;   
k_arg_01_0_1.push_back(RACE_0_ID); k_arg_01_0_1.push_back(WARRIOR_ID); k_arg_01_0_1.push_back(256); k_arg_01_0_1.push_back(256); k_arg_01_0_1.push_back(256);   //COLOR_VIOLET
g_TEXTURE_MANAGER.manage( new TextureOb(SHIP_TEXTURE_ID, "data/ship/k_01_0_1.png", true, &k_arg_01_0_1) );

VEC_int_type k_arg_02_0_0;   
k_arg_02_0_0.push_back(RACE_0_ID); k_arg_02_0_0.push_back(PIRAT_ID); k_arg_02_0_0.push_back(256); k_arg_02_0_0.push_back(256); k_arg_02_0_0.push_back(256);   //COLOR_VIOLET
g_TEXTURE_MANAGER.manage( new TextureOb(SHIP_TEXTURE_ID, "data/ship/k_02_0_0.png", true, &k_arg_02_0_0) );

VEC_int_type k_arg_03_0_0;   
k_arg_03_0_0.push_back(RACE_0_ID); k_arg_03_0_0.push_back(TRADER_ID); k_arg_03_0_0.push_back(256); k_arg_03_0_0.push_back(256); k_arg_03_0_0.push_back(256);   //COLOR_VIOLET
g_TEXTURE_MANAGER.manage( new TextureOb(SHIP_TEXTURE_ID, "data/ship/k_03_0_0.png", true, &k_arg_03_0_0) );

VEC_int_type k_arg_04_0_0;   
k_arg_04_0_0.push_back(RACE_0_ID); k_arg_04_0_0.push_back(DIPLOMAT_ID); k_arg_04_0_0.push_back(256); k_arg_04_0_0.push_back(256); k_arg_04_0_0.push_back(256);   //COLOR_VIOLET
g_TEXTURE_MANAGER.manage( new TextureOb(SHIP_TEXTURE_ID, "data/ship/k_04_0_0.png", true, &k_arg_04_0_0) );


//################################ race voennye
VEC_int_type k_arg_10_0_0;   
k_arg_10_0_0.push_back(RACE_1_ID); k_arg_10_0_0.push_back(RANGER_ID); k_arg_10_0_0.push_back(256); k_arg_10_0_0.push_back(256); k_arg_10_0_0.push_back(256);   //COLOR_GREY
g_TEXTURE_MANAGER.manage( new TextureOb(SHIP_TEXTURE_ID, "data/ship/k_10_0_0.png", true, &k_arg_10_0_0) );

VEC_int_type k_arg_11_0_0;   
k_arg_11_0_0.push_back(RACE_1_ID); k_arg_11_0_0.push_back(WARRIOR_ID); k_arg_11_0_0.push_back(256); k_arg_11_0_0.push_back(256); k_arg_11_0_0.push_back(256);   //COLOR_GREY
g_TEXTURE_MANAGER.manage( new TextureOb(SHIP_TEXTURE_ID, "data/ship/k_11_0_0.png", true, &k_arg_11_0_0) );

VEC_int_type k_arg_12_0_0;   
k_arg_12_0_0.push_back(RACE_1_ID); k_arg_12_0_0.push_back(PIRAT_ID); k_arg_12_0_0.push_back(256); k_arg_12_0_0.push_back(256); k_arg_12_0_0.push_back(256);   //COLOR_GREY
g_TEXTURE_MANAGER.manage( new TextureOb(SHIP_TEXTURE_ID, "data/ship/k_12_0_0.png", true, &k_arg_12_0_0) );

VEC_int_type k_arg_13_0_0;   
k_arg_13_0_0.push_back(RACE_1_ID); k_arg_13_0_0.push_back(TRADER_ID); k_arg_13_0_0.push_back(256); k_arg_13_0_0.push_back(256); k_arg_13_0_0.push_back(256);   //COLOR_GREY
g_TEXTURE_MANAGER.manage( new TextureOb(SHIP_TEXTURE_ID, "data/ship/k_12_0_0.png", true, &k_arg_13_0_0) );

VEC_int_type k_arg_14_0_0;   
k_arg_14_0_0.push_back(RACE_1_ID); k_arg_14_0_0.push_back(DIPLOMAT_ID); k_arg_14_0_0.push_back(256); k_arg_14_0_0.push_back(256); k_arg_14_0_0.push_back(256);   //COLOR_GREY
g_TEXTURE_MANAGER.manage( new TextureOb(SHIP_TEXTURE_ID, "data/ship/k_14_0_0.png", true, &k_arg_14_0_0) );


//################################ race zhuliki
VEC_int_type race2_ranger_00_arg;   
race2_ranger_00_arg.push_back(RACE_2_ID); race2_ranger_00_arg.push_back(RANGER_ID); race2_ranger_00_arg.push_back(256); race2_ranger_00_arg.push_back(256); race2_ranger_00_arg.push_back(256);   
g_TEXTURE_MANAGER.manage( new TextureOb(SHIP_TEXTURE_ID, "data/ship/race2_ranger_00.png", true, &race2_ranger_00_arg) );

VEC_int_type race2_warrior_00_arg;   
race2_warrior_00_arg.push_back(RACE_2_ID); race2_warrior_00_arg.push_back(WARRIOR_ID); race2_warrior_00_arg.push_back(256); race2_warrior_00_arg.push_back(256); race2_warrior_00_arg.push_back(256);   //COLOR_GREEN
g_TEXTURE_MANAGER.manage( new TextureOb(SHIP_TEXTURE_ID, "data/ship/race2_warrior_00.png", true, &race2_warrior_00_arg) );

VEC_int_type race2_trader_00_arg;   
race2_trader_00_arg.push_back(RACE_2_ID); race2_trader_00_arg.push_back(TRADER_ID); race2_trader_00_arg.push_back(256); race2_trader_00_arg.push_back(256); race2_trader_00_arg.push_back(256);   //COLOR_RED
g_TEXTURE_MANAGER.manage( new TextureOb(SHIP_TEXTURE_ID, "data/ship/race2_trader_00.png", true, &race2_trader_00_arg) );

VEC_int_type race2_pirat_00_arg;   
race2_pirat_00_arg.push_back(RACE_2_ID); race2_pirat_00_arg.push_back(PIRAT_ID); race2_pirat_00_arg.push_back(256); race2_pirat_00_arg.push_back(256); race2_pirat_00_arg.push_back(256);   //COLOR_RED
g_TEXTURE_MANAGER.manage( new TextureOb(SHIP_TEXTURE_ID, "data/ship/race2_pirat_00.png", true, &race2_pirat_00_arg) );

VEC_int_type race2_diplomat_00_arg;   
race2_diplomat_00_arg.push_back(RACE_2_ID); race2_diplomat_00_arg.push_back(DIPLOMAT_ID); race2_diplomat_00_arg.push_back(256); race2_diplomat_00_arg.push_back(256); race2_diplomat_00_arg.push_back(256);   //COLOR_GREEN
g_TEXTURE_MANAGER.manage( new TextureOb(SHIP_TEXTURE_ID, "data/ship/race2_diplomat_00.png", true, &race2_diplomat_00_arg) );


//################################ race cheloveki
VEC_int_type k_arg_30_0_0;   
k_arg_30_0_0.push_back(RACE_3_ID); k_arg_30_0_0.push_back(RANGER_ID); k_arg_30_0_0.push_back(256); k_arg_30_0_0.push_back(256); k_arg_30_0_0.push_back(256);   //COLOR_BLUE
g_TEXTURE_MANAGER.manage( new TextureOb(SHIP_TEXTURE_ID, "data/ship/k_30_0_0.png", true, &k_arg_30_0_0) );

VEC_int_type k_arg_31_0_0;   
k_arg_31_0_0.push_back(RACE_3_ID); k_arg_31_0_0.push_back(WARRIOR_ID); k_arg_31_0_0.push_back(256); k_arg_31_0_0.push_back(256); k_arg_31_0_0.push_back(256);   //COLOR_BLUE
g_TEXTURE_MANAGER.manage( new TextureOb(SHIP_TEXTURE_ID, "data/ship/k_31_0_0.png", true, &k_arg_31_0_0) );

VEC_int_type k_arg_31_0_1;   
k_arg_31_0_1.push_back(RACE_3_ID); k_arg_31_0_1.push_back(WARRIOR_ID); k_arg_31_0_1.push_back(256); k_arg_31_0_1.push_back(256); k_arg_31_0_1.push_back(256);   //COLOR_BLUE
g_TEXTURE_MANAGER.manage( new TextureOb(SHIP_TEXTURE_ID, "data/ship/k_31_0_1.png", true, &k_arg_31_0_1) );

VEC_int_type k_arg_32_0_0;   
k_arg_32_0_0.push_back(RACE_3_ID); k_arg_32_0_0.push_back(PIRAT_ID); k_arg_32_0_0.push_back(256); k_arg_32_0_0.push_back(256); k_arg_32_0_0.push_back(256);   //COLOR_BLUE
g_TEXTURE_MANAGER.manage( new TextureOb(SHIP_TEXTURE_ID, "data/ship/k_32_0_0.png", true, &k_arg_32_0_0) );

VEC_int_type k_arg_33_0_0;   
k_arg_33_0_0.push_back(RACE_3_ID); k_arg_33_0_0.push_back(TRADER_ID); k_arg_33_0_0.push_back(256); k_arg_33_0_0.push_back(256); k_arg_33_0_0.push_back(256);   //COLOR_BLUE
g_TEXTURE_MANAGER.manage( new TextureOb(SHIP_TEXTURE_ID, "data/ship/_k_33_0_0.png", true, &k_arg_33_0_0) );

VEC_int_type k_arg_34_0_0;   
k_arg_34_0_0.push_back(RACE_3_ID); k_arg_34_0_0.push_back(DIPLOMAT_ID); k_arg_34_0_0.push_back(256); k_arg_34_0_0.push_back(256); k_arg_34_0_0.push_back(256);   //COLOR_BLUE
g_TEXTURE_MANAGER.manage( new TextureOb(SHIP_TEXTURE_ID, "data/ship/_k_34_0_0.png", true, &k_arg_34_0_0) );


//################################ race bio
VEC_int_type k_arg_41_0_0;   
k_arg_41_0_0.push_back(RACE_4_ID); k_arg_41_0_0.push_back(WARRIOR_ID); k_arg_41_0_0.push_back(256); k_arg_41_0_0.push_back(256); k_arg_41_0_0.push_back(256);   //COLOR_GOLDENROD
g_TEXTURE_MANAGER.manage( new TextureOb(SHIP_TEXTURE_ID, "data/ship/k_41_0_0.png", true, &k_arg_41_0_0) );

VEC_int_type k_arg_43_0_0;   
k_arg_43_0_0.push_back(RACE_4_ID); k_arg_43_0_0.push_back(TRADER_ID); k_arg_43_0_0.push_back(256); k_arg_43_0_0.push_back(256); k_arg_43_0_0.push_back(256);   //COLOR_GOLDENROD
g_TEXTURE_MANAGER.manage( new TextureOb(SHIP_TEXTURE_ID, "data/ship/k_43_0_0.png", true, &k_arg_43_0_0) );

VEC_int_type k_arg_43_0_1;   
k_arg_43_0_1.push_back(RACE_4_ID); k_arg_43_0_1.push_back(TRADER_ID); k_arg_43_0_1.push_back(256); k_arg_43_0_1.push_back(256); k_arg_43_0_1.push_back(256);   //COLOR_GOLDENROD
g_TEXTURE_MANAGER.manage( new TextureOb(SHIP_TEXTURE_ID, "data/ship/k_43_0_1.png", true, &k_arg_43_0_1) );

VEC_int_type k_arg_44_0_0;   
k_arg_44_0_0.push_back(RACE_4_ID); k_arg_44_0_0.push_back(DIPLOMAT_ID); k_arg_44_0_0.push_back(256); k_arg_44_0_0.push_back(256); k_arg_44_0_0.push_back(256);   //COLOR_GOLDENROD
g_TEXTURE_MANAGER.manage( new TextureOb(SHIP_TEXTURE_ID, "data/ship/k_44_0_0.png", true, &k_arg_44_0_0) );


//################################ enemy 1
VEC_int_type k_arg_61_0_0;   
k_arg_61_0_0.push_back(RACE_6_ID); k_arg_61_0_0.push_back(WARRIOR_ID); k_arg_61_0_0.push_back(256); k_arg_61_0_0.push_back(256); k_arg_61_0_0.push_back(256);   //COLOR_GOLDENROD
g_TEXTURE_MANAGER.manage( new TextureOb(SHIP_TEXTURE_ID, "data/ship/k_61_0_0.png", true, &k_arg_61_0_0) );

VEC_int_type k_arg_61_0_1;   
k_arg_61_0_1.push_back(RACE_6_ID); k_arg_61_0_1.push_back(WARRIOR_ID); k_arg_61_0_1.push_back(256); k_arg_61_0_1.push_back(256); k_arg_61_0_1.push_back(256);   //COLOR_GOLDENROD
g_TEXTURE_MANAGER.manage( new TextureOb(SHIP_TEXTURE_ID, "data/ship/k_61_0_1.png", true, &k_arg_61_0_1) );

VEC_int_type k_arg_61_0_2;   
k_arg_61_0_2.push_back(RACE_6_ID); k_arg_61_0_2.push_back(WARRIOR_ID); k_arg_61_0_2.push_back(256); k_arg_61_0_2.push_back(256); k_arg_61_0_2.push_back(256);   //COLOR_GOLDENROD
g_TEXTURE_MANAGER.manage( new TextureOb(SHIP_TEXTURE_ID, "data/ship/k_61_0_2.png", true, &k_arg_61_0_2) );




VEC_int_type k_arg_61_0_3;   
k_arg_61_0_3.push_back(RACE_6_ID); k_arg_61_0_3.push_back(WARRIOR_ID); k_arg_61_0_3.push_back(256); k_arg_61_0_3.push_back(256); k_arg_61_0_3.push_back(256);   //COLOR_GOLDENROD
g_TEXTURE_MANAGER.manage( new TextureOb(SHIP_TEXTURE_ID, "data/ship/k_61_0_3.png", true, &k_arg_61_0_3) );

VEC_int_type k_arg_61_0_4;   
k_arg_61_0_4.push_back(RACE_6_ID); k_arg_61_0_4.push_back(WARRIOR_ID); k_arg_61_0_4.push_back(256); k_arg_61_0_4.push_back(256); k_arg_61_0_4.push_back(256);   //COLOR_GOLDENROD
g_TEXTURE_MANAGER.manage( new TextureOb(SHIP_TEXTURE_ID, "data/ship/k_61_0_4.png", true, &k_arg_61_0_4) );

VEC_int_type k_arg_61_0_5;   
k_arg_61_0_5.push_back(RACE_6_ID); k_arg_61_0_5.push_back(WARRIOR_ID); k_arg_61_0_5.push_back(256); k_arg_61_0_5.push_back(256); k_arg_61_0_5.push_back(256);   //COLOR_GOLDENROD
g_TEXTURE_MANAGER.manage( new TextureOb(SHIP_TEXTURE_ID, "data/ship/k_61_0_5.png", true, &k_arg_61_0_5) );

VEC_int_type k_arg_61_0_6;   
k_arg_61_0_6.push_back(RACE_6_ID); k_arg_61_0_6.push_back(WARRIOR_ID); k_arg_61_0_6.push_back(256); k_arg_61_0_6.push_back(256); k_arg_61_0_6.push_back(256);   //COLOR_GOLDENROD
g_TEXTURE_MANAGER.manage( new TextureOb(SHIP_TEXTURE_ID, "data/ship/k_61_0_6.png", true, &k_arg_61_0_6) );

VEC_int_type k_arg_61_0_7;   
k_arg_61_0_7.push_back(RACE_6_ID); k_arg_61_0_7.push_back(WARRIOR_ID); k_arg_61_0_7.push_back(256); k_arg_61_0_7.push_back(256); k_arg_61_0_7.push_back(256);   //COLOR_GOLDENROD
g_TEXTURE_MANAGER.manage( new TextureOb(SHIP_TEXTURE_ID, "data/ship/k_61_0_7.png", true, &k_arg_61_0_7) );

VEC_int_type k_arg_61_0_8;   
k_arg_61_0_8.push_back(RACE_6_ID); k_arg_61_0_8.push_back(WARRIOR_ID); k_arg_61_0_8.push_back(256); k_arg_61_0_8.push_back(256); k_arg_61_0_8.push_back(256);   //COLOR_GOLDENROD
g_TEXTURE_MANAGER.manage( new TextureOb(SHIP_TEXTURE_ID, "data/ship/k_61_0_8.png", true, &k_arg_61_0_8) );

VEC_int_type k_arg_61_0_9;   
k_arg_61_0_9.push_back(RACE_6_ID); k_arg_61_0_9.push_back(WARRIOR_ID); k_arg_61_0_9.push_back(256); k_arg_61_0_9.push_back(256); k_arg_61_0_9.push_back(256);   //COLOR_GOLDENROD
g_TEXTURE_MANAGER.manage( new TextureOb(SHIP_TEXTURE_ID, "data/ship/k_61_0_9.png", true, &k_arg_61_0_9) );


VEC_int_type k_arg_61_0_10;   
k_arg_61_0_10.push_back(RACE_6_ID); k_arg_61_0_10.push_back(WARRIOR_ID); k_arg_61_0_10.push_back(256); k_arg_61_0_10.push_back(256); k_arg_61_0_10.push_back(256);   //COLOR_GOLDENROD
g_TEXTURE_MANAGER.manage( new TextureOb(SHIP_TEXTURE_ID, "data/ship/k_61_0_10.png", true, &k_arg_61_0_10) );

VEC_int_type k_arg_61_0_11;   
k_arg_61_0_11.push_back(RACE_6_ID); k_arg_61_0_11.push_back(WARRIOR_ID); k_arg_61_0_11.push_back(256); k_arg_61_0_11.push_back(256); k_arg_61_0_11.push_back(256);   //COLOR_GOLDENROD
g_TEXTURE_MANAGER.manage( new TextureOb(SHIP_TEXTURE_ID, "data/ship/k_61_0_11.png", true, &k_arg_61_0_11) );

VEC_int_type k_arg_61_0_12;   
k_arg_61_0_12.push_back(RACE_6_ID); k_arg_61_0_12.push_back(WARRIOR_ID); k_arg_61_0_12.push_back(256); k_arg_61_0_12.push_back(256); k_arg_61_0_12.push_back(256);   //COLOR_GOLDENROD
g_TEXTURE_MANAGER.manage( new TextureOb(SHIP_TEXTURE_ID, "data/ship/k_61_0_12.png", true, &k_arg_61_0_12) );

VEC_int_type k_arg_61_0_13;   
k_arg_61_0_13.push_back(RACE_6_ID); k_arg_61_0_13.push_back(WARRIOR_ID); k_arg_61_0_13.push_back(256); k_arg_61_0_13.push_back(256); k_arg_61_0_13.push_back(256);   //COLOR_GOLDENROD
g_TEXTURE_MANAGER.manage( new TextureOb(SHIP_TEXTURE_ID, "data/ship/k_61_0_13.png", true, &k_arg_61_0_13) );

VEC_int_type k_arg_61_0_g13;   
k_arg_61_0_g13.push_back(RACE_6_ID); k_arg_61_0_g13.push_back(WARRIOR_ID); k_arg_61_0_g13.push_back(256); k_arg_61_0_g13.push_back(256); k_arg_61_0_g13.push_back(256);   //COLOR_GOLDENROD
g_TEXTURE_MANAGER.manage( new TextureOb(SHIP_TEXTURE_ID, "data/ship/k_61_0_g13.png", true, &k_arg_61_0_g13) );

//################################ enemy 2
VEC_int_type k_arg_71_0_0;   
k_arg_71_0_0.push_back(RACE_7_ID); k_arg_71_0_0.push_back(WARRIOR_ID); k_arg_71_0_0.push_back(256); k_arg_71_0_0.push_back(256); k_arg_71_0_0.push_back(256);   //COLOR_GOLDENROD
g_TEXTURE_MANAGER.manage( new TextureOb(SHIP_TEXTURE_ID, "data/ship/k_71_0_0.png", true, &k_arg_71_0_0) );

VEC_int_type k_arg_71_0_1;   
k_arg_71_0_1.push_back(RACE_7_ID); k_arg_71_0_1.push_back(WARRIOR_ID); k_arg_71_0_1.push_back(256); k_arg_71_0_1.push_back(256); k_arg_71_0_1.push_back(256);   //COLOR_GOLDENROD
g_TEXTURE_MANAGER.manage( new TextureOb(SHIP_TEXTURE_ID, "data/ship/k_71_0_1.png", true, &k_arg_71_0_1) );

g_TEXTURE_MANAGER.DEBUG_CheckShipTexOb();

//################################# STAR_TEXTURE_ID ###############################
VEC_int_type s_000_arg;   
s_000_arg.push_back(YELLOW_COLOR_ID); s_000_arg.push_back(1900); 
g_TEXTURE_MANAGER.manage( new TextureOb(STAR_TEXTURE_ID, "data/star/s_000.jpg", false, &s_000_arg) ); 

VEC_int_type s_001_arg; 
s_001_arg.push_back(YELLOW_COLOR_ID); s_001_arg.push_back(1825); 
g_TEXTURE_MANAGER.manage( new TextureOb(STAR_TEXTURE_ID, "data/star/s_001.png", false, &s_001_arg) ); 

VEC_int_type s_100_arg; 
s_100_arg.push_back(BLUE_COLOR_ID); s_100_arg.push_back(2525); 
g_TEXTURE_MANAGER.manage( new TextureOb(STAR_TEXTURE_ID, "data/star/s_100.jpg", false, &s_100_arg) ); 

VEC_int_type s_101_arg; 
s_101_arg.push_back(BLUE_COLOR_ID); s_101_arg.push_back(1925); 
g_TEXTURE_MANAGER.manage( new TextureOb(STAR_TEXTURE_ID, "data/star/s_101.png", false, &s_101_arg) ); 



//################################## NEBULA EFFECT ################################
VEC_int_type narg1;   //[(1.0, 1.0, 1.0), 2, False]) )
narg1.push_back(256); narg1.push_back(256); narg1.push_back(256); narg1.push_back(0);
g_TEXTURE_MANAGER.manage( new TextureOb(NEBULA_TEXTURE_ID, "data/bg_space/nebula.bak/nebula1.png", true, &narg1) );                                         

VEC_int_type narg2;   //[(1.0, 1.0, 1.0), 4, True]) )
narg2.push_back(256); narg2.push_back(256); narg2.push_back(256); narg2.push_back(1);
g_TEXTURE_MANAGER.manage( new TextureOb(NEBULA_TEXTURE_ID, "data/bg_space/nebula.bak/nebula2.png", true, &narg2) );   

VEC_int_type narg3;   //[(1.0, 1.0, 1.0), 2, False]) )
narg3.push_back(256); narg3.push_back(256); narg3.push_back(256); narg3.push_back(0);
g_TEXTURE_MANAGER.manage( new TextureOb(NEBULA_TEXTURE_ID, "data/bg_space/nebula.bak/nebula3.png", true, &narg3) );   

VEC_int_type narg4;   //[(1.0, 1.0, 1.0), 4, True]) )
narg4.push_back(256); narg4.push_back(256); narg4.push_back(256); narg4.push_back(1);
g_TEXTURE_MANAGER.manage( new TextureOb(NEBULA_TEXTURE_ID, "data/bg_space/nebula.bak/nebula4.png", true, &narg4) ); 

VEC_int_type narg5;   //[(1.0, 1.0, 1.0), 2, False]) )
narg5.push_back(256); narg5.push_back(256); narg5.push_back(256); narg5.push_back(0);
g_TEXTURE_MANAGER.manage( new TextureOb(NEBULA_TEXTURE_ID, "data/bg_space/nebula.bak/nebula5.png", true, &narg5) ); 

VEC_int_type narg6;   //[(1.0, 1.0, 1.0), 2, False]) )
narg6.push_back(256); narg6.push_back(256); narg6.push_back(256); narg6.push_back(0);
g_TEXTURE_MANAGER.manage( new TextureOb(NEBULA_TEXTURE_ID, "data/bg_space/nebula.bak/nebula6.png", true, &narg6) ); 

VEC_int_type narg7;   //[(1.0, 1.0, 1.0), 2, False]) )
narg7.push_back(256); narg7.push_back(256); narg7.push_back(256); narg7.push_back(0);
g_TEXTURE_MANAGER.manage( new TextureOb(NEBULA_TEXTURE_ID, "data/bg_space/nebula.bak/nebula7.png", true, &narg7) ); 


VEC_int_type narg8;   //[(1.0, 1.0, 1.0), 2, True]) )
narg8.push_back(256); narg8.push_back(256); narg8.push_back(256); narg8.push_back(1);
g_TEXTURE_MANAGER.manage( new TextureOb(NEBULA_TEXTURE_ID, "data/bg_space/nebula.bak/nebula8.png", true, &narg8) ); 

VEC_int_type narg9;   //[(1.0, 1.0, 1.0), 2, True]) )
narg9.push_back(256); narg9.push_back(256); narg9.push_back(256); narg9.push_back(1);
g_TEXTURE_MANAGER.manage( new TextureOb(NEBULA_TEXTURE_ID, "data/bg_space/nebula.bak/nebula9.png", true, &narg9) ); 


VEC_int_type narg10;   //[(1.0, 1.0, 1.0), 4, False]) )
narg10.push_back(256); narg10.push_back(256); narg10.push_back(256); narg10.push_back(0);
g_TEXTURE_MANAGER.manage( new TextureOb(NEBULA_TEXTURE_ID, "data/bg_space/nebula.bak/nebula10.png", true, &narg10) ); 

VEC_int_type narg11;   // [(1.0, 1.0, 1.0), 2, False]) )
narg11.push_back(256); narg11.push_back(256); narg11.push_back(256); narg11.push_back(0);
g_TEXTURE_MANAGER.manage( new TextureOb(NEBULA_TEXTURE_ID, "data/bg_space/nebula.bak/nebula11.png", true, &narg11) ); 

VEC_int_type narg12;   // [(1.0, 1.0, 1.0), 4, False]) )
narg12.push_back(256); narg12.push_back(256); narg12.push_back(256); narg12.push_back(0);
g_TEXTURE_MANAGER.manage( new TextureOb(NEBULA_TEXTURE_ID, "data/bg_space/nebula.bak/nebula12.png", true, &narg12) ); 

VEC_int_type narg13;   // [(1.0, 1.0, 1.0), 4, False]) )
narg13.push_back(256); narg13.push_back(256); narg13.push_back(256); narg13.push_back(0);
g_TEXTURE_MANAGER.manage( new TextureOb(NEBULA_TEXTURE_ID, "data/bg_space/nebula.bak/nebula13.png", true, &narg13) ); 


VEC_int_type narg14;   // [(1.0, 1.0, 1.0), 4, True]) )
narg14.push_back(256); narg14.push_back(256); narg14.push_back(256); narg14.push_back(1);
g_TEXTURE_MANAGER.manage( new TextureOb(NEBULA_TEXTURE_ID, "data/bg_space/nebula.bak/nebula14.png", true, &narg14) ); 

VEC_int_type narg15;   // [(1.0, 1.0, 1.0), 2, True]) )
narg15.push_back(256); narg15.push_back(256); narg15.push_back(256); narg13.push_back(1);
g_TEXTURE_MANAGER.manage( new TextureOb(NEBULA_TEXTURE_ID, "data/bg_space/nebula.bak/nebula15.png", true, &narg15) ); 


VEC_int_type narg16;   // [(1.0, 1.0, 1.0), 4, False]) )
narg16.push_back(256); narg16.push_back(256); narg16.push_back(256); narg16.push_back(0);
g_TEXTURE_MANAGER.manage( new TextureOb(NEBULA_TEXTURE_ID, "data/bg_space/nebula.bak/nebula16.png", true, &narg16) ); 

VEC_int_type narg17;   // [(1.0, 1.0, 1.0), 4, False]) )
narg17.push_back(256); narg17.push_back(256); narg17.push_back(256); narg17.push_back(0);
g_TEXTURE_MANAGER.manage( new TextureOb(NEBULA_TEXTURE_ID, "data/bg_space/nebula.bak/nebula17.png", true, &narg17) ); 

VEC_int_type narg18;   // [(1.0, 1.0, 1.0), 2, False]) )
narg18.push_back(256); narg18.push_back(256); narg18.push_back(256); narg18.push_back(0);
g_TEXTURE_MANAGER.manage( new TextureOb(NEBULA_TEXTURE_ID, "data/bg_space/nebula.bak/nebula18.png", true, &narg18) ); 

VEC_int_type narg19;   //  [(1.0, 1.0, 1.0), 4, False]) )
narg19.push_back(256); narg19.push_back(256); narg19.push_back(256); narg19.push_back(0); 
g_TEXTURE_MANAGER.manage( new TextureOb(NEBULA_TEXTURE_ID, "data/bg_space/nebula.bak/nebula19.png", true, &narg19) ); 
//### size 2 = 512x512
//### size 4 = 1024x1024 or 512x1024

//################################ LAND_BG_TEXTURE_ID ###################################
VEC_int_type landBg_arg0; 
g_TEXTURE_MANAGER.manage( new TextureOb(LAND_BG_TEXTURE_ID, "data/bg_uninhabited/b_000.jpg", false, &landBg_arg0) );

VEC_int_type landBg_arg1; 
g_TEXTURE_MANAGER.manage( new TextureOb(LAND_BG_TEXTURE_ID, "data/bg_uninhabited/b_001.png", false, &landBg_arg1) );

VEC_int_type landBg_arg2; 
g_TEXTURE_MANAGER.manage( new TextureOb(LAND_BG_TEXTURE_ID, "data/bg_uninhabited/b_002.png", false, &landBg_arg2) );


//################################ KOSMOPORT_BG_TEXTURE_ID ###############################
VEC_int_type angarBg_arg0; 
angarBg_arg0.push_back(RACE_0_ID);
g_TEXTURE_MANAGER.manage( new TextureOb(ANGAR_BG_TEXTURE_ID, "data/bg_kosmoport/an_000.jpg", false, &angarBg_arg0) );

VEC_int_type storeBg_arg0; 
storeBg_arg0.push_back(RACE_0_ID);
g_TEXTURE_MANAGER.manage( new TextureOb(STORE_BG_TEXTURE_ID, "data/bg_kosmoport/st_000.jpg", false, &storeBg_arg0) );

VEC_int_type shopBg_arg0; 
shopBg_arg0.push_back(RACE_0_ID);
g_TEXTURE_MANAGER.manage( new TextureOb(SHOP_BG_TEXTURE_ID, "data/bg_kosmoport/sh_000.jpg", false, &shopBg_arg0) );

VEC_int_type govermentBg_arg0; 
govermentBg_arg0.push_back(RACE_0_ID);
g_TEXTURE_MANAGER.manage( new TextureOb(GOVERMENT_BG_TEXTURE_ID, "data/bg_kosmoport/go_000.jpg", false, &govermentBg_arg0) );



//################################ PLANET_TEXTURE ####################################
VEC_int_type pArg0000; 
pArg0000.push_back(PLANET_EARTH_SURFACE_ID); pArg0000.push_back(5);
g_TEXTURE_MANAGER.manage( new TextureOb(PLANET_TEXTURE_ID, "data/planet/p_0000.png", false, &pArg0000) );

VEC_int_type pArg1000; 
pArg1000.push_back(PLANET_WATER_SURFACE_ID); pArg1000.push_back(5);
g_TEXTURE_MANAGER.manage( new TextureOb(PLANET_TEXTURE_ID, "data/planet/p_1000.png", false, &pArg0000) );

VEC_int_type pArg2000; 
pArg2000.push_back(PLANET_LAVA_SURFACE_ID); pArg2000.push_back(5);
g_TEXTURE_MANAGER.manage( new TextureOb(PLANET_TEXTURE_ID, "data/planet/p_2000.png", false, &pArg2000) );

VEC_int_type pArg3000; 
pArg3000.push_back(PLANET_ICE_SURFACE_ID); pArg3000.push_back(5);
g_TEXTURE_MANAGER.manage( new TextureOb(PLANET_TEXTURE_ID, "data/planet/p_3000.png", false, &pArg3000) );

VEC_int_type pArg4000; 
pArg4000.push_back(PLANET_GAS_SURFACE_ID); pArg4000.push_back(5);
g_TEXTURE_MANAGER.manage( new TextureOb(PLANET_TEXTURE_ID, "data/planet/p_4000.png", false, &pArg4000) );


//################################ ATMOSPHERE_TEXTURE ####################################
VEC_int_type atmosphere_arg_000; 
g_TEXTURE_MANAGER.manage( new TextureOb(ATMOSPHERE_TEXTURE_ID, "data/planet/atmosphere_000.png", true, &atmosphere_arg_000) );

VEC_int_type atmosphere_arg_001; 
g_TEXTURE_MANAGER.manage( new TextureOb(ATMOSPHERE_TEXTURE_ID, "data/planet/atmosphere_001.png", true, &atmosphere_arg_001) );



//################################ EFFECTS TEXTURE ###################################
VEC_int_type particle_Arg0;  
particle_Arg0.push_back(RED_COLOR_ID); 
g_TEXTURE_MANAGER.manage( new TextureOb(PARTICLE_TEXTURE_ID, "data/effect/particles/particle0.png", true, &particle_Arg0) ); 

VEC_int_type particle_Arg1;  
particle_Arg1.push_back(BLUE_COLOR_ID); 
g_TEXTURE_MANAGER.manage( new TextureOb(PARTICLE_TEXTURE_ID, "data/effect/particles/particle1.png", true, &particle_Arg1) ); 

VEC_int_type particle_Arg2;  
particle_Arg2.push_back(YELLOW_COLOR_ID); 
g_TEXTURE_MANAGER.manage( new TextureOb(PARTICLE_TEXTURE_ID, "data/effect/particles/particle2.png", true, &particle_Arg2) ); 

VEC_int_type particle_Arg3;  
particle_Arg3.push_back(GREY_COLOR_ID); 
g_TEXTURE_MANAGER.manage( new TextureOb(PARTICLE_TEXTURE_ID, "data/effect/particles/particle3.png", true, &particle_Arg3) ); 


VEC_int_type lazer_effect_arg0;  
lazer_effect_arg0.push_back(TECH_LEVEL_0_ID); lazer_effect_arg0.push_back(BLUE_COLOR_ID); 
g_TEXTURE_MANAGER.manage( new TextureOb(LAZER_EFFECT_TEXTURE_ID, "data/effect/lazer/l_64_26_000.png", true, &lazer_effect_arg0, 4, 1, 10) );

VEC_int_type lazer_effect_arg1;  
lazer_effect_arg1.push_back(TECH_LEVEL_0_ID); lazer_effect_arg1.push_back(RED_COLOR_ID); 
g_TEXTURE_MANAGER.manage( new TextureOb(LAZER_EFFECT_TEXTURE_ID, "data/effect/lazer/l_001.png", true, &lazer_effect_arg1) );

VEC_int_type lazer_effect_arg2;  
lazer_effect_arg2.push_back(TECH_LEVEL_0_ID); lazer_effect_arg1.push_back(YELLOW_COLOR_ID); 
g_TEXTURE_MANAGER.manage( new TextureOb(LAZER_EFFECT_TEXTURE_ID, "data/effect/lazer/l_002.png", true, &lazer_effect_arg2) );

VEC_int_type lazer_effect_arg3;  
lazer_effect_arg3.push_back(TECH_LEVEL_0_ID); lazer_effect_arg3.push_back(BLUE_COLOR_ID); 
g_TEXTURE_MANAGER.manage( new TextureOb(LAZER_EFFECT_TEXTURE_ID, "data/effect/lazer/l_003.png", true, &lazer_effect_arg3) );


VEC_int_type shield_effect_arg0;  
shield_effect_arg0.push_back(RED_COLOR_ID); 
g_TEXTURE_MANAGER.manage( new TextureOb(SHIELD_EFFECT_TEXTURE_ID, "data/effect/shield/shield0.png", true, &shield_effect_arg0) );

VEC_int_type shield_effect_arg1;  
shield_effect_arg1.push_back(GREEN_COLOR_ID); 
g_TEXTURE_MANAGER.manage( new TextureOb(SHIELD_EFFECT_TEXTURE_ID, "data/effect/shield/shield1.png", true, &shield_effect_arg1) );

VEC_int_type shield_effect_arg2;  
shield_effect_arg2.push_back(BLUE_COLOR_ID); 
g_TEXTURE_MANAGER.manage( new TextureOb(SHIELD_EFFECT_TEXTURE_ID, "data/effect/shield/shield2.png", true, &shield_effect_arg2) );

VEC_int_type shield_effect_arg3;  
shield_effect_arg3.push_back(YELLOW_COLOR_ID); 
g_TEXTURE_MANAGER.manage( new TextureOb(SHIELD_EFFECT_TEXTURE_ID, "data/effect/shield/shield3.png", true, &shield_effect_arg3) );


//TEXTURE_MANAGER.manage( textureOb(DISTANTSTAR_TEXTURE_ID, 'data/star/s1.png', True, []) )
//TEXTURE_MANAGER.manage( textureOb(DISTANTSTAR_TEXTURE_ID, 'data/star/s2.png', True, []) )



//###################################### ITEM TEXTURE ###################################
//############################ DRIVE_ITEM
//#################### RACE_0
//####### TECH_LEVEL_0
VEC_int_type drive_Race0_Tech0_arg;  
drive_Race0_Tech0_arg.push_back(RACE_0_ID); drive_Race0_Tech0_arg.push_back(TECH_LEVEL_0_ID);  
g_TEXTURE_MANAGER.manageItem( new TextureOb(DRIVE_ITEM_TEXTURE_ID, "data/item/drive/drive_Race0_Tech0.png", true, &drive_Race0_Tech0_arg) );

//####### TECH_LEVEL_1
VEC_int_type drive_Race0_Tech1_arg;  
drive_Race0_Tech1_arg.push_back(RACE_0_ID); drive_Race0_Tech1_arg.push_back(TECH_LEVEL_1_ID);  
g_TEXTURE_MANAGER.manageItem( new TextureOb(DRIVE_ITEM_TEXTURE_ID, "data/item/drive/drive_Race0_Tech1.png", true, &drive_Race0_Tech1_arg) );

//####### TECH_LEVEL_2
VEC_int_type drive_Race0_Tech2_arg;  
drive_Race0_Tech2_arg.push_back(RACE_0_ID); drive_Race0_Tech2_arg.push_back(TECH_LEVEL_2_ID); 
g_TEXTURE_MANAGER.manageItem( new TextureOb(DRIVE_ITEM_TEXTURE_ID, "data/item/drive/drive_Race0_Tech2.png", true, &drive_Race0_Tech1_arg) );

//#################### RACE1
//#################### RACE2
//#################### RACE3
//#################### RACE4

//#################### RACE6
//#################### RACE7



//############################ LAZER_ITEM
//#################### RACE_0
//####### TECH_LEVEL_0
VEC_int_type lazer_Race0_Tech0_Red0_arg;  
lazer_Race0_Tech0_Red0_arg.push_back(RACE_0_ID); lazer_Race0_Tech0_Red0_arg.push_back(TECH_LEVEL_0_ID); lazer_Race0_Tech0_Red0_arg.push_back(RED_COLOR_ID); 
g_TEXTURE_MANAGER.manageItem( new TextureOb(LAZER_ITEM_TEXTURE_ID, "data/item/lazer/lazer_Race0_Tech0_Red0.png", true, &lazer_Race0_Tech0_Red0_arg) );

VEC_int_type lazer_Race0_Tech0_Yellow0_arg;  
lazer_Race0_Tech0_Yellow0_arg.push_back(RACE_0_ID); lazer_Race0_Tech0_Yellow0_arg.push_back(TECH_LEVEL_0_ID); lazer_Race0_Tech0_Yellow0_arg.push_back(YELLOW_COLOR_ID); 
g_TEXTURE_MANAGER.manageItem( new TextureOb(LAZER_ITEM_TEXTURE_ID, "data/item/lazer/lazer_Race0_Tech0_Yellow0.png", true, &lazer_Race0_Tech0_Yellow0_arg) );

VEC_int_type lazer_Race0_Tech0_Blue0_arg;  
lazer_Race0_Tech0_Blue0_arg.push_back(RACE_0_ID); lazer_Race0_Tech0_Blue0_arg.push_back(TECH_LEVEL_0_ID); lazer_Race0_Tech0_Blue0_arg.push_back(BLUE_COLOR_ID); 
g_TEXTURE_MANAGER.manageItem( new TextureOb(LAZER_ITEM_TEXTURE_ID, "data/item/lazer/lazer_Race0_Tech0_Blue0.png", true, &lazer_Race0_Tech0_Blue0_arg) );

//####### TECH_LEVEL_1
VEC_int_type lazer_Race0_Tech1_Blue0_arg;  
lazer_Race0_Tech1_Blue0_arg.push_back(RACE_0_ID); lazer_Race0_Tech1_Blue0_arg.push_back(TECH_LEVEL_1_ID); lazer_Race0_Tech1_Blue0_arg.push_back(BLUE_COLOR_ID); 
g_TEXTURE_MANAGER.manageItem( new TextureOb(LAZER_ITEM_TEXTURE_ID, "data/item/lazer/lazer_Race0_Tech1_Blue0.png", true, &lazer_Race0_Tech1_Blue0_arg) );

//#################### RACE_1
//#################### RACE_2
//#################### RACE_3
//#################### RACE_4

//#################### RACE_6
//#################### RACE_7



//############################ LAZER_ITEM
//#################### RACE_0
//####### TECH_LEVEL_0
VEC_int_type rocket_Race0_Tech0_arg;  
rocket_Race0_Tech0_arg.push_back(RACE_0_ID); rocket_Race0_Tech0_arg.push_back(TECH_LEVEL_0_ID); rocket_Race0_Tech0_arg.push_back(YELLOW_COLOR_ID); 
g_TEXTURE_MANAGER.manageItem( new TextureOb(ROCKET_ITEM_TEXTURE_ID, "data/item/rocket/rocket_Race0_Tech0.png", true, &rocket_Race0_Tech0_arg) );
//####### TECH_LEVEL_1
VEC_int_type rocket_Race0_Tech1_arg;  
rocket_Race0_Tech1_arg.push_back(RACE_0_ID); rocket_Race0_Tech1_arg.push_back(TECH_LEVEL_1_ID); rocket_Race0_Tech1_arg.push_back(YELLOW_COLOR_ID); 
g_TEXTURE_MANAGER.manageItem( new TextureOb(ROCKET_ITEM_TEXTURE_ID, "data/item/rocket/rocket_Race0_Tech1.png", true, &rocket_Race0_Tech1_arg) );
//####### TECH_LEVEL_2
VEC_int_type rocket_Race0_Tech2_arg;  
rocket_Race0_Tech2_arg.push_back(RACE_0_ID); rocket_Race0_Tech2_arg.push_back(TECH_LEVEL_1_ID); rocket_Race0_Tech2_arg.push_back(YELLOW_COLOR_ID); 
g_TEXTURE_MANAGER.manageItem( new TextureOb(ROCKET_ITEM_TEXTURE_ID, "data/item/rocket/rocket_Race0_Tech2.png", true, &rocket_Race0_Tech2_arg) );


//TEXTURE_MANAGER.manageItem( textureOb(TORPED_ITEM_TEXTURE_ID, 'data/item/torped/tl0.png', True, [ 'torpedo',       TECH_LEVEL_0_ID, 3, 1, RACE_0_ID, YELLOW_COLOR_ID]) )
//TEXTURE_MANAGER.manageItem( textureOb(TORPED_ITEM_TEXTURE_ID, 'data/item/torped/tl1.png', True, [ 'torpedo',       TECH_LEVEL_0_ID, 3, 1, RACE_0_ID, YELLOW_COLOR_ID]) )


VEC_int_type rocket_bullet0_arg;  
g_TEXTURE_MANAGER.manage( new TextureOb(ROCKET_BULLET_TEXTURE_ID, "data/bullet/r_0.png", true, &rocket_bullet0_arg) );

VEC_int_type rocket_bullet1_arg;  
g_TEXTURE_MANAGER.manage( new TextureOb(ROCKET_BULLET_TEXTURE_ID, "data/bullet/r_1.png", true, &rocket_bullet1_arg) );

//TEXTURE_MANAGER.manage( textureOb(TORPED_BULLET_TEXTURE_ID, 'data/bullet/t_0.png', True, []) )
//TEXTURE_MANAGER.manage( textureOb(TORPED_BULLET_TEXTURE_ID, 'data/bullet/t_1.png', True, []) )



//############################ PROTECTOR_ITEM
//#################### RACE_0
//####### TECH_LEVEL_0
VEC_int_type protector_Race0_Tech0_arg;  
protector_Race0_Tech0_arg.push_back(RACE_0_ID); protector_Race0_Tech0_arg.push_back(TECH_LEVEL_0_ID); 
g_TEXTURE_MANAGER.manageItem( new TextureOb(PROTECTOR_ITEM_TEXTURE_ID, "data/item/protector/protector_Race0_Tech0.png", true, &protector_Race0_Tech0_arg) );

//####### TECH_LEVEL_1
VEC_int_type protector_Race0_Tech1_arg;  
protector_Race0_Tech1_arg.push_back(RACE_0_ID); protector_Race0_Tech1_arg.push_back(TECH_LEVEL_1_ID); 
g_TEXTURE_MANAGER.manageItem( new TextureOb(PROTECTOR_ITEM_TEXTURE_ID, "data/item/protector/protector_Race0_Tech1.png", true, &protector_Race0_Tech1_arg) );

//####### TECH_LEVEL_2
VEC_int_type protector_Race0_Tech2_arg;  
protector_Race0_Tech2_arg.push_back(RACE_0_ID); protector_Race0_Tech2_arg.push_back(TECH_LEVEL_2_ID); 
g_TEXTURE_MANAGER.manageItem( new TextureOb(PROTECTOR_ITEM_TEXTURE_ID, "data/item/protector/protector_Race0_Tech2.png", true, &protector_Race0_Tech2_arg) );

//####### TECH_LEVEL_3
VEC_int_type protector_Race0_Tech3_arg;  
protector_Race0_Tech3_arg.push_back(RACE_0_ID); protector_Race0_Tech3_arg.push_back(TECH_LEVEL_3_ID); 
g_TEXTURE_MANAGER.manageItem( new TextureOb(PROTECTOR_ITEM_TEXTURE_ID, "data/item/protector/protector_Race0_Tech3.png", true, &protector_Race0_Tech3_arg) );


//############################ DROID_ITEM
//#################### RACE_0
//####### TECH_LEVEL_0
VEC_int_type droid_Race0_Tech0_arg;  
droid_Race0_Tech0_arg.push_back(RACE_0_ID); droid_Race0_Tech0_arg.push_back(TECH_LEVEL_0_ID); 
g_TEXTURE_MANAGER.manageItem( new TextureOb(DROID_ITEM_TEXTURE_ID, "data/item/droid/droid_Race0_Tech0.png", true, &droid_Race0_Tech0_arg) );

//####### TECH_LEVEL_1
VEC_int_type droid_Race0_Tech1_arg;  
droid_Race0_Tech1_arg.push_back(RACE_0_ID); droid_Race0_Tech1_arg.push_back(TECH_LEVEL_1_ID); 
g_TEXTURE_MANAGER.manageItem( new TextureOb(DROID_ITEM_TEXTURE_ID, "data/item/droid/droid_Race0_Tech1.png", true, &droid_Race0_Tech1_arg) );

//####### TECH_LEVEL_2
VEC_int_type droid_Race0_Tech2_arg;  
droid_Race0_Tech2_arg.push_back(RACE_0_ID); droid_Race0_Tech2_arg.push_back(TECH_LEVEL_2_ID); 
g_TEXTURE_MANAGER.manageItem( new TextureOb(DROID_ITEM_TEXTURE_ID, "data/item/droid/droid_Race0_Tech2.png", true, &droid_Race0_Tech2_arg) );



//############################ GRAPPLE_ITEM
//#################### RACE_0
//####### TECH_LEVEL_0
VEC_int_type grapple_Race0_Tech0_arg;  
grapple_Race0_Tech0_arg.push_back(RACE_0_ID); grapple_Race0_Tech0_arg.push_back(TECH_LEVEL_0_ID); 
g_TEXTURE_MANAGER.manageItem( new TextureOb(GRAPPLE_ITEM_TEXTURE_ID, "data/item/grapple/grapple_Race0_Tech0.png", true, &grapple_Race0_Tech0_arg) );

//####### TECH_LEVEL_1
VEC_int_type grapple_Race0_Tech1_arg;  
grapple_Race0_Tech1_arg.push_back(RACE_0_ID); grapple_Race0_Tech1_arg.push_back(TECH_LEVEL_1_ID); 
g_TEXTURE_MANAGER.manageItem( new TextureOb(GRAPPLE_ITEM_TEXTURE_ID, "data/item/grapple/grapple_Race0_Tech1.png", true, &grapple_Race0_Tech1_arg) );




//############################ BAK_ITEM
//#################### RACE_0
//####### TECH_LEVEL_0
VEC_int_type bak_Race0_Tech0_arg;  
bak_Race0_Tech0_arg.push_back(RACE_0_ID); bak_Race0_Tech0_arg.push_back(TECH_LEVEL_0_ID); 
g_TEXTURE_MANAGER.manageItem( new TextureOb(BAK_ITEM_TEXTURE_ID, "data/item/bak/bak_Race0_Tech0.png", true, &bak_Race0_Tech0_arg) );

//####### TECH_LEVEL_1
VEC_int_type bak_Race0_Tech1_arg;  
bak_Race0_Tech1_arg.push_back(RACE_0_ID); bak_Race0_Tech1_arg.push_back(TECH_LEVEL_1_ID); 
g_TEXTURE_MANAGER.manageItem( new TextureOb(BAK_ITEM_TEXTURE_ID, "data/item/bak/bak_Race0_Tech1.png", true, &bak_Race0_Tech1_arg) );



//############################ ENERGYBLOCK_ITEM
//#################### RACE_0
//####### TECH_LEVEL_0
VEC_int_type energyBlock_Race0_Tech0_arg;  
energyBlock_Race0_Tech0_arg.push_back(RACE_0_ID); energyBlock_Race0_Tech0_arg.push_back(TECH_LEVEL_0_ID); 
g_TEXTURE_MANAGER.manageItem( new TextureOb(ENERGYBLOCK_ITEM_TEXTURE_ID, "data/item/energyBlock/energyBlock_Race0_Tech0.png", true, &energyBlock_Race0_Tech0_arg) );

//####### TECH_LEVEL_1
VEC_int_type energyBlock_Race0_Tech1_arg;  
energyBlock_Race0_Tech1_arg.push_back(RACE_0_ID); energyBlock_Race0_Tech1_arg.push_back(TECH_LEVEL_1_ID); 
g_TEXTURE_MANAGER.manageItem( new TextureOb(ENERGYBLOCK_ITEM_TEXTURE_ID, "data/item/energyBlock/energyBlock_Race0_Tech1.png", true, &energyBlock_Race0_Tech1_arg) );



//############################ FREEZER_ITEM
//#################### RACE_0
//####### TECH_LEVEL_0
VEC_int_type freezer_Race0_Tech0_arg;  
freezer_Race0_Tech0_arg.push_back(RACE_0_ID); freezer_Race0_Tech0_arg.push_back(TECH_LEVEL_0_ID); 
g_TEXTURE_MANAGER.manageItem( new TextureOb(FREEZER_ITEM_TEXTURE_ID, "data/item/freezer/freezer_Race0_Tech0.png", true, &freezer_Race0_Tech0_arg) );

//####### TECH_LEVEL_1
VEC_int_type freezer_Race0_Tech1_arg;  
freezer_Race0_Tech1_arg.push_back(RACE_0_ID); freezer_Race0_Tech1_arg.push_back(TECH_LEVEL_1_ID); 
g_TEXTURE_MANAGER.manageItem( new TextureOb(FREEZER_ITEM_TEXTURE_ID, "data/item/freezer/freezer_Race0_Tech1.png", true, &freezer_Race0_Tech1_arg) );



//############################ FREEZER_ITEM
//#################### RACE_0
//####### TECH_LEVEL_0
VEC_int_type scaner_Race0_Tech0_arg;  
scaner_Race0_Tech0_arg.push_back(RACE_0_ID); scaner_Race0_Tech0_arg.push_back(TECH_LEVEL_0_ID); 
g_TEXTURE_MANAGER.manageItem( new TextureOb(SCANER_ITEM_TEXTURE_ID, "data/item/scaner/scaner_Race0_Tech0.png", true, &scaner_Race0_Tech0_arg, 3, 1) );
//####### TECH_LEVEL_1
VEC_int_type scaner_Race0_Tech1_arg;  
scaner_Race0_Tech1_arg.push_back(RACE_0_ID); scaner_Race0_Tech1_arg.push_back(TECH_LEVEL_1_ID); 
g_TEXTURE_MANAGER.manageItem( new TextureOb(SCANER_ITEM_TEXTURE_ID, "data/item/scaner/scaner_Race0_Tech1.png", true, &scaner_Race0_Tech1_arg, 3, 1) );


//############################ FREEZER_ITEM
//#################### RACE_0
//####### TECH_LEVEL_0
VEC_int_type radar_Race0_Tech0_arg;  
radar_Race0_Tech0_arg.push_back(RACE_0_ID); radar_Race0_Tech0_arg.push_back(TECH_LEVEL_0_ID); 
g_TEXTURE_MANAGER.manageItem( new TextureOb(RADAR_ITEM_TEXTURE_ID, "data/item/radar/radar_Race0_Tech0.png", true, &radar_Race0_Tech0_arg, 3, 1) );
//####### TECH_LEVEL_1
VEC_int_type radar_Race0_Tech1_arg;  
radar_Race0_Tech1_arg.push_back(RACE_0_ID); radar_Race0_Tech1_arg.push_back(TECH_LEVEL_1_ID); 
g_TEXTURE_MANAGER.manageItem( new TextureOb(RADAR_ITEM_TEXTURE_ID, "data/item/radar/radar_Race0_Tech1.png", true, &radar_Race0_Tech1_arg, 3, 1) );



VEC_int_type text_background_arg;  
g_TEXTURE_MANAGER.manage( new TextureOb(TEXT_BACKGROUND_TEXTURE_ID, "data/other/text_background.png", true, &text_background_arg) );

}


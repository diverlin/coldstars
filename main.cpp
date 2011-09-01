/*
Copyright (C) ColdStars, Aleksandr Pivovarov <<coldstars8@gmail.com>>

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software F*oundation; either version 2
of the L icense, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#include "include.h"

void starsystemSimulation_inDynamic_TRUE(StarSystem* pTo_ss)
{
    	pTo_ss->asteroidManager(10); 

    	pTo_ss->updateEntities_inDynamic_TRUE();
    	pTo_ss->rocketCollision_TRUE();
    	pTo_ss->asteroidCollision_TRUE();

    	pTo_ss->manageEntities(); 

    	pTo_ss->fireEvents_TRUE(g_TIMER);
}

void starsystemSimulation_inDynamic_FALSE(StarSystem* pTo_ss)
{
    	pTo_ss->asteroidManager(10); 

    	pTo_ss->updateEntities_inDynamic_FALSE();
    	pTo_ss->manageEntities(); 

    	if (randIntInRange(1,10) == 1)
    	{
        	pTo_ss->rocketCollision_FALSE();
        	pTo_ss->asteroidCollision_FALSE();

        	pTo_ss->fireEvents_FALSE(g_TIMER);
    	}
}

void starsystemSimulation_inStatic_TRUE(StarSystem* pTo_ss)
{    
    	pTo_ss->removeDeadEntities(); 
    	pTo_ss->updateEntities_inStatic(); 
}

void starsystemSimulation_inStatic_FALSE(StarSystem* pTo_ss)
{   
	// freq: once per turn (when pause phase begins)
    	pTo_ss->removeDeadEntities(); 
    	pTo_ss->updateEntities_inStatic(); 
}

void starsystemRender(StarSystem* pTo_ss)
{
    	//pTo_ss->renderBackground();  // moved to ss
    	pTo_ss->findVisibleEntities();
    	if (USE_MODERN_HW == true)
    		pTo_ss->renderEntities_NEW();
    	else
        	pTo_ss->renderEntities_OLD(); 
}

void playerScan(Ship* pTo_ship, bool in_store = false, bool allow_full_control = false)
{
    	pTo_SHIP_GUI->bindShip(pTo_ship);                               // improove to perform only once
    	pTo_SHIP_GUI->bindSkill(pTo_ship->pTo_npc_owner->pTo_skill);    // improove to perform only once

    	if (pTo_PLAYER->pTo_ship->id == pTo_ship->id)
        	allow_full_control = true;  
    	// modify full control for friend ships

    	pTo_SHIP_GUI->renderInternaly();

    	if (in_store == false)
    	{
        	pTo_SHIP_GUI->renderSkill();
        	pTo_SHIP_GUI->manageSkill(allow_full_control);
    	}   

    	pTo_SHIP_GUI->mouseControl(allow_full_control, in_store);
    	if (pTo_CURSOR->pTo_otsec_slot->getEquipedStatus() == false)
        	pTo_SHIP_GUI->renderItemInfo();

    	pTo_CURSOR->updatePos();
    	pTo_CURSOR->renderFrame();
}




int main()
{       
    g_APP.SetFramerateLimit(g_FPS_LIMIT); // Limit to 60 frames per second
    g_APP.PreserveOpenGLStates(true);
    g_APP.UseVerticalSync(g_VERT_SYNC);

    g_FONT.LoadFromFile("data/font/font.ttf");

    initGL(g_VIEW_WIDTH, g_VIEW_HEIGHT); 

    loadResources();

    bool calculation_per_turn_allowed = true;
    bool algorythm_TRUE = true;      // debug for ss_active  

    KeyEventsInSpace g_KEY_EVENTS_IN_SPACE = KeyEventsInSpace(); 

    Galaxy galaxy;
    InterfaceInSpace interfaceInSpace 	      = InterfaceInSpace();
    InterfaceInKosmoport interfaceInKosmoport = InterfaceInKosmoport();

    pTo_CURSOR = new Cursor();
    pTo_SHIP_GUI = new ShipInternal();

    //// player
    pTo_PLAYER = new PlayerInstance();
    Ship* pTo_pship = galaxy.pTo_ss_active->SHIP_pList[0];

    //equip(pTo_pship); // debug

    //pTo_pship->drive_slot.getDriveEquipment()->getSpeed()*=5;   // hack debug
    //pTo_pship->updateAllStuff(); 

    pTo_PLAYER->setShip(pTo_pship);

    pTo_pship->getPoints()->setCenter(-200,-200);
    //// player

    float fps;

    std::string coord_str;
    std::string fps_str = "";


    g_TIMER = -1; 
    // GAME LOOP
    while (g_APP.IsOpened())
    {    
       ///////////// AUTOTURN //////////////////
       //if (g_TIMER < -50)
       //{   g_TIMER = TURN_TIME;
           //TURN_COUNT++;
           //printf("        *** auto turn END was activated, turn num = %i\n", TURN_COUNT);
       //}

       if (pTo_PLAYER->in_SPACE == true)
       {  
           //////////// SPACE ///////////////
           g_KEY_EVENTS_IN_SPACE.getSimpleInputs();
           g_KEY_EVENTS_IN_SPACE.getRealTimeInputs();
           g_KEY_EVENTS_IN_SPACE.scrollCamera();

           if (g_TIMER > 0)   
           {
               if (algorythm_TRUE)
                   starsystemSimulation_inDynamic_TRUE(galaxy.pTo_ss_active);
               else
                   starsystemSimulation_inDynamic_FALSE(galaxy.pTo_ss_active);

               for (unsigned int si = 0; si < galaxy.hSTARSYSTEM_pList.size(); si++)
                   starsystemSimulation_inDynamic_FALSE(galaxy.hSTARSYSTEM_pList[si]);

               calculation_per_turn_allowed = true;
           }
           else
           {
               if (calculation_per_turn_allowed == true)
               {
                   pTo_PLAYER->pTo_ship->reloadAllWeapons();   // remove from here
                   pTo_PLAYER->pTo_ship->pTo_navigator->updateTargetCoords();   // remove from here
                   
                   starsystemSimulation_inStatic_TRUE(galaxy.pTo_ss_active);
                   //world.pTo_ss_active->debug__();                                 // debug
                   for (unsigned int si = 0; si < galaxy.hSTARSYSTEM_pList.size(); si++)
                   {    
                        starsystemSimulation_inStatic_FALSE(galaxy.hSTARSYSTEM_pList[si]);
                        //world.hSTARSYSTEM_pList[si]->debug__();                       // debug
                   }

                   calculation_per_turn_allowed = false;
               }

           }

           starsystemRender(galaxy.pTo_ss_active);

           if ( (pTo_PLAYER->is_SCANNING == false) && (pTo_PLAYER->in_WORLDMAP == false) )
              galaxy.pTo_ss_active->mouseControl();   

           //////////// SCAN ///////////////
           if ( pTo_PLAYER->is_SCANNING == true )  
              playerScan(pTo_PLAYER->pTo_npc->pTo_scanShip);


           /////////// WORLDMAP ///////////
           if ( pTo_PLAYER->in_WORLDMAP == true )  
           {
               galaxy.manage_map();   
               galaxy.render_map();   
           }

           interfaceInSpace.mouseInteraction();
           interfaceInSpace.render();
       }


       //bool ___show_in_kosmoport = true;    // debug
       //if (___show_in_kosmoport)             // debug

       if (pTo_PLAYER->in_SPACE == false)
       {
           g_KEY_EVENTS_IN_SPACE.getSimpleInputs();
           g_KEY_EVENTS_IN_SPACE.getRealTimeInputs();

           
           pTo_PLAYER->pTo_npc->pTo_kosmoport->clearScreen();

           if (interfaceInKosmoport.angar_screen_SELECTED == true)
           {
               pTo_PLAYER->pTo_npc->pTo_kosmoport->pTo_angar->mouseControl();
               pTo_PLAYER->pTo_npc->pTo_kosmoport->pTo_angar->renderBackground();
               pTo_PLAYER->pTo_npc->pTo_kosmoport->pTo_angar->renderInternals();
               if (pTo_PLAYER->is_SCANNING == true)  
                   playerScan(pTo_PLAYER->pTo_npc->pTo_scanShip);
               else
                   pTo_PLAYER->pTo_npc->pTo_kosmoport->pTo_angar->renderItemInfo();
           }

           if (interfaceInKosmoport.store_screen_SELECTED == true)
           {
               pTo_PLAYER->pTo_npc->pTo_kosmoport->pTo_store->mouseControl();
               pTo_PLAYER->pTo_npc->pTo_kosmoport->pTo_store->renderBackground();
               pTo_PLAYER->pTo_npc->pTo_kosmoport->pTo_store->renderInternals();
               playerScan(pTo_PLAYER->pTo_ship, interfaceInKosmoport.store_screen_SELECTED);
               pTo_PLAYER->pTo_npc->pTo_kosmoport->pTo_store->renderItemInfo();
           }

           if (interfaceInKosmoport.shop_screen_SELECTED == true)
           {
               pTo_PLAYER->pTo_npc->pTo_kosmoport->pTo_shop->render();
           }

           if (interfaceInKosmoport.galaxymap_screen_SELECTED == true)
           {
               galaxy.manage_map();   
               galaxy.render_map();   
           }

           if (interfaceInKosmoport.goverment_screen_SELECTED == true)
           {
               pTo_PLAYER->pTo_npc->pTo_kosmoport->pTo_goverment->render();
           }

           interfaceInKosmoport.mouseInteraction(); 
           interfaceInKosmoport.render();       
           interfaceInKosmoport.renderInfo();   
       } 

       
       float fps = 1.f / g_APP.GetFrameTime();

       coord_str = "world coord: " + int2str(g_SCROLL_COORD_X) + "," + int2str(g_SCROLL_COORD_Y);
       if (randIntInRange(0, 20) == 1)
          fps_str = "FPS:" + int2str((int)fps);

       sf::String coord_Str(coord_str, g_FONT, 14);
       coord_Str.SetColor(sf::Color(255, 255, 255));
       coord_Str.SetPosition(g_VIEW_WIDTH - 200, 15); 

       sf::String fps_Str(fps_str, g_FONT, 14);
       fps_Str.SetColor(sf::Color(255, 255, 255));
       fps_Str.SetPosition(100, 15); 

       g_APP.Draw(coord_Str);
       g_APP.Draw(fps_Str);

       // Finally, display rendered frame on screen
       g_APP.Display();

       g_TIMER--;
    }

    return EXIT_SUCCESS;
}





//######################## UPRAVLENIE
//# 1,2,3 aktivacija oruzhija po donomu(na tekuwij moment radius dejstvija bolshevat, no eto s celju testa)
//# a - aktivacija/deaktivacija vsex slotov oruzhija odnovremenno
//# g - aktivacija/deaktivacija zaxvata (u4ti zaxvat ne mozhet  tjanut' oskolki bolshe 30 kazhetsja :) i ewe pered tem kak sxvatit chtoto ootkljuchi vse pushki, a to ja ewe ne dodelal intelekt chtob ne streljal asteopidy po umolchaniju)
//# p - pokazat' podpisi planetam/asteroidam/mineralam
//# o - vkl/vykl otrisovku orbit vsex nebesnyx tel
//# SPACE - propusk xoda
//#################################################

//# cvet ekrana zavisit ot cveta solnca i rasstojanija k nemu
//# nevedommye rassy(ten')
//# zhivye planety, kokony
//# centr solnechnoj vselennoj chernaja dyra
//# chernaja dyra lovushka korabljam, pomexi radaru
//# oruzhie gravitacionnaja bomba(chernaja dyra/lipuchka sozdajuwaja  gravitacionnyj kollaps)
//# asteroidnoe pole = nevozmozhnost' isp raketnogo orduija => collision rocket i asteroidnogo polja
//# kual' kua, zhivoj wit
//# energija ot sonca, rasxod na plazmu (energo wit) i lazery
//# modul' robota pomownika
//# vspyshka na solnce vykljuchaet radary + drugie anomalii
//# stolknovenie s bol'shim asteroidom raznosit korpus korablja
//# rakety vzryvajutsja ot soprikosnovenija s planetami
//# gravitacionnoe pole chernym dyram
//# asteroidnoe pole
//# stacionarnye miny vblizi giperperexodov
//# bol'shie korabli bol'she zamedljajut xod dvizhenija vbili krupnyx nebesnyx tel (gravitacija)
//# luchevoe oruzhie i wity effektivnee vblizi zvezd
//# razdvedchiki inoplanetnye
//# Receive Informations from NPC or News.
//# space monsters! as living ships!
//#- minery, otdel'nye korabli minirujuwie oblasti giperprostranstvennogo perexoda. miny zamaskirovannye melkimi asteroidami
//#- kvarkovaja bomba, posle aktivacii porazhdaet chernuju dyru, pomewennaja v centr vragov zasasuet korablej gravitacionnym polem
//#- rakety podvlasny vlijajuniju chernyx dyr, zatjagivajutsja momental'no
//#- oruzhie menjajuwie orbity asteroidov(neposredstvenno vblizi asteroida). Vozmozhnost' zaminirovat' asteroid prikrepiv k nemu bombu(naprimer kvarkovuju) nu i v epicentr.
//#- komety(s xvostom), vozmozhnost' prjatatsja v pylevom xvoste
//#- naxozhdenie na planete ponemnogu vosstanavlivaet povrezhdenija korpusa
//#- silnyj grapple uderzhivaet malenkij korabl'
//#- QUEST: esli u korablja konchilos' toplivo, buksirovat na blizhajshuju planetu
//#- SPACE: zaxvatom mozhno zamedljat' skorost' protivnika
//# rassa ameb(biologichekie korabli)
//# kvest raznesti gromadnyj asteroid!!!
//# setka, nevozmozhnost' posadki pilotom korablja, ili zhe zaxvat
//# miny
//# vozmozhnost' modificirovat' 1-2 slota pod svoju nuzhdy!!
//# samoe luchshee vooruzhenie na voennyx bazax
//# populjacija planet >> proizvodstvo sputnikov i kollichestvo oborudovanija
//# epidemija na planete, populjacija umen#shaetsja, vvoz midekamentov
//# rakety prilipaly uvelichivajuwie massu ob'ekta
//# populjacija planety vlijaet na tovary
//# sputniki istochnik informacii
//# kolonizacija planet, teramorfing, uchastie igroka v etom processe
//# magnetik mines
//# sputniki spamjat korabljam
//# prodazha topliva pilotu v bezvyxodnoj situacii, nakrutka ceny
//# poedajuwie korabli
//# szhiganie luchem esli protivnik na korme
//# birzha truda
//# cvet texta povrezhdenij

//# generacija: planeta s rassoj, v magazine texnika tol'ko etoj rassy, dobavit' v generator, textura planety tozhe budet imet' metku na rassu
//# generacija nebol'shoj plejady(skoplenija) tusklyx golubyx zvezd
//# vvesti ogranichenie na max protection v zavisimosti ot korpusa korablja(napr mal korablik ne moyhet byt# silno zawiwen)
//# TODO make all textures are external
//# traektorii korablej vne solnca i 4d, odnako 4d zatjagivaet korabl' postepenno zatjagivaja korabli, pricel zstrel'ba po dvizhku i zasovyvat' korabli v 4d
//# xakerstvo
//# umirajuwaja zvezda, planety podderzhujuwie solnce ot vymiranija
//# organotexnologii
//# vvesti ksenofobiju na otdel'nyx lichnostej
//# zaxvat ottalkivaet mineral vo vragov
//# formacii voennyx (klin, krug) i t.d., sootvetstvenno soprovozhdenie vazhnyx lic v takoj formacii, i kvesty za piratov po unichtozheniju kljuchevogo zvena

//#### sjuzhetka ####
//# ljudi vs kto to, biologicheskoe oruzhie, bio rassa nejtralizovala ego i predotvratila polnoe razrushenie
//# biorassa obladaet psi sposobnostjami, gumanoidy xakery
//# biorassa psi delaet dvojnika-maket
//# radio
//# stiranie li4nosti
//# zavisimost' povrezhdenija ot rasstojanija
//# rakety vblizi solnca vzryvajutsja

//# rassa kazhdyj junit = funkcija (korabl' radar, korabl' pochinka, karabl' zawitnik i t.d.), takticheskoe poverzhenie
//# korabli pobolshe mogut vmewat' v sebja korabli pomen'she, kotorye vyletajut v sluchae neobxodimosti


//# minirovanie asteroida!



//# minigame:
//# zaxvat bazy (kontra)
//# gonki (zvezdnye vojny)



//# gravitacionnaja mina, lokal'noe uvelichenie gravitacionnogo polja, effect shockwave zamedlennyj(puzyr')
//# korpus piratov dop sekretnyj slot s ogranichennym ob'emom dlja perevozki zapretnyx tovarov



// navyk xakerstva

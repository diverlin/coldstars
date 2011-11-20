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

#include "include.hpp"

int main()
{       
 	init();

    	KeyEventsInSpace keyEvents = KeyEventsInSpace(); 

    	g_GALAXY = new Galaxy();
    	SpaceMap spaceMap;
    	spaceMap.bindGalaxy(g_GALAXY);
        
    	InterfaceInSpace interfaceInSpace 	  = InterfaceInSpace();
    	InterfaceInKosmoport interfaceInKosmoport = InterfaceInKosmoport();

    	g_SHIP_GUI = new ShipInternal();
        g_SHIP_GUI->createControlSkillButtons();
        
    	pPLAYER   = new Player();    
	pPLAYER->setStarSystem(g_GALAXY->getRandomStarSystem());      
      		
    	Npc* pnpc = pPLAYER->getStarSystem()->NPC_inSPACE_vec[0];
    	pPLAYER->bindNpc(pnpc);
    	pnpc->getShip()->getPoints()->setCenter(-400,-400);
    	//// player

    	std::string coord_str;
    	std::string fps_str = "";

    	g_TIMER = -1; 
    	// GAME LOOP
    	while (g_APP.IsOpened())
    	{    
       		/////////// AUTO-TURN /////////////
       		if ( (g_TIMER < -50) and (g_AUTOTURN_ENABLE == true) )
       		{  
       			g_TIMER = TURN_TIME;
           		TURN_COUNT++;
           		printf("        *** auto turn END was activated, turn num = %i\n", TURN_COUNT);
                }

		pPLAYER->update_inSpace();

       		if (pPLAYER->getPlaceTypeId() == SPACE_ID)
       		{  
           		//////////// in SPACE ///////////////
           		keyEvents.update();

			for (int i = 0; i < g_GAMESPEED; i++)  // fakse
			{
       				g_GALAXY->update(g_TIMER);
       			}

           		pPLAYER->getStarSystem()->render(); 
                        
                        if (g_TIMER < 0)  
                        {
                                if ( (pPLAYER->getScanFlag() == false) && (pPLAYER->getWorldMapShowFlag() == false) )
                                {
                                        pPLAYER->getStarSystem()->mouseControl();  // improove to exclude all render calls
                                }
                        }

           		//////////// SCAN ///////////////
           		if ( pPLAYER->getScanFlag() == true )
                        {                                
              			g_SHIP_GUI->update();
                                g_SHIP_GUI->render();
                        }

           		/////////// WORLDMAP ///////////
           		if ( pPLAYER->getWorldMapShowFlag() == true )  
           		{
               			spaceMap.update();   
               			spaceMap.render(false);   
          		}

           		interfaceInSpace.update();    
           		interfaceInSpace.render();
       		}


       		if (pPLAYER->getPlaceTypeId() == KOSMOPORT_ID)
       		{
           		keyEvents.update2();
          
           		if (interfaceInKosmoport.getActiveScreenId() == SCREEN_ANGAR_ID)
           		{
               			pPLAYER->getPilot()->getKosmoport()->getAngar()->update();                                
               			pPLAYER->getPilot()->getKosmoport()->getAngar()->render();

                                if (pPLAYER->getScanFlag() == true) 
                                { 
                                        g_SHIP_GUI->update();
                                        g_SHIP_GUI->render();
                                }
               			else
                                {
                   			pPLAYER->getPilot()->getKosmoport()->getAngar()->renderItemInfo();
                                }
           		}

           		if (interfaceInKosmoport.getActiveScreenId() == SCREEN_STORE_ID)
           		{
                                pPLAYER->getPilot()->getKosmoport()->getStore()->update();
               			pPLAYER->getPilot()->getKosmoport()->getStore()->render();                                 
                                                 
                                g_SHIP_GUI->configure(pPLAYER->getShip(), true);
               			g_SHIP_GUI->update();
                                g_SHIP_GUI->render();
                        }

           		if (interfaceInKosmoport.getActiveScreenId() == SCREEN_SHOP_ID)
           		{
                                pPLAYER->getPilot()->getKosmoport()->getShop()->update();
                                pPLAYER->getPilot()->getKosmoport()->getShop()->render();
           		}

           		if (interfaceInKosmoport.getActiveScreenId() == SCREEN_GALAXYMAP_ID)
           		{
               			spaceMap.update();
                                spaceMap.render(true);   
           		}

           		if (interfaceInKosmoport.getActiveScreenId() == SCREEN_GOVERMENT_ID)
           		{
                                pPLAYER->getPilot()->getKosmoport()->getGoverment()->update();
                                pPLAYER->getPilot()->getKosmoport()->getGoverment()->render();
           		}

           		interfaceInKosmoport.update(); 
           		interfaceInKosmoport.render(); 
       		} 

       
       		float fps = 1.f / g_APP.GetFrameTime();

       		coord_str = "world coord: " + int2str(g_SCROLL_COORD_X) + "," + int2str(g_SCROLL_COORD_Y);
       		if (getRandInt(0, 20) == 1)
       		{
          		fps_str = "FPS:" + int2str((int)fps);
          	}

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

	printf("EXIT_SUCCESS");
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

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

    	// GAME LOOP
    	while (g_APP.IsOpened())
    	{    
		pPLAYER->update_inSpace();

       		if (pPLAYER->getPlaceTypeId() == SPACE_ID)
       		{  
           		//////////// in SPACE ///////////////
           		g_KEYEVENTS->update_inSpace();

			for (int i = 0; i < g_GAMESPEED; i++)  // fakse
			{
       				g_GALAXY->update(g_TIMER->getTurnTick());
       			}

           		//pPLAYER->getStarSystem()->render(pPLAYER->getShowOrbits(), pPLAYER->getShowShipWays()); 
           		pPLAYER->getStarSystem()->render(false, true); 
                                                
                        if (g_TIMER->getTurnEnded() == true)  
                        {
                                if ( (pPLAYER->getScanFlag() == false) && (pPLAYER->getWorldMapShowFlag() == false) )
                                {
                                        pPLAYER->getStarSystem()->mouseControl();  // improove to exclude all render calls
                                }
                        }

           		//////////// SCAN ///////////////
           		if ( pPLAYER->getScanFlag() == true )
                        {                                
              			g_GUI_SHIP->update();
                                g_GUI_SHIP->render();
                        }

           		/////////// WORLDMAP ///////////
           		if ( pPLAYER->getWorldMapShowFlag() == true )  
           		{
               			g_GUI_MAP->update();   
               			g_GUI_MAP->render(false);   
          		}

           		g_GUI_SPACE->update();    
           		g_GUI_SPACE->render();
       		}


       		if (pPLAYER->getPlaceTypeId() == KOSMOPORT_ID)
       		{
           		g_KEYEVENTS->update_inKosmoport();
          
           		if (g_GUI_KOSMOPORT->getActiveScreenId() == SCREEN_ANGAR_ID)
           		{
               			pPLAYER->getPilot()->getKosmoport()->getAngar()->update();                                
               			pPLAYER->getPilot()->getKosmoport()->getAngar()->render();

                                if (pPLAYER->getScanFlag() == true) 
                                { 
                                        g_GUI_SHIP->update();
                                        g_GUI_SHIP->render();
                                }
               			else
                                {
                   			pPLAYER->getPilot()->getKosmoport()->getAngar()->renderItemInfo();
                                }
           		}

           		if (g_GUI_KOSMOPORT->getActiveScreenId() == SCREEN_STORE_ID)
           		{
                                pPLAYER->getPilot()->getKosmoport()->getStore()->update();
               			pPLAYER->getPilot()->getKosmoport()->getStore()->render();                                 
                                                 
                                g_GUI_SHIP->configure(pPLAYER->getShip(), true);
               			g_GUI_SHIP->update();
                                g_GUI_SHIP->render();
                        }

           		if (g_GUI_KOSMOPORT->getActiveScreenId() == SCREEN_SHOP_ID)
           		{
                                pPLAYER->getPilot()->getKosmoport()->getShop()->update();
                                pPLAYER->getPilot()->getKosmoport()->getShop()->render();
           		}

           		if (g_GUI_KOSMOPORT->getActiveScreenId() == SCREEN_GALAXYMAP_ID)
           		{
               			g_GUI_MAP->update();
                                g_GUI_MAP->render(true);   
           		}

           		if (g_GUI_KOSMOPORT->getActiveScreenId() == SCREEN_GOVERMENT_ID)
           		{
                                pPLAYER->getPilot()->getKosmoport()->getGoverment()->update();
                                pPLAYER->getPilot()->getKosmoport()->getGoverment()->render();
           		}

           		g_GUI_KOSMOPORT->update(); 
           		g_GUI_KOSMOPORT->render(); 
       		} 

            	
            	g_FPS->update();
            	g_FPS->draw();            	


		g_TIMER->update();
		
       		// Finally, display rendered frame on screen
       		g_APP.Display();
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

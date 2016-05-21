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

#include "equipment/BakEquipmentBuilder.hpp"
#include "equipment/DriveEquipmentBuilder.hpp"
#include "equipment/GrappleEquipmentBuilder.hpp"
#include "equipment/LazerEquipmentBuilder.hpp"
#include "equipment/ProtectorEquipmentBuilder.hpp"
#include "equipment/RocketEquipmentBuilder.hpp"
#include "equipment/ScanerEquipmentBuilder.hpp"
#include "equipment/DroidEquipmentBuilder.hpp"
#include "equipment/RadarEquipmentBuilder.hpp"
#ifdef USE_EXTRA_EQUIPMENT
#include "equipment/FreezerEquipmentBuilder.hpp"
#include "equipment/EnergizerEquipmentBuilder.hpp"
#endif

#ifdef USE_MODULES
#include "modules/BakModuleBuilder.hpp"
#include "modules/DriveModuleBuilder.hpp"
#include "modules/GrappleModuleBuilder.hpp"
#include "modules/LazerModuleBuilder.hpp"
#include "modules/ProtectorModuleBuilder.hpp"
#include "modules/RocketModuleBuilder.hpp"
#include "modules/ScanerModuleBuilder.hpp"
#include "modules/DroidModuleBuilder.hpp"
#include "modules/RadarModuleBuilder.hpp"
#endif // USE_MODULES

#ifdef USE_ARTEFACTS
#include "artefacts/GravityArtefactBuilder.hpp"
#include "artefacts/ProtectorArtefactBuilder.hpp"
#endif // USE_ARTEFACTS

#include "other/BombBuilder.hpp"

    

        



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

#include "AiModelCollector.hpp"
#include <types/MyInt.hpp>

AiModelCollector& AiModelCollector::Instance()
{
    static AiModelCollector instance;
    return instance;
}

AiModelCollector::~AiModelCollector()
{}

void AiModelCollector::RegisterAiModel(BaseAiModel* ai_model)
{
    aimodel_map.insert(std::make_pair(ai_model->GetTypeId(), ai_model));
}
          
BaseAiModel* AiModelCollector::GetAiModel(int type_id) const
{
    if (type_id != NONE_ID)
    {
        return (aimodel_map.find(type_id))->second;
    }
    
    return nullptr;
}

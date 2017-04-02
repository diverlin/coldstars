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

#include <core/common/Base.hpp>

namespace descriptor {
class Item;
} // namespace descriptor

namespace model {
class Item;
} // namespace model

namespace slot {
class Item;
} // namespace slot


namespace control {

class Item : public Base
{
public:
    Item(model::Item*, descriptor::Item*);
    virtual ~Item() = default;

    virtual void putChildrenToGarbage() const {}

    void setSlot(slot::Item* slot)  { m_slot = slot; }

    slot::Item* slot() const { return m_slot; }

    bool isDamaged() const;
    bool isLocked() const;
    int isFunctioning() const;

    void useNormalDeterioration();
    void useOverloadDeterioration();

    void doBreak();
    void deteriorationEvent();
    void doLock(int lock = 1);
    void doUnlock();
    bool doRepair();

    virtual void updateProperties() {}
    virtual void updateInStatic() { _updateLock(); }

    //        void UpdateInfo();

    //        virtual void Render(const jeti::Renderer&, const ceti::Box2D&, const glm::vec2&, bool draw_text = true);
    //        void RenderKorpus(const jeti::Renderer&, const ceti::Box2D&);
    //        void RenderInfo(const jeti::Renderer&, const glm::vec2&);

protected:
    void _updateLock();

    virtual void AddCommonInfo()=0;
    virtual void addUniqueInfo()=0;

public:
    model::Item* model() const { return m_model_item; }
    descriptor::Item* descriptor() const { return m_descriptor_item; }

private:
    model::Item* m_model_item = nullptr;
    descriptor::Item* m_descriptor_item = nullptr;

    slot::Item* m_slot = nullptr;
};

} // namespace control

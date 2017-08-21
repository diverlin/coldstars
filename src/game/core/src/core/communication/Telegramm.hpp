#pragma once

#include <ceti/type/IdType.hpp>

#include <string>

namespace core {
namespace comm {

class Telegramm
{
public:
    enum class Type : int
    {
        NONE,
        /** CREATE */
        // spaceobjects
        CREATE_STARSYSTEM,
        CREATE_SHIP,
        CREATE_BOMB,
        CREATE_GOODS,
        CREATE_CONTAINER,
        CREATE_BULLET,
        // items
        CREATE_BAK,
        CREATE_DRIVE,
        CREATE_DROID,
        CREATE_GRAPPLE,
        CREATE_SCANER,
        CREATE_RADAR,
        CREATE_PROTECTOR,
        // effects
        CREATE_EXPLOSION_EFFECT,
        /** */

        /** DOCK */
        DOCK_SHIP,
        LAUNCH_SHIP,

        /** JUMP */
        JUMP_IN,
        JUMP_OUT,

        /** DROP_GRAB */
        DROP_ITEM,
        TAKE_CONTAINER,

        /** TRANSITION */
        ADD_SHIP_TO_STARSYSTEM,
        ADD_CONTAINER_TO_STARSYSTEM,
        INSERT,
        REMOVE,
        DELETE,
        /** */

        HIT,
        EXPLOSION,

        // kill
        KILL_VEHICLE,
        KILL_ASTEROID,
        KILL_BULLET,
        KILL_CONTAINER
    };

public:
    Telegramm(Type, const std::string& data = "", double delay = -1.0);

    bool operator<(const Telegramm&) const;

    Type type() const { return m_type; }
    std::string data() const { return m_data; }
    double delay() const { return m_delay; }
    double dispatchTime() const { return m_dispatchTime; }

    void setDispatchTime(double dispatchTime) {
        m_dispatchTime = dispatchTime;
    }

private:
    //id_type id = 0;
    Type m_type = Type::NONE;
    std::string m_data = "";

    double m_delay = -1.0;
    double m_dispatchTime = 0.0;
};

} // namespace comm
} // namespace core

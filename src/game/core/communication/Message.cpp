#include "Message.hpp"
#include <ceti/myStr.hpp>
#include <assert.h>

Message::Message(TELEGRAM type_id, const std::string& data, double delay)
    :
      type_id(type_id)
    , data(data)
    , delay(delay)
{}

//Message::Message(const Message& message)
//{
//    delay       = message.delay;
//    sender_id   = message.sender_id;
//    receiver_id = message.receiver_id;
//    type_id     = message.type_id;
//    extra       = message.extra;
//}


bool Message::operator<(const Message& rhs) const
{
    return (dispatch_time < rhs.dispatch_time);
}


//HitEvent::HitEvent(const ID& agressor, const ID& victim, int damage)
//    :
//      agressor( agressor),
//      victim(victim),
//      damage(damage)
//{}

//HitEvent::HitEvent(const std::string& data) {
//    const std::vector<std::string>& v = ceti::split(data, ";");
//    assert(v.size() == 3);
//    agressor = std::stoi(v[0]);
//    victim = std::stoi(v[1]);
//    damage = std::stoi(v[2]);
//}

//std::string HitEvent::data() const {
//    return ceti::str(agressor) + ";" + ceti::str(victim) + ";" + ceti::str(damage);
//}


//Message getMessage(const HitDescri& hitEvent, double delay) {
//    return Message(TELEGRAM::HIT, hitEvent.data(), delay);
//}

//Message getMessage(const StarSystemDescriptor& descriptor, double delay) {
//    return Message(TELEGRAM::CREATE_STARSYSTEM, descriptor.data(), delay);
//}

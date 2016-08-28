#pragma once

#include <ceti/type/IdType.hpp>

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

#include <glm/glm.hpp>

class AddToStarsystemDescriptor {
    public:
        AddToStarsystemDescriptor(const id_type& owner,
                                  const id_type& object,
                                  const glm::vec3& position = glm::vec3(0.0f),
                                  const glm::vec3& angle = glm::vec3(0.0f));

        AddToStarsystemDescriptor(const std::string& data);

        id_type owner = 0;
        id_type object = 0;
        glm::vec3 position;
        glm::vec3 angle;

        std::string data() const;

    private:
        friend class boost::serialization::access;
        template<class Archive>
        void serialize(Archive & ar, const unsigned int version)
        {
            ar & owner;
            ar & object;
            ar & position.x;
            ar & position.y;
            ar & position.z;
            ar & angle.x;
            ar & angle.y;
            ar & angle.z;
        }
};



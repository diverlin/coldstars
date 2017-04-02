#pragma once

#include <ceti/type/IdType.hpp>

#include <meti/VectorUtils.hpp>

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

#include <glm/glm.hpp>

class AddToStarsystemDescriptor {
    public:
        AddToStarsystemDescriptor(int_t owner,
                                  int_t object,
                                  const meti::vec3& position = meti::vec3(0.0f),
                                  const meti::vec3& angle = meti::vec3(0.0f));

        AddToStarsystemDescriptor(const std::string& data);

        int_t owner = 0;
        int_t object = 0;
        meti::vec3 position;
        meti::vec3 angle;

        std::string data() const;

    private:
        friend class boost::serialization::access;
        template<class Archive>
        void serialize(Archive & ar, const unsigned int version) {
            ar & owner;
            ar & object;
            ar & position;
            ar & angle;
        }
};



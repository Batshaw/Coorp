#ifndef HIT_HPP
#define HIT_HPP

#include <glm/vec3.hpp>
#include <Shape.hpp>

class Shape;

struct Hit
{
        float distance_;
        bool isHit_;
        glm::vec3 coor_;
        glm::vec3 normal_;
        Shape const *obj_;

        Hit() : distance_{2000},
                isHit_{false},
                coor_{0.0f, 0.0f, 0.0f},
                normal_{0.0, 0.0, 0.0},
                obj_{nullptr} {};

        Hit(Hit const &input_) : distance_{input_.distance_},
                                 isHit_{input_.isHit_},
                                 coor_{input_.coor_},
                                 normal_{input_.normal_},
                                 obj_{input_.obj_} {};

        Hit(Shape const *input_) : distance_{2000},
                                   isHit_{false},
                                   coor_{0.0f, 0.0f, 0.0f},
                                   normal_{0.0, 0.0, 0.0},
                                   obj_{input_} {};

        Hit(float distance, bool is_hit, glm::vec3 const &point, glm::vec3 const &normal, Shape const *obj) : distance_{distance},
                                                                                                              isHit_{is_hit},
                                                                                                              coor_{point},
                                                                                                              normal_{normal},
                                                                                                              obj_{obj} {};
};

#endif //HIT_HPP

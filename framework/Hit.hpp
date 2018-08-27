#ifndef HIT_HPP
#define HIT_HPP

#include <glm/glm.hpp>
#include <memory>
#include "Shape.hpp"
#include "Ray.hpp"
#include "material.hpp"

struct Hit
{

    float distance_;
    bool isHit_;
    glm::vec3 coor_;
    glm::vec3 normal_;

    std::shared_ptr<Shape> closest_;

    Hit() : distance_{2000},
            isHit_{false},
            coor_{0.0f, 0.0f, 0.0f},
            normal_{0.0, 0.0, 0.0},
            closest_{nullptr} {};

    Hit(Hit const &input_) : distance_{input_.distance_},
                             isHit_{input_.isHit_},
                             coor_{input_.coor_},
                             normal_{input_.normal_},
                             closest_{input_.closest_} {};

    Hit(std::shared_ptr<Shape> input_) : distance_{2000},
                                         isHit_{false},
                                         coor_{0.0f, 0.0f, 0.0f},
                                         normal_{0.0, 0.0, 0.0},
                                         closest_{input_} {};
};

#endif

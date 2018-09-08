#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <string>
#include "color.hpp"
#include <ostream>
#include "material.hpp"
#include "ray.hpp"
#include "glm/vec3.hpp"
#include "Hit.hpp"
#include <memory>

class Shape{
    public:
        Shape();
        /*Shape(std::string const& name);
        Shape(std::shared_ptr<Material> material);*/
        Shape(std::string const& name, std::shared_ptr<Material> const& material);
        Shape(std::string const& name, std::shared_ptr<Material> const& material, glm::mat4 worldTransform);
        virtual ~Shape();

        std::string getName() const;
        Color getColor() const;
        std::shared_ptr<Material> getMaterial() const;
        virtual glm::mat4 getWorldMat() const;
        virtual glm::mat4 getWorldMatInv() const;

        virtual float area() const = 0;
        virtual float volumen() const = 0;
        
        virtual bool intersect(Ray const& r, float& t) = 0;
        virtual Hit intersectHit(Ray const& ray) = 0;

        virtual void translate(glm::vec3 const& p);
        virtual void scale(glm::vec3 const& s);
        virtual void rotate(float fi, glm::vec3 const& roVec);
        
        virtual std::ostream& print(std::ostream& os) const;

    protected:
        std::string name_;
        std::shared_ptr<Material> material_;

        glm::mat4 world_transformation_{1, 0, 0, 0,
                                        0, 1, 0, 0,
                                        0, 0, 1, 0,
                                        0, 0, 0, 1};
        
        glm::mat4 world_transformation_inv_{1, 0, 0, 0,
                                        0, 1, 0, 0,
                                        0, 0, 1, 0,
                                        0, 0, 0, 1};

};

std::ostream& operator<<(std::ostream&os, Shape const& s);

#endif  //SHAPE_HPP
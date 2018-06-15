#ifndef SHAPE_HPP
#define SHAPE_HPP

class Shape{
    public:

        virtual float area() const = 0;
        virtual float volumen() const = 0;
        

    private:
        string name_;

};

#endif  //SHAPE_HPP
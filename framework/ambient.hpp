#ifndef AMBIENT_HPP
#define AMBIENT_HPP

struct Ambient{

    Ambient():
        color_{0.0f, 0.0f, 0.0f}  {}

    Ambient(Color color):
        color_{color}   {}

    Color color_;
};

#endif  //AMBIENT_HPP
#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include <ostream>
#include "color.hpp"
#include <string>

struct Material{

    Material(): name_{"default"}, ka_{1, 0, 0}, kd_{1, 0, 0}, ks_{1, 1, 1}, m_{10.0f}  {}   //Default Konstruktor
    Material(Color ka, Color kd, Color ks, float m):
        name_{"unknown"}, ka_{ka}, kd_{kd}, ks_{ks}, m_{m}  {}
    Material(std::string name, Color ka, Color kd, Color ks, float m):
        name_{name}, ka_{ka}, kd_{kd}, ks_{ks}, m_{m}  {}

    // friend makes operator<< a non-Memberfunction but can acces to Material.variablen
    friend std::ostream& operator<<(std::ostream& os, Material const& m){
        os<< "Material: "<< m.name_<< " Materialkoeffizienten: ("
        << m.ka_<< ", "<< m.kd_<< ", "<< m.ks_<< ").\n"
        << "Spekularreflexionsexponenten: "<< m.m_<< ". \n";
        return os;
    }

    std::string name_;
    Color ka_;  //Materialkoeffizient
    Color kd_;
    Color ks_;
    float m_;   //Spekularreflexionsexponenten
};

#endif  //MATERIAL_HPP
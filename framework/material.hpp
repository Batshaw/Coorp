#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include <ostream>
#include "color.hpp"
#include <string>

struct Material
{
    //Default Konstruktor
    Material() : name_{"default"}, ka_{1, 0, 0}, kd_{1, 0, 0}, ks_{1, 1, 1}, m_{10.0f} {}

    //Material ohne Name
    Material(Color const &ka, Color const &kd, Color const &ks, float m) : name_{"unknown"}, ka_{ka}, kd_{kd}, ks_{ks}, m_{m} {}

    //Material mit beliebigen Werte und Namen
    Material(std::string const &name, Color const &ka, Color const &kd, Color const &ks, float m) : name_{name}, ka_{ka}, kd_{kd}, ks_{ks}, m_{m} {}

    //Kopie Konstrktor
    Material(Material const &input) : name_{input.name_}, ka_{input.ka_}, kd_{input.kd_}, ks_{input.ks_}, m_{input.m_} {}

    // friend makes operator<< a non-Memberfunction but can acces to Material.variablen
    friend std::ostream &operator<<(std::ostream &os, Material const &m)
    {
        os << "Material: " << m.name_ << ". Materialkoeffizienten: ("
           << m.ka_ << ", " << m.kd_ << ", " << m.ks_ << ").\n"
           << "Spekularreflexionsexponenten: " << m.m_ << ". \n";
        return os;
    }

    //Membervariable
    std::string name_;
    Color ka_; //Materialkoeffizient
    Color kd_;
    Color ks_;
    float m_; //Spekularreflexionsexponenten
};

#endif //MATERIAL_HPP
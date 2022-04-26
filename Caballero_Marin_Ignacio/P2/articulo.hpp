#ifndef ARTICULO_H_
#define ARTICULO_H_

#include <iostream>
#include "../P1/fecha.hpp"
#include "../P1/cadena.hpp"

class Articulo
{
    public:

        //Constructor
        Articulo(Cadena ref, Cadena titulo, Fecha f_pub, double precio, int stock = 0): referencia_(ref), titulo_(titulo), f_publicacion_(f_pub), precio_(precio), stock_(stock) {};

        //Observadores
        Cadena referencia() const {return referencia_;};
        Cadena titulo() const {return titulo_;};
        Fecha f_publi() const {return f_publicacion_;};
        double precio() const {return precio_;};
        double& precio() {return precio_;};
        int stock() const {return stock_;};
        int& stock() {return stock_;};

    private:
    
        Cadena referencia_, titulo_;
        Fecha f_publicacion_;
        double precio_;
        int stock_;
};

//Op. de insercion
std::ostream& operator<<(std::ostream& os, const Articulo& a)noexcept;

#endif
#ifndef ARTICULO_H_
#define ARTICULO_H_

#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <set>
#include <locale>
#include "../P1/fecha.hpp"
#include "../P1/cadena.hpp"

class Autor
{
    public:
        //Ctor
        Autor(const Cadena& nom, const Cadena& apell, const Cadena& direcc);

        //Observadores
        const Cadena& nombre() const noexcept {return nombre_;}
        const Cadena& apellidos() const noexcept {return apellidos_;}
        const Cadena& direccion() const noexcept {return direccion_;}

    private:
        Cadena nombre_;
        Cadena apellidos_;
        Cadena direccion_;
};

class Articulo
{
    public:
        //Diccionario de autores
        typedef std::set<Autor*> Autores;

        //Constructor
        Articulo(const Autores& autores, const Cadena& ref, const Cadena& titulo, const Fecha& f_pub, const double precio);

        //Observadores
        inline Cadena referencia() const {return referencia_;}
        inline Cadena titulo() const {return titulo_;}
        inline Fecha f_publi() const {return f_publicacion_;}
        inline double precio() const {return precio_;}
        inline double& precio() {return precio_;}
        inline const Autores& autores() const {return autores_;}

        //Autores vacios
        class Autores_vacios{};

        //Ostream
        virtual void impresion_especifica(std::ostream&) const = 0;

        virtual ~Articulo(){};

    private:
        const Autores autores_;
        Cadena referencia_, titulo_;
        Fecha f_publicacion_;
        double precio_;
};

class LibroDigital : public Articulo
{
    public:
        LibroDigital(const Autores& autores, const Cadena& ref, const Cadena& titulo, const Fecha& f_pub, const double precio, const Fecha& fExp);

        const Fecha f_expir() const noexcept {return f_expir_;}
        
        void impresion_especifica(std::ostream& os) const;
    private:
        const Fecha f_expir_;
};

class ArticuloAlmacenable : public Articulo
{
    public:
        ArticuloAlmacenable(const Autores& autores, const Cadena& ref, const Cadena& titulo, const Fecha& f_pub, const double precio, unsigned stock = 0);

        const unsigned stock() const noexcept{return stock_;}
        unsigned& stock() noexcept {return stock_;}
    
    protected:
        unsigned stock_;
};

class Libro : public ArticuloAlmacenable
{
    public:
        Libro(const Autores& autores, const Cadena& ref, const Cadena& titulo, const Fecha& f_pub, const double precio, unsigned paginas, unsigned stock = 0);

        const unsigned n_pag() const noexcept {return n_pag_;}
        void impresion_especifica(std::ostream& os) const;

    private:
        const unsigned n_pag_;
};

class Cederron : public ArticuloAlmacenable
{
    public:
        Cederron(const Autores& autores, const Cadena& ref, const Cadena& titulo, const Fecha& f_pub, const double precio, unsigned tamano, unsigned stock = 0);

        const unsigned tam() const noexcept {return tam_;}
        void impresion_especifica(std::ostream& os) const;
    private:
        const unsigned tam_;
};

//Op. de insercion
std::ostream& operator<<(std::ostream& os, const Articulo& a)noexcept;

#endif
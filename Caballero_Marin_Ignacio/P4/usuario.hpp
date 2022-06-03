#ifndef USUARIO_H_
#define USUARIO_H_

#include "../P1/cadena.hpp"
#include "tarjeta.hpp"
#include "articulo.hpp"
#include <iostream>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <string.h>
#include <unistd.h>
#include <random>
#include <iomanip>
#include <set>
class Numero;
class Clave
{
    public:

        //Constructor
        Clave(const char* cad);
        //Observador
        Cadena clave() const;
        //Metodos
        bool verifica(const char* cad) const;

        enum Razon {CORTA, ERROR_CRYPT};
        //Clase incorrecta
        class Incorrecta
        {
            public:
                Incorrecta(const Clave::Razon r);
                Clave::Razon razon() const;
            private:
                Clave::Razon r_;
                
        };

        //Destructor
        ~Clave();

    private:
        Cadena contrasena_;
};

class Usuario
{
    public:
        //Constantes
        typedef std::map<Numero, Tarjeta*> Tarjetas;
        typedef std::unordered_map<Articulo*, unsigned> Articulos;


        //Constructores
        Usuario(const Cadena& id, const Cadena& nom, const Cadena& apell, const Cadena& direc, const Clave& pass);
        Usuario(const Usuario& that) = delete;
        Usuario& operator=(const Usuario&) = delete;

        //Clase Id_Duplicado
        class Id_Duplicado
        {
            public:
                Id_Duplicado(const Cadena& c) : idd_(c) {};
                const Cadena& idd() const {return idd_;};
            private:
                Cadena idd_;
        };

        //Observadores
        const Cadena& id() const {return ID_;};
        const Cadena& nombre() const {return nombre_;};
        const Cadena& apellido() const {return apellido_;};
        const Cadena& direccion() const {return direccion_;};
        const Tarjetas& tarjetas() const {return tarjetas_;};
        const size_t n_articulos() const {return n_articulos_;};
        const Articulos& compra() const {return articulos_;};

        //Funciones
        void es_titular_de(const Tarjeta&);
        void no_es_titular_de(const Tarjeta&);
        void compra(const Articulo& a, size_t cant = 1);

        friend std::ostream& operator<<(std::ostream& os, const Usuario& u);

        //Destructor
        ~Usuario();
    private:
        Cadena ID_, nombre_, apellido_, direccion_;
        Clave pass_;
        Tarjetas tarjetas_;
        Articulos articulos_;
        size_t n_articulos_;
        static std::unordered_set<Cadena> registrados;
};

std::ostream& operator<<(std::ostream& os, const Usuario& u);
void mostrat_carro(std::ostream& os, const Usuario& u);

#endif
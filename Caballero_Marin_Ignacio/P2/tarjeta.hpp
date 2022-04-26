#ifndef TARJETA_H_
#define TARJETA_H_
#include "../P1/cadena.hpp"
#include "../P1/fecha.hpp"
#include "usuario.hpp"

class Numero
{
    public:
        //Constructor
        Numero(const char* cad);
        //Métodos internos 
        const char* toString();
        //Observadores
        Cadena numero() const {return numero_;};
    
        enum Razon {LONGITUD, DIGITOS, NO_VALIDO};
        //Clase Incorrecto
        class Incorrecto
        {
            public:

                Incorrecto(Numero::Razon r): r_(r) {};
                Numero::Razon razon() const {return r_;};

            private:

                Numero::Razon r_;
        };

        ~Numero();

    private:

        Cadena numero_;
};

//Métodos externos
bool operator<(Numero n1, Numero n2);

class Tarjeta
{
    public:
        enum Tipo {Otro, VISA, Mastercard, Maestro, JCB, AmericanExpress};

        //Constructor
        Tarjeta(Numero& num, Usuario& usuario, const Fecha& caducidad);
        Tarjeta(const Tarjeta& that) = delete;
        Tarjeta& operator=(const Tarjeta& ) = delete;

        //Clase caducada
        class Caducada
        {
            public:
                Caducada(const Fecha& f) : fecha_cad_(f) {};
                const Fecha& cuando() const {return fecha_cad_;};
            private:
                Fecha fecha_cad_;
        };

        //Clase Num_Duplicado
        class Num_Duplicado
        {
            public:
                Num_Duplicado(const Numero& numero) : num_(numero) {};
                const Numero& que() const {return num_;};
            private:
                Numero num_;
        };

        //Clase Desactivada
        class Desactivada
        {
            public:
                Desactivada();
            private:
        };

        //Observadores
        const Tarjeta::Tipo tipo() const {return tipo_;};
        const Numero& numero() const {return n_tarjeta_;};
        Usuario* titular() const {return titular_;};
        const Fecha& caducidad() const {return caducidad_;};
        const bool activa() const {return activa_;};

        //Funciones
        void anular_tarjeta();
        Tipo esTipo();

        //Destructor
        ~Tarjeta();

    private:
        Numero n_tarjeta_;
        Usuario* titular_;
        Fecha caducidad_;
        bool activa_ = true;
        Tipo tipo_;
};

std::ostream& operator<<(std::ostream& os, const Tarjeta& t);
std::ostream& operator<<(std::ostream& os, const Tarjeta::Tipo& tipo);
bool operator<(const Tarjeta& t1, const Tarjeta& t2);
bool operator>(const Tarjeta& t1, const Tarjeta& t2);

#endif
#ifndef CADENA_HPP_
#define CADENA_HPP_

#include <iterator>

class Cadena
{
    public:

        //Constructores
        Cadena(size_t l = 0, char c = ' ');
        Cadena(const Cadena& c);
        Cadena(const char* s);

        //Destructor
        ~Cadena();

        //Observadores
        const char* puts();
        const char* puts() const;

        //Funciones
        size_t length();
        const size_t length() const;
        size_t length(const char* c);
        const size_t length(const char* c) const;
        const char* c_str() const;

        //Op. Aritmeticos
        Cadena operator+=(const Cadena& c);

        //Op. de Asignacion
        Cadena& operator= (const Cadena& c);
        Cadena& operator= (const char* c);

        //Op. de Indice
        char& operator[] (size_t i);
        const char& operator[] (size_t i) const;
        char& at(size_t i);
        const char& at(size_t i) const;
        Cadena substr(size_t i, size_t fin) const;

    private:

        char *s_;
        size_t tam_;

        void copiar(const Cadena& c);
        void copiar(const char*);
};

//Op. Aritmeticos
Cadena operator+(const Cadena& a, const Cadena& b);

//Op. Lógicos
bool operator==(const Cadena& a, const Cadena& b);
bool operator!=(const Cadena& a, const Cadena& b);
bool operator>(const Cadena& a, const Cadena& b);
bool operator<(const Cadena& a, const Cadena& b);
bool operator>=(const Cadena& a, const Cadena& b);
bool operator<=(const Cadena& a, const Cadena& b);

#endif
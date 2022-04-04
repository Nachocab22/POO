#ifndef CADENA_HPP_
#define CADENA_HPP_

#include <iterator>
#include <functional>

class Cadena
{
    public:

        //Constructores
        Cadena(size_t l = 0, char c = ' ');
        Cadena(const Cadena& c);
        Cadena(const char* s);
        Cadena(Cadena&& c); //ctor. movimiento NEW

        //Destructor
        ~Cadena();

        //Observadores
        const char* puts() {return s_;};
        const char* puts() const {return s_;};

        //Funciones
        size_t length() noexcept{return tam_;};
        const size_t length() const noexcept{return tam_;};
        size_t length(const char* c)noexcept;
        const size_t length(const char* c) const noexcept;
        const char* c_str() const noexcept{return s_;};

        //Op. Aritmeticos
        Cadena operator+=(const Cadena& c);

        //Op. de Asignacion
        Cadena& operator= (const Cadena& c);
        Cadena& operator= (const char* c);
        Cadena& operator= (Cadena&& c); //Asignacion de movimiento NEW

        //Op. de Indice
        char& operator[] (size_t i) noexcept;
        const char& operator[] (size_t i) const noexcept;
        char& at(size_t i);
        const char& at(size_t i) const;
        Cadena substr(size_t i, size_t tam) const;

        //Iteradores
        typedef char* iterator;
        typedef const char* const_iterator;
        typedef std::reverse_iterator<iterator> reverse_iterator;
        typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

        //Funciones iteradores
        iterator begin() noexcept{return s_;};
        const_iterator begin() const noexcept{return const_iterator(s_);};
        const_iterator cbegin() const noexcept{return const_iterator(s_);};
        reverse_iterator rbegin() noexcept{return reverse_iterator(end());}; 
        const_reverse_iterator rbegin() const noexcept{return const_reverse_iterator(end());};
        const_reverse_iterator crbegin() const noexcept{return const_reverse_iterator(end());};

        iterator end() noexcept{return s_ + tam_;};
        const_iterator end() const noexcept{return const_iterator(s_ + tam_);};
        const_iterator cend() const noexcept{return const_iterator(s_ + tam_);};
        reverse_iterator rend() noexcept{return reverse_iterator(begin());};
        const_reverse_iterator rend() const noexcept{return const_reverse_iterator(begin());};
        const_reverse_iterator crend() const noexcept{return const_reverse_iterator(begin());};


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

//Entrada - salida
std::ostream& operator<<(std::ostream& os, const Cadena& c) noexcept;
std::istream& operator>>(std::istream& is, Cadena& c) noexcept;

#endif
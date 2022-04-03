#include <iostream>
#include <cstring>
#include <stdexcept>
#include "cadena.hpp"

using namespace std;

//FUNCIONES PUBLICAS

//Constructores
Cadena::Cadena(size_t l, char c): s_(new char[l + 1]), tam_(l)
{
    while (l-->0) s_[l] = c;;
    s_[tam_] = '\0';
}

Cadena::Cadena(const Cadena& c): s_{new char[c.tam_ + 1]}, tam_{c.tam_} {copiar(c);}
Cadena::Cadena(const char* s): s_{new char[length(s) + 1]}, tam_{length(s)} {copiar(s);}
Cadena::~Cadena()
{
    tam_ = 0;
    delete[] s_;
}

//Observadores
inline const char* Cadena::puts()       {return s_;}
inline const char* Cadena::puts() const {return s_;}

//Funciones
size_t Cadena::length() {return tam_;}
const size_t Cadena::length() const {return tam_;}
size_t Cadena::length(const char* s)
{
    int i = 0;
    while (s[i]) i++;
    return i;
    
}
const size_t Cadena::length(const char* s) const
{
    int i = 0;
    while (s[i]) i++;
    return i;
    
}

//Op. aritmeticos
Cadena Cadena::operator+=(const Cadena& c)
{
    char* caux = new char[tam_ + 1];
    strcpy(caux, s_);

    tam_ += c.tam_;

    delete[] s_;
    s_ = new char[tam_ + 1];

    int i = 0;
    while(caux[i])
    {
        s_[i] = caux[i];
        i++;
    }

    int j = i;
    i = 0;
    while(c[i])
    {
        s_[j] = c.s_[i];
        i++;
        j++;
    }

    s_[j] = '\0';
    return *this;
}

//Op. de Asignacion
Cadena& Cadena::operator= (const Cadena& c)
{
    if(*this != c) copiar(c);
    return *this;
}

Cadena& Cadena::operator= (const char* c)
{
    Cadena cc(c);
    if(*this != cc) copiar(c);
    return *this;
}

//Op. indice
char& Cadena::operator[] (size_t i){return s_[i];}
const char& Cadena::operator[] (size_t i) const {return s_[i];}
char& Cadena::at(size_t i)
{
    if(i < tam_) return s_[i];
    else {
        throw std::out_of_range("Funcion at(): indice fuera de rango de la Cadena");
    }
}
Cadena Cadena::substr(size_t i, size_t fin) const
{
    if(i > tam_ || fin > tam_){
        throw std::out_of_range("Funcion substr(): indice fuera de rango");
    }
    if(i > fin) std::swap(i,fin);
    Cadena caux(fin - i + 1);
    int j = 0;
    while (i <= fin)
    {
        caux[j] = s_[i];
        i++;
        j++;
    }

    caux[j] = '\0';
    return caux;
}

//FUNCIONES PRIVADAS

void Cadena::copiar(const Cadena& c)
{
    tam_ = c.tam_;
    delete[] s_;
    s_ = new char[tam_ + 1];
    strcpy(s_, c.s_);
}

void Cadena::copiar(const char* c)
{
    tam_ = strlen(c);
    delete[] s_;
    s_ = new char[tam_ + 1];
    strcpy(s_, c);
}

//Op. Aritmeticos
Cadena operator+(const Cadena& a, const Cadena& b)
{
    Cadena caux(a);
    return caux += b;
}

//Op. Logicos
bool operator==(const Cadena& a, const Cadena& b)
{
    if(a.length() != b.length()) return false;

    int last = std::min(a.length(), b.length());

    for(int i = 0; i < last; i++)
    {
        if(a.at(i) != b.at(i))
            return false;
    }
}

bool operator!=(const Cadena& a, const Cadena& b) {return !(a == b);}
bool operator<(const Cadena& a, const Cadena& b)
{
    if(a.length() > b.length()) return false;
    if(a.length() < b.length()) return true;
    int last = std::min(a.length(), b.length());
    for(int i = 0; i < last; i++){
        if(static_cast<int>(a.at(i)) > static_cast<int>(b.at(i))) return false;
    }
    return true;
}

bool operator>(const Cadena& a, const Cadena& b) {return (b < a);}
bool operator>=(const Cadena& a, const Cadena& b)
{
    if(a == b) return true;
    return a > b;
}

bool operator<=(const Cadena& a, const Cadena& b)
{
    if(a == b) return true;
    return a < b;
}


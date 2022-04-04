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
Cadena::Cadena(Cadena&& c): tam_(c.tam_), s_(c.s_)
{
    c.tam_ = 0;
    c.s_ = nullptr;
}

//Destructor
Cadena::~Cadena()
{
    tam_ = 0;
    delete[] s_;
}

//Funciones
size_t Cadena::length(const char* s)noexcept
{
    int i = 0;
    while (s[i]) i++;
    return i;
    
}
const size_t Cadena::length(const char* s) const noexcept
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

Cadena& Cadena::operator= (Cadena&& c)
{
    tam_ = c.tam_;
    delete[] s_;
    s_ = c.s_;
    c.tam_ = 0;
    c.s_ = nullptr;
    return *this;
}

//Op. indice
char& Cadena::operator[] (size_t i) noexcept{return s_[i];}
const char& Cadena::operator[] (size_t i) const noexcept{return s_[i];}
char& Cadena::at(size_t i)
{
    if(i < tam_) return s_[i];
    else {
        throw std::out_of_range("Funcion at(): indice fuera de rango de la Cadena");
    }
}

const char& Cadena::at(size_t i) const
{
    if(i < tam_) return s_[i];
    else {
        throw std::out_of_range("Funcion at(): indice fuera de rango de la Cadena");
    }
}

Cadena Cadena::substr(size_t i, size_t tam) const
{
    if(i > tam_ || tam > tam_ || (i + tam) > tam_){
        throw std::out_of_range("Funcion substr(): indice fuera de rango");
    }

    char *caux = new char[tam + 1];
    int j = 0;
    unsigned int fin = i + tam;
    while (i < fin)
    {
        caux[j] = s_[i];
        i++;
        j++;
    }

    caux[j] = '\0';
    Cadena cc(caux);
    delete[] caux;

    return cc;
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
    return true;
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

//Entrada - Salida
std::ostream& operator<<(std::ostream& os, const Cadena& c)noexcept
{
    os << c.c_str();
    return os;
}

std::istream& operator>>(std::istream& is, Cadena& c)noexcept
{
    char s[33] = "";
    is.width(33);
    is >> s;
    c = s;
    return is;
}
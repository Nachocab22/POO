#include "tarjeta.hpp"

#include <iostream>
#include <string.h>
#include <iterator>
#include <algorithm>
#include <cstddef>

////NUMERO////
//Algoritmo de Luhn
bool luhn(const Cadena& numero)
{
  size_t n = numero.length();
  size_t suma = 0;
  bool alt = false;
  for (int i = n - 1; i > -1; --i) {
    n = numero[size_t(i)] - '0';
    if (alt) {
      n *= 2;
      if (n > 9)
	n = (n % 10) + 1;
    }
    alt = !alt;
    suma += n;
  }
  return !(suma % 10);
}

//Constructor
Numero::Numero(const char* cad)
{
    std::string s = cad;
    std::string::iterator pos_f = std::remove(s.begin(), s.end(), ' ');
    s.erase(pos_f, s.end());

    for(int i = 0; i < s.length(); i++)
    {
        if(isalpha(s[i]))
            throw Incorrecto(DIGITOS);
    }

    char c[s.length() + 1];
    strcpy(c, s.c_str());

    numero_ = c;

    if(numero_.length() < 13 || numero_.length() > 19)
        throw Incorrecto(LONGITUD);
    else if(!luhn(numero_))
        throw Incorrecto(NO_VALIDO);
}

const char* Numero::toString()
{
    return numero_.c_str();
}

//Funciones externas
bool operator<(Numero n1, Numero n2)
{
    if(strcmp(n1.toString(), n2.toString()) < 0)
        return true;
    else    
        return false;
}

////TARJETA////
//Constructor
Tarjeta::Tarjeta(Numero& num, Usuario& usuario, const Fecha& caducidad) : n_tarjeta_(num), titular_(usuario), caducidad_(caducidad) 
{
    if(caducidad < Fecha())
        throw Caducada(caducidad);

    titular_->es_titular_de(*this);
}

//Funciones
void Tarjeta::anular_tarjeta()
{
    activa_ = false;
    const_cast<Usuario*&>(titular_) = nullptr;
}

Tarjeta::Tipo Tarjeta::esTipo()
{
    int a = atoi(n_tarjeta_.numero().substr(0, 2).c_str());
    switch (a/10)
    {
    case 3:
        if(a == 34 || a == 37) return Tarjeta::AmericanExpress;
        else return Tarjeta::JCB;
        break;
    case 4:
        return Tarjeta::VISA;
        break;
    case 5:
        return Tarjeta::Mastercard;
        break;
    case 6: 
        return Tarjeta::Maestro;
        break;
    default:
        return Tarjeta::Otro;
    }
}

//Operadores
std::ostream& operator<<(std::ostream& os, const Tarjeta& t)
{
    os << t.tipo() << std::endl << t.numero() << std::endl;
    Cadena aux = t.titular()->nombre();
    int i = 0;
    while (aux[i] != '\0')
    {
        if(islower(aux[i])) 
            aux[i] = toupper(aux[i]);
        i++;
    }
    os << aux << " ";

    i = 0;
    aux = t.titular()->apellidos();
    while(aux[i] != '\0')
    {
        if(islower(aux[i]))
            aux[i] = toupper(aux[i]);
        i++;
    }
    os << aux << std::endl;

    os << "Caduca: " << std::setfill('0') << std::setw(2) << t.caducidad().mes() << "/" << std::setw(2) << (t.caducidad().anno() % 100) << std::endl;
    return os;
}

std::ostream& operator<<(std::ostream& os, const Tarjeta::Tipo tipo)
{
    switch (tipo)
    {
    case Tarjeta::VISA : os << "VISA"; break;
    case Tarjeta::Mastercard : os << "Mastercard"; break;
    case Tarjeta::Maestro : os << "Maestro"; break;
    case Tarjeta::JCB : os << "JCB"; break;
    case Tarjeta::AmericanExpress : os << "AmericanExpress"; break;
    case Tarjeta::Otro : os << "Otro"; break;
    default : os << "Error";
    }
    return os;
}

bool operator<(const Tarjeta& t1, const Tarjeta& t2) {return t1.numero() < t2.numero();};
bool operator>(const Tarjeta& t1, const Tarjeta& t2) {return t2.numero() < t1.numero();};

//Destructor
Tarjeta::~Tarjeta()
{
    if(titular_)
        titular_->no_es_titular_de(*this);
}
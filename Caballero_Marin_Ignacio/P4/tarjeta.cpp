#include "tarjeta.hpp"

#include <iomanip>
#include <cstring>
#include <string.h>
#include <cctype>
#include <algorithm>

using namespace std;

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
Numero::Numero(const Cadena& cad)
{
    Cadena n(cad);
    Cadena::iterator i = std::remove_if(n.begin(), n.end(), [](char x) {return std::isspace(x);});
    if(i != n.end())
    {
        *i = '\0';
        n = Cadena(n.c_str());
    }

    unary_negate<esDigito> not_esDigito((esDigito()));
    Cadena::const_iterator it = find_if(n.begin(), n.end(), not_esDigito);
    if(it != n.end()) throw Incorrecto(Razon::DIGITOS);

    if(n.length()>19 || n.length()<13)
        throw Incorrecto(Razon::LONGITUD);
    if(!luhn(n))
        throw Incorrecto(Razon::NO_VALIDO);
    
    numero_ = n;
}

//Funciones externas
void eliminarChar(Cadena& cad, size_t pos)
{
    Cadena nuevo = cad.substr(0, pos);
    
    if((pos + 1) < cad.length())
        nuevo += Cadena(cad.substr(pos+1, cad.length()));

    cad = move(nuevo);
}

bool operator<(Numero n1, Numero n2)
{
    return strcmp(n1, n2) < 0;
}

////TARJETA////
//Constructor
Tarjeta::Tarjeta(const Numero& num, Usuario& usuario, const Fecha& caducidad) : n_tarjeta_(num), titular_(&usuario), caducidad_(caducidad) 
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
    aux = t.titular()->apellido();
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

std::ostream& operator<<(std::ostream& os, const Tarjeta::Tipo& tipo)
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
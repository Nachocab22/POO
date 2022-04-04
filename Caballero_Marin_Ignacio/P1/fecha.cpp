#include <ctime>
#include <new>
#include <iomanip>
#include <cstdio>
#include <iostream>
#include "fecha.hpp"

using namespace std;

//CLASE INVALIDA
Fecha::Invalida::Invalida(const char* in): r_(in){}
inline const char* Fecha::Invalida::por_que() const {return r_;}

//FUNCIONES PRIVADAS
void Fecha::corregir()
{
    try{
        while(mes_ > 12)
        {
            mes_-=12;
            anno_++;
        }
        while (dia_ > ult_dia())
        {
            dia_ -= ult_dia();
            if(++mes_ > 12){
                mes_ = 1;
                anno_++;
            }
        }
        while (dia_ <= 0)
        {
            if(--mes_ <= 0){
                mes_ = 12;
                anno_--;
            }
            dia_ += ult_dia();
        }
        if(!valida()) {Fecha::Invalida in("Fecha invalida"); throw in;}
    }
    catch(Fecha::Invalida in) {cerr <<in.por_que()<<endl;};
}

bool Fecha::valida() const
{
    return !(dia_ > ult_dia() || dia_< 1 || mes_ > 12 || mes_ < 1 || anno_ > Fecha::AnnoMaximo || anno_ < Fecha::AnnoMinimo);
}

int Fecha::ult_dia() const
{
    try{
        if(mes_ == 1 || mes_ == 3 || mes_ == 5 || mes_ == 7 || mes_ == 8 || mes_ == 10 || mes_ == 12) return 31;
        else if(mes_ == 4 || mes_ == 6 || mes_ == 9 || mes_ == 11) return 30;
        else if(mes_ == 2){
            if (anno_ % 4 == 0 && (anno_ % 400 == 0 || anno_ % 100 != 0)) return 29;
            else return 28;
        }
        else {Fecha::Invalida in("Mes invalido"); throw in;}
    }
    catch(Fecha::Invalida in) {cerr<<in.por_que()<<endl;}
    return 0;
}

//FUNCIONES PUBLICAS

//Constructor

Fecha::Fecha(int d, int m, int a): dia_(d), mes_(m), anno_(a) 
{
    std::time_t tiempo_calendario = std::time(0);
    std::tm* tiempo_descompuesto = std::localtime(&tiempo_calendario);

    if(anno_ == 0) anno_ = tiempo_descompuesto->tm_year + 1900;
    if(mes_ == 0) mes_ = tiempo_descompuesto->tm_mon + 1;
    if(dia_ == 0) dia_ = tiempo_descompuesto->tm_mday;
    corregir();
}

Fecha::Fecha(const char* c)
{
    dia_ = -2; 
    mes_ = -2;
    anno_ = -2;
    sscanf(c, "%d/%d/%d", &dia_, &mes_, &anno_);

    std::time_t tiempo_calendario = std::time(0);
    std::tm* tiempo_descompuesto = std::localtime(&tiempo_calendario);
    if(anno_ == 0) anno_ = tiempo_descompuesto->tm_year + 1900;
        else while(anno_ > 9999) anno_ /= 10;
    if(mes_ == 0) mes_ = tiempo_descompuesto->tm_mon + 1;
    if(dia_ == 0) dia_ = tiempo_descompuesto->tm_mday;

    if(!valida()) throw Fecha::Invalida ("Fecha invalida");
}

//Constructor de conversion
const char* Fecha::cadena() const{
    
    static char* buffer = new char[40];
    tm f = {};
    f.tm_mday = dia_;
    f.tm_mon = mes_ - 1;
    f.tm_year = anno_ - 1900;

    mktime(&f);
    strftime(buffer, 40, "%A %d de %B de %Y", &f);

    return buffer;
}

//Destructor

Fecha::~Fecha(){dia_ = 0; mes_ = 0; anno_ = 0;}

//Operadores

Fecha& Fecha::operator++()
{
    *this+=1;
    return *this;
}

Fecha Fecha::operator++(int)
{
    Fecha f(*this);
    *this +=(1);
    return f;
}

Fecha& Fecha::operator+=(int dias)
{
    this->dia_ += dias;

    corregir();
    return *this;
}

Fecha& Fecha::operator--()
{
    *this-=1;
    return *this;
}

Fecha Fecha::operator--(int)
{
    Fecha f(*this);
    *this -= 1;
    return f;
}

Fecha& Fecha::operator-=(int dias)
{
    *this -=(dias);
    return *this;
}

//Op. aritmeticos
Fecha Fecha::operator+(int dia) const
{
    Fecha f(*this);
    f +=(dia);
    return f;
}

Fecha Fecha::operator-(int dia) const
{
    Fecha f(*this);
    f -=(dia);
    return f;
}

//Op. logicos
bool operator ==(const Fecha& a, const Fecha& b)
{
    return (a.dia() == b.dia() && a.mes() == b.mes() && a.anno() == b.anno());
}

bool operator <(const Fecha& a, const Fecha& b)
{
    if(a.anno() < b.anno()) return true;
    else if(a.anno() > b.anno()) return false;
    else if(a.mes() < b.mes()) return true;
    else if(a.mes() > b.mes()) return false;
    else if(a.dia() < b.dia()) return true;
    else if(a.dia() > b.dia()) return false;
    else return false;
}

bool operator >(const Fecha& a, const Fecha& b)
{
    return (b < a);
}

bool operator !=(const Fecha& a, const Fecha& b)
{
    return !(a == b);
}

bool operator <=(const Fecha& a, const Fecha& b)
{
    return !(a > b);
}

bool operator >=(const Fecha& a, const Fecha& b)
{
    return !(a < b);
}

//Entrada - salida

std::ostream& operator<<(std::ostream& os, const Fecha& f)noexcept
{
    os<<f.cadena();
    return os;
}

std::istream& operator>>(std::istream& is, Fecha& f)
{
    char* s = new char[11];
    is.width(11); 
    is >> s;
    try{
        f = s;
    }catch(Fecha::Invalida i){
        is.setstate(std::ios::failbit);
        delete[] s;
        throw Fecha::Invalida("Error de formato en el operador >>. Se esperaba dd/mm/aaaa");
    }
    delete[] s;

    return is;
}
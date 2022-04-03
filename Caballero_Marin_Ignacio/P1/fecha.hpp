#ifndef FECHA_HPP_
#define FECHA_HPP_

class Fecha
{
    public:

        //Clase Invalida
        class Invalida
        {
            public:
                Invalida(const char* r);
                const char* por_que() const;
            private:
                const char* r_;
        };

        static const int AnnoMinimo = 1902, AnnoMaximo = 2037;

        //Constructores
        explicit Fecha(int d = 0, int m = 0, int a = 0);
        Fecha(const char* c);
        Fecha(const Fecha &f); //Constructor de copia
        operator const char* () const; //Conversor a const char*

        //Destructor
        ~Fecha();

        //Operadores
        Fecha operator ++();
        Fecha& operator ++(int);
        Fecha operator +=(int dias);

        Fecha operator --();
        Fecha& operator --(int);
        Fecha operator -=(int dias);
        
        //Observadores
        int dia() const;
        int mes() const;
        int anno() const;

    private:

        int dia_, mes_, anno_;

        void corregir();
        bool valida() const;
        int ult_dia() const;
};

//Op. aritmeticos
Fecha operator +(const Fecha f, int dias);
Fecha operator -(const Fecha f, int dias);

//Op. logicos
bool operator ==(const Fecha& a, const Fecha& b);
bool operator <(const Fecha& a, const Fecha& b);
bool operator >(const Fecha& a, const Fecha& b);
bool operator !=(const Fecha& a, const Fecha& b);
bool operator <=(const Fecha& a, const Fecha& b);
bool operator >=(const Fecha& a, const Fecha& b);

//Entrada - salida
std::ostream& operator<<(std::ostream& os, const Fecha& f);
std::istream& operator>>(std::istream& is, Fecha& f);

#endif
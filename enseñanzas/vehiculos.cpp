#include <vector>
#include <iostream>
#include <iomanip>

using namespace std;

class Vehiculo {
    public:
        Vehiculo(int numBastidor) : motorValido(true), tanqueLleno(true), lucesOk(true), numBastidor(numBastidor) {}
        inline int numeroBastidor() const { return numBastidor; }
        bool motorValido;
        bool tanqueLleno;
        bool lucesOk;

    private:
        int numBastidor;
};

class Moto: public Vehiculo {
    public:
        Moto(int numBastidor) : Vehiculo(numBastidor), tieneCasco(true) {}
        bool tieneCasco;
};

class Coche: public Vehiculo {
    public:
        Coche(int numBastidor) : Vehiculo(numBastidor), embragueTiene(true) {}
        bool embragueTiene;
};

class Camion: public Vehiculo {
    public:
        Camion(int numBastidor) : Vehiculo(numBastidor), pesoValido(true) {}
        bool pesoValido;
};

void comprobar(const vector<Vehiculo*> &v){
    for(Vehiculo *actual : v) {
        cout 
            << actual->numeroBastidor() 
            << "\nMotor: " << boolalpha << actual->motorValido 
            << "\nTanque: " << actual->tanqueLleno 
            << "\nLuces: " << actual->lucesOk
            << "\n";

        if(Coche *c = static_cast<Coche*>(actual))
            cout << "Embrague coche: " << c->embragueTiene;
        else if(Moto *m = static_cast<Moto*>(actual))
            cout << "Casto moto: " << m->tieneCasco;
        else if(Camion *c = static_cast<Camion*>(actual))
            cout << "Peso camión: " << c->pesoValido;

        cout  << "\n-------------------------\n";
    }
}

int main(int argc, char const *argv[]) {
    Coche c1(1);
    Moto m1(2);
    Camion ca(3);
    Coche WanCar(5);

    comprobar({&c1, &m1, &ca, &WanCar});

    return 0;
}


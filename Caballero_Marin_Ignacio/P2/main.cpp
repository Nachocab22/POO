#include "articulo.hpp"
#include "../P1/cadena.hpp"
#include "../P1/fecha.hpp"
using namespace std;

int main(){
    Articulo A("1284", "Caja de carton", "12/06/2004", 13.5, 125);
    cout << A << endl;
}
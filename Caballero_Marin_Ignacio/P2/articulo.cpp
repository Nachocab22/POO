#include <iostream>
#include <stdlib.h>
#include "articulo.hpp"

std::ostream& operator<<(std::ostream& os, const Articulo& a)noexcept
{
    os << "[" + a.referencia() + "] \"" + a.titulo() + "\", " + a.f_publi().cadena() + ". " + a.precio() + " €";
    return os;
}

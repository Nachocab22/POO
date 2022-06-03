#include <iostream>
#include <stdlib.h>
#include <iomanip>
#include "articulo.hpp"
#include "fecha.hpp"
#include "cadena.hpp"

using namespace std;

////CLASE ARTICULO////
Articulo::Articulo(const Autores& autores, const Cadena& ref, const Cadena& titulo, const Fecha& f_pub, const double precio) : autores_(autores), referencia_(ref), titulo_(titulo), f_publicacion_(f_pub), precio_(precio)
{
    if(autores.empty()) 
        throw Autores_vacios();
}

std::ostream& operator<<(std::ostream& os, const Articulo& a)noexcept
{
    std::locale::global(std::locale(""));
    os << "[" + a.referencia() + "] \"" + a.titulo() + "\", de";
    const auto& autores = a.autores();
    auto i = autores.begin();
    os << (*i)->apellidos();
    while (++i != autores.end())
    {
        os << ", " << (*i)->apellidos();
    }
    os << ". " << a.f_publi().anno() << ". " << fixed << setprecision(2) << a.precio() << "€\n\t";
    a.impresion_especifica(os);
    return os;
}

////CLASE LIBRODIGITAL////
LibroDigital::LibroDigital::LibroDigital(const Autores& autores, const Cadena& ref, const Cadena& titulo, const Fecha& f_pub, const double precio,const Fecha& fExp) : Articulo(autores, ref, titulo, f_pub, precio), f_expir_(fExp){}

void LibroDigital::impresion_especifica(ostream& os) const{
    os << "A la venta hasta el " << f_expir_ << ".";
}

////CLASE ARTICULOALMACENABLE////
ArticuloAlmacenable::ArticuloAlmacenable(const Autores& autores, const Cadena& ref, const Cadena& titulo, const Fecha& f_pub, const double precio, unsigned stock) : Articulo(autores, ref, titulo, f_pub, precio), stock_(stock){}

////CLASE LIBRO////

Libro::Libro(const Autores& autores, const Cadena& ref, const Cadena& titulo, const Fecha& f_pub, const double precio, unsigned paginas, unsigned stock) : ArticuloAlmacenable(autores, ref, titulo, f_pub, precio, stock), n_pag_(paginas){}

void Libro::impresion_especifica(ostream& os) const
{
    os << n_pag_ << " págs., " << stock_ << " unidades.";
}

////CLASE CEDERRON////
Cederron::Cederron(const Autores& autores, const Cadena& ref, const Cadena& titulo, const Fecha& f_pub, const double precio, unsigned tamano, unsigned stock) : ArticuloAlmacenable(autores, ref, titulo, f_pub, precio, stock), tam_(tamano){}

void Cederron::impresion_especifica(ostream& os) const
{
    os << tam_ << " MB, " << stock_ << " unidades.";
}

////CLASE AUTOR////
Autor::Autor(const Cadena& nombre, const Cadena& apellido, const Cadena& direccion): nombre_(nombre), apellidos_(apellido), direccion_(direccion){}
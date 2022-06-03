#include "pedido.hpp"

using namespace std;

unsigned Pedido::N_Pedidos = 0;

//Constructor
Pedido::Pedido(Usuario_Pedido& up, Pedido_Articulo& pa, Usuario& usuario, const Tarjeta& tarjeta, const Fecha& f) : n_p_(N_Pedidos+1), tarjeta_(&tarjeta), fPedido_(f), importe_(0.)
{
    if(usuario.compra().empty())
        throw Pedido::Vacio(&usuario);
    if(tarjeta.titular() != &usuario)
        throw Pedido::Impostor(&usuario);
    if(tarjeta.caducidad() < f)
        throw Tarjeta::Caducada(tarjeta.caducidad());
    if(!tarjeta.activa())
        throw Tarjeta::Desactivada();
    
    auto carro = usuario.compra();
    for(auto& iter : carro){
        if(ArticuloAlmacenable* aa = dynamic_cast<ArticuloAlmacenable*>(iter.first)){
            if(iter.second > aa->stock())
                const_cast<Usuario::Articulos&>(usuario.compra()).clear();
                throw SinStock(iter.first);
        }
        else
            if(LibroDigital* ld = dynamic_cast<LibroDigital*>(iter.first))
                if(ld->f_expir() < f)
                    usuario.compra(*iter.first, 0);
    }

    if(usuario.compra().empty())
        throw Vacio(&usuario);

    up.asocia(*this, usuario);
    carro = usuario.compra();

    for(auto& iter : carro){
        importe_ += iter.first->precio() * iter.second;
        pa.pedir(*iter.first, *this, iter.first->precio(), iter.second);
        if(ArticuloAlmacenable* aa = dynamic_cast<ArticuloAlmacenable*>(iter.first))
            aa->stock() -= iter.second;
    }

    const_cast<Usuario::Articulos&>(usuario.compra()).clear();
    n_p_ = ++N_Pedidos;
}

//Op. Insercion
std::ostream& operator <<(std::ostream& os, const Pedido& p)
{
    os << left;
    os << "Núm. pedido: " << p.numero() << endl;
    os << setw(13) << "Fecha: " << p.fecha() << endl;
    os << setw(13) << "Pagado con: " << p.tarjeta()->tipo() << " n.º: " << p.tarjeta()->numero() << endl;
    os << setw(13) << "Importe: " << fixed << setprecision(2) << p.total() << " €" << endl;

    return os;
}
#ifndef PEDIDO_ARTICULO_HPP
#define PEDIDO_ARTICULO_HPP

#include <iostream>
#include <iomanip>
#include "articulo.hpp"
#include "pedido.hpp"

class LineaPedido
{
    public:
        //Constructor
        explicit LineaPedido(double pr, unsigned c=1);

        //Observadores
        const double precio_venta() const {return precio_;}
        const unsigned cantidad() const {return cantidad_;}
    private:
        double precio_;
        unsigned cantidad_;
};

std::ostream& operator<<(std::ostream& os, const LineaPedido& p);

class Pedido;
class Articulo;

class OrdenaPedidos: public std::binary_function<Pedido*, Pedido*, bool>
{
    public:
        bool operator()(const Pedido* p1, const Pedido* p2) const {return (p1->numero() < p2->numero());}
};
class OrdenaArticulos: public std::binary_function<Articulo*, Articulo*, bool>
{
    public:
        bool operator()(const Articulo* a1, const Articulo* a2) const {return (a1->referencia() < a2->referencia());}
};

class Pedido_Articulo
{
    public:
        //Librerias
        typedef std::map<Articulo*, LineaPedido, OrdenaArticulos> ItemsPedido;
        typedef std::map<Pedido*, LineaPedido, OrdenaPedidos> Pedidos;
        typedef std::map<Pedido*, ItemsPedido, OrdenaPedidos> PedArt;
        typedef std::map<Articulo*, Pedidos, OrdenaArticulos> ArtPed;

        //Observadores
        void pedir(Pedido& ped, Articulo& art, double precio, unsigned cantidad=1);
        void pedir(Articulo& art, Pedido& ped, double precio, unsigned cantidad=1);
        const ItemsPedido& detalle(Pedido& p);
        Pedidos ventas(Articulo& a);
        std::ostream& mostrarDetallePedidos(std::ostream& os) const;
        std::ostream& mostrarVentasArticulos(std::ostream& os) const;

    private:
        PedArt ped_art_;
        ArtPed art_ped_;
};

std::ostream& operator<<(std::ostream& os, const Pedido_Articulo::ItemsPedido& ip);
std::ostream& operator<<(std::ostream& os, const Pedido_Articulo::Pedidos& p);

#endif
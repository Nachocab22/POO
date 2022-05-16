#include "usuario.hpp"

using namespace std;
unordered_set<Cadena> Usuario::registrados;

////CLAVE////

//CLASE CLAVE::INCORRECTA
Clave::Incorrecta::Incorrecta(const Clave::Razon r)
{
    r_ = r;
}

Clave::Razon Clave::Incorrecta::razon() const
{
    return r_;
}

//CLASE CLAVE
Clave::Clave(const char* cad)
{
    setlocale(LC_ALL, "");

    if(strlen(cad) < 5) throw Clave::Incorrecta(Clave::CORTA); //ERROR - Clave <5 digitos

    random_device r;
    uniform_int_distribution<size_t> dist(0, 63);
    char const MD5chars[] = "./ABCDEFGHIJKLMNOPQRSTUVWYZabcdefghijklmnopqrstuvwyz0123456789";
    char salt[2] = {MD5chars[dist(r)], MD5chars[dist(r)]};

    if(crypt(cad, salt) == nullptr) throw Clave::Incorrecta(Clave::ERROR_CRYPT); //ERROR - Error al encriptar
    
    contrasena_ = crypt(cad, salt);
}

Cadena Clave::clave() const
{
    return contrasena_;
}

bool Clave::verifica(const char* cad) const
{
    char* c = crypt(cad, contrasena_.c_str());

    return c == Clave::contrasena_;
}

////USUARIO////

//Constructor
Usuario::Usuario(const Cadena& id, const Cadena& nom, const Cadena& apell, const Cadena& direc, const Clave& pass) : ID_(id), nombre_(nom), apellido_(apell), direccion_(direc), pass_(pass), n_articulos_(articulos_.size())
{
    if(!registrados.insert(ID_).second)
        throw Id_Duplicado(ID_);
}

//Funciones
void Usuario::es_titular_de(const Tarjeta &t)
{
    if(t.titular() == this)
        tarjetas_[t.numero()] = const_cast<Tarjeta*>(&t);
}

void Usuario::no_es_titular_de(const Tarjeta &t)
{
    tarjetas_.erase(t.numero());
}

void Usuario::compra(const Articulo& a, size_t cant)
{
    Usuario::Articulos::const_iterator got = articulos_.find(const_cast<Articulo*>(&a));

    if(got == articulos_.end()){
        if(cant > 0)
        {
            articulos_[const_cast<Articulo*>(&a)] = cant;
            n_articulos_++;
        }
    }
    else
    {
        if(cant > 0)
            articulos_[const_cast<Articulo*>(&a)] = cant;
        else
        {
            articulos_.erase(const_cast<Articulo*>(&a));
            n_articulos_--;
        }
    }
}

//Destructor
Usuario::~Usuario()
{
    for(auto& i : tarjetas_)
        i.second->anular_tarjeta();
    registrados.erase(ID_);
}

//Operadores
std::ostream& operator<<(std::ostream& os, const Usuario& u)
{
    setlocale(LC_ALL, "");
    os << u.ID_ << " [" << u.pass_.clave() << "] " << u.nombre_ << " " << u.apellido_ << endl;
    os << u.direccion_ << endl;
    os << "Tarjetas:\n";

    for(auto& t : u.tarjetas_)
        os << *t.second << endl;

    return os;
}

void mostrar_carro(ostream& os, const Usuario& u)
{
    os << "Carrito de compra de " << u.id() << " [Articulos: " << u.n_articulos() << "]" << endl << " Cantidad/Articulo" << endl;
    os << "=============================" << endl;

    for(Usuario::Articulos::const_iterator i = u.compra().begin(); i != u.compra().end(); i++){
        os << " " << i->second << "\t" << "[" << i->first->referencia() << "] \"" << i->first->titulo() << "\", ";
        os << i->first->f_publi().anno() << ". " << setprecision(2) << std::fixed << i->first->precio() << " €" << endl;
    }
}
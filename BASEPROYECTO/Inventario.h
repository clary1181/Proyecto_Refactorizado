#pragma once
#include <vector>
#include <iostream>
#include "Producto.h"

using std::string;
using std::cout;
using std::endl;

class Inventario
{
private:
    vector<Producto> productos;

    // Miembro estatico para la unica instancia
    static Inventario* instancia;

    // Constructor privado para evitar la instanciacion externa
    Inventario() = default;

    // Se agrego esta nueva funcion porque se noto 
    //que existia una duplicacion de datos inecesaria
    //con esta funcinion separamos la responsabilidad 
    //para no tener duplicados
    void mostrarEncabezadoTabla() const;

    // Eliminar constructor copia y operador asignacion para evitar copias
    Inventario(const Inventario&) = delete;
    Inventario& operator=(const Inventario&) = delete;

public:

    // Metodo publico estatico para acceder a la �nica instancia
    static Inventario& getInstance();

    void guardarInventarioEnArchivo(const string& nombreArchivo) const;
    void cargarInventarioDesdeArchivo(const string& nombreArchivo);
    bool productosVacios() const;
    void agregarProducto(const Producto& p);
    Producto* buscarProducto(int id);
    const Producto* buscarProducto(int id) const;
    void mostrarProductos() const;
    void buscarPorDescripcion(const string& texto) const;
    void mostrarProductoPorBusqueda() const;
};



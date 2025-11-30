#pragma once
#include <vector>
#include <map>
#include <iostream>
#include <memory>
#include "Inventario.h"
#include "Cliente.h"
#include "Venta.h"
#include "Reporte.h"

using std::string;
using std::cout;
using std::endl;
using std::unique_ptr;

class SistemaTienda
{
private:
    vector<Cliente> clientes;
    vector<Venta> ventas;
    int siguienteIdVenta = 1;
    int siguienteIdCliente = 1;

    // ESTAS FUNCIONES FUERON MOVIDAD DE PUBLIC A PRIVATE 
    // YA QUE SON PASOS INTERNOS PARA QUE LA FACHADA FUNCIONE
    Cliente* buscarCliente(int id);
    int obtenerSiguienteIdVenta();
    void guardarVentaEnArchivo(const Venta& venta);
    void cargarVentasEnMemoria();
    void generarReporte(Reporte* reporte) const;
    void buscarProductoInteractivo() const;
    void buscarProductoPorDescripcion(const std::string& texto) const;

public:
    //Inventario inventario;
    // Se quito Inventario inventario; 
    // Ahora SistemaTienda accede al Inventario a traves de Inventario::getInstance()

    void guardarInventario() const;
    void cargarInventario();
    void agregarProductoInventario(int id, const string& nombre, const string& talla, const string& color, double precio, int stock, string ubicacion);
    bool inventarioVacio() const;
    void mostrarInventario() const;
    void menuCatalogoProductos() const;

    // Métodos de Soporte Agregados para el Patrón Comando
    bool mostrarProductoPorId(int id) const; // Busca, muestra info, y retorna existencia
    bool actualizarStockProducto(int id, int cantidadAdicional); // Permite manipular el stock

    // Métodos Fachada para el subsistema de Ventas/Clientes:
    Cliente* agregarCliente(const string& nombre, const string& telefono, const string& email);
    
    void realizarVenta(int idCliente, const map<int, int>& productosComprados);
    void mostrarVentas() const;

    void cargarVentasDesdeArchivo();
    void menuReportes() const;
    const vector<Venta>& getVentas() const;
};
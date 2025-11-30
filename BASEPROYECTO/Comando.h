#pragma once

// Patron Comando para para convertir cada opción del menú en un objeto.
#include "SistemaTienda.h"
#include "Utilidades.h" 
#include <iostream>
#include <string>
#include <memory>
#include <map>
#include <cstdlib>

// La interfaz base del Comando
class Comando {
protected:
    // El Receiver (Receptor): la instancia de SistemaTienda que ejecuta la accion
    SistemaTienda& tienda;

public:
    Comando(SistemaTienda& t) : tienda(t) {}
    virtual ~Comando() = default;
    virtual void ejecutar() = 0;
};


// =======================================================
// COMANDOS CONCRETOS (Para menuGerente)
// =======================================================

class ComandoAgregarProducto : public Comando {
public:
    ComandoAgregarProducto(SistemaTienda& t) : Comando(t) {}
    void ejecutar() override {
        std::system("cls");

        // Lógica copiada del caso 1 en menuGerente de BASEPROYECTO.cpp
        int id = leerEntero("ID: ");

        if (tienda.mostrarProductoPorId(id)) { // Función que muestra info y retorna true si existe
            std::cout << "Este producto ya existe en el inventario.\n";
            int stockAdicional = leerEntero("¿Cuantas unidades desea agregar al stock existente? ");

            if (stockAdicional > 0) {
                if (tienda.actualizarStockProducto(id, stockAdicional)) {
                    std::cout << "Stock actualizado correctamente.\n";
                }
                else {
                    std::cout << "Error al actualizar el stock (ID no encontrado).\n";
                }
            }
            else {
                std::cout << "No se agregaron unidades al stock.\n";
            }
        }
        else {
            // El producto no existe, continuar con el flujo normal
            int stock;
            std::string nombre, talla, color, ubicacion;
            double precio;

            std::cout << "Nombre: "; std::cin >> nombre;
            std::cout << "Talla: "; std::cin >> talla;
            std::cout << "Color: "; std::cin >> color;
            std::cout << "Seccion: "; std::cin >> ubicacion;
            precio = leerFloat("Ingrese el precio: ");
            stock = leerEntero("Cantidad: ");

            tienda.agregarProductoInventario(id, nombre, talla, color, precio, stock, ubicacion);
            std::cout << "Producto agregado correctamente.\n";
        }

        std::cout << "\n\n";
        std::system("pause");
    }
};

class ComandoVerInventario : public Comando {
public:
    ComandoVerInventario(SistemaTienda& t) : Comando(t) {}
    void ejecutar() override {
        std::system("cls");
        tienda.menuCatalogoProductos();
        // La pausa es manejada internamente por menuCatalogoProductos si el usuario lo solicita
    }
};

class ComandoMostrarHistorialVentas : public Comando {
public:
    ComandoMostrarHistorialVentas(SistemaTienda& t) : Comando(t) {}
    void ejecutar() override {
        std::system("cls");
        tienda.mostrarVentas();
        std::cout << "\n\n";
        std::system("pause");
    }
};

class ComandoGestionReportes : public Comando {
public:
    ComandoGestionReportes(SistemaTienda& t) : Comando(t) {}
    void ejecutar() override {
        tienda.menuReportes();
    }
};

// =======================================================
// COMANDOS CONCRETOS (Para menuEmpleado)
// =======================================================

class ComandoVerInventarioEmpleado : public Comando {
public:
    ComandoVerInventarioEmpleado(SistemaTienda& t) : Comando(t) {}
    void ejecutar() override {
        std::system("cls");
        tienda.menuCatalogoProductos();
    }
};

class ComandoRealizarVenta : public Comando {
public:
    ComandoRealizarVenta(SistemaTienda& t) : Comando(t) {}
    void ejecutar() override {
        std::system("cls");
        std::cout << "\n=== REALIZAR VENTA ===\n";

        // Lógica copiada/ajustada del caso 2 en menuEmpleado
        std::string nombre, tel, email;
        std::cout << "Nombre del cliente: ";
        std::cin >> nombre;
        std::cout << "Telefono: ";
        std::cin >> tel;
        std::cout << "Email: ";
        std::cin >> email;
        Cliente* cliente = tienda.agregarCliente(nombre, tel, email);

        std::map<int, int> productos;
        int idProd, cantidad;
        char mas;
        do {
            idProd = leerEntero("ID del producto: ");
            cantidad = leerEntero("Cantidad: ");
            productos[idProd] = cantidad;
            std::cout << "¿Agregar otro producto? (s/n): ";
            std::cin >> mas;
        } while (mas == 's' || mas == 'S');

        tienda.realizarVenta(cliente->getId(), productos);
        std::cout << "\n\n";
        std::system("pause");
    }
};
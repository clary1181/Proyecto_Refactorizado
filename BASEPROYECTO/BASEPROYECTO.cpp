// Sistema de tienda de ropa 
// 

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <vector>
#include <iostream>
#include "SistemaTienda.h"
#include "Usuario.h"
#include "Cliente.h"
#include "Inventario.h"

#include <cstdlib>
#include <fstream> // para ifstream y ofstream
#include <sstream> // para stringstream
#include "Utilidades.h"  //Para entrada de datos 

// AQUI INCLUIMOS LO DEL PATRON COMANDO
#include "Comando.h"

using std::string;
using std::cout;
using std::endl;

// === Usuarios del sistema ===
vector<Usuario> usuarios;

const string ARCHIVO_USUARIOS = "usuarios.txt";

void cargarUsuariosDesdeArchivo()
{
    usuarios.clear();
    std::ifstream archivo(ARCHIVO_USUARIOS);
    if (!archivo) {
        std::cerr << "No se encontro archivo de usuarios, se creara uno nuevo al registrar.\n";
        return;
    }

    string linea;
    while (getline(archivo, linea)) {
        std::stringstream ss(linea);
        string nombre, clave, rolTexto;
        ss >> nombre >> clave >> rolTexto;
        RolUsuario rol = (rolTexto == "GERENTE") ? GERENTE : EMPLEADO;
        usuarios.emplace_back(nombre, clave, clave, rol);
    }
}

void guardarUsuarioEnArchivo(const Usuario& u) {
    std::ofstream archivo(ARCHIVO_USUARIOS, std::ios::app);
    if (!archivo) {
        std::cerr << "Error al abrir archivo de usuarios para escritura.\n";
        return;
    }

    archivo << u.getNombre() << " " << u.getContrasena() << " " << u.getRolComoTexto() << "\n";
}

// === Lógica de autenticación ===
static Usuario* iniciarSesion()
{
    string nombre, clave;
    cout << "Usuario: ";
    cin >> nombre;
    cout << "Contrasenia: ";
    cin >> clave;

    for (auto& u : usuarios)
    {
        if (u.getNombre() == nombre && u.autenticar(clave))
        {
            cout << "\nBienvenido, " << u.getNombre() << " (" << u.getRolComoTexto() << ")\n";
            system("pause");
            return &u;
        }
    }

    cout << "\nNombre o contrasenia incorrectos.\n";
    system("pause");
    return nullptr;
}

// === Menú Gerente Refactorizado con Comando ===
static void menuGerente(SistemaTienda& tienda)
{
    // Crear el mapa de comandos (Invocador)
    std::map<int, std::unique_ptr<Comando>> comandos;
    comandos[1] = std::make_unique<ComandoAgregarProducto>(tienda);
    comandos[2] = std::make_unique<ComandoVerInventario>(tienda);
    comandos[3] = std::make_unique<ComandoMostrarHistorialVentas>(tienda);
    comandos[4] = std::make_unique<ComandoGestionReportes>(tienda);

    int opcion;
    do {
        std::system("cls");
        std::cout << "\n--- Menu Gerente (Comando) ---\n";
        std::cout << "1. Agregar/Aumentar Stock de Producto\n";
        std::cout << "2. Ver inventario\n";
        std::cout << "3. Ver historial de ventas\n";
        std::cout << "4. Generar reportes\n";
        std::cout << "0. Cerrar Sesion\n";

        opcion = leerEntero("Opcion: ");

        if (comandos.count(opcion)) {
            // Ejecutar el Comando seleccionado
            comandos[opcion]->ejecutar();
        }
        else if (opcion != 0) {
            std::cout << "Opcion no valida.\n";
            std::system("pause");
        }
    } while (opcion != 0);
}

// === Menú Empleado Refactorizado con Comando ===
static void menuEmpleado(SistemaTienda& tienda)
{
    // Crear el mapa de comandos (Invocador)
    std::map<int, std::unique_ptr<Comando>> comandos;
    comandos[1] = std::make_unique<ComandoVerInventarioEmpleado>(tienda);
    comandos[2] = std::make_unique<ComandoRealizarVenta>(tienda);

    int opcion;
    do {
        std::system("cls");
        std::cout << "\n--- Menu Empleado (Comando) ---\n";
        std::cout << "1. Ver inventario\n";
        std::cout << "2. Realizar venta\n";
        std::cout << "0. Cerrar Sesion\n";

        opcion = leerEntero("Opcion: ");

        if (comandos.count(opcion)) {
            // Ejecutar el Comando seleccionado
            comandos[opcion]->ejecutar();
        }
        else if (opcion != 0) {
            std::cout << "Opcion invalida.\n";
            std::system("pause");
        }
    } while (opcion != 0);
}

static void crearCuenta()
{
    string nombre, clave, confirmacion;
    system("cls");
    cout << "\n------ Crear nueva cuenta ------\n";
    cout << "Nombre de usuario: ";
    cin >> nombre;

    for (const auto& u : usuarios) {
        if (u.getNombre() == nombre) {
            cout << "Ese nombre de usuario ya existe.\n";
            return;
        }
    }

    cout << "Contrasenia: ";
    cin >> clave;
    cout << "Confirmar contrasenia: ";
    cin >> confirmacion;

    if (clave != confirmacion) {
        cout << "Las contrasenias no coinciden.\n";
        return;
    }

    RolUsuario nuevoRol = EMPLEADO;
    Usuario nuevo(nombre, clave, clave, nuevoRol);
    usuarios.push_back(nuevo);
    guardarUsuarioEnArchivo(nuevo);

    cout << "Cuenta creada exitosamente. Ahora puede iniciar sesion.\n\n";
    system("pause");
}

// === Función principal ===
int main()
{
    SistemaTienda tienda;

    // Cargar usuarios desde archivo
    cargarUsuariosDesdeArchivo();

    tienda.cargarInventario();  // << cargar desde archivo
    tienda.cargarVentasDesdeArchivo();

    // Si quieres crear productos solo si el archivo no existe
    // El acceso al inventario ahora se hace a través del Singleton
    // Antes: if (tienda.inventario.inventarioVacio())
    if (Inventario::getInstance().productosVacios()) {
        tienda.agregarProductoInventario(1, "Camisa", "M", "Azul", 19.99, 4, "Camisas");
        tienda.agregarProductoInventario(2, "Pantalón", "L", "Negro", 39.99, 20, "Pantalones");
        tienda.agregarProductoInventario(3, "Chaqueta", "S", "Rojo", 59.99, 2, "Chamarras");
    }

    int opcion;
    do {
        Usuario* usuarioActual = nullptr;

        do {
            system("cls");
            cout << "\n====== Bienvenido a la Tienda de Ropa ======\n";
            cout << "1. Iniciar sesion\n";
            cout << "2. Crear cuenta\n";
            cout << "0. Salir\n";
            opcion = leerEntero("Seleccione una opcion : ");

            switch (opcion) {
            case 1:
                usuarioActual = iniciarSesion();
                break;
            case 2:
                crearCuenta();
                break;
            case 0:
                cout << "Saliendo del sistema...\n";
                return 0;
            default:
                cout << "Opcion invalida.\n";
            }
        } while (!usuarioActual && opcion != 0);

        // Si se inició sesión correctamente, se accede al menú según el rol
        if (usuarioActual) {
            if (usuarioActual->getRol() == GERENTE) {
                menuGerente(tienda);
            }
            else {
                menuEmpleado(tienda);
            }
        }

        // Al salir de un menú, se vuelve a mostrar el menú principal

    } while (true);  // Vuelve al inicio del programa tras salir de un menú
    tienda.guardarInventario();
    return 0;
}
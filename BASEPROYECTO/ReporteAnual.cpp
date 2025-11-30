#include "ReporteAnual.h"
#include <iostream>
#include <iomanip>
#include <algorithm>

using std::cout;
using std::endl;
using std::left;
using std::setw;

ReporteAnual::ReporteAnual(int anio)
    : Reporte("REPORTE ANUAL DE VENTAS"), anio(anio) {
}

void ReporteAnual::mostrarEncabezado() const {
    cout << "\n" << string(60, '=') << endl;
    cout << "    " << titulo << " - ANIO " << anio << endl;
    cout << string(60, '=') << endl;
}


//Centraliza la logica de negocio (cálculos y filtros)
// que antes estaba duplicada en generar() y escribirContenidoArchivo().
ReporteAnual::DatosAnuales ReporteAnual::calcularDatosAnuales() const {
    DatosAnuales datos;

    for (int mes = 1; mes <= 12; mes++) {
        datos.ventasPorMes[mes] = 0.0;
        datos.cantidadPorMes[mes] = 0;
    }
    
    for (const auto& venta : ventas) {
        if (venta.getAnio() == anio) {
            datos.ventasAnio.push_back(venta);
            
            int mesVenta = venta.getMes();
            double totalVenta = venta.getTotal();
            
            datos.ventasPorMes[mesVenta] += totalVenta;
            datos.cantidadPorMes[mesVenta]++;
        }
    }


 
    datos.totalAnual = calcularTotalVentas(datos.ventasAnio);
    datos.cantidadVentas = static_cast<int>(datos.ventasAnio.size());

    
    return datos;
}

void ReporteAnual::generar() const {
    mostrarEncabezado();

    DatosAnuales datos = calcularDatosAnuales();

    if (datos.ventasAnio.empty()) {
        cout << "\nNo se encontraron ventas para el anio " << anio << ".\n" << endl;
        return;
    }

    cout << "\n--- RESUMEN ANUAL ---" << endl;
    cout << "Numero total de ventas: " << datos.cantidadVentas << endl;
    cout << "Total de ingresos anuales: $" << std::fixed << std::setprecision(2) << datos.totalAnual << endl;
    cout << "Promedio mensual: $" << std::fixed << std::setprecision(2) << (datos.totalAnual / 12) << endl;

   // Ya no se llama a calcularVentasPorMes() aquí.
    map<int, double> ventasPorMes = datos.ventasPorMes;
    map<int, int> cantidadPorMes = datos.cantidadPorMes; // Usar el dato precalculado

    cout << "\n--- VENTAS POR MES ---" << endl;
    string nombresMeses[] = { "", "Enero", "Febrero", "Marzo", "Abril", "Mayo", "Junio",
                            "Julio", "Agosto", "Septiembre", "Octubre", "Noviembre", "Diciembre" };

    cout << left << setw(12) << "Mes" << setw(15) << "Total Ventas" << setw(10) << "Cantidad" << endl;
    cout << string(37, '-') << endl;

    for (int mes = 1; mes <= 12; mes++) {
        double totalMes = ventasPorMes[mes];
        int cantidadMes = cantidadPorMes[mes]; // Se usa el dato calculado, ELIMINANDO EL BUCLE DUPLICADO.

        cout << left << setw(12) << nombresMeses[mes]
            << "$" << std::fixed << std::setprecision(2) << setw(14) << totalMes
                << setw(10) << cantidadMes << endl;
    }

    // Mostrar gr�fico simple
    mostrarGraficoVentasMensuales(ventasPorMes);

    // Encontrar mejor y peor mes
    auto mejorMes = std::max_element(ventasPorMes.begin(), ventasPorMes.end(),
        [](const std::pair<int, double>& a, const std::pair<int, double>& b) {
            return a.second < b.second;
        });

    auto peorMes = std::min_element(ventasPorMes.begin(), ventasPorMes.end(),
        [](const std::pair<int, double>& a, const std::pair<int, double>& b) {
            return a.second < b.second && a.second > 0;
        });

    cout << "\n--- ANALISIS ---" << endl;
    if (mejorMes != ventasPorMes.end() && mejorMes->second > 0) {
        cout << "Mejor mes: " << nombresMeses[mejorMes->first]
            << " ($" << std::fixed << std::setprecision(2) << mejorMes->second << ")" << endl;
    }

    if (peorMes != ventasPorMes.end() && peorMes->second > 0) {
        cout << "Mes con menores ventas: " << nombresMeses[peorMes->first]
            << " ($" << std::fixed << std::setprecision(2) << peorMes->second << ")" << endl;
    }

    cout << string(60, '=') << endl;
}

void ReporteAnual::mostrarGraficoVentasMensuales(const map<int, double>& ventasPorMes) const {
    cout << "\n--- GRAFICO DE VENTAS MENSUALES ---" << endl;

    // Encontrar el valor m�ximo para escalar el gr�fico
    double maxVenta = 0;
    for (const auto& par : ventasPorMes) {
        if (par.second > maxVenta) {
            maxVenta = par.second;
        }
    }

    if (maxVenta == 0) {
        cout << "No hay datos para mostrar el grafico." << endl;
        return;
    }

    string nombresMeses[] = { "", "Ene", "Feb", "Mar", "Abr", "May", "Jun",
                            "Jul", "Ago", "Sep", "Oct", "Nov", "Dic" };

    for (int mes = 1; mes <= 12; mes++) {
        double ventaMes = ventasPorMes.at(mes);
        int barras = static_cast<int>((ventaMes / maxVenta) * 30); // Escalar a 30 caracteres m�ximo

        cout << nombresMeses[mes] << " |";
        for (int i = 0; i < barras; i++) {
            cout << " ";
        }
        cout << " $" << std::fixed << std::setprecision(0) << ventaMes << endl;
    }
}

int ReporteAnual::getAnio() const {
    return anio;
}

void ReporteAnual::setAnio(int anio) {
    this->anio = anio;
}

void ReporteAnual::escribirContenidoArchivo() const {

    DatosAnuales datos = calcularDatosAnuales();

    if (datos.ventasAnio.empty()) {
        archivoSalida << "\nNo se encontraron ventas para el a�o " << anio << ".\n";
        return;
    }

    

    archivoSalida << "\n--- RESUMEN ANUAL ---\n";
    archivoSalida << "Numero total de ventas: " << datos.cantidadVentas << "\n";
    archivoSalida << "Total de ingresos anuales: $" << std::fixed << std::setprecision(2) << datos.totalAnual << "\n";
    archivoSalida << "Promedio mensual: $" << std::fixed << std::setprecision(2) << (datos.totalAnual / 12) << "\n";

    // Usar los datos precalculados
    map<int, double> ventasPorMes = datos.ventasPorMes;
    map<int, int> cantidadPorMes = datos.cantidadPorMes;

    string nombresMeses[] = { "", "Enero", "Febrero", "Marzo", "Abril", "Mayo", "Junio",
                            "Julio", "Agosto", "Septiembre", "Octubre", "Noviembre", "Diciembre" };

    archivoSalida << "\n--- VENTAS POR MES ---\n";
    archivoSalida << std::left << std::setw(12) << "Mes" << std::setw(15) << "Total Ventas" << std::setw(10) << "Cantidad" << "\n";
    archivoSalida << std::string(37, '-') << "\n";

    for (int mes = 1; mes <= 12; mes++) {
        double totalMes = ventasPorMes[mes];
        int cantidadMes = cantidadPorMes[mes]; // Se usa el dato calculado, ELIMINANDO EL BUCLE DUPLICADO.

        archivoSalida << std::left << std::setw(12) << nombresMeses[mes]
             << "$" << std::fixed << std::setprecision(2) << std::setw(14) << totalMes
             << std::setw(10) << cantidadMes << "\n";
    }

    // Encontrar mejor y peor mes
    auto mejorMes = std::max_element(ventasPorMes.begin(), ventasPorMes.end(),
        [](const std::pair<int, double>& a, const std::pair<int, double>& b) {
            return a.second < b.second;
        });

    auto peorMes = std::min_element(ventasPorMes.begin(), ventasPorMes.end(),
        [](const std::pair<int, double>& a, const std::pair<int, double>& b) {
            return a.second < b.second && a.second > 0;
        });

    archivoSalida << "\n--- ANALISIS ---\n";
    if (mejorMes != ventasPorMes.end() && mejorMes->second > 0) {
        archivoSalida << "Mejor mes: " << nombresMeses[mejorMes->first]
            << " ($" << std::fixed << std::setprecision(2) << mejorMes->second << ")\n";
    }

    if (peorMes != ventasPorMes.end() && peorMes->second > 0) {
        archivoSalida << "Mes con menores ventas: " << nombresMeses[peorMes->first]
            << " ($" << std::fixed << std::setprecision(2) << peorMes->second << ")\n";
    }
}
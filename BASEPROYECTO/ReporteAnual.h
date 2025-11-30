#pragma once
#include "Reporte.h"
#include <map>
#include <vector>

using std::map;
using std::vector;

class ReporteAnual : public Reporte
{
private:
    int anio;

    // Estructura para agrupar todos los resultados calculados.
    struct DatosAnuales {
        vector<Venta> ventasAnio;
        double totalAnual = 0.0;
        int cantidadVentas = 0;
        map<int, double> ventasPorMes;
        map<int, int> cantidadPorMes;
        //std::vector<Venta> ventasAnio;
    };

    // Obtiene todos los datos calculados
    // haciendo que no ocupe recalcular en cada funcion
    //siendo independiente 
    DatosAnuales calcularDatosAnuales() const;


    void mostrarGraficoVentasMensuales(const map<int, double>& ventasPorMes) const;

public:
    ReporteAnual(int anio);
    void generar() const override;
    void mostrarEncabezado() const override;

    void escribirContenidoArchivo() const override;

    int getAnio() const;
    void setAnio(int anio);
};

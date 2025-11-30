#include "ReporteFactory.h"
#include "ReporteMensual.h" 
#include "ReporteAnual.h"
#include <stdexcept>
#include <iostream>

std::unique_ptr<Reporte> ReporteFactory::crearReporte(
    TipoReporte tipo,
    int parametro1,
    int parametro2)
{
    switch (tipo) {
    case MENSUAL:
        // Parametro1 es el mes, Parametro2 es el anio
        if (parametro1 < 1 || parametro1 > 12) {
            throw std::invalid_argument("Mes fuera de rango.");
        }
        return std::make_unique<ReporteMensual>(parametro1, parametro2);

    case ANUAL:
        // Parametro1 es el anio
        return std::make_unique<ReporteAnual>(parametro1);

    default:
        throw std::invalid_argument("Tipo de reporte no valido.");
    }
}
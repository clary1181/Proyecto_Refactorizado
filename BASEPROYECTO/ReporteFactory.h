#pragma once

#include <memory>
#include "Reporte.h"
#include "ReporteMensual.h"
#include "ReporteAnual.h"

// Factory que crea los objetos Reporte
class ReporteFactory {
public:
    // Enumeración para definir el tipo de reporte a crear
    enum TipoReporte {
        MENSUAL = 1,
        ANUAL = 2
    };

    // Método estático de la fábrica
    static std::unique_ptr<Reporte> crearReporte(
        TipoReporte tipo,
        int parametro1,     // Mes o Año
        int parametro2 = 0  // Solo Año (opcional)
    );
};
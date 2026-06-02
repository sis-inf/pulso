#ifndef LOADAVG_COLLECTOR_H
#define LOADAVG_COLLECTOR_H

/**
 * Estructura que almacena los promedios de carga del sistema
 * para los últimos 1, 5 y 15 minutos respectivamente.
 */
struct LoadAvgInfo {
    float load1;
    float load5;
    float load15;
};

/**
 * Lee el archivo virtual /proc/loadavg y extrae los promedios de carga.
 * @return Una estructura LoadAvgInfo poblada con las métricas del sistema.
 * @throws std::runtime_error si el archivo no puede abrirse o no existe.
 */
LoadAvgInfo getLoadAverage();

#endif // LOADAVG_COLLECTOR_H

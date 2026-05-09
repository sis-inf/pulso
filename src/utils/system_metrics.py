import os

def read_cpu_stats(proc_path="/proc/stat"):
    """
    Lee estadísticas de CPU desde /proc/stat o un archivo mock.
    
    Args:
        proc_path (str): Ruta al archivo (útil para pruebas con mocks)
    
    Returns:
        dict: Diccionario con estadísticas de CPU o None si hay error
    """
    try:
        with open(proc_path, 'r') as f:
            lines = f.readlines()
        
        for line in lines:
            if line.startswith('cpu '):
                parts = line.split()
                return {
                    'user': int(parts[1]),
                    'nice': int(parts[2]),
                    'system': int(parts[3]),
                    'idle': int(parts[4]),
                    'iowait': int(parts[5]),
                    'irq': int(parts[6]),
                    'softirq': int(parts[7]),
                    'steal': int(parts[8]),
                    'guest': int(parts[9]),
                    'guest_nice': int(parts[10])
                }
        return None
    except (IOError, OSError, IndexError, ValueError):
        return None

def calculate_cpu_usage(stat1, stat2):
    """
    Calcula el porcentaje de uso de CPU entre dos mediciones.
    
    Args:
        stat1 (dict): Primera medición
        stat2 (dict): Segunda medición
    
    Returns:
        float: Porcentaje de uso de CPU
    """
    total1 = sum(stat1.values())
    total2 = sum(stat2.values())
    
    idle1 = stat1['idle'] + stat1['iowait']
    idle2 = stat2['idle'] + stat2['iowait']
    
    total_diff = total2 - total1
    idle_diff = idle2 - idle1
    
    if total_diff == 0:
        return 0.0
    
    return 100.0 * (total_diff - idle_diff) / total_diff

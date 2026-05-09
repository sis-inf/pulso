import unittest
import os
import sys

# Agregar src al path
sys.path.insert(0, os.path.abspath(os.path.join(os.path.dirname(__file__), '../src')))

from utils.system_metrics import read_cpu_stats, calculate_cpu_usage

class TestSystemMetrics(unittest.TestCase):
    
    def test_read_cpu_stats_from_mock(self):
        """Verificar que lee correctamente el archivo mock"""
        mock_path = "tests/fixtures/proc_stat_sample"
        stats = read_cpu_stats(mock_path)
        
        self.assertIsNotNone(stats)
        self.assertEqual(stats['user'], 128825)
        self.assertEqual(stats['nice'], 84)
        self.assertEqual(stats['system'], 38633)
        self.assertEqual(stats['idle'], 1538934)
    
    def test_calculate_cpu_usage(self):
        """Verificar cálculo de porcentaje de CPU"""
        stat1 = {
            'user': 10, 'nice': 0, 'system': 5, 'idle': 85,
            'iowait': 0, 'irq': 0, 'softirq': 0, 'steal': 0,
            'guest': 0, 'guest_nice': 0
        }
        
        stat2 = {
            'user': 20, 'nice': 0, 'system': 10, 'idle': 85,
            'iowait': 0, 'irq': 0, 'softirq': 0, 'steal': 0,
            'guest': 0, 'guest_nice': 0
        }
        
        usage = calculate_cpu_usage(stat1, stat2)
        self.assertAlmostEqual(usage, 100.0, places=1)
    
    def test_read_cpu_stats_file_not_found(self):
        """Verificar que maneja archivo inexistente"""
        stats = read_cpu_stats("/ruta/inexistente/archivo")
        self.assertIsNone(stats)

if __name__ == '__main__':
    unittest.main()

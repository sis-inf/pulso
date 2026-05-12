package edu.sisinf.estante.util;

import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.*;

class ValidadorSQLTest {

    @Test
    void testSelect() {
        assertTrue(ValidadorSQL.esSelect("SELECT * FROM usuarios"));
        assertTrue(ValidadorSQL.esSelect("select * from usuarios"));
        assertTrue(ValidadorSQL.esSelect("   SELECT * FROM productos"));
    }

    @Test
    void testDML() {
        assertTrue(ValidadorSQL.esDML("INSERT INTO usuarios VALUES (1,'Juan')"));
        assertTrue(ValidadorSQL.esDML("UPDATE usuarios SET nombre='Carlos'"));
        assertTrue(ValidadorSQL.esDML("DELETE FROM usuarios"));
    }

    @Test
    void testDDL() {
        assertFalse(ValidadorSQL.esSelect("DROP TABLE usuarios"));
        assertFalse(ValidadorSQL.esDML("CREATE TABLE usuarios"));
    }

    @Test
    void testBorde() {
        assertFalse(ValidadorSQL.esSelect(""));
        assertFalse(ValidadorSQL.esSelect(null));
    }
}
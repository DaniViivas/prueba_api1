<?php
class Persona {
    private $conn;

    public $id_persona_pk;
    public $nombre;
    public $apellido;
    public $fecha_nacimiento;
    public $telefono;
    public $direccion;

    public function __construct($db) {
        $this->conn = $db;
    }

    // Leer todas las personas
    public function leer() {
        $query = "CALL sp_leer_persona()";
        $stmt = $this->conn->prepare($query);
        $stmt->execute();
        return $stmt;
    }

    // Obtener una persona por ID
    public function obtener($id) {
        $query = "CALL sp_obtener_persona(:p_id_persona_pk)";
        $stmt = $this->conn->prepare($query);
        $stmt->bindParam(':p_id_persona_pk', $id);
        $stmt->execute();
        return $stmt;
    }

    // Crear una nueva persona
    public function crear() {
        $query = "CALL sp_crear_persona(:p_nombre, :p_apellido, :p_fecha_nacimiento, :p_telefono, :p_direccion)";
        $stmt = $this->conn->prepare($query);
        $stmt->bindParam(':p_nombre', $this->nombre);
        $stmt->bindParam(':p_apellido', $this->apellido);
        $stmt->bindParam(':p_fecha_nacimiento', $this->fecha_nacimiento);
        $stmt->bindParam(':p_telefono', $this->telefono);
        $stmt->bindParam(':p_direccion', $this->direccion);

        if ($stmt->execute()) {
            return true;
        }
        return false;
    }

    // Actualizar una persona
    public function actualizar() {
        $query = "CALL sp_actualizar_persona(:p_id_persona_pk, :p_nombre, :p_apellido, :p_fecha_nacimiento, :p_telefono, :p_direccion)";
        $stmt = $this->conn->prepare($query);

        $stmt->bindParam(':p_id_persona_pk', $this->id_persona_pk);
        $stmt->bindParam(':p_nombre', $this->nombre);
        $stmt->bindParam(':p_apellido', $this->apellido);
        $stmt->bindParam(':p_fecha_nacimiento', $this->fecha_nacimiento);
        $stmt->bindParam(':p_telefono', $this->telefono);
        $stmt->bindParam(':p_direccion', $this->direccion);

        if ($stmt->execute()) {
            return true;
        }
        return false;
    }

    // Eliminar una persona
    public function eliminar($id) {
        $query = "CALL sp_eliminar_persona(:p_id_persona_pk)";
        $stmt = $this->conn->prepare($query);
        $stmt->bindParam(':p_id_persona_pk', $id);

        if ($stmt->execute()) {
            return true;
        }
        return false;
    }
}

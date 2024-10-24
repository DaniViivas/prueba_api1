<?php

class Producto {

    private $conn;

    public $id_producto_pk;
    public $nombre;
    public $descripcion;
    public $precio;

    public function __construct($db) {
        $this->conn = $db;
    }

//leer todos los productos
    public function leer() {
        $query = "CALL sp_leer_producto()";
        $stmt = $this->conn->prepare($query);
        $stmt->execute();
        return $stmt;
    }

    //obtener un producto por ID
    public function obtener($id) {
        $query = "CALL sp_obtener_producto(:p_id_producto_pk)";
        $stmt = $this->conn->prepare($query);
        $stmt->bindParam(':p_id_producto_pk', $id);
        $stmt->execute();
        return $stmt;
    }


    //crear un nuevo producto
    public function crear() {
        $query = "CALL sp_crear_producto(:p_nombre, :p_descripcion, :p_precio)";
        $stmt = $this->conn->prepare($query);
        $stmt->bindParam(':p_nombre', $this->nombre);
        $stmt->bindParam(':p_descripcion', $this->descripcion);
        $stmt->bindParam(':p_precio', $this->precio);
        if ($stmt->execute()) {
            return true;
        }
        return false;
    }

    //actualizar un producto
    public function actualizar() {
        $query = "CALL sp_actualizar_producto(:p_id_producto_pk, :p_nombre, :p_descripcion, :p_precio)";
        $stmt = $this->conn->prepare($query);
        $stmt->bindParam(':p_id_producto_pk', $this->id_producto_pk);
        $stmt->bindParam(':p_nombre', $this->nombre);
        $stmt->bindParam(':p_descripcion', $this->descripcion);
        $stmt->bindParam(':p_precio', $this->precio);
        if ($stmt->execute()) {
            return true;
        }
        return false;
    }

    //eliminar un producto
    public function eliminar($id) {
        $query = "CALL sp_eliminar_producto(:p_id_producto_pk)";
        $stmt = $this->conn->prepare($query);
        $stmt->bindParam(':p_id_producto_pk', $id);
        if ($stmt->execute()) {
            return true;
        }
        return false;
    }

}
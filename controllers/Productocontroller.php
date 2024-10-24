<?php
include_once './config/Database.php';
include_once './models/Producto.php';

Class Productocontroller {
    private $producto;

    public function __construct() {
        $database = new Database();
        $db = $database->getConnection();
        $this->producto = new Producto($db);
    }
    
// OBTENER TODOS LOS PRODUCTOS
    public function leer() {
        $stmt = $this->producto->leer();
        $productos = $stmt->fetchAll(PDO::FETCH_ASSOC);
        echo json_encode($productos);
    }   



    //OBTENER UN PRODUCTO POR ID
    public function obtener($id) {
        $stmt = $this->producto->obtener($id);
        $producto = $stmt->fetch(PDO::FETCH_ASSOC);
        echo json_encode($producto);            
    }



    // CREAR NUEVO PRODUCTO
    public function crear($data) {
        $this->producto->nombre = $data->nombre;
        $this->producto->descripcion = $data->descripcion;
        $this->producto->precio = $data->precio;
        if ($this->producto->crear()) {
            echo json_encode(["mensaje" => "Producto creado exitosamente."]);
        } else {
            echo json_encode(["mensaje" => "Error al crear el producto."]);
        }
    }

    // ACTUALIZAR PRODUCTO
    public function actualizar($data) {
        $this->producto->id_producto_pk = $data->id_producto_pk;
        $this->producto->nombre = $data->nombre;
        $this->producto->descripcion = $data->descripcion;
        $this->producto->precio = $data->precio;
        if ($this->producto->actualizar()) {
            echo json_encode(["mensaje" => "Producto actualizado exitosamente."]);
        } else {
            echo json_encode(["mensaje" => "Error al actualizar el producto."]);
        }
    }

    // ELIMINAR PRODUCTO
    public function eliminar($id) {
        if ($this->producto->eliminar($id)) {
            echo json_encode(["mensaje" => "Producto eliminado exitosamente."]);
        } else {
            echo json_encode(["mensaje" => "Error al eliminar el producto."]);
        }
    }


}   



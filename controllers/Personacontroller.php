<?php
include_once './config/Database.php';
include_once './models/Persona.php';

class PersonaController {
    private $persona;

    public function __construct() {
        $database = new Database();
        $db = $database->getConnection();
        $this->persona = new Persona($db);
    }



     // Obtener una persona por ID
     public function obtener($id) {
        $stmt = $this->persona->obtener($id);
        $persona = $stmt->fetch(PDO::FETCH_ASSOC);
        echo json_encode($persona);
    }


    // Obtener todas las personas
    public function leer() {
        $stmt = $this->persona->leer();
        $personas = $stmt->fetchAll(PDO::FETCH_ASSOC);
        echo json_encode($personas);
    }

   
    // Crear nueva persona
    public function crear($data) {
        $this->persona->nombre = $data->nombre;
        $this->persona->apellido = $data->apellido;
        $this->persona->fecha_nacimiento = $data->fecha_nacimiento;
        $this->persona->telefono = $data->telefono;
        $this->persona->direccion = $data->direccion;

        if ($this->persona->crear()) {
            echo json_encode(["mensaje" => "Persona creada exitosamente."]);
        } else {
            echo json_encode(["mensaje" => "Error al crear la persona."]);
        }
    }

    // Actualizar persona
    public function actualizar($data) {
        $this->persona->id_persona_pk = $data->id_persona_pk;
        $this->persona->nombre = $data->nombre;
        $this->persona->apellido = $data->apellido;
        $this->persona->fecha_nacimiento = $data->fecha_nacimiento;
        $this->persona->telefono = $data->telefono;
        $this->persona->direccion = $data->direccion;

        if ($this->persona->actualizar()) {
            echo json_encode(["mensaje" => "Persona actualizada exitosamente."]);
        } else {
            echo json_encode(["mensaje" => "Error al actualizar la persona."]);
        }
    }

    // Eliminar persona
    public function eliminar($id) {
        if ($this->persona->eliminar($id)) {
            echo json_encode(["mensaje" => "Persona eliminada exitosamente."]);
        } else {
            echo json_encode(["mensaje" => "Error al eliminar la persona."]);
        }
    }
}
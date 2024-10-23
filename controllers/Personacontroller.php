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

    // Obtener todas las personas
    public function obtenerPersonas() {
        $stmt = $this->persona->leerPersonas();
        $personas = $stmt->fetchAll(PDO::FETCH_ASSOC);
        echo json_encode($personas);
    }

    // Obtener una persona por ID
    public function obtenerPersona($id) {
        $stmt = $this->persona->obtenerPersona($id);
        $persona = $stmt->fetch(PDO::FETCH_ASSOC);
        echo json_encode($persona);
    }

    // Crear nueva persona
    public function crearPersona($data) {
        $this->persona->nombre = $data->nombre;
        $this->persona->apellido = $data->apellido;
        $this->persona->fecha_nacimiento = $data->fecha_nacimiento;
        $this->persona->telefono = $data->telefono;
        $this->persona->direccion = $data->direccion;

        if ($this->persona->crearPersona()) {
            echo json_encode(["mensaje" => "Persona creada exitosamente."]);
        } else {
            echo json_encode(["mensaje" => "Error al crear la persona."]);
        }
    }

    // Actualizar persona
    public function actualizarPersona($data) {
        $this->persona->id_persona_pk = $data->id_persona_pk;
        $this->persona->nombre = $data->nombre;
        $this->persona->apellido = $data->apellido;
        $this->persona->fecha_nacimiento = $data->fecha_nacimiento;
        $this->persona->telefono = $data->telefono;
        $this->persona->direccion = $data->direccion;

        if ($this->persona->actualizarPersona()) {
            echo json_encode(["mensaje" => "Persona actualizada exitosamente."]);
        } else {
            echo json_encode(["mensaje" => "Error al actualizar la persona."]);
        }
    }

    // Eliminar persona
    public function eliminarPersona($id) {
        if ($this->persona->eliminarPersona($id)) {
            echo json_encode(["mensaje" => "Persona eliminada exitosamente."]);
        } else {
            echo json_encode(["mensaje" => "Error al eliminar la persona."]);
        }
    }
}
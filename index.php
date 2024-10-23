<?php
header("Access-Control-Allow-Origin: *");
header("Content-Type: application/json");

include_once 'controllers/Personacontroller.php';

$controller = new PersonaController();
$method = $_SERVER['REQUEST_METHOD'];

switch ($method) {
    case 'GET':
        if (isset($_GET['id'])) {
            $controller->obtenerPersona($_GET['id']);
        } else {
            $controller->obtenerPersonas();
        }
        break;

    case 'POST':
        $data = json_decode(file_get_contents("php://input"));
        $controller->crearPersona($data);
        break;

    case 'PUT':
        $data = json_decode(file_get_contents("php://input"));
        $controller->actualizarPersona($data);
        break;

    case 'DELETE':
        if (isset($_GET['id'])) {
            $controller->eliminarPersona($_GET['id']);
        }
        break;

    default:
        http_response_code(405); // Código de respuesta para método no permitido
        echo json_encode(["mensaje" => "Método no soportado"]);
        break;
}


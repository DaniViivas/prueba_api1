<?php
header("Access-Control-Allow-Origin: *");
header("Content-Type: application/json");

include_once 'controllers/Personacontroller.php';
include_once 'controllers/Productocontroller.php';

// Obtener la entidad desde la URL (por ejemplo: 'personas' o 'productos')
$uri = explode('/', parse_url($_SERVER['REQUEST_URI'], PHP_URL_PATH));
$resource = isset($uri[3]) ? $uri[3] : null; // Index  asume que tienes algo como /prueba_api1/index.php/{entidad}

// Obtener el método HTTP (GET, POST, PUT, DELETE)
$method = $_SERVER['REQUEST_METHOD'];

if ($resource === 'personas') {
    $controller = new PersonaController();
} elseif ($resource === 'productos') {
    $controller = new ProductoController();
} else {
    http_response_code(404); // Código de respuesta para recurso no encontrado
    echo json_encode(["mensaje" => "Recurso no encontrado"]);
    exit;
}

// Manejar la solicitud según el método HTTP
switch ($method) {
    case 'GET': 
        if (isset($_GET['id'])) {
            $controller->obtener($_GET['id']);
        } else {
            $controller->leer();
        }
            
        break;

    case 'POST':
        $data = json_decode(file_get_contents("php://input"));
        $controller->crear($data);
        break;

    case 'PUT':
        $data = json_decode(file_get_contents("php://input"));
        $controller->actualizar($data);
        break;

    case 'DELETE':
        if (isset($_GET['id'])) {
            $controller->eliminar($_GET['id']);
        }
        break;

    default:
        http_response_code(405); // Método no permitido
        echo json_encode(["mensaje" => "Método no soportado"]);
        break;
}
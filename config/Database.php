<?php
Class Database { 
    private $host = "localhost";
    private $user = "root";
    private $password = "";
    private $database = "prueba_api";
    private $conn;

public function getConnection() {
    
    $this->conn = null;
    try {
        $this->conn = new PDO("mysql:host=" . $this->host . ";dbname=" . $this->database, $this->user, $this->password);
        $this->conn->exec("set names utf8");
    } catch(PDOException $exception) {
        echo "ERROR DE CONEXION: " . $exception->getMessage();
    }
    return $this->conn;
}  

}        
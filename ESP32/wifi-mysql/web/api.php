<?php

// Servidor SQL, nombre bd, usuario y contraseña
$servername = "localhost";
$dbname = "esp_bd";
$username = "tu_usuario";
$password = "tu_contraseña";

// Si cambia el valor de apiKeyValue, el archivo INO también debe tener la misma clave
$api_key_value = "mNpsDHYQjaDmTzknzPc";

$api_key= $sensor = $value1 = "";

if ($_SERVER["REQUEST_METHOD"] == "POST") {
    $api_key = test_input($_POST["api_key"]);
    if($api_key == $api_key_value) {
        $sensor = test_input($_POST["sensor"]);
        $value1 = test_input($_POST["value1"]);
        
        // Conexión a la bd
        $conn = new mysqli($servername, $username, $password, $dbname);

        if ($conn->connect_error) {
            die("La conexión falló: " . $conn->connect_error);
        } 
        
        $sql = "INSERT INTO sensordata (sensor, value1) VALUES ('" . $sensor . "', '" . $value1 . "')";
        
        if ($conn->query($sql) === TRUE) {
            echo "Nuevo registro creado correctamente.";
        } 
        else {
            echo "Error: " . $sql . "<br>" . $conn->error;
        }
    
        $conn->close();
    }
    else {
        echo "Clave API incorrecta.";
    }

}
else {
    echo "No se ha realizado la HTTP POST.";
}

function test_input($data) {
    $data = trim($data);
    $data = stripslashes($data);
    $data = htmlspecialchars($data);
    return $data;
}
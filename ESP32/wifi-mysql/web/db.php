<!DOCTYPE html>
<html><body>
<?php

// Servidor SQL, nombre bd, usuario y contraseña
$servername = "localhost";
$dbname = "esp_bd";
$username = "tu_usuario";
$password = "tu_contraseña";

$conn = new mysqli($servername, $username, $password, $dbname);

if ($conn->connect_error) {
    die("La conexión falló: " . $conn->connect_error);
} 

$sql = "SELECT id, sensor, value1, reading_time FROM sensordata ORDER BY id DESC";

echo '<table cellspacing="4" cellpadding="4">
      <tr> 
        <td>ID</td> 
        <td>Sensor</td> 
        <td>Value 1</td> 
        <td>Timestamp</td> 
      </tr>';
 
if ($result = $conn->query($sql)) {
    while ($row = $result->fetch_assoc()) {
        $row_id = $row["id"];
        $row_sensor = $row["sensor"];
        $row_value1 = $row["value1"];
        $row_reading_time = $row["reading_time"];
      
        echo '<tr> 
                <td>' . $row_id . '</td> 
                <td>' . $row_sensor . '</td> 
                <td>' . $row_value1 . '</td> 
                <td>' . $row_reading_time . '</td> 
              </tr>';
    }
    $result->free();
}

$conn->close();
?> 
</table>
</body>
</html>
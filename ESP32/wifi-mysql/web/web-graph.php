<!DOCTYPE html>
<html>
<head>
    <title>Gráfico del sensor</title>
    <script src="https://cdn.jsdelivr.net/npm/chart.js"></script> 
    <script src="https://cdn.jsdelivr.net/npm/chartjs-adapter-date-fns"></script> 
</head>
<body>
    <canvas id="sensorChart" width="400" height="200"></canvas>

    <?php
    // Servidor SQL, nombre bd, usuario y contraseña
    $servername = "localhost";
    $dbname = "esp_bd";
    $username = "tu_usuario";
    $password = "tu_contraseña";

    $conn = new mysqli($servername, $username, $password, $dbname);

    if ($conn->connect_error) {
        die("Connection failed: " . $conn->connect_error);
    }

    $sql = "SELECT sensor, value1, reading_time FROM sensordata ORDER BY reading_time ASC";
    $labels = [];
    $data = [];

    if ($result = $conn->query($sql)) {
        while ($row = $result->fetch_assoc()) {
            $labels[] = date('c', strtotime($row["reading_time"])); 
            $data[] = $row["value1"]; 
        }
        $result->free();
    }

    $conn->close();
    ?>

    <script>
        var labels = <?php echo json_encode($labels); ?>;
        var data = <?php echo json_encode($data); ?>;

        var ctx = document.getElementById('sensorChart').getContext('2d');
        var sensorChart = new Chart(ctx, {
            type: 'line',
            data: {
                labels: labels,
                datasets: [{
                    label: 'Valor del Sensor',
                    data: data,
                    borderColor: 'rgba(75, 192, 192, 1)',
                    backgroundColor: 'rgba(75, 192, 192, 0.2)',
                    borderWidth: 1
                }]
            },
            options: {
                responsive: true,
                scales: {
                    x: {
                        type: 'timeseries',
                        time: {
                            unit: 'minute'
                        },
                        title: {
                            display: true,
                            text: 'Fecha y Hora'
                        }
                    },
                    y: {
                        title: {
                            display: true,
                            text: 'Valor'
                        }
                    }
                }
            }
        });
    </script>
</body>
</html>

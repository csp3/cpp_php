<?php

$host = "localhost";
$user = "root";
$pass = ""; 
$bd = "dbdas"; 
$conexion = new mysqli($host, $user, $pass, $bd);

if($conexion->connect_error)
{
	$conexion->close(); 
	return json_encode("error conectando"); 
}

$methodHTTP = $_SERVER['REQUEST_METHOD'];

$id = $_POST['ide'];

$consulta = sprintf("SELECT * FROM empleados WHERE id='%s' and estado=1 ", mysqli_real_escape_string($conexion,$id));
$resultado = $conexion->query($consulta); 
if(!$resultado)
{
	$conexion->close(); 
    echo json_encode("error-consulta");
}
else
{
	if ($resultado->num_rows > 0) 
	{
		$data = array();
		while ($row = mysqli_fetch_array($resultado)) 
		{
    			$data[] = $row;
  		}
			
		echo json_encode($data);
	}
	else 
		echo json_encode("datos-no-encontrados");
}

            

/*
$n1 = $_POST['n1']; 
$n2 = $_POST['n2'];

echo "--> ";
echo $n1 + $n2;
*/
?>
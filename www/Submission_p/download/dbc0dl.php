<?php
include('../connect.php');

$id = $_GET["id"];

$func = "SELECT C0, C0size FROM DAQ_p WHERE assoc_module=\"$id\"";

mysql_query('USE cmsfpix_u', $connection);

$file = mysql_query($func, $connection);

	    header ("Content-Type: image/gif");

echo mysql_result($file, 0, 'C0');

mysql_free_result($file);
?>

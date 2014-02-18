<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01//EN" "http://www.w3.org/TR/html4/strict.dtd">
<html>
<head>
  <meta content="text/html; charset=ISO-8859-1"
 http-equiv="content-type">
  <title>Assembly</title>
</head>
<body>

<form method="link" action="../index.html">
<input type="submit" value="MAIN MENU">
</form>

<br>

<form method="link" action="../assembly/status.php">
<input type="submit" value="BACK">
</form>

<br>

<?php
ini_set('display_errors', 'On');
error_reporting(E_ALL | E_STRICT);
include('../functions/popfunctions.php');
include('../connect.php');

$part = $_GET['part'];
$sl = $_GET['sl'];
$part = $part."_p";

$func = "SELECT name, id from ".$part." WHERE assembly=".$sl." ORDER BY name";

if($part == "wafer_p"){
	$steparray = array("Received", "Inspected", "Tested", "Promoted", "Ready for Shipping", "Shipped");
	$page = "wafer.php";
}
elseif($part == "module_p"){
	$steparray = array("Expected", "Received", "Inspected", "IV Tested", "Ready for HDI Assembly", "HDI Attached", "Wirebonded", "Encapsulated", "Tested", "Thermal Cycling", "Tested", "Ready for Shipping", "Shipped");
	$page = "bbm.php"; 
}
elseif($part == "HDI_p"){
	$steparray = array("Received", "Inspected", "Ready for Assembly", "On Module");
	$page = "hdi.php"; 
}

$num=count($steparray);

$i=0;

mysql_query('USE cmsfpix_u', $connection);

$output = mysql_query($func, $connection);

echo "<table cellspacing=10 border=2>";
echo "<tr valign=top>";
echo "<td valign=top>";
echo $steparray[$sl];
echo "</td>";
echo "</tr>";

while($row = mysql_fetch_assoc($output)){
	echo "<tr valign=top>";
	echo "<td valign=top>";
	echo "<a href=".$page."?id=".$row['id'].">".$row['name']."</a>";
	echo "</td>";
	echo "</tr>";
}

echo "</table>";
?>

<br>

<form method="link" action="../assembly/status.php">
<input type="submit" value="BACK">
</form>

<br>

<form method="link" action="../index.html">
<input type="submit" value="MAIN MENU">
</form>

</body>
</html>

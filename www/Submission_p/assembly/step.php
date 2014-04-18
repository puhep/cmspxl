<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01//EN" "http://www.w3.org/TR/html4/strict.dtd">
<html>
<head>
  <meta content="text/html; charset=ISO-8859-1"
 http-equiv="content-type">
  <title>Assembly</title>
</head>
<body>

<form method="link" action="../index.php">
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

$prepart = $_GET['part'];
$sl = $_GET['sl'];
$part = $prepart."_p";

$sortby = $_GET['sort'];

$order = "name";
if($sortby == "ar"){
	$order = "arrival";
}
if($sortby == "sh" && $part == "module_p" && $sl == 12){
	$order = "shipped";
}

$func = "SELECT name, id, arrival, shipped from ".$part." WHERE assembly=".$sl." ORDER BY ".$order." DESC";

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
echo "<a href=step.php?sort=na&part=".$prepart."&sl=".$sl.">".$steparray[$sl]."</a>";
echo "</td>";

if($part=="module_p" && $sl==12){
echo "<td valign=top>";
echo "<a href=step.php?sort=sh&part=".$prepart."&sl=".$sl.">Ship Date</a>";
echo "</td>";

echo "<td valign=top>";
#echo "<a href=step.php?sort=sh&part=".$prepart."&sl=".$sl.">Destination</a>";
echo "Destination";
echo "</td>";
}

echo "</tr>";

while($row = mysql_fetch_assoc($output)){
	echo "<tr valign=top>";

	echo "<td valign=top>";
	echo "<a href=../summary/".$page."?id=".$row['id'].">".$row['name']."</a>";
	echo "</td>";

	if($part=="module_p" && $sl==12){

	$modfunc = "SELECT destination FROM module_p WHERE id=".$row['id'];
	$modout = mysql_query($modfunc, $connection);
	$modrow = mysql_fetch_assoc($modout);

	echo "<td valign=top>";
	echo $row['shipped'];
	echo "</td>";

	echo "<td valign=top>";
	echo $modrow['destination'];
	echo "</td>";
	}
	
	#else{
	#echo "<td valign=top>";
	#echo "<a href=".$page."?id=".$row['id'].">".$row['name']."</a>";
	#echo "</td>";
	#}

	echo "</tr>";
}

echo "</table>";
?>

<br>

<form method="link" action="../assembly/status.php">
<input type="submit" value="BACK">
</form>

<br>

<form method="link" action="../index.php">
<input type="submit" value="MAIN MENU">
</form>

</body>
</html>

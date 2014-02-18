<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01//EN" "http://www.w3.org/TR/html4/strict.dtd">
<html>
<head>
  <meta content="text/html; charset=ISO-8859-1"
 http-equiv="content-type">
  <title>Module Assembly Flow</title>
</head>
<body>
<form method="post" enctype="multipart/form-data">
<?php

ini_set('display_error', 'On');
error_reporting(E_ALL | E_STRICT);

include('../connect.php');
include('../functions/editfunctions.php');
include('../functions/curfunctions.php');
include('../functions/popfunctions.php');
include('../functions/submitfunctions.php');


mysql_query('USE cmsfpix_u', $connection);

$id = $_GET['id'];
echo "<input type='hidden' name='id' value='".$_GET['id']."'>";

$search = "SELECT name, assembly FROM module_p WHERE id=$id";
$table = mysql_query($search, $connection);
$row = mysql_fetch_assoc($table);
$assembly = $row['assembly'];
curname("module_p", $id);


$steparray = array("Received", "Inspected", "IV Tested", "Ready for HDI Assembly", "HDI Attached", "Wirebonded", "Encapsulated", "Tested", "Thermal Cycling", "Tested", "Ready for Shipping", "Shipped");

if(isset($_POST['submit']) && isset($_POST['box']) && $_POST['who'] != "" && (!is_null($_POST['hdi']) || $assembly!=4)){
	$submittedstep = $steparray[$assembly]." by ".$_POST['who'];
	if($_POST['notes']!=""){
		$submittednotes = $_POST['notes'];
	}
	addcomment("module_p", $id, $submittedstep);
	addcomment("module_p", $id, $submittednotes);
	$assembly++;
	$funcassembly = "UPDATE module_p SET assembly=$assembly WHERE id=$id";
	mysql_query($funcassembly, $connection);
	
	if($assembly==5){
		$hdi = $_POST['hdi'];
		$newname = "M".substr($row['name'], 2);
		$funchdi = "UPDATE HDI_p SET module=$id WHERE id=$hdi";
		$funchdi2 = "UPDATE HDI_p SET assembly=3 WHERE id=$hdi";
		$funcmod = "UPDATE module_p SET assoc_HDI=$hdi WHERE id=$id";
		$funcmod2 = "UPDATE module_p SET name=\"$newname\" WHERE id=$id";
		mysql_query($funchdi, $connection);
		mysql_query($funchdi2, $connection);
		mysql_query($funcmod, $connection);
		mysql_query($funcmod2, $connection);
	}
}

$checker = " CHECKED ";

if($assembly == 0){
	echo"Received   <input name=\"box\" value=\"rec\" type=\"checkbox\">";
	echo"User: <input name=\"who\" type=\"text\">   ";
	echo"Comments: <input name=\"notes\" type=\"text\">   ";
	$checker = "";
}
else{
	echo"Received   <input name=\"box\" value=\"rec\"
 	type=\"checkbox\"".$checker."DISABLED>";
}

echo"<br>";

if($assembly == 1){
	echo"Inspected   <input name=\"box\" value=\"inspect\" type=\"checkbox\">";
	echo"User: <input name=\"who\" type=\"text\">   ";
	echo"Comments: <input name=\"notes\" type=\"text\">   ";
	$checker = "";
}
else{
	echo"Inspected   <input name=\"box\" value=\"inspect\"
 	type=\"checkbox\"".$checker."DISABLED>";
}

echo"<br>";

if($assembly == 2){
	echo"IV Tested   <input name=\"box\" value=\"iv\" type=\"checkbox\">";
	echo"User: <input name=\"who\" type=\"text\">   ";
	echo"Comments: <input name=\"notes\" type=\"text\">   ";
	$checker = "";
}
else{
	echo"IV Tested   <input name=\"box\" value=\"iv\"
 	type=\"checkbox\"".$checker."DISABLED>";
}

echo"<br>";

if($assembly == 3){
	echo"Ready for HDI Assembly   <input name=\"box\" value=\"HDIready\" type=\"checkbox\">";
	echo"User: <input name=\"who\" type=\"text\">   ";
	echo"Comments: <input name=\"notes\" type=\"text\">   ";
	$checker = "";
}
else{
	echo"Ready for HDI Assembly   <input name=\"box\" value=\"HDIready\"
 	type=\"checkbox\"".$checker."DISABLED>";
}

echo"<br>";

if($assembly == 4){
	echo"HDI Attached   <input name=\"box\" value=\"hdi\" type=\"checkbox\">";
	echo"HDI: <select name=\"hdi\">";
	availhdi();
	echo"</select>";
	echo"User: <input name=\"who\" type=\"text\">   ";
	echo"Comments: <input name=\"notes\" type=\"text\">   ";
	$checker = "";
}
else{
	echo"HDI Attached   <input name=\"box\" value=\"hdi\"
 	type=\"checkbox\"".$checker."DISABLED>";
}

echo"<br>";

if($assembly == 5){
	echo"Wirebonded   <input name=\"box\" value=\"wb\" type=\"checkbox\">";
	echo"User: <input name=\"who\" type=\"text\">   ";
	echo"Comments: <input name=\"notes\" type=\"text\">   ";
	$checker = "";
}
else{
	echo"Wirebonded   <input name=\"box\" value=\"wb\"
 	type=\"checkbox\"".$checker."DISABLED>";
}

echo"<br>";

if($assembly == 6){
	echo"Encapsulated   <input name=\"box\" value=\"encapsulate\" type=\"checkbox\">";
	echo"User: <input name=\"who\" type=\"text\">   ";
	echo"Comments: <input name=\"notes\" type=\"text\">   ";
	$checker = "";
}
else{
	echo"Encapsulated   <input name=\"box\" value=\"encapsulate\"
 	type=\"checkbox\"".$checker."DISABLED>";
}

echo"<br>";

if($assembly == 7){
	echo"Tested    <input name=\"box\" value=\"test4\" type=\"checkbox\" DISABLED>";
	$checker = "";
}
else{
	echo"Tested    <input name=\"box\" value=\"test4\"
 	type=\"checkbox\"".$checker."DISABLED>";
}

echo"<br>";

If($assembly == 8){
	echo"Thermal Cycling    <input name=\"box\" value=\"thermal\" type=\"checkbox\">";
	echo"User: <input name=\"who\" type=\"text\">   ";
	echo"Comments: <input name=\"notes\" type=\"text\">   ";
	$checker = "";
}
else{
	echo"Thermal Cycling    <input name=\"box\" value=\"thermal\"
 	type=\"checkbox\"".$checker."DISABLED>";
}

echo"<br>";

if($assembly == 9){
	echo"Tested    <input name=\"box\" value=\"tst\" type=\"checkbox\">";
	echo"User: <input name=\"who\" type=\"text\">   ";
	echo"Comments: <input name=\"notes\" type=\"text\">   ";
	$checker = "";
}
else{
	echo"Tested    <input name=\"box\" value=\"tst\"
 	type=\"checkbox\"".$checker."DISABLED>";
}

echo"<br>";

if($assembly == 10){
	echo"Ready for Shipping    <input name=\"box\" value=\"ready\" type=\"checkbox\">";
	echo"User: <input name=\"who\" type=\"text\">   ";
	echo"Comments: <input name=\"notes\" type=\"text\">   ";
	$checker = "";
}
else{
	echo"Ready for Shipping    <input name=\"box\" value=\"ready\"
 	type=\"checkbox\"".$checker."DISABLED>";
}

echo"<br>";

if($assembly == 11){
	echo"Shipped    <input name=\"box\" value=\"ship\" type=\"checkbox\">";
	echo"User: <input name=\"who\" type=\"text\">   ";
	echo"Comments: <input name=\"notes\" type=\"text\">   ";
	$checker = "";
}
else{
	echo"Shipped    <input name=\"box\" value=\"ship\"
 	type=\"checkbox\"".$checker."DISABLED>";
}

echo"<br>";

if($assembly > 11){
	echo "END MESSAGE FOR THIS PART";
}

echo"<br>";

conditionalSubmit();

?>
</form>

<br>

<form method="post" action="assemblypic.php">
<?php
   echo "<input type='hidden' name='part' value='module_p'>";
   echo "<input type='hidden' name='id' value='".$id."'>";
?>
<input type="submit" value="Add a Picture">
</form>

<br>

<form method="get" action="../summary/bbm.php">
<?php
   echo "<input type='hidden' name='id' value='".$id."'>";
?>
<input type="submit" value="Part Summary">
</form>

<br>

<form method="link" action="status.php">
<input type="submit" value="Assembly Status">
</form>

<br>

<form method="link" action="../index.html">
<input type="submit" value="MAIN MENU">
</form>
</body>
</html>

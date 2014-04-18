<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01//EN" "http://www.w3.org/TR/html4/strict.dtd">
<html>
<head>
  <meta content="text/html; charset=ISO-8859-1"
 http-equiv="content-type">
  <title>HDI Assembly Flow</title>
</head>
<body>
<form method="post" enctype="multipart/form-data">
<?php

ini_set('display_error', 'On');
error_reporting(E_ALL | E_STRICT);

include('../connect.php');
include('../functions/editfunctions.php');
include('../functions/curfunctions.php');
include('../functions/submitfunctions.php');

mysql_query('USE cmsfpix_u', $connection);

$id = $_GET['id'];
echo "<input type='hidden' name='id' value='".$_GET['id']."'>";

$search = "SELECT assembly FROM HDI_p WHERE id=$id";
$table = mysql_query($search, $connection);
$row = mysql_fetch_assoc($table);
$assembly = $row['assembly'];

curname("HDI_p", $id);


$steparray = array("Inspected", "Ready for Assembly", "On Module");


if(isset($_POST['submit']) && isset($_POST['box']) && $_POST['who'] != ""){
	$submittedstep = $steparray[$assembly]." by ".$_POST['who'];
	if($_POST['notes']!=""){
		$submittednotes = $_POST['notes'];
	}
	addcomment("HDI_p", $id, $submittedstep);
	addcomment("HDI_p", $id, $submittednotes);
	$assembly++;
	if($_POST['box'] == "reject"){
		$assembly *= -1;
	}
	$funcassembly = "UPDATE HDI_p SET assembly=$assembly WHERE id=$id";
	mysql_query($funcassembly, $connection);
}

$checker = " CHECKED ";
$rework = "";
if($assembly < 0){
	$rework = " DISABLED ";
}

if($assembly == 0){
	echo"Inspected   <input name=\"box\" value=\"inspect\" type=\"checkbox\"".$rework.">";
	echo"User: <input name=\"who\" type=\"text\"".$rework.">   ";
	echo"Comments: <input name=\"notes\" type=\"text\">   ";
	$checker = "";
}
else{
	echo"Inspected   <input name=\"box\" value=\"inspect\"
 	type=\"checkbox\"".$checker."DISABLED>";
}

echo"<br>";

if($assembly == 1){
	echo"Ready for Assembly   <input name=\"box\" value=\"ready\" type=\"checkbox\">";
	echo"OR   Reject   <input name=\"box\" value=\"reject\" type=\"checkbox\">";
	echo"<br>";
	echo"User: <input name=\"who\" type=\"text\">   ";
	echo"Comments: <input name=\"notes\" type=\"text\">   ";
	$checker = "";
}
else{
	if($assembly > 0){
		$readychecker = " CHECKED ";
		$rejectchecker = "";
	}
	else{
		$readychecker = "";
		$rejectchecker = " CHECKED ";
		$checker = "";
	}
	echo"Ready for Assembly   <input name=\"box\" value=\"ready\"
 	type=\"checkbox\"".$readychecker."DISABLED>";

	echo"Reject   <input name=\"box\" value=\"reject\"
 	type=\"checkbox\"".$rejectchecker."DISABLED>";
}

echo"<br>";

if($assembly == 2){
	echo"On Module   <input name=\"box\" value=\"on\" type=\"checkbox\" DISABLED>";
	echo"Attached to $mod";
	$checker = "";
}
else{
	echo"On Module   <input name=\"box\" value=\"on\"
 	type=\"checkbox\"".$checker."DISABLED>";
}

echo"<br>";

if($assembly > 2){
	echo "Attached to ";
	curmod($id, "HDI_p");
}

if($assembly < 0){
	echo "HDI rejected";
}

echo"<br>";
echo"<br>";

conditionalSubmit();

?>
</form>

<br>

<form method="post" action="assemblypic.php">
<?php
   echo "<input type='hidden' name='part' value='HDI_p'>";
   echo "<input type='hidden' name='id' value='".$id."'>";
?>
<input type="submit" value="Add a Picture">
</form>

<br>

<form method="get" action="../summary/hdi.php">
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

<form method="link" action="../index.php">
<input type="submit" value="MAIN MENU">
</form>
</body>
</html>

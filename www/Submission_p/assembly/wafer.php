<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01//EN" "http://www.w3.org/TR/html4/strict.dtd">
<html>
<head>
  <meta content="text/html; charset=ISO-8859-1"
 http-equiv="content-type">
  <title>Wafer Assembly Flow</title>
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

$search = "SELECT assembly,name FROM wafer_p WHERE id=$id";
$table = mysql_query($search, $connection);
$row = mysql_fetch_assoc($table);
$assembly = $row['assembly'];

curname("wafer_p", $id);

$steparray = array("Inspected", "Tested", "Promoted", "Ready for Shipping", "Shipped");


if(isset($_POST['submit']) && isset($_POST['box']) && $_POST['who'] != ""){
	$submittedstep = $steparray[$assembly]." by ".$_POST['who'];
	if($_POST['notes']!=""){
		$submittednotes =$_POST['notes'];
	}

	addcomment("wafer_p", $id, $submittedstep);
	addcomment("wafer_p", $id, $submittednotes);

	$assembly++;
	$funcassembly = "UPDATE wafer_p SET assembly=$assembly WHERE id=$id";
	mysql_query($funcassembly, $connection);
	if($assembly == 3){
		if(!empty($_POST[sens])){
			foreach($_POST[sens] as $promotedid){
				sensorSetPromote($promotedid);
			}
		}

	}
	if($assembly == 5){
		promoteSensors($id);
	}
}

$checker = " CHECKED ";
$rework = "";
#if($assembly < 0){
	#$rework = " DISABLED ";
#}

if($assembly == 0){
	echo"Inspected   <input name=\"box\" value=\"insp\" type=\"checkbox\"".$rework.">";
	echo"User: <input name=\"who\" type=\"text\"".$rework.">   ";
	echo"Comments: <input name=\"notes\" type=\"text\"".$rework.">   ";
	$checker = "";
}  
else{
	echo"Inspected   <input name=\"box\" value=\"insp\"
 	type=\"checkbox\"".$checker."DISABLED>";
}

echo"<br>";

if($assembly == 1){
	echo"Tested   <input name=\"box\" value=\"test\" type=\"checkbox\" DISABLED>";
	
	$checker = "";
	isTestedWaferDisp($id);
}
else{
	echo"Tested   <input name=\"box\" value=\"test\"
 	type=\"checkbox\"".$checker."DISABLED>";
}

echo"<br>";

if($assembly == 2){
	echo"Promoted   <input name=\"box\" value=\"promote\" type=\"checkbox\"".$rework.">";
	echo"User: <input name=\"who\" type=\"text\"".$rework.">   ";
	echo"Comments: <input name=\"notes\" type=\"text\"".$rework.">   ";
	$checker = "";
	promoteBoxes($id);
}
else{
	echo"Promoted   <input name=\"box\" value=\"promote\"
 	type=\"checkbox\"".$checker."DISABLED>";
}

echo"<br>";

if($assembly == 3){
	echo"Ready for Shipping   <input name=\"box\" value=\"ready\" type=\"checkbox\"".$rework.">";
	echo"User: <input name=\"who\" type=\"text\"".$rework.">   ";
	echo"Comments: <input name=\"notes\" type=\"text\"".$rework.">   ";
	$checker = "";
}
else{
	echo"Ready for Shipping   <input name=\"box\" value=\"ready\"
 	type=\"checkbox\"".$checker."DISABLED>";
}

echo"<br>";

if($assembly == 4){
	echo"Shipped   <input name=\"box\" value=\"ship\" type=\"checkbox\"".$rework.">";
	echo"User: <input name=\"who\" type=\"text\"".$rework.">   ";
	echo"Comments: <input name=\"notes\" type=\"text\"".$rework.">   ";
	$checker = "";
}
else{
	echo"Shipped   <input name=\"box\" value=\"ship\"
 	type=\"checkbox\"".$checker."DISABLED>";
}

echo"<br>";

if($assembly > 4){
	echo "Wafer fully tested and shipped";
}
#else{
	#echo"Rework   <input name=\"box\" value=\"rework\" type=\"checkbox\">";
	#echo"Comments: <input name=\"notes\" type=\"text\">   ";
#}

echo"<br>";

conditionalSubmit();

?>
</form>

<br>

<form method="post" action="assemblypic.php">
<?php
   echo "<input type='hidden' name='part' value='wafer_p'>";
   echo "<input type='hidden' name='id' value='".$id."'>";
?>
<input type="submit" value="Add a Picture">
</form>

<br>

<form method="get" action="../summary/wafer.php">
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

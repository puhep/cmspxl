<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01//EN" "http://www.w3.org/TR/html4/strict.dtd">
<html>
<head>
  <meta content="text/html; charset=ISO-8859-1"
 http-equiv="content-type">
  <title>Measurement Submission</title>
</head>
<body>
<form action='meassubmit.php' method='post' enctype='multipart/form-data'>
<?php
include('../functions/submitfunctions.php');
include('../functions/popfunctions.php');
include('../functions/curfunctions.php');
if(!isset($_POST['wafers'])){
?>
Available Wafers
<select name="wafers">
<?php
waferpop();
?>
</select>

<?php
}
else{
?>

Available Sensors
<select name="sensors">
<?php
sensorpop($_POST['wafers']);
?>
</select>

<br>
<br>

Scan Type: <input name="scan" value="IV" type="radio">IV
&nbsp; &nbsp; <input name="scan" value="CV"
 type="radio">CV<br>
<br>
Scan Level: &nbsp;<input name="level" value="wafer" type="radio"> On Wafer
 &nbsp; &nbsp; 
 <input name="level" value="module" type="radio"> Bare Module
 &nbsp; &nbsp; 
 <input name="level" value="assembled" type="radio"> Fully-Assembled Module
<br>
<br>
XML file:
<input name="xml" type="file">
<?php
echo "<input type='hidden' name='wafers' value='".$_POST['wafers']."'>";
?>
<br>
<br>
Additional Notes <textarea cols="40" rows="5" name="notes"></textarea>
<?php
}
?>

<br>
<br>

<?php

conditionalSubmit();

if(isset($_POST['submit']) &&  $_FILES['xml']['size'] > 0 && isset($_POST['level']) && isset($_POST['scan'])){
	
	$fp = fopen($_FILES['xml']['tmp_name'],'r');
	$content = fread($fp,filesize($_FILES['xml']['tmp_name']));
	$content = addslashes($content);
	fclose($fp);
 
	measurement($_POST['sensors'],$_POST['level'],$_POST['scan'],$_POST['notes'],$content,$_FILES['xml']['size'], $_FILES['xml']['name']);
}
	if($_POST['level'] == "wafer"){
		isTestedWaferUpdate($_POST['wafers']);
	}
?>
</form>

<br>

<form method="link" action="../index.php">
<input type="submit" value="MAIN MENU">
</form>

</body>
</html>

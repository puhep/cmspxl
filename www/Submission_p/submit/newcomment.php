<!DOCTYPE html PUBLIC '-//W3C//DTD HTML 4.01//EN' 'http://www.w3.org/TR/html4/strict.dtd'>
<html>
<head>
  <meta content='text/html; charset=ISO-8859-1'
 http-equiv='content-type'>
  <title>New Comment Submission</title>
</head>
<body>
<form action='newcomment.php' method='post' enctype='multipart/form-data'>

<?php
ini_set('display_errors', 'On');
error_reporting(E_ALL | E_STRICT);
include('../functions/popfunctions.php');
include('../functions/editfunctions.php');
include('../functions/curfunctions.php');
include('../functions/submitfunctions.php');
if(!isset($_POST['screen'])){
?>
  <input type='hidden' name='screen' value='1'>

  Wafer <input name='part' value='wafer_p' type='radio'> or Sensor <input name='part'   value='sensor_p' type='radio'>
  <br>
  Select a wafer:
  <select name='wafid'>
  <?php
    waferpop();
  ?>
  </select>
  <br>
  <br>
  HDI: <input name='part' value='HDI_p' type='radio'>
  <br>
  <select name='hdiid'>
  <?php
    hdipop();
  ?>
  </select>
  <br>
  <br>
  BBM: <input name='part' value='module_p'
   type='radio'>
  <br>
  <select name='bbmid'>
  <?php
    modulepop();
  ?>
  </select>
  <br>
  <br>

<?php
}
elseif($_POST['screen']==1){
  	echo "<input type='hidden' name='screen' value='1'>";
	echo "<input type='hidden' name='part' value='".$_POST['part']."'>";

	if($_POST['part'] == 'sensor_p' && !isset($_POST['id'])){
		echo "Available Sensors";
		echo "<select name='id'>";

		sensorpop($_POST['wafid']);
		echo "</select>";
		echo"<br>";
		echo"<br>";
	}
	else{
		if(!isset($_POST['id'])){
			$part = $_POST['part'];

			if($part == 'wafer_p'){
				echo "<input type='hidden' name='id' value='".$_POST['wafid']."'>";
				$id=$_POST['wafid'];}
			if($part == 'sensor_p'){
				echo "<input type='hidden' name='id' value='".$_POST['sensorid']."'>";
				$id=$_POST['sensorid'];}
			if($part == 'module_p'){
				echo "<input type='hidden' name='id' value='".$_POST['bbmid']."'>";
				$id=$_POST['bbmid'];}
			if($part == 'HDI_p'){
				echo "<input type='hidden' name='id' value='".$_POST['hdiid']."'>";
				$id=$_POST['hdiid'];}
		}
		else{
			$id=$_POST['id'];
		}

		if(isset($_POST['submit']) && isset($_POST['notes'])){
			addcomment($_POST['part'],$id,$_POST['notes']);
		}

 	 	echo "<input type='hidden' name='id' value='".$id."'>";
	
		curname($_POST['part'],$id);
		curnotes($_POST['part'],$id);

		echo"<br>";
		echo"<br>";
		echo"Additional Notes <textarea cols=\"40\" rows=\"5\" name=\"notes\"></textarea>";
		echo"<br>";
		echo"<br>";

	}
}

conditiionalSubmit();
?>

<br>

<form method='link' action='../index.html'>
<input type='submit' value='MAIN MENU'>
</form>

</body>
</html>

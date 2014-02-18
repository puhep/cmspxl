<!DOCTYPE html PUBLIC '-//W3C//DTD HTML 4.01//EN' 'http://www.w3.org/TR/html4/strict.dtd'>
<html>
<head>
  <meta content='text/html; charset=ISO-8859-1'
 http-equiv='content-type'>
  <title>New Picture Submission</title>
</head>
<body>
<form action='newpic.php' method='post' enctype='multipart/form-data'>

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
  HDI: <input name='part' value='HDI_p' type='radio'>
  <br>
  <select name='hdiid'>
  <?php
    hdipop();
  ?>
  </select>

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
		if (isset($_POST['submit']) && isset($_FILES['pic']['size'])){

			$filename = $_FILES['pic']['name'];
			$tmploc = $_FILES['pic']['tmp_name'];

			$part = $_POST['part'];
			$cwd = getcwd();

			$num = 0;

			while(file_exists($cwd."/../pics/".$part."/".$part.$id."pic".$num.".jpg")){
				$num = $num +1;
			}

			$newfilename = $part.$id."pic".$num;
	
			move_uploaded_file($tmploc, $cwd."/../pics/".$part."/".$newfilename.".jpg");

			$textfile = $cwd."/../pics/".$part."/".$newfilename.".txt";
			$fp = fopen($textfile, 'w');

			$date = date('Y-m-d H:i:s ');
		
			fwrite($fp, $date.$_POST['notes']."\n");
			fclose($fp);
		}

		echo "<input type='hidden' name='id' value='".$id."'>";
	
		curname($_POST['part'], $id);
		curpics($_POST['part'], $id);

		echo "<br>";

		echo "Picture File <input name=\"pic\" type=\"file\">";
		echo "<br>";
		echo "<br>";
		echo "Additional Notes <textarea cols=\"40\" rows=\"5\" name=\"notes\"></textarea>";
	}
}

conditionalSubmit();
?>

<br>

<form method="link" action="../index.html">
<input type="submit" value="MAIN MENU">
</form>

</body>
</html>

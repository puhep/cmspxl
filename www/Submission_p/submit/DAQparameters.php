<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01//EN" "http://www.w3.org/TR/html4/strict.dtd">
<html>
<head>
  <meta content="text/html; charset=ISO-8859-1"
 http-equiv="content-type">
  <title>DAQ Parameters Submission</title>
</head>
<body>
<form action="<?=$_SERVER['PHP_SELF']?>" method="post" enctype="multipart/form-data">
Available Modules<select name = "bbm">
<?php
include('../functions/submitfunctions.php');
include('../functions/popfunctions.php');
modulepop();
?>
</select>
<br>
<br>
Please submit the following files:
<br>
C0.gif
<input name="C0" type="file">
<br>
addressParameters.dat
<input name="aP" type="file">
<br>
dacParameters_C0.dat
<input name="dP" type="file">
<br>
phCalibrationFitTan_C0.dat
<input name="ph" type="file">
<br>
summary_C0.txt
<input name="sum" type="file">
<br>
SCurveData_C0.dat
<input name="SCD" type="file">
<br>
testParameters.dat
<input name="tP" type="file">
<br>
trimParameters60_C0.dat
<input name="tP60" type="file">
<br>
<br>
Noise mu
<textarea cols="10" rows="1" name="noise"></textarea>
<br>
<br>
Gain mu
<textarea cols="10" rows="1" name="gain"></textarea>
<br>
<br>
Additional Notes <textarea cols="40" rows="5" name="notes"></textarea><br>
<br>

<?php

conditionalSubmit();

if(isset($_POST['submit']) && !is_null($_POST['bbm'])){
 	DAQinfo($_POST['bbm'], $_FILES['C0']['tmp_name'], $_FILES['C0']['size'], $_FILES['aP']['tmp_name'], $_FILES['dP']['tmp_name'], $_FILES['ph']['tmp_name'], $_FILES['sum']['tmp_name'], $_FILES['SCD']['tmp_name'], $_FILES['tP']['tmp_name'], $_FILES['tP60']['tmp_name'], $_POST['notes'], $_POST['noise'], $_POST['gain']);

	


}
?>
</form>

<br>

<form method="link" action="../index.php">
<input type="submit" value="MAIN MENU">
</form>

</body>
</html>

<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01//EN" "http://www.w3.org/TR/html4/strict.dtd">
<html>
<head>
  <meta content="text/html; charset=ISO-8859-1"
 http-equiv="content-type">
  <title>Recieved Module Submission</title>
</head>
<body>
<form action='modulesubmit.php' method='post' enctype='multipart/form-data'>
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

Available Modules
<select name="modules">
<?php
availmodule($_POST['wafers']);
?>
</select>

<br>
<br>

<input name="QC" value="accept" type="radio">Accept
&nbsp; &nbsp; <input name="QC" value="reject"
 type="radio">Reject<br>
<br>
Additional Notes <textarea cols="40" rows="5" name="notes"></textarea>
<?php
}
?>

<br>
<br>

<?php

conditionalSubmit();

if(isset($_POST['submit']) && isset($_POST['modules']) && isset($_POST['QC'])){
	if(!strcmp($_POST['QC'],"accept")){
		$good = 1;
	}
	else{
		$good = -1;
	}
	$func = 'UPDATE module_p set assembly='.$good.' WHERE id='.$_POST['modules'];
}
?>
</form>
<br>

<form method="link" action="../index.html">
<input type="submit" value="MAIN MENU">
</form>

</body>
</html>

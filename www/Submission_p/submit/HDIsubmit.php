<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01//EN" "http://www.w3.org/TR/html4/strict.dtd">
<html>
<head>
  <meta content="text/html; charset=ISO-8859-1"
 http-equiv="content-type">
  <title>HDI Submission</title>
</head>
<body>
<form action="<?=$_SERVER['PHP_SELF']?>" method="post" enctype="multipart/form-data">
HDI ID <textarea cols="20" rows="1" name="HDI_id"></textarea><br>
<br>
Arrival Date (mm/dd/yyyy) <textarea cols="10" rows="1" name="arrival"></textarea>
<br>
Additional Notes <textarea cols="40" rows="5" name="notes"></textarea><br>
<br>

<?php
include('../functions/submitfunctions.php');

conditionalSubmit();

if(isset($_POST['submit']) && isset($_POST['HDI_id']) && isset($_POST['arrival'])){
 
 hdiinfo($_POST['HDI_id'],$_POST['notes'],$_POST['arrival']);
}
elseif(isset($_POST['submit'])){
 echo "Not all forms were filled, please retry.";
}
?>
</form>

<form method="link" action="../index.html">
<input type="submit" value="MAIN MENU">
<form>

</body>
</html>

<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01//EN" "http://www.w3.org/TR/html4/strict.dtd">
<html>
<head>
  <meta content="text/html; charset=ISO-8859-1"
 http-equiv="content-type">
  <title>New Comment Submission</title>
</head>
<body>
<form action="summarycomment.php" method="post" enctype="multipart/form-data">

<?php
ini_set('display_errors', 'On');
error_reporting(E_ALL | E_STRICT);
include('../functions/editfunctions.php');
include('../functions/curfunctions.php');
include('../functions/submitfunctions.php');

if (isset($_POST['submit']) && $_POST['notes'] != ""){

	addcomment($_POST['part'],$_POST['id'], $_POST['notes']);

}

echo "<input type='hidden' name='part' value='".$_POST['part']."'>";

echo "<input type='hidden' name='id' value='".$_POST['id']."'>";

curname($_POST['part'], $_POST['id']);
curnotes($_POST['part'], $_POST['id']);


?>


<br>
<br>
Additional Notes <textarea cols="40" rows="5" name="notes"></textarea><br>
<br>

<?php
  conditionalSubmit();
?>

<br>
<br>
</form>

<form method="GET" action="
<?php
  if($_POST['part'] == "module_p"){
  echo "bbm";}	
  if($_POST['part'] == "wafer_p"){
  echo "wafer";}	
  if($_POST['part'] == "sensor_p"){
  echo "sensor";}	
  if($_POST['part'] == "ROC_p"){
  echo "roc";}	
  if($_POST['part'] == "HDI_p"){
  echo "hdi";}	

  echo ".php";
?>
">
<?php
  echo "<input type='hidden' name='id' value='".$_POST['id']."'>";
?>
<input type="submit" value="Back to Summary">
</form>

</body>
</html>

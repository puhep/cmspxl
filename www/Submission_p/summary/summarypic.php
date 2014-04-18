<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01//EN" "http://www.w3.org/TR/html4/strict.dtd">
<html>
<head>
  <meta content="text/html; charset=ISO-8859-1"
 http-equiv="content-type">
  <title>New Picture Submission</title>
</head>
<body>
<form action="summarypic.php" method="post" enctype="multipart/form-data">

<?php
 #ini_set('display_errors', 'On');
 #error_reporting(E_ALL | E_STRICT);
include('../functions/curfunctions.php');
include('../functions/submitfunctions.php');

if (isset($_POST['submit']) && $_FILES['pic']['size'] > 0){

	$filename = $_FILES['pic']['name'];
	$tmploc = $_FILES['pic']['tmp_name'];

	echo $tmploc;

	$part = $_POST['part'];
	$id = $_POST['id'];
	$cwd = getcwd();

	echo $cwd;

	$num = 0;

	while(file_exists($cwd."/../pics/".$part."/".$part.$id."pic".$num.".jpg")){
		$num = $num +1;
	}

	$newfilename = $part.$id."pic".$num;

	move_uploaded_file($tmploc, $cwd."/../pics/".$part."/".$newfilename.".jpg");

	$textfile = $cwd."/../pics/".$part."/".$newfilename.".txt";
	$fp = fopen($textfile, 'w');

	$date = date('Y-m-d H:i:s ');
	
	fwrite($fp, $date.$_POST['notes']);
	

	fclose($fp);
}

echo "<input type='hidden' name='part' value='".$_POST['part']."'>";

echo "<input type='hidden' name='id' value='".$_POST['id']."'>";
curname($_POST['part'], $_POST['id']);
curpics($_POST['part'], $_POST['id']);

?>


<br>
Picture File <input name="pic" type="file">
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

<form mehod="GET" action="
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

</form>
</body>
</html>

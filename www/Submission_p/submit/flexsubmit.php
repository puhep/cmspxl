<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01//EN" "http://www.w3.org/TR/html4/strict.dtd">
<html>
<head>
  <meta content="text/html; charset=ISO-8859-1"
 http-equiv="content-type">
  <title>Flex Cable Submission</title>
</head>
<body>
<form  method="post" enctype="multipart/form-data">

<?php
include('../functions/submitfunctions.php');
include('../functions/curfunctions.php');
include('../functions/editfunctions.php');
include('../connect.php');

mysql_query('USE cmsfpix_u', $connection);

if(isset($_POST['submit'])){

	$add=0;
	$ship=0;
	$trash=0;

	if(isset($_POST['add'])){
		$add = $_POST['add'];}
	if(isset($_POST['ship'])){
		$ship = $_POST['ship'];}
	if(isset($_POST['trash'])){
		$trash = $_POST['trash'];}

	$func1 = "UPDATE flex_p SET current=current+".$add.", tot_received=tot_received+".$add." WHERE id=1";
	mysql_query($func1, $connection);
	
	$func2 = "UPDATE flex_p SET current=current-".$ship.", tot_shipped=tot_shipped+".$ship." WHERE id=1";
	mysql_query($func2, $connection);
	
	$func3 = "UPDATE flex_p SET current=current-".$trash.", tot_trashed=tot_trashed+".$trash." WHERE id=1";
	mysql_query($func3, $connection);
	
	$func4 = "SELECT current FROM flex_p";
	$output = mysql_query($func4, $connection);
	$row = mysql_fetch_assoc($output);
	$curcount = $row['current'];
	echo $curcount;
	
	$tally = "Flex Cables Added:".$add." Shipped:".$ship." Trashed:".$trash." Current Total:".$curcount;
	
	addcomment("flex_p",1,$tally);
	addcomment("flex_p",1,$_POST['notes']);

}

echo "Current Number of Flex Cables: ";

$func = "SELECT current FROM flex_p";
$output = mysql_query($func, $connection);
$row = mysql_fetch_assoc($output);
$curcount = $row['current'];
echo $curcount;
?>

<br>
<br>

Flex Cables Recieved: <textarea cols="2" rows="1" name="add"></textarea>

<br>
<br>

Flex Cables Shipped Out: <textarea cols="2" rows="1" name="ship"></textarea>

<br>
<br>

Flex Cables Discarded: <textarea cols="2" rows="1" name="trash"></textarea>

<br>
<br>

Additional Notes <textarea cols="40" rows="5" name="notes"></textarea>
<br>
<br>

<?php

curnotes("flex_p",1);

echo"<br>";
echo"<br>";

conditionalSubmit();

?>

</form>
<br>
<form method="link" action="../index.php">
<input type="submit" value="MAIN MENU">
</form>
</body>
</html>

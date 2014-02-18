<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01//EN" "http://www.w3.org/TR/html4/strict.dtd">
<html>
<?php
	ini_set('display_error', 'On');
	error_reporting(E_ALL | E_STRICT);

	include('../functions/curfunctions.php');
	include('../functions/popfunctions.php');

	$part = "wafer_p";
	$id = $_GET['id'];
	$names = namedump($part, $id);

	$dumped = dump($part, $id);
?>
<head>
  <meta content="text/html; charset=ISO-8859-1"
 http-equiv="content-type">
  <link rel="stylesheet" type="text/css" href="../css/summary3.css" />
  <?php
	echo "<title>";
	echo $dumped['name'];
	echo " Summary";
	echo "</title>";
  ?>
</head>
<body>
<?php

		echo "<p>";
		echo "<part>";
		echo $dumped['name'];
		echo "</part>";
		echo "<br>";
		echo "<br>";

		echo "<h>";
		echo "Arrival Date: ";
		echo "</h>";
		echo $dumped['received'];
		echo "<br>";
		echo "<br>";

		#echo "<h>";
		#echo "Added to Database: ";
		#echo "</h>";
		#echo $dumped['time_created'];
		#echo "<br>";
		#echo "<br>";

		echo "<h>";
		echo "Vendor: ";
		echo "</h>";
		echo $dumped['vendor'];
		echo "<br>";
		echo "<br>";

		echo "<h>";
		echo "Thickness: ";
		echo "</h>";
		echo $dumped['thickness'];
		echo "<br>";
		echo "<br>";

		echo "<h>";
		echo "Comprised of:";
		echo "</h>";
		echo "<br>";
		sensorlist($id);
		echo "<br>";
		echo "<br>";

		echo "<h>";
		echo "IV Scans:";
		echo "</h>";
		echo "<br>";
		echo "<br>";
		echo "Diodes";
		echo "<br>";
		echo "<a href=\"../graphing/fullwafer.php?scan=IV&partid=$id&type=D\" target=\"_blank\"><img src=\"../graphing/fullwafer.php?scan=IV&partid=$id&type=D\" width=\"355\" height=\"200\" /></a>";
		echo "<br>";
		echo "<br>";
		echo "1x1s";
		echo "<br>";
		echo "<a href=\"../graphing/fullwafer.php?scan=IV&partid=$id&type=S\" target=\"_blank\"><img src=\"../graphing/fullwafer.php?scan=IV&partid=$id&type=S\" width=\"355\" height=\"200\" /></a>";
		echo "<br>";
		echo "<br>";
		echo "2x8s";
		echo "<br>";
		echo "<a href=\"../graphing/fullwafer.php?scan=IV&partid=$id&type=L\" target=\"_blank\"><img src=\"../graphing/fullwafer.php?scan=IV&partid=$id&type=L\" width=\"355\" height=\"200\" /></a>";
		echo "<br>";
		echo "<br>";
		echo "<br>";

		curpics($part, $id);
		echo "<br>";
		echo "<br>";
		echo "</p>";


		echo "<notes>";
		echo "<h>";
		echo "Notes: ";
		echo "</h>";
		echo "<br>";
		echo nl2br($dumped['notes']);
		echo "</notes>";
		echo "<br>";
		echo "<br>";


?>
<p>
<form method="post" action="summarycomment.php">
<?php
  echo "<input type='hidden' name='part' value='".$part."'>";
  echo "<input type='hidden' name='id' value='".$id."'>";
?>
<input type="submit" value="Add Comment to This Part">
</form>

<form method="post" action="summarypic.php">
<?php
  echo "<input type='hidden' name='part' value='".$part."'>";
  echo "<input type='hidden' name='id' value='".$id."'>";
?>
<input type="submit" value="Add Picture to This Part">
</form>

<form method="get" action="../assembly/wafer.php">
<?php
  echo "<input type='hidden' name='id' value='".$id."'>";
?>
<input type="submit" value="Part Assembly Flow">
</form>

<form method="link" action="list.php">
<input type="submit" value="BACK">
</form>
</p>
</body>
</html>

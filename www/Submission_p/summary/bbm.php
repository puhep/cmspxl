<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01//EN" "http://www.w3.org/TR/html4/strict.dtd">
<html>
<?php 
	ini_set('display_error', 'On');
	error_reporting(E_ALL | E_STRICT);


	include('../functions/curfunctions.php');

	$part = "module_p";
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

		echo "<part>";
		echo $dumped['name'];
		echo "</part>";
		echo "<br>";
		echo "<br>";

		#echo "<h>";
		#echo "Arrival Date:";
		#echo "</h>";
		#echo $dumped['arrival'];
		#echo "<br>";
		#echo "<br>";

		#echo "<h>";
		#echo "Added to Database: ";
		#echo "</h>";
		#echo $dumped['time_created'];
		#echo "<br>";
		#echo "<br>";

		if($dumped['assembly'] != 12){
		echo "<h>";
		echo "Location: ";
		echo "</h>";
		}
		else{
		echo "<h>";
		echo "Processed at: ";
		echo "</h>";
		}

		echo $dumped['location'];
		echo "<br>";
		echo "<br>";

		echo "<h>";
		echo "Status: ";
		echo "</h>";
		curstep("module", $dumped['assembly']);
		echo "<br>";
		echo "<a href=\"../assembly/bbm.php?id=$id\">Update Status</a>";
		echo "<br>";
		echo "<br>";

		echo "<h>";
		echo "Comprised of:";
		echo "</h>";
		echo "<br>";
		$sensid = $names['sensor'];
		$hdiid = $names['hdi'];
		echo "Sensor: <a href=\"sensor.php?id=".$dumped['assoc_sens']."\">$sensid</a>";
		echo "<br>";
		echo "HDI: <a href=\"hdi.php?id=".$dumped['assoc_HDI']."\">$hdiid</a>";
		echo "<br>";
		echo "ROCs:";
		echo "<br>";
		currocs($dumped['id']);
		echo "<br>";

		echo "<h>";
		echo "IV/CV Scans:";
		echo "</h>";
		echo "<br>";
		curgraphs($dumped['assoc_sens'], "IV");
		echo "<br>";
		echo "<br>";
		xmlbuttongen($dumped['assoc_sens'], "IV");
		echo "<br>";
		echo "<br>";

		curgraphs($dumped['assoc_sens'], "CV");
		echo "<br>";
		echo "<br>";
		xmlbuttongen($dumped['assoc_sens'], "CV");
		echo "<br>";
		echo "<br>";

		echo "<h>";
		echo "DAQ Data:";
		echo "</h>";
		echo "<br>";
		daqdump($id);
		echo "<br>";
		echo "<br>";
		echo "<br>";

		curpics($part, $id);
		echo "<br>";
		echo "<br>";

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

<form method="get" action="../assembly/bbm.php">
<?php
   echo "<input type='hidden' name='id' value='".$id."'>";
?>
<input type="submit" value="Part Assembly Flow">
</form>

<form method="link" action="list.php">
<input type="submit" value="BACK">
</form>
</body>
</html>

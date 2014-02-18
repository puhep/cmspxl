<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01//EN" "http://www.w3.org/TR/html4/strict.dtd">
<html>
<head>
  <meta content="text/html; charset=ISO-8859-1"
 http-equiv="content-type">
  <title>Summary</title>
</head>
<body>

<form method="link" action="../index.html">
<input type="submit" value="MAIN MENU">
</form>

<?php
include('../connect.php');

$func1 = "SELECT name, id from wafer_p ORDER BY name";
$func2 = "SELECT name, id from sensor_p ORDER BY name";
$func3 = "SELECT name, id from HDI_p ORDER BY name";
$func4 = "SELECT name, id from module_p WHERE name LIKE 'B%' ORDER BY name";
$func5 = "SELECT name, id from module_p WHERE name LIKE 'M%' ORDER BY name";
$i=0;
$j=0;
$dataarray;
$partarray = array("wafer", "sensor", "hdi", "bbm", "bbm");
$fpartarray = array("Wafer", "Sensor", "HDI", "BBM", "Fully Assembled");

mysql_query('USE cmsfpix_u', $connection);

$output1 = mysql_query($func1, $connection);
while($row1 = mysql_fetch_assoc($output1)){
	$dataarray[0][$i] = $row1['name'];
	$dataarray[1][$i] = $row1['id'];
	$i++;
}

$output2 = mysql_query($func2, $connection);
while($row2 = mysql_fetch_assoc($output2)){
	$dataarray[2][$j] = $row2['name'];
	$dataarray[3][$j] = $row2['id'];
	$j++;
}

if($j > $i){$i = $j;}
$j=0;

$output3 = mysql_query($func3, $connection);
while($row3 = mysql_fetch_assoc($output3)){
	$dataarray[4][$j] = $row3['name'];
	$dataarray[5][$j] = $row3['id'];
	$j++;
}

if($j > $i){$i = $j;}
$j=0;

$output4 = mysql_query($func4, $connection);
while($row4 = mysql_fetch_assoc($output4)){
	$dataarray[6][$j] = $row4['name'];
	$dataarray[7][$j] = $row4['id'];
	$j++;
}

if($j > $i){$i = $j;}
$j=0;

$output5 = mysql_query($func5, $connection);
while($row5 = mysql_fetch_assoc($output5)){
	$dataarray[8][$j] = $row5['name'];
	$dataarray[9][$j] = $row5['id'];
	$j++;
}

if($j > $i){$i = $j;}

echo "<table cellspacing=60 border=0>";
echo "<tr valign=top>";

for($l=0;$l<5;$l++){
	echo "<td>";


	echo "<table cellspacing=0 border=2>";
	echo "<tr><td>";
	echo "$fpartarray[$l]";
	echo "</tr></td>";
	for($k=0; $k<$i; $k++){

		if(is_array($dataarray[2*$l]) && isset($dataarray[2*$l][$k])){
			echo "<tr>";
			echo "<td>";

			echo "<a href=\"".$partarray[$l].".php?id=".$dataarray[2*$l+1][$k]."\">".$dataarray[2*$l][$k]."</a>";
			
			echo "</td>";
			echo "</tr>";
		}

	}
	echo "</table>";
	echo "</td>";
}

echo "</tr>";
echo "</table>";

echo"<br>";
echo"<br>";
?>

<form method="link" action="../index.html">
<input type="submit" value="MAIN MENU">
</form>

</body>
</html>

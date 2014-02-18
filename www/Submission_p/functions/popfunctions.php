<?php

function waferpop(){

include('../connect.php');

	mysql_query('USE cmsfpix_u', $connection);

	$available = mysql_query('SELECT name,id FROM wafer_p',$connection);

	echo "<option value=\"NULL\">Select a wafer</option>\n";

	while($waferrow = mysql_fetch_assoc($available)){
		$id = $waferrow['id'];
		$waferid = $waferrow['name'];
		echo "<option value=\"$id\">".$waferid."</option>\n";
	}	
}

function sensorpop($wafer){

include('../connect.php');

	mysql_query('USE cmsfpix_u', $connection);
	$func = 'SELECT name,id FROM sensor_p WHERE assoc_wafer LIKE '.$wafer;
	
	$available = mysql_query($func, $connection);

	echo "<option value=\"NULL\">Select a sensor</option>\n";

	while($sensrow = mysql_fetch_assoc($available)){
		$id = $sensrow['id'];
		$sensid = $sensrow['name'];
		echo "<option value=\"$id\">".$sensid."</option>\n";
	}	
}

function sensorlist($wafer){

include('../connect.php');

	mysql_query('USE cmsfpix_u', $connection);
	$func = 'SELECT name,id FROM sensor_p WHERE assoc_wafer LIKE '.$wafer;
	
	$available = mysql_query($func, $connection);

	while($sensrow = mysql_fetch_assoc($available)){
		$id = $sensrow['id'];
		$sensid = $sensrow['name'];
		echo "<a href=\"sensor.php?id=".$id."\">$sensid</a><br>";
	}	
}

function availsensor(){

include('../connect.php');

	mysql_query('USE cmsfpix_u', $connection);

	$waffunc = 'SELECT id from wafer_p';
	$output = mysql_query($waffunc, $connection);
	
	echo "<option value=\"NULL\">Select a sensor</option>\n";
	
	while($wafrow = mysql_fetch_assoc($output)){
		$wafer = $wafrow['id'];

		$func = 'SELECT name,id FROM sensor_p WHERE assoc_wafer LIKE '.$wafer.' AND module IS NULL';

		$available = mysql_query($func, $connection);

		while($sensrow = mysql_fetch_assoc($available)){
			$id = $sensrow['id'];
			$sensid = $sensrow['name'];
			echo "<option value=\"$id\">".$sensid."</option>\n";
		}	
	}	
}

function modulepop(){

include('../connect.php');

	mysql_query('USE cmsfpix_u', $connection);

	$available = mysql_query('SELECT name,id FROM module_p',$connection);

	echo "<option value=\"NULL\">Select a module</option>\n";

	while($modrow = mysql_fetch_assoc($available)){
		$id = $modrow['id'];
		$name = $modrow['name'];
		echo "<option value=\"$id\">".$name."</option>\n";
	}	
}

function availmodule($wafer){

include('../connect.php');

	mysql_query('USE cmsfpix_u', $connection);

	$sensfunc = 'SELECT id from sensor_p WHERE assoc_wafer='.$wafer;
	$output = mysql_query($sensfunc, $connection);
	
	echo "<option value=\"NULL\">Select a module</option>\n";

	while($sensrow = mysql_fetch_assoc($output)){
		$sensor = $sensrow['id'];
	
		$func = 'SELECT name,id FROM module_p WHERE assoc_sens='.$sensor.' AND assembly=0';

		$available = mysql_query($func, $connection);

		while($modrow = mysql_fetch_assoc($available)){
			$id = $modrow['id'];
			$modid = $modrow['name'];
			echo "<option value=\"$id\">".$modid."</option>\n";
		}	
	}	
}

function hdipop(){

include('../connect.php');

	mysql_query('USE cmsfpix_u', $connection);

	$available = mysql_query('SELECT name,id FROM HDI_p',$connection);

	echo "<option value=\"NULL\">Select an HDI </option>\n";

	while($hdirow = mysql_fetch_assoc($available)){
		$id = $hdirow['id'];
		$hdiid = $hdirow['name'];
		echo "<option value=\"$id\">".$hdiid."</option>\n";
	}	
}

function availhdi(){

include('../connect.php');

	mysql_query('USE cmsfpix_u', $connection);

	$func = "SELECT name, id FROM HDI_p WHERE assembly=2";

	$available = mysql_query($func, $connection);

	echo "<option value=\"NULL\">Select an HDI</option>\n";

	while($hdirow = mysql_fetch_assoc($available)){
		$id = $hdirow['id'];
		$hdiid = $hdirow['name'];
		echo "<option value=\"$id\">".$hdiid."</option>\n";
	}	
	
}

?>

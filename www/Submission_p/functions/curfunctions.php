<?php

function curnotes($db, $id){
	include('../connect.php');

	mysql_query('USE cmsfpix_u', $connection);

	$func = "SELECT notes from ".$db." WHERE id=".$id;

	$output = mysql_query($func, $connection);
	$noterow = mysql_fetch_assoc($output);
	if($noterow['notes']!=""){
		echo "<br>";
		echo nl2br($noterow["notes"]);
	}
	else{
		echo "This part has no comments";
	}
}

function curpics($type, $id){

	$cwd = getcwd();
	$num = 0;

	echo "<table border=1 align=\"center\">";
	while(file_exists($cwd."/../pics/".$type."/".$type.$id."pic".$num.".jpg")){
	
		echo "<tr>";

		$src = "../pics/".$type."/".$type.$id."pic".$num.".jpg";
		$txt = "../pics/".$type."/".$type.$id."pic".$num.".txt";
	
		echo "<td>";	
		echo "<a href=".$src." target =\"_blank\"><img src=".$src." width=\"200\" height=\"200\" /></a>";
		echo "</td>";

		echo "<td>";
		if(file_exists($txt)){
			$fp = fopen($txt, 'r');
			echo nl2br(fread($fp, filesize($txt)));
			fclose($fp);
		}
		echo "</td>";
		
		echo "<td>";
		
		echo "<form method=\"post\" action=\"../summary/piccomedit.php\">";
		echo "<input type='hidden' name='file' value='".$txt."'>";
		echo "<input type='hidden' name='id' value='".$id."'>";
		echo "<input type='hidden' name='part' value='".$type."'>";
		echo "<input type='submit' value='Add Comments'>";
		echo "</form>";

		echo "</td>";

		echo "</tr>";

		$num = $num+1;
	}
	echo "</table>";

	if($num==0){
		echo "No pictures for this part";
	}
}

function curgraphs($sensorid, $scan){
	include('../connect.php');

	$func = "SELECT filesize,notes  FROM measurement_p WHERE part_ID =$sensorid AND scan_type=\"$scan\"";
	mysql_query('USE cmsfpix_u', $connection);

	$output = mysql_query($func, $connection);
	
	$any = 0;
	while($row = mysql_fetch_assoc($output)){
		$exists = $row['filesize'];
		if($exists){
			break;}
	}
	if($exists){
		echo "<a href=\"../download/dbxmldlgraph.php?id=$sensorid&scan=$scan\" target =\"_blank\"><img src=\"../download/dbxmldlgraph.php?id=$sensorid&scan=$scan\" width=\"335\" height=\"200\" /></a>";
		
	}
	else{
		echo "No ".$scan." scan data for this part";
	}
}

function curname($db, $id){
	include('../connect.php');

	mysql_query('USE cmsfpix_u', $connection);

	$func = "SELECT name FROM $db WHERE id=$id";
	
	$output = mysql_query($func, $connection);
	$array = mysql_fetch_assoc($output);
	$name = $array['name'];

	echo "<b>$name</b><br>";
}

function curstep($part, $assembly){

	$wafsteps = array("Recieved", "Inspected", "Tested", "Ready for Shipping", "Shipped");
	$modulesteps = array("Expected", "Recieved", "Inspected", "IV Tested", "Ready for HDI Assembly", "HDI Attached", "Wirebonded", "Encapsulated", "Tested (Post-Encapsulation)", "Thermal Cycling", "Tested (Post-Thermal Cycling)", "Ready for Shipping", "Shipped");
	$hdisteps = array("Recieved", "Inspected", "Ready for Assembly", "On Module");

	if(!strcmp($part, "wafer")){
		echo $wafsteps[$assembly];}
	if(!strcmp($part, "module")){
		echo $modulesteps[$assembly];}
	if(!strcmp($part, "hdi")){
		echo $hdisteps[$assembly];}

}

function currocs($module){
	include('../connect.php');

	mysql_query('USE cmsfpix_u', $connection);

	$func = "SELECT name from ROC_p WHERE assoc_module=\"$module\" ORDER BY position";

	$output = mysql_query($func, $connection);

	echo "<table border=0>";

	echo "<tr>";
	echo "<td>";

	echo "<table border=1>";
	for($i=0;$i<8;$i++){

		echo "<tr>";

		echo "<td>";
		echo "ROC".$i;
		echo "</td>";

		echo "<td>";
		$rocrow = mysql_fetch_assoc($output);
		echo $rocrow['name'];
		echo "</td>";

		echo "</tr>";
	}
	echo "</table>";

	echo "</td>";

	echo "<td>";

	echo "<table border=1>";
	for($i=8;$i<16;$i++){

		echo "<tr>";

		echo "<td>";
		echo "ROC".$i;
		echo "</td>";

		echo "<td>";
		$rocrow = mysql_fetch_assoc($output);
		echo $rocrow['name'];
		echo "</td>";

		echo "</tr>";
	}
	echo "</table>";

	echo "</td>";
	echo "</tr>";

	echo "</table>";


}

function findid($db, $name){
	include('../connect.php');

	mysql_query('USE cmsfpix_u', $connection);

	$func = "SELECT id FROM $db WHERE name=\"$name\"";
	
	$output = mysql_query($func, $connection);
	$array = mysql_fetch_assoc($output);
	$id = $array['id'];

	return $id;
}

function dump($db, $id){
	include('../connect.php');

	mysql_query("USE cmsfpix_u", $connection);

	$func = "SELECT * FROM $db WHERE id=$id";
	
	$output = mysql_query($func, $connection);
	$dump = mysql_fetch_assoc($output);
	return $dump;
}

function daqdump($id){

	$src = "../download/dbc0dl.php?id=$id";

	include('../connect.php');

	mysql_query('USE cmsfpix_u', $connection);

	$func = "SELECT * from DAQ_p WHERE assoc_module=\"$id\"";

	$output = mysql_query($func, $connection);
	$row = mysql_fetch_assoc($output);

	$C0=$row['C0'];
	if($C0){
		echo "<a href=".$src." target =\"_blank\"><img src=".$src." height=\"300\" width=\"300\"></a><br>";
	
	$addressParameters = $row['addressParameters'];
	$dacParameters = $row['dacParameters'];
	$phCalibrationFitTan = $row['phCalibrationFitTan'];
	$summary = $row['summary'];
	$SCurveData = $row['SCurveData'];
	$testParameters = $row['testParameters'];
	$trimParameters = $row['trimParameters'];
	$notes = $row['notes'];

	$tmpaP = "tmpaP.txt";
	$fh = fopen($tmpaP, 'w') or die("This file cannot be opened");
	fwrite($fh, $addressParameters);
	echo "<a href=".$tmpaP." target =\"blank\">Address Parameters</a><br>";
	fclose($fh);

	$tmpdP = "tmpdP.txt";
	$fh = fopen($tmpdP, 'w') or die("This file cannot be opened");
	fwrite($fh, $dacParameters);
	echo "<a href=".$tmpdP." target =\"blank\">DAC Parameters</a><br>";

	$tmpph = "tmpph.txt";
	$fh = fopen($tmpph, 'w') or die("This file cannot be opened");
	fwrite($fh, $phCalibrationFitTan);
	echo "<a href=".$tmpph." target =\"blank\">PH Calibration Fit</a><br>";

	$tmpsummary = "tmpsummary.txt";
	$fh = fopen($tmpsummary, 'w') or die("This file cannot be opened");
	fwrite($fh, $summary);
	echo "<a href=".$tmpsummary." target =\"blank\">Summary</a><br>";

	$tmpSCD = "tmpSCD.txt";
	$fh = fopen($tmpSCD, 'w') or die("This file cannot be opened");
	fwrite($fh, $SCurveData);
	echo "<a href=".$tmpSCD." target =\"blank\">SCurve Data</a><br>";

	$tmptest = "tmptest.txt";
	$fh = fopen($tmptest, 'w') or die("This file cannot be opened");
	fwrite($fh, $testParameters);
	echo "<a href=".$tmptest." target =\"blank\">Test Parameters</a><br>";

	$tmptrim = "tmptrim.txt";
	$fh = fopen($tmptrim, 'w') or die("This file cannot be opened");
	fwrite($fh, $trimParameters);
	echo "<a href=".$tmptrim." target =\"blank\">Trim Parameters</a><br>";
	
	echo $notes;
	echo "<br><br>";
	}
	else{
		echo "No DAQ data for this part";
	}

}

function namedump($db, $id){
	include('../connect.php');

	$namearr;
	$hdi = $id;

	if($db == "module_p" || $db == "HDI_p"){$rocdb = 1;}
	else{$hdidb = 0;}

	mysql_query("USE cmsfpix_u", $connection);

	if($db == "module_p"){
		$bbmfunc = "SELECT name,assoc_HDI,assoc_sens FROM module_p WHERE id=$id";
		$bbm = mysql_query($bbmfunc, $connection);
		$row = mysql_fetch_assoc($bbm);
		$namearr["bbm"] = $row['name'];
		$id = $row['assoc_sens'];
		$hdi = $row['assoc_HDI'];
		$db="sensor_p";
	}
	
	if($db == "sensor_p"){
		$sensorfunc = "SELECT name, assoc_wafer FROM sensor_p WHERE id=$id";
		$sensor = mysql_query($sensorfunc, $connection);
		$row = mysql_fetch_assoc($sensor);
		$namearr["sensor"] = $row['name'];
		if($namearr['bbm'] == ""){
			$bbmfunc = "SELECT name from module_p WHERE assoc_sens=$id";
			$bbm = mysql_query($bbmfunc, $connection);
			$subrow = mysql_fetch_assoc($bbm);
			$namearr['bbm'] = $row['name'];
		}
		$id = $row['assoc_wafer'];
		$db = "wafer_p";
	}

	if($db == "wafer_p"){
		$waferfunc = "SELECT name FROM wafer_p WHERE id=$id";
		$wafer = mysql_query($waferfunc, $connection);
		$row = mysql_fetch_assoc($wafer);
		$namearr["wafer"] = $row['name'];
		if($namearr['sensor'] == ""){
			$sensorfunc = "SELECT name from sensor_p WHERE assoc_wafer=$id";
			$sensor = mysql_query($sensorfunc, $connection);
			$subrow = mysql_fetch_assoc($sensor);
			$namearr['sensor'] = $row['name'];
		}
	}
	
	if($rocdb == 1){
		$id = $hdi;
		$hdifunc = "SELECT name from HDI_p WHERE id=$id";
		$hdi = mysql_query($hdifunc, $connection);
		$row = mysql_fetch_assoc($hdi);
		$namearr["hdi"] = $row['name'];
		if($namearr['bbm'] == ""){
			$bbmfunc = "SELECT name from module_p WHERE assoc_sens=$id";
			$bbm = mysql_query($bbmfunc, $connection);
			$subrow = mysql_fetch_assoc($bbm);
			$namearr['bbm'] = $row['name'];
		}
	}
	
	return $namearr;
}

function xmlbuttongen($id, $scan){
	include('../connect.php');

	$func = "SELECT id, part_type FROM measurement_p WHERE part_ID=\"$id\" AND scan_type=\"$scan\"";
	
	$id1=0;
	$id2=0;
	
	mysql_query('USE cmsfpix_u', $connection);

	$output = mysql_query($func, $connection);

	while($row = mysql_fetch_assoc($output)){
		
		if($row['part_type'] == "wafer"){
			$id1 = $row['id'];
		}
		if($row['part_type'] == "module"){
			$id2 = $row['id'];
		}
	}

	if($id1>0){
		echo "<form><input type=\"button\" value=\"Download On-Wafer $scan Data\" onClick=\"window.location.href='../download/dbxmldl.php?id=$id1'\"></form>";
		echo "<a href=\"../download/XMLfiles.php?part=wafer&partid=$id&scan=$scan\" target=\"_blank\">More Files</a>";
	}
	if($id2>0){
		echo "<form><input type=\"button\" value=\"Download Bare Module $scan Data\" onClick=\"window.location.href='../download/dbxmldl.php?id=$id2'\"></form>";
		echo "<a href=\"../download/XMLfiles.php?part=module&partid=$id&scan=$scan\" target=\"_blank\">More Files</a>";
	}
}

function curmod($id,$part){
	include('../connect.php');

	if($part=="sensor_p"){
		$field = "assoc_sens";
	}
	if($part=="HDI_p"){
		$field = "assoc_HDI";
	}


	$func = "SELECT name, id FROM module_p WHERE $field=$id";
	mysql_query('USE cmsfpix_u', $connection);

	$output = mysql_query($func, $connection);
	
	$any=0;
	while($row = mysql_fetch_assoc($output)){
		$bbmid = $row['id'];
		$name = $row['name'];
		echo "<a href=\"../summary/bbm.php?id=".$bbmid."\">$name</a>";
		$any=1;
	}

	if($any == 0){
		echo "None";
	}
}

function isTestedWaferDisp($id){
	include('../connect.php');
	mysql_query("USE cmsfpix_u", $connection);

	$sensorfunc = "SELECT name,id FROM sensor_p WHERE assoc_wafer=$id ORDER BY name";
	$sensorout = mysql_query($sensorfunc, $connection);
	while($sensorrow = mysql_fetch_assoc($sensorout)){
		$sensid = $sensorrow['id'];
		$sensname = $sensorrow['name'];
		$measfunc = "SELECT filesize FROM measurement_p WHERE part_type=\"wafer\" AND scan_type=\"IV\" AND part_ID=$sensid";
		$measout = mysql_query($measfunc, $connection);
		$measrow = mysql_fetch_assoc($measout);
		echo "<br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;";
		echo "$sensname  &nbsp;&nbsp;&nbsp;"; 
		echo "IV  <input name=\"box\" value=\"$sensname\" type=\"checkbox\""; 
		if($measrow['filesize'] >0){
			echo " CHECKED";
		}
		echo " DISABLED> &nbsp;&nbsp;&nbsp;";
		if(substr($sensname,0,1) != "S"){
			$measfunc2 = "SELECT filesize from measurement_p WHERE part_type=\"wafer\" AND scan_type=\"CV\" AND part_ID=$sensid";
			$measout2 = mysql_query($measfunc2, $connection);
			$measrow2 = mysql_fetch_assoc($measout2);

		echo "CV  <input name=\"box\" value=\"$sensname\" type=\"checkbox\""; 
			if($measrow2['filesize']>0){
				echo " CHECKED";
			}
		echo " DISABLED>";
		}
	}

}

function isTestedWaferUpdate($id){
	include('../connect.php');
	mysql_query("USE cmsfpix_u", $connection);

	$all=0;
	$lastname="";

	$sensorfunc = "SELECT name,id FROM sensor_p WHERE assoc_wafer=$id";
	$sensorout = mysql_query($sensorfunc, $connection);
	while($sensorrow = mysql_fetch_assoc($sensorout)){
		$sensid = $sensorrow['id'];
		$sensname = $sensorrow['name'];
		$measfunc = "SELECT filesize FROM measurement_p WHERE part_type=\"wafer\" AND scan_type=\"IV\" AND part_ID=$sensid";
		$measout = mysql_query($measfunc, $connection);
		$measrow = mysql_fetch_assoc($measout);
		
		if($measrow['filesize'] >0 && $sensname != $lastname){
			$all++;
		}
		if(substr($sensname,0,1) != "S"){
			$measfunc2 = "SELECT filesize from measurement_p WHERE part_type=\"wafer\" AND scan_type=\"CV\" AND part_ID=$sensid";
			$measout2 = mysql_query($measfunc2, $connection);
			$measrow2 = mysql_fetch_assoc($measout2);

			if($measrow2['filesize']>0 && $sensname != $lastname){
				$all++;
			}
		}
		$lastname = $sensname;
	}
	if($all == 22){

		$updatefunc = "UPDATE wafer_p SET assembly=2 WHERE id=$id";
		mysql_query($updatefunc, $connection);
	}

}

function isTestedModuleUpdate($id){
	include('../connect.php');
	mysql_query("USE cmsfpix_u", $connection);

	$sensorfunc = "SELECT name,id FROM sensor_p WHERE assoc_wafer=$id";
	$sensorout = mysql_query($sensorfunc, $connection);
	while($sensorrow = mysql_fetch_assoc($sensorout)){
		$sensid = $sensorrow['id'];
		$sensname = $sensorrow['name'];
		$measfunc = "SELECT filesize FROM measurement_p WHERE part_type=\"wafer\" AND scan_type=\"IV\" AND part_ID=$sensid";
		$measout = mysql_query($measfunc, $connection);
		$measrow = mysql_fetch_assoc($measout);
		echo "<br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;";
		echo "$sensname  &nbsp;&nbsp;&nbsp;"; 
		echo "IV  <input name=\"box\" value=\"$sensname\" type=\"checkbox\""; 
		if($measrow['filesize'] >0){
			echo " CHECKED";
		}
		echo " DISABLED> &nbsp;&nbsp;&nbsp;";
		if(substr($sensname,0,1) == "S"){
			$measfunc2 = "SELECT filesize from measurement_p WHERE part_type=\"wafer\" AND scan_type=\"CV\" AND part_ID=$sensid";
			$measout2 = mysql_query($measfunc2, $connection);
			$measrow2 = mysql_fetch_assoc($measout2);

		echo "CV  <input name=\"box\" value=\"$sensname\" type=\"checkbox\""; 
			if($measrow2['filesize']>0){
				echo " CHECKED";
			}
		echo " DISABLED>";
		}
	}

}

function promoteBoxes($id){
	include('../connect.php');
	mysql_query("USE cmsfpix_u", $connection);

	$func = "SELECT name, id FROM sensor_p WHERE assoc_wafer=$id AND name LIKE 'WL%'";

	$output = mysql_query($func, $connection);

	echo"<br>";

	while($row = mysql_fetch_assoc($output)){
		$sensid = $row['id'];
		$sensname = $row['name'];
		echo ($sensname."<input name=\"sens[]\" value=\"$sensid\" type=\"checkbox\">"); 
		echo "<br>";
	}
}

function sensorSetPromote($id){
	include('../connect.php');
	mysql_query("USE cmsfpix_u", $connection);

	$func = "UPDATE sensor_p SET promote=1 WHERE id=".$id;

	mysql_query($func, $connection);
}

function promoteSensors($id){
	include('../connect.php');
	include('../functions/submitfunctions.php');
	mysql_query("USE cmsfpix_u", $connection);
	
	$func = "SELECT name,promote,id FROM sensor_p WHERE assoc_wafer=$id";

	$output = mysql_query($func, $connection);

	while($row = mysql_fetch_assoc($output)){
		if($row['promote']==1){
			moduleinfo($row['name']);		
		}
	}
}

function isLocal(){
	$ip = $_SERVER['REMOTE_ADDR'];

	if(!strncmp($ip, "128.210", 7)){
		return 1;
	}
	else{
		return 0;
	}
}

?>

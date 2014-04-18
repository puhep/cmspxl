<?php

function waferinfo($id, $rec, $notes){
include('../connect.php');

	$fthickness = 285;

	$date = date('Y-m-d H:i:s');

	if($notes != ""){
		$notes = $date."  ".$notes."\n";
	}

	$func = "INSERT INTO wafer_p(notes, name, vendor, thickness, received, assembly) VALUES (\"$notes\", \"$id\", \"SINTEF\", \"$fthickness\", \"$rec\", 0)";

	mysql_query('USE cmsfpix_u' , $connection);

	if(mysql_query($func,$connection)){
		echo("Wafer ".$id." has been added to the database.<br>");
	}
	else{
		echo("An error has occurred and the data has not been added.<br>");
	}


}

function sensorinfo($id, $notes, $wafer){
include('../connect.php');

	
	$date = date('Y-m-d H:i:s');

	if($notes != ""){
		$notes = $date."  ".$notes."\n";
	}

	$func = "INSERT INTO sensor_p(notes, name, assoc_wafer, assembly) VALUES (\"$notes\", \"$id\", \"$wafer\", 0)";

	mysql_query('USE cmsfpix_u' , $connection);

	if(mysql_query($func,$connection)){
		echo("Sensor ".$id." has been added to the database.<br>");
	}
	else{
		echo("An error has occurred and the data has not been added.<br>");
	}

}

function measurement($id, $parttype, $scan, $notes, $file, $size, $name){
include('../connect.php');
include('../functions/curfunctions.php');

	$sensordata = dump("sensor_p", $id);
	$sensorname = $sensordata['name'];

	$date = date('Y-m-d H:i:s');

	if($notes != ""){
		$notes = $date."  ".$notes."\n";
	}
	$func = "INSERT INTO measurement_p(part_ID, part_type, scan_type, notes, file, filesize, filename) VALUES (\"$id\", \"$parttype\", \"$scan\", \"$notes\", \"$file\",\"$size\",\"$name\")";
	
	mysql_query('USE cmsfpix_u', $connection);

	if(mysql_query($func,$connection)){
		echo "The $scan measurement on sensor $sensorname has been added to the database.<br>";
	}
	else{
		echo("An error has occurred and the data has not been added.<br>");
	}
	
}

function batchmeasurement($zipfile, $parttype, $notes){

	#####Clear the tmp directory before putting in new files#####
	#$files = glob("/project/cmsfpix/.www/Submission_p/tmp");
	#foreach ($files as $file){
		#if(is_file($file)){
			#unlink($file);
		#}
	#}
	move_uploaded_file($zipfile, "/project/cmsfpix/.www/Submission_p/tmp/tmpzip.zip");
	try{
	#$p = new PharData('../tmp/tmpzip.zip');
	#$p->extractTo("/project/cmsfpix/.www/Submission_p/tmp");
	}
	catch(UnexpectedValueException $e){
		echo "ERROR BRO";
	}
	#$gzflen = strlen($zipfile);
	#$tarfile = substr($zipfile, 0, $gzflen-3);

	#echo "TEST COMPLETE";
	
}

function hdiinfo($name, $notes, $arrival, $loc){
include('../connect.php');

	$date = date('Y-m-d H:i:s');

	if($notes != ""){
		$notes = $date."  ".$notes."\n";
	}

	$func = "INSERT INTO HDI_p(notes, name, arrival, assembly, location) VALUES (\"$notes\", \"$name\", \"$arrival\", 0, \"$loc\")";

	mysql_query('USE cmsfpix_u' , $connection);

	if(mysql_query($func,$connection)){
		echo("HDI ".$name." has been added to the database.<br>");
	}
	else{
		echo("An error has occurred and the data has not been added.<br>");
	}

}

function moduleinfo($sensor){
include('../connect.php');
include('../functions/curfunctions.php');

	mysql_query('USE cmsfpix_u' , $connection);
	
	$date = date('Y-m-d H:i:s');

	$sensorid = findid("sensor_p", $sensor);
	
	$name = "B".substr($sensor,1);

	$func = "INSERT INTO module_p(name, assoc_sens, assembly) VALUES (\"$name\", \"$sensorid\", 0)";


	if(mysql_query($func,$connection)){
	
		$modid = findid("module_p", $name);	

		$func2 = "UPDATE sensor_p SET module=\"$modid\" WHERE id=\"$sensorid\"";
		mysql_query($func2, $connection);
		#echo("BBM ".$name." has been added to the database.<br>");
	}
	else{
		echo("An error has occurred and the data has not been added.<br>");
	}

}

function ROCinfo($module){
include('../connect.php');

	mysql_query('USE cmsfpix_u', $connection);

	$date = date('Y-m-d H:i:s');

	$i = 0;

	for($i=0;$i<16;$i++){

	$func = "INSERT INTO ROC_p(assoc_module, position) VALUES (\"$module\", \"$i\")";

		if(!mysql_query($func,$connection)){
			echo("An error has occurred.<br>");
			break;
		}
	}



}

function DAQinfo($module, $C0file, $C0size, $aPfile, $dPfile, $phfile, $sumfile, $SCDfile, $tPfile, $tP60file, $notes, $noise, $gain){

	include('../connect.php');
	include('../functions/curfunctions.php');

	$date = date('Y-m-d H:i:s');
	
	if($notes != ""){
		$notes = $date."  ".$notes."\n";
	}

	$fnoise = floatval($noise);
	$fgain = floatval($gain);

	$C0 = fopen($C0file, 'r');
	$C0content = fread($C0, filesize($C0file));
	$C0content = addslashes($C0content);

	$aP = fopen($aPfile, 'r');
	$apcontent = fread($aP, filesize($aPfile));
	$apcontent = addslashes($apcontent);
	
	$dP = fopen($dPfile, 'r');
	$dpcontent = fread($dP, filesize($dPfile));
	$dpcontent = addslashes($dpcontent);

	$ph = fopen($phfile, 'r');
	$phcontent = fread($ph, filesize($phfile));
	$phcontent = addslashes($phcontent);

	$sum = fopen($sumfile, 'r');
	$sumcontent = fread($sum, filesize($sumfile));
	$sumcontent = addslashes($sumcontent);

	$SCD = fopen($SCDfile, 'r');
	$SCDcontent = fread($SCD, filesize($SCDfile));
	$SCDcontent = addslashes($SCDcontent);

	$tP = fopen($tPfile, 'r');
	$tpcontent = fread($tP, filesize($tPfile));
	$tpcontent = addslashes($tpcontent);
	
	$tP60 = fopen($tP60file, 'r');
	$tp60content = fread($tP60, filesize($tP60file));
	$tp60content = addslashes($tp60content);

	$func = "INSERT INTO DAQ_p(assoc_module, C0, C0size, addressParameters, dacParameters, phCalibrationFitTan, summary, SCurveData, testParameters, trimParameters, notes, Noise, Gain) VALUES (\"$module\",\"$C0content\", \"$C0size\",\"$apcontent\", \"$dpcontent\", \"$phcontent\", \"$sumcontent\", \"$SCDcontent\", \"$tpcontent\", \"$tp60content\", \"$notes\", \"$fnoise\", \"$fgain\")";

	mysql_query('USE cmsfpix_u', $connection);

	if(mysql_query($func, $connection)){
		$dumped = dump("module_p",$module);
		if($dumped['assembly'] == 5){
			$modfunc = "UPDATE module_p SET assembly=6 WHERE id=$module";
			mysql_query($modfunc, $connection);
		}
		echo "Parameters have been added to the database.<br>";
	}
	else{
		echo "An error has occurred and data has not been added.<br>";
	} 

	fclose($C0);
	fclose($aP);
	fclose($dP);
	fclose($sum);
	fclose($ph);
	fclose($SCD);
	fclose($tP);
	fclose($tP60);
}

function conditionalSubmit(){
  include("../functions/curfunctions.php");
  if(isLoggedIn()){ 
      echo "<input name=\"submit\" value=\"SUBMIT\" type=\"submit\">";
  }
  else{
     echo "Editing and submission not available";
  }

}

?>

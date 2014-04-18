<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01//EN" "http://www.w3.org/TR/html4/strict.dtd">
<html>
<head>
  <meta content="text/html; charset=ISO-8859-1"
 http-equiv="content-type">
  <title>6" Wafer Submission</title>
</head>
<body>
<form  method="post" enctype="multipart/form-data">

Wafer Number <textarea cols="10" rows="1" name="wafer_id"></textarea>
<br>
<br>
Receive Date (MM/DD/YYYY)<textarea cols="5" rows="1" name="receive"></textarea>
<br>
<br>
Prototype?
<input type="radio" name="prototype" value="yes">Yes
<input type="radio" name="prototype" value="no">No
<br>
<br>
Additional Notes <textarea cols="40" rows="5" name="notes"></textarea>
<br>
<br>

<?php
include('../functions/submitfunctions.php');
include('../functions/curfunctions.php');

conditionalSubmit();

if(isset($_POST['submit']) && $_POST['wafer_id']!="" && $_POST['receive']!="" && isset($_POST['prototype'])){
	$iwafer = intval($_POST['wafer_id']);
	if(($iwafer < 0) || ($iwafer > 899) || ($iwafer > 99 && $_POST['prototype']=="yes")){
		echo "Wafer ID formatting incorrect, please retry";
	}
	else{ 
 		$name=str_pad($_POST['wafer_id'],2,"0", STR_PAD_LEFT);
 		if($_POST['prototype']=="yes"){
   			$name="9".$name;
		}
 		else{
   			$name=str_pad($name,3,"0", STR_PAD_LEFT);
 		}
 		waferinfo($name,$_POST['receive'],$_POST['notes']);

  		$wafid = findid("wafer_p",$name); 

  		sensorinfo("WL_TT_".$name,"2x8 automatically added to the database",$wafid);
 		sensorinfo("WL_FL_".$name,"2x8 automatically added to the database",$wafid);
  		sensorinfo("WL_LL_".$name,"2x8 automatically added to the database",$wafid);
  		sensorinfo("WL_CL_".$name,"2x8 automatically added to the database",$wafid);
  		sensorinfo("WL_CR_".$name,"2x8 automatically added to the database",$wafid);
  		sensorinfo("WL_RR_".$name,"2x8 automatically added to the database",$wafid);
  		sensorinfo("WL_FR_".$name,"2x8 automatically added to the database",$wafid);
  		sensorinfo("WL_BB_".$name,"2x8 automatically added to the database",$wafid);
  		sensorinfo("WS_TR_".$name,"1x1 automatically added to the database",$wafid);
  		sensorinfo("WS_MR_".$name,"1x1 automatically added to the database",$wafid);
  		sensorinfo("WS_BR_".$name,"1x1 automatically added to the database",$wafid);
  		sensorinfo("WS_TL_".$name,"1x1 automatically added to the database",$wafid);
  		sensorinfo("WS_ML_".$name,"1x1 automatically added to the database",$wafid);
  		sensorinfo("WS_BL_".$name,"1x1 automatically added to the database",$wafid);
  		sensorinfo("WA_TL_".$name,"Slim-edge 1x1 automatically added to the database",$wafid);
  		sensorinfo("WA_BL_".$name,"Slim-edge 1x1 automatically added to the database",$wafid);
  		sensorinfo("WA_TR_".$name,"Slim-edge 1x1 automatically added to the database",$wafid);
  		sensorinfo("WA_BR_".$name,"Slim-edge 1x1 automatically added to the database",$wafid);
  		sensorinfo("WD_TL_".$name,"Diode automatically added to the database",$wafid);
  		sensorinfo("WD_TR_".$name,"Diode automatically added to the database",$wafid);
  		sensorinfo("WD_BL_".$name,"Diode automatically added to the database",$wafid);
  		sensorinfo("WD_BR_".$name,"Diode automatically added to the database",$wafid);
	}
}
elseif(isset($_POST['submit'])){
 	echo "All fields were not filled, please retry";
}
?>

</form>
<br>
<form method="link" action="../index.php">
<input type="submit" value="MAIN MENU">
</form>
</body>
</html>

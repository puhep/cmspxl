<?php
include('../connect.php');
require_once('../jpgraph/src/jpgraph.php');
require_once('../jpgraph/src/jpgraph_scatter.php');
require_once('../jpgraph/src/jpgraph_log.php');
include('../functions/curfunctions.php');

$scan = $_GET['scan'];
$partid = $_GET['partid'];
$sensortype = $_GET['type'];

switch($sensortype){
case 'D':
	$title = "Diode";
	break;
case 'S':
	$title = "1x1";
	break;
case 'L':
	$title = "2x8";
	break;
default:
	break;
}

if($scan == "IV"){
$y = "ACTV_CURRENT_AMP";}
if($scan == "CV"){
$y = "ACTV_CAP_FRD";}

$dumped = dump("wafer_p",$partid);

$graphname = "Wafer ".$dumped['name']." ".$title." Scans";
$datacount = 0;
$timestamp;

$docs;
$names;
$doccount = 0;

$colorarr = array("#000000","#ffff00","#a020f0","#ffa500","#add8e6","#ff0000","#bebebe","#00ff00","#ff1493","#0000ff","#ffa07a","#ee82ee","#98fb98","#8b4513","#9acd32","#6b8e23");

$func = "SELECT file, part_ID FROM measurement_p WHERE scan_type=\"$scan\" AND part_type=\"wafer\"";

mysql_query("USE cmsfpix_u", $connection);
$output = mysql_query($func, $connection);
while($row = mysql_fetch_assoc($output)){
	$thisid = $row['part_ID'];
	$func2 = "SELECT name,assoc_wafer FROM sensor_p WHERE id=$thisid";
	$output2 = mysql_query($func2, $connection);
	$row2 = mysql_fetch_assoc($output2);

	if($row2['assoc_wafer'] == $partid && $sensortype == substr($row2['name'],0,1)){
		$docs[$doccount] = simplexml_load_string($row['file']);
		$names[$doccount] = $row2['name'];
		$doccount++;
	}
}

if($doccount==0){
	echo "No scans";
	return;
}

for($looper=0;$looper<$doccount;$looper++){
	$thiscount = count($docs[$looper]->DATA_SET->DATA);
	if($thiscount > $datacount){
		$datacount = $thiscount;
	}
	$timestamp[$looper] = $docs[$looper]->HEADER->RUN->RUN_BEGIN_TIMESTAMP;
	if($timestamp[$looper] == ""){
		$timestamp[$looper] = "No Timestamp";
	}
}

$arr2d;
$limitarr;
$marked=array_fill(0,$doccount,0);

for($loop=0;$loop<$doccount;$loop++){
	for($subloop=0;$subloop<$datacount;$subloop++){

		$arr2d[$doccount][$subloop]=$docs[$loop]->DATA_SET->DATA[$subloop]->VOLTAGE_VOLT;

		settype($arr2d[$doccount][$subloop],"float");
		if($arr2d[$doccount][$subloop]<=260){
			$limitarr[$subloop]=1E-6;}
		elseif($arr2d[$doccount][$subloop]<=310){
			$limitarr[$subloop]=2E-6;}
		else{
			$limitarr[$subloop]=1E-3;}


		$arr2d[$loop][$subloop]=$docs[$loop]->DATA_SET->DATA[$subloop]->$y;
		settype($arr2d[$loop][$subloop],"float");
		if($arr2d[$loop][$subloop] < 0){
			$arr2d[$loop][$subloop] = $arr2d[$loop][$subloop]*-1;
		}
		if($arr2d[$loop][$subloop] > $limitarr[$subloop]){
			$marked[$loop]=1;
		}
	}
}

$graph=new Graph(670,400);
$graph->SetScale("linlog");
$graph->img->SetMargin(70,80,40,40);	

$graph->title->Set($graphname);

$graph->title->SetFont(FF_FONT1,FS_BOLD);

$graph->xaxis->title->Set("Bias Voltage [V]");

if($scan=="IV"){
$graph->yaxis->title->Set("Sensor Leakage Current [A]");}
if($scan=="CV"){
$graph->yaxis->title->Set("Capacitance [F]");}

$graph->yaxis->title->SetMargin(30);
$graph->SetFrame(true,'black',0);

for($looper=0;$looper<$doccount;$looper++){
	$sp[$looper] = new ScatterPlot($arr2d[$looper],$arr2d[$doccount]);
	$sp[$looper]->mark->SetWidth(4);
	$sp[$looper]->mark->SetFillColor($colorarr[$looper]);
	$sp[$looper]->link->Show();
	$graph->Add($sp[$looper]);
	$sp[$looper]->SetLegend($names[$looper]."\n".$timestamp[$looper]);
}

/*if($scan=="IV"){
$splim = new ScatterPlot($limitarr,$arr2d[$doccount]);
$splim->mark->SetWidth(4);
$splim->mark->SetFillColor("red");
$splim->link->Show();
$graph->Add($splim);
$splim->SetLegend("Limit");
}*/

$graph->Stroke();
?>

<?php
function xmldepvolt($file, $scan){
#require_once('../jpgraph/src/jpgraph.php');
#require_once('../jpgraph/src/jpgraph_scatter.php');
#require_once('../jpgraph/src/jpgraph_log.php');
#require_once('../jpgraph/src/jpgraph_line.php');
#require_once('../jpgraph/src/jpgraph_utils.inc.php');

require_once('jpgraph/src/jpgraph.php');
require_once('jpgraph/src/jpgraph_scatter.php');
require_once('jpgraph/src/jpgraph_log.php');
require_once('jpgraph/src/jpgraph_line.php');
require_once('jpgraph/src/jpgraph_utils.inc.php');

if(!is_null($file)){
$doc=simplexml_load_string($file);}

if($scan == "IV"){
$y = "ACTV_CURRENT_AMP";}
if($scan == "CV"){
$y = "ACTV_CAP_FRD";}

$datacount = 0;

if(!is_null($file)){
	$datacount = count($doc->DATA_SET->DATA);
	$timestamp = $doc->HEADER->RUN->RUN_BEGIN_TIMESTAMP;
	if($timestamp == ""){
		$timestamp = "No Timestamp";
	}
}

$arr2d;
$markedA=0;

for($loop=0;$loop<$datacount;$loop++){

	if(!is_null($file)){
		$arr2d[0][$loop]=$doc->DATA_SET->DATA[$loop]->VOLTAGE_VOLT;}
		
	settype($arr2d[0][$loop],"float");

	if(!is_null($file)){
	$arr2d[1][$loop]=$doc->DATA_SET->DATA[$loop]->$y;
		settype($arr2d[1][$loop],"float");
		if($arr2d[1][$loop] < 0){
			$arr2d[1][$loop] = $arr2d[1][$loop]*-1;
		}
	}
}

$graph = new Graph(670,400);
$graph->img->SetMargin(70,80,40,40);
$graph->SetScale("linlog");


$sp1 = new ScatterPlot($arr2d[1], $arr2d[0]);
$sp1->mark->SetWidth(4);
$sp1->link->Show();
$graph->Add($sp1);


$res;
$res2;
$breakdown = 0;
$prevval = 0;
for($loop=2;$loop<$datacount-2;$loop++){
	$sigxy=0;
	$sigx=0;
	$sigy=0;
	$sigx2=0;
	$subarray;
	for($subloop=-2;$subloop<=2;$subloop++){
		$sigx += $arr2d[0][$loop+$subloop];
		$sigy += $arr2d[1][$loop+$subloop];
		$sigxy += $arr2d[0][$loop+$subloop]*$arr2d[1][$loop+$subloop];
		$sigx2 += pow($arr2d[0][$loop+$subloop],2);
	}

	$m = (($datacount*$sigxy) - ($sigx*$sigy))/(($datacount*$sigx2)-pow($sigx,2));

	$curbreakdown=($arr2d[0][$loop]/$arr2d[1][$loop])*$m;
	
	if($curbreakdown > $prevval){
		$breakdown=$arr2d[0][$loop];
		$prevval = $curbreakdown;
	}
}

$sp1->SetLegend($breakdown);

$graph->Stroke();
}
?>

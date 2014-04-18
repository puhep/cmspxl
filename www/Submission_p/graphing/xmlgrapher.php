<?php
function xmlgrapher($file1, $file2, $file3, $scan, $partname){
require_once('../jpgraph/src/jpgraph.php');
require_once('../jpgraph/src/jpgraph_scatter.php');
require_once('../jpgraph/src/jpgraph_log.php');


if(!is_null($file1)){
$doc1=simplexml_load_file($file1);}

if(!is_null($file2)){
$doc2=simplexml_load_file($file2);}

if(!is_null($file3)){
$doc3=simplexml_load_file($file3);}

if($scan == "IV"){
$y = "ACTV_CURRENT_AMP";
$y2 = "ACTV_CURRENT_AMP";}
if($scan == "CV"){
$y = "ACTV_CAP_FRD";}

$graphname = $partname." ".$scan." Scan";
$datacountlim = 0;

if(!is_null($file1)){
	$datacount1 = count($doc1->DATA_SET->DATA);
	$datacountlim = $datacount1;
	$timestamp1 = $doc1->HEADER->RUN->RUN_BEGIN_TIMESTAMP;
	if($timestamp1 == ""){
		$timestamp1 = "No Timestamp";
	}
}
if(!is_null($file2)){
	$datacount2 = count($doc2->DATA_SET->DATA);
	if($datacount2 > $datacountlim){
		$datacountlim = $datacount2;
	}

	$timestamp2 = $doc2->HEADER->RUN->RUN_BEGIN_TIMESTAMP;
	if($timestamp2 == ""){
		$timestamp2 = "No Timestamp";
	}
}
if(!is_null($file3)){
	$datacount3 = count($doc3->DATA_SET->DATA);
	if($datacount3 > $datacountlim){
		$datacountlim = $datacount3;
	}

	$timestamp3 = $doc3->HEADER->RUN->RUN_BEGIN_TIMESTAMP;
	if($timestamp3 == ""){
		$timestamp3 = "No Timestamp";
	}
}
$arr1;
$arr2;
$arr3;
$limitarr;
$markedA=0;
$markedB=0;
$markedC=0;

for($loop=0;$loop<$datacountlim;$loop++){

	$limitarr[0][$loop]=$doc2->DATA_SET->DATA[$loop]->VOLTAGE_VOLT;

		settype($limitarr[0][$loop],"float");
		if($limitarr[0][$loop]<=260){
			$limitarr[1][$loop]=8E-6;}
		elseif($limitarr[0][$loop]<=310){
			$limitarr[1][$loop]=9E-6;}
		else{
			$limitarr[1][$loop]=1E-3;}
}


if(!is_null($file1)){
	for($loop=0;$loop<$datacount1;$loop++){

		$arr1[0][$loop]=$doc1->DATA_SET->DATA[$loop]->VOLTAGE_VOLT;

		settype($arr1[0][$loop],"float");

		$arr1[1][$loop]=$doc1->DATA_SET->DATA[$loop]->$y;
			settype($arr1[1][$loop],"float");
			if($arr1[1][$loop] < 0){
				#$arr1[1][$loop] = 1E-10;
				$arr1[1][$loop] *= -1;
			}
			if($arr1[1][$loop] > $limitarr[$loop]){
				$markedA=1;
			}
	}
}

if(!is_null($file2)){
	for($loop=0;$loop<$datacount2;$loop++){

		$arr2[0][$loop]=$doc2->DATA_SET->DATA[$loop]->VOLTAGE_VOLT;
		
		settype($arr2[0][$loop],"float");

		$arr2[1][$loop]=$doc2->DATA_SET->DATA[$loop]->$y2;
			settype($arr2[1][$loop],"float");
		if($arr2[1][$loop] < 0){
			#$arr2[1][$loop] = 1E-10;
			$arr2[1][$loop] *= -1;
		}
		if($arr2[1][$loop] > $limitarr[$loop]){
			$markedB=1;
		}
	}
}

if(!is_null($file3)){
	for($loop=0;$loop<$datacount3;$loop++){

		$arr3[0][$loop]=$doc3->DATA_SET->DATA[$loop]->VOLTAGE_VOLT;
		
		settype($arr3[0][$loop],"float");

		$arr3[1][$loop]=$doc3->DATA_SET->DATA[$loop]->$y2;
			settype($arr3[1][$loop],"float");
		if($arr3[1][$loop] < 0){
			#$arr3[1][$loop] = 1E-10;
			$arr3[1][$loop] *= -1;
		}
		if($arr3[1][$loop] > $limitarr[$loop]){
			$markedC=1;
		}
	}
}

$graph=new Graph(1340,800);
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


if(!is_null($file1)){
$sp1 = new ScatterPlot($arr1[1],$arr1[0]);
$sp1->mark->SetWidth(8);
$sp1->mark->SetFillColor("blue");
$sp1->link->Show();
$graph->Add($sp1);
$sp1->SetLegend("On Wafer\n".$timestamp1);
}

if(!is_null($file2)){
$sp2 = new ScatterPlot($arr2[1],$arr2[0]);
$sp2->mark->SetWidth(8);
$sp2->mark->SetFillColor("chartreuse3");
$sp2->link->Show();
$graph->Add($sp2);
$sp2->SetLegend("Bare Module\n".$timestamp2);
}

if(!is_null($file3)){
$sp3 = new ScatterPlot($arr3[1],$arr3[0]);
$sp3->mark->SetWidth(8);
$sp3->mark->SetFillColor("orange");
$sp3->link->Show();
$graph->Add($sp3);
$sp3->SetLegend("Assembled Module\n".$timestamp3);
}

if($scan=="IV"){
$splim = new ScatterPlot($limitarr[1],$limitarr[0]);
$splim->mark->SetWidth(8);
$splim->mark->SetFillColor("red");
$splim->link->Show();
$graph->Add($splim);
$splim->SetLegend("Limit");
}

$graph->Stroke();

}
?>

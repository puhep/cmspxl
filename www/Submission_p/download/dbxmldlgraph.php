<?php
include('../connect.php');
include('../graphing/xmlgrapher.php');

$id = $_GET["id"];
$scan = $_GET['scan'];

$func = "SELECT file, filesize, part_type FROM measurement_p WHERE part_ID=\"$id\" AND scan_type=\"$scan\"";
$namefunc = "SELECT name FROM sensor_P WHERE id=\"$id\"";


mysql_query('USE cmsfpix_u', $connection);

$file = mysql_query($func, $connection);

$nameout = mysql_query($namefunc, $connection);
$namerow = mysql_fetch_assoc($nameout);
$name = $namerow['name'];

while($row = mysql_fetch_assoc($file)){

if($row['part_type'] == "wafer"){
$tmpfile1 = "/tmp/tmpxml".$id."1.xml";
$fh = fopen($tmpfile1, 'w') or die("This file cannot be opened");
fwrite($fh, $row['file']);
fclose($fh);
}

if($row['part_type'] == "module"){
$tmpfile2 = "/tmp/tmpxml".$id."2.xml";
$fh = fopen($tmpfile2, 'w') or die("This file cannot be opened");
fwrite($fh, $row['file']);
fclose($fh);
}
}

if($tmpfile1 || $tmpfile2){
xmlgrapher($tmpfile1,$tmpfile2, $scan, $name);

mysql_free_result($file);

unlink($tmpfile1);
unlink($tmpfile2);
}
?>

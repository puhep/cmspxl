<?php

function addcomment($db, $id, $new){

	include('../connect.php');

	if($new == ""){
		return;
	}

	mysql_query('USE cmsfpix_u', $connection);

	$func1 = "SELECT notes from ".$db." WHERE id=".$id;
	$oldnotes = "";

	$output = mysql_query($func1, $connection);
	$noterow = mysql_fetch_assoc($output);
	$oldnotes = $noterow["notes"];

	$date = date('Y-m-d H:i:s');

	$newnotes = $oldnotes.$date."  ".$new."\n";

	$func2 = "UPDATE ".$db." SET notes=\"".$newnotes."\" WHERE id=".$id;
	
	mysql_query($func2, $connection);

}

?>

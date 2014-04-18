<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01//EN" "http://www.w3.org/TR/html4/strict.dtd">
<html>
<head>
  <meta content="text/html; charset=ISO-8859-1"
 http-equiv="content-type">
  <title>ROC Submission</title>
</head>
<body>
<form action='ROCsubmit.php' method='post' enctype='multipart/form-data'>
<?php
include('../connect.php');
include('../functions/submitfunctions.php');
include('../functions/popfunctions.php');
include('../functions/curfunctions.php');
if(!isset($_POST['modules'])){
?>
Available Modules
<select name="modules">
<?php
modulepop();
?>
</select>

<?php
}
else{

echo "<input type='hidden' name='modules' value='".$_POST['modules']."'>";

curname("module_p", $_POST['modules']);

$func = 'SELECT name from ROC_p WHERE assoc_module='.$_POST['modules'].' ORDER BY position';

$i = 0;

mysql_query('USE cmsfpix_u', $connection);
$output = mysql_query($func, $connection);
while($rocrow = mysql_fetch_assoc($output)){
	$i++;
}
if($i == 0){
	ROCinfo($_POST['modules']);
}

?>

<table>
	<tr>
		<td>
		ROC0
		<textarea cols="20" rows="1" name="ROC0"></textarea> 
		</td>
		<td>
		ROC15
		<textarea cols="20" rows="1" name="ROC15"></textarea> 
		</td>
	</tr>
	<tr>
		<td>
		ROC1
		<textarea cols="20" rows="1" name="ROC1"></textarea> 
		</td>
		<td>
		ROC14
		<textarea cols="20" rows="1" name="ROC14"></textarea> 
		</td>
	</tr>
	<tr>
		<td>
		ROC2
		<textarea cols="20" rows="1" name="ROC2"></textarea> 
		</td>
		<td>
		ROC13
		<textarea cols="20" rows="1" name="ROC13"></textarea> 
		</td>
	</tr>
	<tr>
		<td>
		ROC3
		<textarea cols="20" rows="1" name="ROC3"></textarea> 
		</td>
		<td>
		ROC12
		<textarea cols="20" rows="1" name="ROC12"></textarea> 
		</td>
	</tr>
	<tr>
		<td>
		ROC4
		<textarea cols="20" rows="1" name="ROC4"></textarea> 
		</td>
		<td>
		ROC11
		<textarea cols="20" rows="1" name="ROC11"></textarea> 
		</td>
	</tr>
	<tr>
		<td>
		ROC5
		<textarea cols="20" rows="1" name="ROC5"></textarea> 
		</td>
		<td>
		ROC10
		<textarea cols="20" rows="1" name="ROC10"></textarea> 
		</td>
	</tr>
	<tr>
		<td>
		ROC6
		<textarea cols="20" rows="1" name="ROC6"></textarea> 
		</td>
		<td>
		ROC9
		<textarea cols="20" rows="1" name="ROC9"></textarea> 
		</td>
	</tr>
	<tr>
		<td>
		ROC7
		<textarea cols="20" rows="1" name="ROC7"></textarea> 
		</td>
		<td>
		ROC8
		<textarea cols="20" rows="1" name="ROC8"></textarea> 
		</td>
	</tr>
</table>
<br>
<br>

<?php
}
?>

<br>
<br>

<?php

conditionalSubmit();

if(isset($_POST['submit']) && isset($_POST['ROC0'])){
	
	$j = 0;

	for($j=0;$j<16;$j++){

		$roctag = 'ROC'.$j;
		$func2 = 'UPDATE ROC_p SET name="'.$_POST[$roctag].'" WHERE assoc_module='.$_POST['modules'].' AND position='.$j;

		if(!mysql_query($func2,$connection)){
			echo "An error occurred and the changes have not been added to the database.";
		break;
		}

	}
	echo "Changes added to the database.";
}

?>
</form>

<br>

<form method="link" action="../index.php">
<input type="submit" value="MAIN MENU">
</form>

</body>
</html>

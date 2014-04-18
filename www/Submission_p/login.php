<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01//EN" "http://www.w3.org/TR/html4/strict.dtd">
<html>
<head>
  <meta content="text/html; charset=ISO-8859-1"
 http-equiv="content-type">
  <title>Log In</title>
  <script src="js/sha512.js"></script>
  <script src="js/forms.js"></script>
</head>
<body>
<form action='login.php' method='post' enctype='multipart/form-data'>

<br>
<br>

Username: <input type="text" name="u">
Password: <input type="password" name="p">

<br>
<br>

<input type="button" value="Log In" onclick="formhash(this.form,this.form.p);"/>

<?php
if(isset($_POST['u']) && isset($_POST['p'])){

	include('../../Submission_p_secure_pages/connect.php');

	mysql_query("USE cmsfpix_u", $connection);

	$func = "SELECT password FROM members WHERE username=\"".$_POST['u']."\"";

	$output = mysql_query($func, $connection);

	$row = mysql_fetch_assoc($output);

	if($row['password'] == $_POST['p']){
		session_start();
		$_SESSION['user'] = $_POST['u'];
		echo "<br>";
		echo "You have logged in successfully";
	}
	else{
		echo "<br>";
		echo "Username or password incorrect. Please try again.";
	}
}
?>
</form>

<br>

<form method="link" action="index.php">
<input type="submit" value="MAIN MENU">
</form>

</body>
</html>

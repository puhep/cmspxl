<html>
<head>
<title> SINTEF 2012 6" Submission </title>
<body>
Submission Form for Purdue University Sensor Data
<div style="position:fixed;left:400px;top:2px;">
<form method="link" action="login.php">
<input type="submit" value="LOG IN">
</form>
</div>
<br>
<div2 style="position:fixed;left:400px;top:30px;">
<form method="link" action="logout.php">
<input type="submit" value="LOG OUT">
</form>
</div2>
Pre-Production/Production
<br>
<br>

Assembly Flow Handler
<form action="assembly/status.php" method="post">
  <input name="assembly" value="Assembly Status" type="submit">
  </form>
<br>

Data Viewing
<form action="summary/list.php" method="post">
  <input name="summary" value="Part Summary"
 type="submit"></form>
<br>

New Parts Information
<form action="submit/wafersubmit.php" method="post">
  <input name="wafer" value="Wafer Submit" type="submit">
  </form>

<form action="submit/HDIsubmit.php" method="post">
  <input name="hdi" value="HDI Submit" type="submit">
  </form>

<form action="submit/modulesubmit.php" method="post">
  <input name="module" value="Module Submit" type="submit">
  </form>

<form action="submit/ROCsubmit.php" method="post">
  <input name="ROC" value="ROC Submit" type="submit">
  </form>

<form action="submit/flexsubmit.php" method="post">
  <input name="flex" value="Flex Cable Submit" type="submit">
  </form>

<br>

Testing Data
<form action="submit/meassubmit.php" method="post">
  <input name="meas" value="Measurement Submit" type="submit">
  </form>

<form action="submit/DAQparameters.php" method="post">
  <input name="daq" value="DAQ Parameters Submit" type="submit">
  </form>
<br>

Change/Edit
<form action="submit/newcomment.php" method="post">
  <input name="comment" value="Add Comments to Existing Part" type="submit">
  </form>
<form action="submit/newpic.php" method="post">
  <input name="pic" value="Add Pictures to Existing Part" type="submit">
  </form>
<br>


</body>
</html>

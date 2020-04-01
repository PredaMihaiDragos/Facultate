<?php
require_once 'dbfReader.php';

$file = fopen("ChestionarBase.txt", "r");
$db = fread($file, filesize("ChestionarBase.txt")) or die("Error");
fclose($file);

$r1 = explode(" ", $db, 5);
$r2 = explode(" ", $r1[4], 5);
$r3 = explode(" ", $r2[4], 5);
$r4 = explode(" ", $r3[4], 5);
$r5 = explode(" ", $r4[4], 5);

$r1[0] = intval($r1[0]);
$r1[1] = intval($r1[1]);
$r1[2] = intval($r1[2]);
$r1[3] = intval($r1[3]);

$r2[0] = intval($r2[0]);
$r2[1] = intval($r2[1]);
$r2[2] = intval($r2[2]);
$r2[3] = intval($r2[3]);

$r3[0] = intval($r3[0]);
$r3[1] = intval($r3[1]);
$r3[2] = intval($r3[2]);
$r3[3] = intval($r3[3]);

$r4[0] = intval($r4[0]);
$r4[1] = intval($r4[1]);
$r4[2] = intval($r4[2]);
$r4[3] = intval($r4[3]);

$r5[0] = intval($r5[0]);
$r5[1] = intval($r5[1]);
$r5[2] = intval($r5[2]);
$r5[3] = intval($r5[3]);

if($_POST['r1'] == "fb") $r1[0]++;
else if($_POST['r1'] == "b") $r1[1]++;
else if($_POST['r1'] == "s") $r1[2]++;
else if($_POST['r1'] == "n") $r1[3]++;

if($_POST['r2'] == "fb") $r2[0]++;
else if($_POST['r2'] == "b") $r2[1]++;
else if($_POST['r2'] == "s") $r2[2]++;
else if($_POST['r2'] == "n") $r3[3]++;

if($_POST['r3'] == "fb") $r3[0]++;
else if($_POST['r3'] == "b") $r3[1]++;
else if($_POST['r3'] == "s") $r3[2]++;
else if($_POST['r3'] == "n") $r3[3]++;

if($_POST['r4'] == "fb") $r4[0]++;
else if($_POST['r4'] == "b") $r4[1]++;
else if($_POST['r4'] == "s") $r4[2]++;
else if($_POST['r4'] == "n") $r4[3]++;

if($_POST['r5'] == "fb") $r5[0]++;
else if($_POST['r5'] == "b") $r5[1]++;
else if($_POST['r5'] == "s") $r5[2]++;
else if($_POST['r5'] == "n") $r5[3]++;

$file = fopen("ChestionarBase.txt", "w");

for($i = 0; $i < 4; $i++)
{ fwrite($file, $r1[$i] . " "); }
fwrite($file, "\n");

for($i = 0; $i < 4; $i++)
{	fwrite($file, $r2[$i] . " "); }
fwrite($file, "\n");

for($i = 0; $i < 4; $i++)
{	fwrite($file, $r3[$i] . " "); }
fwrite($file, "\n");

for($i = 0; $i < 4; $i++)
{	fwrite($file, $r4[$i] . " "); }
fwrite($file, "\n");

for($i = 0; $i < 4; $i++)
{	fwrite($file, $r5[$i] . " "); }
fwrite($file, "\n");

fclose($file);
?>
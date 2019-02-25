<?php
 header("Content-type: application/json");
$con = mysql_connect("localhost","root","");

if (!$con) {
  die('Could not connect: ' . mysql_error());
}

mysql_select_db("coba", $con);

$sth = mysql_query("SELECT (UNIX_TIMESTAMP(tanggal)) AS tanggal ,IFNULL(nilai,'null')AS nilai FROM sensor WHERE id=1 ORDER BY tanggal DESC LIMIT 1");
$rows = array();
$rows['name'] = 'Node 1';
while($r = mysql_fetch_array($sth)) {
    $rows['data'][] = $r['tanggal']*1000;
    $rows['data'][] =$r['nilai'];
}

$sth = mysql_query("SELECT (UNIX_TIMESTAMP(tanggal)) AS tanggal ,IFNULL(nilai,'null')AS nilai FROM sensor WHERE id=2 ORDER BY tanggal DESC LIMIT 1");
$rows1 = array();
$rows1['name'] = 'Node 2';
while($rr = mysql_fetch_assoc($sth)) {
    $rows1['data'] []= $rr['tanggal']*1000;
   $rows1['data'] []=$rr['nilai'];
}

$result = array();
array_push($result,$rows);
array_push($result,$rows1);



print json_encode($result, JSON_NUMERIC_CHECK);

mysql_close($con);
?>

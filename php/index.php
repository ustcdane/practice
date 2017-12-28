<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=gbk"/>
<title>PC Bigram Browser</title>
<script language="javascript">
function focus(){
	 document.getElementById("bi_left").focus();
}
</script>
</head>
<body onLoad="focus();">
<center>
</br>
</br>
<p><font size="6">PC Bigram Browser</font><font size="2"> Tool</font></p>

<form action="index.php" method="post">
	<table border="0" width="60%">
		<tr>
			<td><p align="right">版本号:</p></td>
			<td><label>
				<select name="version">
				<option value="20171011" selected="selected">20171011</option>
				<option value="20170706">20170706</option>
				<option value="20170330">20170330</option>
				</select></label> 
			</td>
		</tr>
		<tr>
			<td><p align="right">left:</p></td>
			<td><input type="text" id="bi_left" name="biL"/></td>
		</tr>
	
		<tr>
			<td><p align="right">right:</p></td>
			<td><input type="text" id="bi_right" name="biR"/></td>
		</tr>
		<tr>
		</tr>
		<tr>
			<td></td><td><input type="submit" value="Browse"/></td>
		</tr>
	</table>
</form>
</br>
</center>

<left>
<?php
function convert2utf8( $string )
{
  return iconv("gbk", "utf-8", $string);
}

function convert2gbk( $string )
{
  return iconv('utf-8',"gbk", $string);
}


$ver=$_POST["version"];
$biL = $_POST["biL"];
$biL_gbk = convert2gbk($biL);
$biR = $_POST["biR"];
$biR_gbk = convert2gbk($biR);
if ($biL != "" && $biR != "") {
  echo "version:$ver</br>";
  echo "bigram left: ".$biL."</br>";
  echo "bigram right: ".$biR."</br>";
  echo "-------------------------------------------------</br></br>";
  
  $message=shell_exec("sh search.sh $biL_gbk $biR_gbk $ver");
  echo "<strong>查询结果:</strong><br/>";
  #echo str_replace("\n","</br>",convert2utf8( $message ))."</br></br>";
  echo convert2utf8( $message );
 }else{
  echo "</br></br></br>";
 }
?>
</left>
<hr>
<left>
	  <p><b>说明:</b></p>
	  <p><font size="2">选择指定版本词库并输入左右元词条即可查询二元关系</font></p>
</left>
</body>
</html>

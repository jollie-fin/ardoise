<?php
include 'layout.php';
mysql_connect($mysql_host,$_SERVER['PHP_AUTH_USER'],$_SERVER['PHP_AUTH_PW']);
mysql_select_db($mysql_db);
if(!$_POST['year'])
{
  $_POST['year']=0;
  $_POST['month']=0;
  $_POST['day']=0;
}

$q="SELECT *,YEAR(date_conso) as year FROM consos WHERE date_conso>='".$_POST['year'].'-'.$_POST['month'].'-'.$_POST['day']."'";

if($_POST['pname'] || $_GET['pname'])
{
  if(!$_POST['pname'])
    $_POST['pname']=$_GET['pname'];
  $q=mysql_query($q." AND pname='".$_POST['pname']."' ORDER BY date_conso DESC");
  while($t=mysql_fetch_array($q))
    {
      $table.="<tr><td>".$t['date_conso'].'</td><td>'.$t['pname'].'</td><td><a href="ardoises?login='.$t['login'].'">'.$t['login'].'</a></td></tr>';
    }
  $text="<table><tr><td class='title'>Date</td><td class='title'>Conso</td><td class='title'>Login</td></tr>$table</table>";
}
else
{
  $q=mysql_query($q.' ORDER BY date_conso ASC');
  $firstyear=0;
  $lastyear=0;
  $consos=array();
  $flags=array();
  while($t=mysql_fetch_array($q))
    {
      if($firstyear==0)
	$firstyear=$t['year'];
      if($t['year']>$lastyear)
	$lastyear=$t['year'];
      $q0=mysql_query('select * from produits where pname=\''.$t['pname'].'\'');
      $t0=mysql_fetch_array($q0);
      $flags[$t['pname']]=$t0['flags'];
      if($t0['flags']!='d')
	$bieres++;
      $total++;
      $consos[$t['pname']]++;
    }
  
  
  for($i=1;$i<=31;$i++)
    {$day.="<option value='$i'>$i</option>";}
  for($i=1;$i<=12;$i++)
    {$month.="<option value='$i'>$i</option>";}
  for($i=$firstyear;$i<=$lastyear;$i++)
    {$year.="<option value='$i'>$i</option>";}
  
  $date_form="<select name='day'>$day</select><select name='month'>$month</select><select name='year'>$year</select>";
  
  $text="<form action='consos' method='post'>
<table><tr><td>pname : </td><td><input type='text' name='pname'/></td></tr>
<tr><td>depuis le : </td><td>$date_form</td></table><br/>
<table><tr><td class='title'>pname</td><td class='title'>Consommation</td><td class='title'>Pourcentage</td><td class='title'>Pourcentage des bi&egrave;res</td></tr>
";
  arsort($consos);
  foreach($consos as $key=>$value)
    {
      if($flags[$key]=='d')
	$rapportbieres='';
      else
	$rapportbieres=(((int)($value/$bieres*1000))/10).'%';

      $rapport=((int)($value/$total*1000))/10;
      $text.="<tr><td><a href='consos?pname=$key'>$key</a></td><td>$value</td><td>$rapport%</td><td>$rapportbieres</td></tr>";
    }
  $text.="</table>";


  $i=1;
  $table='';
  $q=("SELECT *,YEAR(date_conso) as year FROM consos WHERE date_conso>='".$_POST['year'].'-'.$_POST['month'].'-'.$_POST['day']."' ORDER BY date_conso DESC");
  $q=mysql_query($q);
  while($t=mysql_fetch_array($q) && $i<=20)
    {
      $table.="<tr><td>".$t['date_conso'].'</td><td>'.$t['pname'].'</td><td><a href="ardoises?login='.$t['login'].'">'.$t['login'].'</a></td></tr>';
      $i++;
    }
  $text.="<table><tr><td class='title'>Date</td><td class='title'>Conso</td><td class='title'>Login</td></tr>$table</table>";
  
}
ecrire("Consos",$text); 
?>

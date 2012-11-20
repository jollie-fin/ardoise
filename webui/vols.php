<?php
include 'layout.php';
mysql_connect($mysql_host,$_SERVER['PHP_AUTH_USER'],$_SERVER['PHP_AUTH_PW']);
mysql_select_db($mysql_db);
if(!$_POST['year'])
{
  if (date('d')>7 or date('n')>1)  
	$_POST['year'] = date('Y'); 
  else 
	{$_POST['year'] = date('Y')-1;}
	;
  if (date(d)>7)  $_POST['month']= date (n); else $_POST['month']= date(n) -1;
  if (date(d)>7)  {$_POST['day'] = date(d)-7;} else {$_POST['day']= 24+ date(d);};
}

$q="SELECT *,YEAR(date_conso) as year FROM consos WHERE date_conso>='".$_POST['year'].'-'.$_POST['month'].'-'.$_POST['day']."'";

$q=mysql_query($q);
$firstyear=0;
$lastyear=0;
$consos=array();
$vol=array();
$flags=array();
$total_gain=0;
$total_perte =0;
$total_somme = 0;
$vol2=0;

while($t=mysql_fetch_array($q))
{
  if($firstyear==0)
    $firstyear=$t['year'];
  if($t['year']>$lastyear)
    $lastyear=$t['year'];
  $q0=mysql_query('select * from produits where pname=\''.$t['pname'].'\'');
  $t0=mysql_fetch_array($q0);
  $flags[$t['pname']]=$t0['flags'];
  $total++;
  $consos[$t['pname']]++;
  if($t['login']=='vol')
	{
    	$vol[$t['pname']]++;
	$total_perte = $total_perte + $t0['prix_achat'];
	}	
elseif($t['login']=='antivol')
	{
	$vol[$t['pname']]--;
	$total_perte = $total_perte - $t0['prix_achat'];
	}
  else
	{
	$total_gain = $total_gain + $t0['price'] - $t0['prix_achat'];
	}

}

$total_somme = $total_gain - $total_perte;


for($i=1;$i<=31;$i++)
{$day.="<option value='$i'>$i</option>";}
for($i=1;$i<=12;$i++)
{$month.="<option value='$i'>$i</option>";}
for($i=$firstyear;$i<=$lastyear;$i++)
{$year.="<option value='$i'>$i</option>";}

$date_form="<select name='day'>$day</select><select name='month'>$month</select><select name='year'>$year</select>";

$text="<form action='vols' method='post'>
<table><tr><td>pname : </td><td><input type='text' name='pname'/></td></tr>
<tr><td>Depuis le : </td><td>$date_form</td></table><br/><input type='submit' value='Ok'/></form>
<table><tr><td class='title'>pname</td><td class='title'>Vols</td><td class='title'>Pourcentage</td></tr>
";
arsort($vol);
foreach($vol as $key=>$value)
{
  $rapport=((int)($value/$consos[$key]*1000))/10;
  $text.="<tr><td><a href='vols?pname=$key'>$key</a></td><td>$value</td><td>$rapport%</td></tr>";
}
$text.="</table>";
echo "_ _ _ pertes _ ".$total_perte;
echo "_ _ _ gains _ ".$total_gain;
echo "_ _ _ somme _ ".$total_somme;
ecrire("Calcul des vols",$text); 
?>

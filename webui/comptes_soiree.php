<?php
include 'layout_norules.php';
mysql_connect('localhost', $_SERVER['PHP_AUTH_USER'], $_SERVER['PHP_AUTH_PW']);
mysql_select_db($mysql_db);

if($_POST['submit'])
{
  $soiree=$_POST['soiree'];
  $ardoise=mysql_query("SELECT *,SUBSTRING(login,2) AS ordering FROM persons ORDER BY ordering ASC");
  $total=0;
  while($t=mysql_fetch_array($ardoise))
    {
      $login=$t['login'];
      $money=str_replace(',','.',$_POST[$t['login']]);
      $total+=$money;
      mysql_query("INSERT INTO soiree_tmp(soiree,login,money) VALUES('$soiree','$login',$money)");
    }
  $text="Votre soiree a ete prise en compte.<br/>Total des recettes : $total";
}
else{
$ardoise=mysql_query("SELECT *,SUBSTRING(login,2) AS ordering FROM persons ORDER BY ordering ASC");
while($t=mysql_fetch_array($ardoise))
{
  $login=$t['login'];
  $table.="<tr><td>$login</td><td>".$t['fullname'].
    "</td><td><input type='text' name='$login'/></td></tr>";
}
$text.="<form action='comptes_soiree.php' method='post'>
Nom de la soiree : <input type='text' name='soiree'/><br/>
<table><tr><td class='title'>Login</td><td class='title'>Nom complet</td><td class='title'>Ardoise</td></tr>";
$text.=$table."</table><br/><input type='submit' name='submit' value='ok'/></form>".
"<br/><br/>Total : $total<br/>Total positif : $positif<br/>";
}

ecrire("Ardoises de soiree", $text);
?>

<?php
include 'layout.php';
mysql_connect('localhost', $_SERVER['PHP_AUTH_USER'], $_SERVER['PHP_AUTH_PW']);
mysql_select_db($mysql_db);

if($_POST['submit'])
{
  $soiree=$_POST['soiree'];
  $ardoise=mysql_query("SELECT *,SUBSTRING(login,2) AS ordering FROM soiree_tmp ORDER BY ordering ASC");
  while($t=mysql_fetch_array($ardoise))
    {
      $login=$t['login'];
      $id=$t['id'];
      $soiree=$t['soiree'];
      $money=str_replace(',','.',$t['money']);
      mysql_query("INSERT INTO soirees(date_soiree,nom_soiree,login,debit) VALUES(CURDATE(),'$soiree','$login',$money)");
      mysql_query("UPDATE persons set money=money+$money where login='$login'");
      mysql_query("DELETE FROM soiree_tmp WHERE id=$id"); 
    }
  if($del=$_GET['del'])
    mysql_query("DELETE FROM soiree_tmp WHERE id=$del");
}
else
{     
$ardoise=mysql_query("SELECT *,SUBSTRING(login,2) AS ordering FROM soiree_tmp ORDER BY ordering ASC");
while($t=mysql_fetch_array($ardoise))
{
  $login=$t['login'];
  $id=$t['id'];
  $money=$t['money'];
  $table.="<tr><td><a href='comptes_soiree_admin.php?del=$id'>Supprimer</a></td><td>$login</td><td>$soiree</td><td>$money</td></tr>";
}
if($table)
{
$text.="<form action='comptes_soiree_admin' method='post'>
<table><tr><td></td><td class='title'>Login</td><td class='title'>Ardoise</td></tr>";
$text.=$table."</table><br/><input type='submit' name='submit' value='ok'/></form>";
}
else
$text='Pas de soiree';
}
ecrire("Ardoises", $text);
?>

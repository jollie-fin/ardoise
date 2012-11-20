<?php
include 'layout.php';
mysql_connect('localhost', $_SERVER['PHP_AUTH_USER'], $_SERVER['PHP_AUTH_PW']);
mysql_select_db($mysql_db);


//// Gestions des modifications de la base ////

if($login=$_GET['del'])
  mysql_query("DELETE FROM persons WHERE login='$login'");
if($login=$_GET['arch'])
  {
    $q=mysql_query("SELECT * FROM persons WHERE login='$login'");
    if($t=mysql_fetch_array($q))
      {
	$money=$t['money'];
	$fullname=$t['fullname'];
	$promo=$t['infos'];
	$email=$t['email'];
	mysql_query("DELETE FROM persons WHERE login='$login'");
	mysql_query("INSERT INTO persons_inactive(money,fullname,login,infos,email) VALUES($money,'$fullname','$login','$promo','$email')");
      }
  }
if($login=$_GET['unarch'])
  {
    $q=mysql_query("SELECT * FROM persons_inactive WHERE login='$login'");
    if($t=mysql_fetch_array($q))
      {
	$money=$t['money'];
	$fullname=$t['fullname'];
	$promo=$t['infos'];
	$email=$t['email'];
	mysql_query("DELETE FROM persons_inactive WHERE login='$login'");
	mysql_query("INSERT INTO persons(money,fullname,login,infos,email) "
		    ."VALUES($money,'$fullname','$login','$promo','$email')");
      }
  }



if($_GET['showarch'])
  $table_db='persons_inactive';
 else
   $table_db='persons';


//// Ecriture d'une personne ////
//// Avec ses 10 dernieres consos ///
if($_POST['login']|| $_GET['login'])
  {
    if(!$login=$_POST['login'])
      $login=$_GET['login'];
    $ardoise=mysql_query("SELECT * FROM $table_db WHERE login='$login'");
    $consos=mysql_query("SELECT * FROM consos WHERE login='$login' ORDER BY date_conso DESC");
    while($t=mysql_fetch_array($ardoise))
      {
	$table.="<tr><td>".$t['login']."</td><td>".$t['fullname'].
	  "</td><td>".$t['money']."</td></tr>";
      }
    $text.="<table><tr><td class='title'>Login</td><td class='title'>Nom complet</td><td class='title'>Ardoise</td></tr>";
    $text.=$table."</table>";
    $i=0;
    while(($login=='vol' || $i<10) && $t=mysql_fetch_array($consos))
      {
	$table_consos.="<tr><td>".$t['date_conso']
	  ."</td><td><a href='consos?pname=".$t['pname']
	  ."'>".$t['pname']."</a></td></tr>";
	$i++;
      }
    $text.="<table><tr><td class='title'>Date</td><td class='title'>Code</td></tr>";
    $text.=$table_consos."</table><br/>"
      ."<img src='images/arrow.jpg'/><a href='ardoises?$add"."del=$login'>Supprimer</a><br/>";
    if(!$_GET['showarch'])
      $text.="<img src='images/arrow.jpg'/><a href='ardoises?$add"."arch=$login'>Archiver</a><br/>";
    else
      $text.="<img src='images/arrow.jpg'/><a href='ardoises?$add"."unarch=$login'>D&eacute;sarchiver</a><br/>";
  }


//// Ecriture de toute la base ////


else
{
  if(!$_GET['showarch'])
    $text="<img src='images/arrow.jpg'/><a href='ardoises?showarch=1'>Voir les archives</a>";
  else
    $text="<img src='images/arrow.jpg'/><a href='ardoises'>Voir la table active</a>";
  $ardoise=mysql_query("SELECT * FROM $table_db ORDER BY money DESC");
  $id=0;
  while($t=mysql_fetch_array($ardoise))
    {
      if($_POST["email".$t['login']])
	{
	  mysql_query("UPDATE persons set email='".str_replace("'","\\'",$_POST["email".$t['login']])
		      ."' WHERE login='".$t['login']."'");
	  $t['email']=str_replace("'","\\'",$_POST["email".$t['login']]);
	}
      if($table_db=='persons_inactive')
	$add='showarch=1&';
      else
	$add='';
      $table.="<tr><td><a href='ardoises?$add"."login=".$t['login']."'>".$t['login']."</a></td><td>".$t['fullname'].
	"</td><td>".$t['money']."</td>".
	"<td><input type='text' name='email".$t['login']."' value='".$t['email']."'></tr>";
      $id++;
      if($t['money']>0)
	$positif+=$t['money'];
      $total+=$t['money'];
    }
  $text.="<form action='ardoises.php' method='post'><table><tr><td class='title'>Login</td><td class='title'>Nom complet</td><td class='title'>Ardoise</td><td class='title'>Email</td></tr>";
  $text.=$table."</table><input type=hidden name='id' value='$id'/><input type='submit' value='ok'/></form>".
    "<br/><br/>Total : $total<br/>Total positif : $positif<br/>";
}
ecrire("Ardoises", $text);
?>

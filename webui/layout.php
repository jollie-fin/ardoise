<?php
include "db.php";

function ecrire_global($title, $text,$style)
{
  if(!$style)
    $style='style.css';
  echo "<!DOCTYPE html PUBLIC '-//W3C//DTD XHTML 1.0 Transitional//EN' 'http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd'>
<html xmlns='http://www.w3.org/1999/xhtml'>
<head>
<title>Sobolef - $title$site_user</title>
<meta http-equiv='Content-Type' content='text/html; charset=utf-8' />
<meta http-equiv='Content-Language' content='fr' />
<style type='text/css' media='all'>@import 'images/$style';</style>
</head>

<body>
<div class='content'>
<div id='toph'></div>
<div id='header'>
<div class='rside'>
<div class='citation'>
<h2>$title</h2>
</div>
</div>
<div class='lside'>
<div class='title'><h2>SOBOLEF</h2></div>
</div>
</div>
<div id='main'>
<div class='center'>
$text
</div>

<div class='leftmenu'>
<div class='nav'>
<ul>
<li><a href='index'>D&eacute;but</a></li>
<li><a href='ardoises'>Ardoises</a></li>
<li><a href='consos'>Consos</a></li>
<li><a href='produits'>Produits</a></li>
<li><a href='vols'>Vols</a></li>
<li><a href='consignes'>Consignes</a></li>
<li><a href='commandes'>Commandes</a></li>
<li><a href='soirees'>Soir&eacute;es</a></li>
<li><a href='finances'>Finances</a></li>
<li><a href='reserve'>R&eacute;serve</a></li>
<li><a href='wallpaper'>Changer le fond d'écran</a></li>
</ul>
</div>
<div class='padding'>
<h2>Vite, une ardoise</h2>
<form action='ardoises.php' method='post'>
<div class='search'>			
<input type='text' value='' name='login' class='text' />
<input type='submit' value='Go' class='searchbutton' /><br />
</div>
</form>
<br/>
<hr/>
</div>

</div>
</div>
<br />&nbsp;<br />
<div id='footer'>2007 - pe $site_user
</div>
</div>
</body>
</html>";
}

function ecrire($title, $text)
{
  if(!isset($_SERVER['PHP_AUTH_USER']) || !isset($_SERVER['PHP_AUTH_PW']))
    {
      header('WWW-Authenticate: Basic realm="Authentification"');
      header('HTTP/1.0 401 Unauthorized');
      $_SERVER['PHP_AUTH_USER']=$_SERVER['PHP_AUTH_USER'];
      $mysql_pw=$_SERVER['PHP_AUTH_PW'];
    } 
  else
    ecrire_global($title, $text,"style.css");
}
function ecrire_brut($title, $text)
{
  if(!isset($_SERVER['PHP_AUTH_USER']) || !isset($_SERVER['PHP_AUTH_PW']))
    {
      header('WWW-Authenticate: Basic realm="Authentification"');
      header('HTTP/1.0 401 Unauthorized');
      $_SERVER['PHP_AUTH_USER']=$_SERVER['PHP_AUTH_USER'];
      $mysql_pw=$_SERVER['PHP_AUTH_PW'];
    } 
  else
    ecrire_global($title, $text,"style_raw.css");
}
?>

<?php
include "db.php";
function ecrire_global($title, $text,$style)
{
  if(!$style)
    $style='style.css';
  echo "<!DOCTYPE html PUBLIC '-//W3C//DTD XHTML 1.0 Transitional//EN' 'http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd'>
<html>
<head>
<title>Sobolef - $title$site_user</title>
<meta http-equiv='Content-Type' content='text/html; charset=iso-8859-1' />
<meta http-equiv='Content-Language' content='en-us' />
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
  ecrire_global($title, $text,"style.css");
}

function ecrire_brut($title, $text)
{
    ecrire_global($title, $text,"style_raw.css");
}
?>

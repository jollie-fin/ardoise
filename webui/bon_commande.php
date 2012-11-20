<?php
include 'layout.php';
mysql_connect('localhost', $_SERVER['PHP_AUTH_USER'], $_SERVER['PHP_AUTH_PW']);
mysql_select_db($mysql_db);

if($_POST['submit'])
{
  header("Content-type:application/tex");
  $lasti=$_POST['i'];
  for($i=0;$i<=$lasti;$i++)
    {
      if($_POST["commande$i"]>0)
	{
	  if($_POST["gratuite$i"]>0)
	    {
	      $commande=$_POST["commande$i"]."+".$_POST["gratuite$i"];
	      $gratuite=$_POST["gratuite$i"];
	    }
	  else
	    {
	      $commande=$_POST["commande$i"];
	      $gratuite=0;
	    }
	  $table.=$_POST["ref$i"].'&'.$_POST["nom$i"].'&'.$_POST["unite$i"]."&$commande\\\\\\hline\n";
	  $id=$_POST["id$i"];
	  $q=mysql_query("SELECT * FROM ref WHERE id=$id");
	  if($id && mysql_fetch_array($q))
	      mysql_query("UPDATE ref SET ref=".$_POST["ref$i"].", nom='".
			  $_POST["nom$i"]."', prix=".$_POST["prix$i"].
			  ", pname='".$_POST["pname$i"].",unite=".$_POST["unite$i"]." WHERE id=$id");
	  else
	  {
	  	if(!$_POST["prix$i"])
			$_POST["prix$i"]=0;
		if(!$_POST["ref$i"])
			$_POST["ref$i"]=0;
		if(!$_POST["unite$i"])
			$_POST["unite$i"]=24;
	      mysql_query("INSERT INTO ref(ref,nom,prix,pname,unite) VALUES(".$_POST["ref$i"].
			  ",'".$_POST["nom$i"]."',".$_POST["prix$i"].",'".$_POST["pname$i"]."',".
			  $_POST["unite$i"].')');
	}
$q="INSERT INTO bon_commande(date,ref,nom,commande,gratuite,pname) VALUES(CURDATE(),".
	    $_POST["ref$i"].",'".$_POST["nom$i"]."',".$_POST["commande$i"].",$gratuite,'".$_POST["pname$i"]."')";
	  mysql_query($q);
	  //echo $q;
	}
    }
  include 'commande_headers.tex';
  echo $table;
  include 'commande_footer.tex';
}
else
{
  $q=mysql_query("SELECT * FROM ref");
  $i=0;
  $lasti=$_POST['i'];
  // Si le nouveau produit n'a pas de nom, on ne le rajoute pas
  if($_POST["nom".($lasti-1)]=='')
    $lasti--;
  $last=0;
  // Cette boucle doit tenir compte des champs donnes dans $_POST
  while(($t=mysql_fetch_array($q)) || (!$t && $last==0) || ($last && $i<=$lasti))
    {
      if(!$t) // Pour la nouvelle entree
	{$last=1;$ref='';$commande='';$gratuite='';$nom='';$prix='';$pname='';$unite='';$ref='';}

      $commande=$_POST["commande$i"];
      $gratuite=$_POST["gratuite$i"];
      //////
      if($_POST["ref$i"])
	$ref=$_POST["ref$i"];
      elseif($t['ref'])
	$ref=$t['ref'];
      else
	$ref='';

      $ref="<input type='text' size='8' name='ref$i' value='$ref'/>";
      //////
      if($_POST["nom$i"])
	$nom=$_POST["nom$i"];
      elseif($t['nom'])
	$nom=$t['nom'];
      //////
      if($_POST["unite$i"])
	$unite=$_POST["unite$i"];
      elseif($t['unite'])
	$unite=$t['unite'];
      //////
      if($_POST["prix$i"])
	$prix=$_POST["prix$i"];
      elseif($t['prix'])
	$prix=$t['prix'];
      //////
      $pname=$_POST["pname$i"];
      //////
      if($t)
	$id=$t['id'];
      else
	$id='';
      $table.="<tr><td>$ref<input type='hidden' name='id$i' value='$id'/></td>".
	"<td><input type='text' name='nom$i' value='".$nom."'/></td>".
	"<td><input type='text' size='3' name='unite$i' value='".$unite."'/></td>".
	"<td><input type='text' size='5' name='prix$i' value='".$prix."'/></td>".
	"<td><input type='text' size='4' name='commande$i' value='".$commande."'/></td>".
	"<td><input type='text' size='4' name='gratuite$i' value='".$gratuite."'/></td>".
	"<td><input type='text' size='15' name='pname$i' value='".$pname."'/></td></tr>";
      $i++;
    }
  $q=mysql_query("SELECT * FROM reception_commande ORDER BY date DESC");
  $t=mysql_fetch_array($q);
  $date=$t['date'];
  $text="<h2>Derniere commande</h2>$date</br><br/><br/><h2>Bon de commande</h2><br/>".
    "<form action='bon_commande' method='post'>".
    "<table><tr><td class='title'>Reference</td><td class='title'>Nom</td>".
    "<td class='title'>Caisse</td><td class='title'>Prix</td><td class='title'>Commande</td>".
    "<td class='title'>Gratuit&eacute;</td><td class='title'>Nom dans sobolef</td></tr>$table</table>".
    "<input type='hidden' name='i' value='$i'/>".
    "<input type='submit' value='ok'/>".
    "<input type='submit' name='submit' value='Envoyer'/></form>";
  
  ecrire_brut('Bon de commande',$text,'style_raw.css'); 
}
?>

<?php
include 'layout.php';
mysql_connect('localhost', $_SERVER['PHP_AUTH_USER'], $_SERVER['PHP_AUTH_PW']);
mysql_select_db($mysql_db);

if($_POST['submit'])
{
  for($i=0;$i<$_POST['i'];$i++)
    {
      $pname=$_POST["pname$i"];
      $q=mysql_query("select unite from ref where pname='$pname'");
      $t=mysql_fetch_array($q);
      $commande=$_POST["commande$i"]*$t['unite'];
      mysql_query("INSERT INTO reception_commande(date,pname,commande) VALUES(CURDATE(),'".$_POST["pname$i"]."',$commande)");
    }
  for($j=0;$j<$_POST['j'];$j++)
    mysql_query("INSERT INTO consignes_commande(date,nom,number) VALUES(CURDATE(),'".$_POST["nomconsigne$j"]."',".$_POST["consigne$j"].")");
  
  mysql_query("INSERT INTO finances(date,nom,valeur,source) VALUES(NOW(),'Commande', -".$_POST['finances'].",'compte')");
  $text="R&eacute;ception enregistr&eacute;e.";
  mysql_query("DELETE FROM bon_commande");
}
else
{
  $q=mysql_query("SELECT * FROM bon_commande");
  if($t=mysql_fetch_array($q))
    {

      // Reception
      $q=mysql_query("SELECT * FROM bon_commande");
      $i=0;
      while($t=mysql_fetch_array($q))
	{
	  $nom=$t['nom'];
	  $commande=$t['commande']+$t['gratuite'];
	  $pname=$t['pname'];
	  $table.="<tr><td>$nom<input type='hidden' name='pname$i' value='$pname'/></td><td><input type='text' name='commande$i' size='4' value='$commande'/></td></tr>";
	  $i++;
	}
      // Ecriture de la table de consignes
      $q=mysql_query("SELECT * FROM consignes");
      $j=0;
      while($t=mysql_fetch_array($q))
	{
	  $nom=$t['nom'];
	  $table_consignes.="<tr><td>$nom<input type='hidden' name='nomconsigne$j'/></td><td><input type='text' name='consigne$j' size='4'/></td></tr>";
	  $j++;
	}
      
      $text="<form action='reception_commande' method='post'>
<h2>Reception</h2>
<table>$table</table><br/>
<h2>Consignes</h2>
<table>$table_consignes</table><br/>
<h2>Finances</h2>
Montant pour le compte du foyer : <input type='text' name='finances'/>
<br/><br/>
<input type='hidden' name='i' value='$i'/>
<input type='hidden' name='j' value='$j'/>
<input type='submit' value='ok' name='submit'/></form>
";
    }
  else
    $text="Pas de commande en cours.";
  
}

ecrire("Receptionner une commande", $text);
?>

<?php
include 'layout.php';
mysql_connect('localhost', $_SERVER['PHP_AUTH_USER'], $_SERVER['PHP_AUTH_PW']);
mysql_select_db($mysql_db);

if($_POST['caisse'])
     mysql_query("INSERT INTO finances(date,nom,valeur,source) VALUES
(NOW(),'Transfert de caisse',".$_POST['caisse'].",'compte')");

if($_POST['montant'] && $_POST['nom'])
{
  if($_POST['nom']=='Transfert de caisse')
    $_POST['nom']='Transfert de caisse - manuel';
  mysql_query("INSERT INTO finances(date,nom,valeur,source) VALUES
(NOW(),'".$_POST['nom']."',".$_POST['montant'].",'caisse')");
}
if($_POST['montant_facture'] && $_POST['nom_facture'])
{
  if($_POST['nom']=='Transfert de caisse')
    $_POST['nom']='Transfert de caisse - manuel';
  mysql_query("INSERT INTO finances(date,nom,valeur,source) VALUES
(NOW(),'".$_POST['nom_facture']."', -".$_POST['montant_facture'].",'compte')");
}

if($id=$_GET['del'])
     mysql_query("DELETE FROM finances WHERE id=$id");
$q=mysql_query("SELECT *,date_format(date,'%e-%m-%Y') as date_simple FROM finances");
$date='0-0-0';
$total_credits=0;
$total_liquide=0;
while($t=mysql_fetch_array($q))
{
  $caisse='';
  $montant=$t['valeur'];
  $nom=$t['nom'];
  $source=$t['source'];
  if($nom=='Transfert de caisse')
    {
      $q_credits=mysql_query("SELECT * FROM credits WHERE date>='$date' AND date<='".$t['date']."'");
      $credits=0;
      while($t_credits=mysql_fetch_array($q_credits))
	{
	  $credits+=$t_credits['valeur'];
	}
      $date=$t['date'];
      $total_credits+=$credits;
      $liquide=$montant-$credits;
      $total_liquide+=$liquide;
    }
  else
    {
      $credits='';
      $liquide='';
    }
  if($montant>0 && $source=='compte')
    {
      $recettes=$montant;
      $depenses='';
      $total+=$montant;
      $total_recettes+=$montant;
    }
  elseif ($source=='compte')
    {
      $depenses=-$montant;
      $recettes='';
      $total+=$montant;
      $total_depenses-=$montant;
    }
  else
    {
      $caisse=$montant;
      $depenses='';
      $recettes='';
      $total_caisse+=$montant;
    }
  $id=$t['id'];
  $table.="<tr><td><a href='finances.php?del=$id'><img src='images/arrow.gif' alt='' border='0'/></a></td>
<td>".$t['date_simple']."</td><td>$nom</td><td>$recettes</td><td>$depenses</td><td>$caisse</td><td>$credits</td><td>$liquide</td></tr>";
}
if($total>=0)
     $positif='positif';
     else
     $positif='negatif';
$text="<form action='finances.php' method='post'>
<h2>Vider la caisse</h2>
Montant : <input type='text' name='caisse'/>
<h2>Operations sur la caisse</h2>
<table><tr>
<td>Nom : </td><td><input type='text' name='nom'/></td></tr>
<tr><td>Montant : </td><td><input type='text' name='montant'/></td></tr>
</table>
<h2>Autres factures</h2>
<table><tr>
<td>Nom : </td><td><input type='text' name='nom_facture'/></td></tr>
<tr><td>Montant : </td><td><input type='text' name='montant_facture'/></td></tr>
</table>
<h2>Bilan financier</h2>
<table><tr>
<td class='title'></td>
<td class='title'>Date</td>
<td class='title'>Op&eacute;ration</td>
<td class='title'>Recettes</td><td class='title'>D&eacute;penses</td>
<td class='title'>Caisse</td>
<td class='title'>Credits</td>
<td class='title'>Liquide</td></tr>
$table
<tr><td></td><td></td><td class='title'>Total</td>
<td class='title'>$total_recettes</td>
<td class='title'>$total_depenses</td><td class='title'>$total_caisse</td></tr>
<tr><td></td><td></td><td class='title'>Total cumule</td>
<td class='$positif'>$total</td><td></td><td></td><td>$total_credits</td><td>$total_liquide</td></tr>
</table>
<input type='submit' value='ok'/>
</form>
";

ecrire("Finances",$text); 
?>

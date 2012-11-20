<?php
include 'layout.php';
mysql_connect($mysql_host,$_SERVER['PHP_AUTH_USER'],$_SERVER['PHP_AUTH_PW']);
mysql_select_db($mysql_db);


//// Difference commande - consommation ////
$q=mysql_query("SELECT * FROM consos");
$produits=array();
while($t=mysql_fetch_array($q))
{
  if(!isset($produits[$t['pname']]))
    $produits[$t['pname']]=0;

  if($t['login']=='antivol')
    $produits[$t['pname']]++;
  else
    $produits[$t['pname']]--;
}
$q=mysql_query("SELECT * FROM reception_commande");
while($t=mysql_fetch_array($q))
{
  $produits[$t['pname']]+=$t['commande'];
}

//// Prise en compte des entrees des formulaires ////
if($_POST['submit']) // Compter les vols
{
  $q=mysql_query("SELECT * FROM produits WHERE NOT outdated");
  while($t=mysql_fetch_array($q))
    {
      $id=$t['id'];
      $pname=$t['pname'];
      while($_POST["n$id"]<$produits[$pname])
	{
	  // On commence par supprimer des vols
	  $q0=mysql_query("SELECT * FROM consos WHERE login='antivol' AND pname='$pname'");
	  if($t0=mysql_fetch_array($q0))
	    {
	      $id0=$t0['IDconso'];
	      mysql_query("DELETE FROM consos WHERE id=$id0");
	    }
	  else // Puis on rajoute des anti-consos quand il n'y a plus de vols
	    {mysql_query("INSERT INTO consos(date_conso,login,pname) VALUES(CURDATE(),'vol','$pname')");}
	  $produits[$pname]--;
	}
      while($_POST["n$id"]>$produits[$pname])
	{
	  // On commence par supprimer des vols
	  $q0=mysql_query("SELECT * FROM consos WHERE login='vol' AND pname='$pname'");
	  if($t0=mysql_fetch_array($q0))
	    {
	      $id0=$t0['IDconso'];
	      mysql_query("DELETE FROM consos WHERE id=$id0");
	    }
	  else // Puis on rajoute des anti-consos quand il n'y a plus de vols
	    {mysql_query("INSERT INTO consos(date_conso,login,pname) VALUES(CURDATE(),'antivol','$pname')");}
	  $produits[$pname]++;
	}
    }
}

if($_POST['init']) // Initialiser la base en comptant la reserve comme des commandes
{
  $q=mysql_query("SELECT * FROM produits");
  while($t=mysql_fetch_array($q))
    {
      $id=$t['id'];
      $pname=$t['pname'];
      if($_POST["n$id"]!=$produits[$pname])
	{
	  $commande=$_POST["n$id"]-$produits[$pname];
	  mysql_query("INSERT INTO reception_commande(date,commande,pname) VALUES(CURDATE(),$commande,'$pname')");
	  $produits[$pname]+=$commande;
	}
    }
}

//// Ecriture de la table ////
$q=mysql_query("SELECT * FROM produits ORDER BY flags,product_name ASC");
while($t=mysql_fetch_array($q))
{
  $pname=$t['pname'];
  $product_name=$t['product_name'];
  $id=$t['id'];
  $outdated=$t['outdated'];
  $n=$produits[$pname];
  // Calcul du coût
  $q_cout=mysql_query("SELECT price FROM produits WHERE pname='$pname'");
  if($t_cout=mysql_fetch_array($q_cout))
    {
      $realprice=$t_cout['price'];
      $value=$n*$realprice;
      $total+=$value;
    }
  else
    $value=0;
  if ($outdated)
  {
    $disabled='disabled="disabled"';
  }
  else
  {
    $disabled='';
  }
  // Affichage
  $table.="<tr><td>$product_name</td><td><a href='consos?pname=$pname'>$pname</a></td><td><input type='text' name='n$id' value='$n' size='5' $disabled/></td><td align='right'>$value</td></tr>";
}
$text="
<form action='reserve' method='post'>
  <table>
    <tr>
      <td class='title'>Nom</td>
      <td class='title'>Code</td>
      <td class='title'>R&eacute;serve</td>
      <td class='title'>Prix</td>
    </tr>
      $table
    <tr>
      <td class='title'>Total</td>
      <td></td>
      <td class='title'>$total</td>
    </tr>
  </table>
  <input type='submit' name='submit' value='OK'/><input type='submit' name='init' value='Initialiser'/>
</form>";

ecrire("R&eacute;serve",$text); 
?>

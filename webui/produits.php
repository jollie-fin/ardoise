<?php
include 'layout.php';
mysql_connect($mysql_host,$_SERVER['PHP_AUTH_USER'],$_SERVER['PHP_AUTH_PW']);
mysql_select_db($mysql_db);


if($_POST['submit']) // Mettre le flag outdated des produits à jour.
{
  $q=mysql_query("SELECT * FROM produits");
  while($t=mysql_fetch_array($q))
    {
	
       $pname=$t['pname'];
	  $newvalue=$_POST["obs_$pname"];
	$nouv_prix_achat = $_POST["prix_achat_$pname"];
	$nouv_prix_vente = $_POST["prix_vente_$pname"];
      if (!isset($newvalue)) { $value=0; } else { $value=1; }
      mysql_query("UPDATE produits SET 
	prix_achat='$nouv_prix_achat', outdated='$newvalue' WHERE pname='$pname'");
    }
}

$q=mysql_query("SELECT * FROM produits ORDER BY flags,product_name ASC");
while($t=mysql_fetch_array($q))
{
  $pname=$t['pname'];
  $product_name=$t['product_name'];
  if ($t['outdated'])
  { $checked='checked="checked"'; }
  else
  { $checked = ""; }
  $id=$t['id'];
  $n=$produits[$pname];
  $q_cout=mysql_query("SELECT * FROM produits WHERE pname='$pname'");
  $t_cout=mysql_fetch_array($q_cout);
  $price=$t_cout['price'];
  $prix_achat = $t_cout['prix_achat'];
	echo $prix_achat;
  // Affichage
  $table.="
	<tr>
		<td>$product_name</td>
		<td><a href='consos?pname=$pname'>$pname</a></td>
		<td>$price</td>
		<td align='center'><input type='checkbox' name='obs_$pname' value='yes' $checked/></td>
		<td> <input type='text' size='4' name ='prix_vente_$pname' value='$price' /></td>
		<td> <input type='text' size='4' name ='prix_achat_$pname' value='$prix_achat' /> </td>
	</tr>";
}

$text="
<form action='produits' method='post'>
  <table>
    <tr>
      <td class='title'>Nom</td>
      <td class='title'>Code</td>
      <td class='title'>Prix</td>
      <td class='title'>Plus en vente</td>
	<td class='title'>Prix vente</td>
	<td class= 'title'>Prix achat</td>
    </tr>
      $table
  </table>
  <input type='submit' name='submit' value='OK'/>
</form>";

ecrire("Produits", $text);

?>
<?php
include 'layout.php';

$dir='wallpapers/';
$listcmd='ls -1 '.$dir .' | grep -E \'\.jpg\>\'';
$scancmd="cat $dir/display";
exec($listcmd, $files);
exec($scancmd, $displayed);

if ($_POST['submit'])
{
  if (move_uploaded_file($_FILES['file']['tmp_name'],$dir.$_FILES['file']['name']))
  {
    $text="OK\n";
  }
  else
  {
    //File has passed all validation, copy it to the final destination and remove the temporary file:
    $text="Une erreur est survenue, recommencez\n";
  }
}

foreach($files as $pic)
{
  $basename=ereg_replace('.jpg', '', $pic);
  if ($_POST["del$basename"])
  {
    $delcmd="rm -f $dir/$pic";
    exec($delcmd);
  }
}

if ($_POST["apply"])
{
  $clrcmd="echo '' > $dir/display";
  exec($clrcmd);
  foreach($files as $pic)
  {
    $basename=ereg_replace('.jpg', '', $pic);
    $addcmd="echo $pic >> $dir/display";
    if ($_POST["disp$basename"]) { exec($addcmd); }
  }
}

unset($files);
unset($displayed);
exec($listcmd, $files);
exec($scancmd, $displayed);

{
  foreach($files as $pic)
  {
    $basename=ereg_replace('.jpg', '', $pic);
    if (in_array($pic, $displayed)) { $checked="checked='checked'"; }
    else { $checked=""; }
    $table.="
    <tr>
      <td>
        $pic
      </td>
      <td align='center'>
        <a href='$dir/$pic'>
          <img height='100px' alt='$pic' src='$dir/$pic'/>
        </a>
      </td>
      <td align='center'>
        <input type='checkbox' name='disp$basename' value='yes' $checked/>
      </td>
      <td align='center'>
        <form action='wallpaper' method='post'>
          <input type='submit' name='del$basename' value='Supprimer'/>
        </form>
      </td>
    </tr>";
  }
  $text.="
  <form action='wallpaper.php' method='post' enctype='multipart/form-data'>
    <table width='100%'>
      <tr>
        <td class='title'>Nom</td>
        <td class='title' align='center'>Aperçu</td>
        <td class='title' align='center'>Afficher</td>
        <td class='title' align='center'>Supprimer</td>
      </tr>
        $table
    </table>
    <input type='submit' name='apply' value='Appliquer'/>
    <br/>
    <br/>
    <hr/>
    Ajouter un fond d'écran :<br/><br/>
    <input type='file' name='file'/>
    <input type='submit' name='submit' value='Envoyer'/>
    <hr/>
  </form>";
}

ecrire("Fonds d'&eacute;cran",$text); 
?>

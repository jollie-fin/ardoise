<?php
include 'layout.php';
mysql_connect('localhost', $_SERVER['PHP_AUTH_USER'], $_SERVER['PHP_AUTH_PW']);
mysql_select_db($mysql_db);
header("Content-disposition: attachment; filename=ardoise.tex");
header("Content-type:application/tex");
$size='70pt';
$maxi=60;
$text='\documentclass{article}
\usepackage[left=20pt,right=20pt,top=20pt,bottom=20pt]{geometry}
\begin{document}
\begin{tabular}{|l|l|l|l|l|l|}\hline';

$ardoise=mysql_query("SELECT *,SUBSTRING(login,2) AS ordering FROM persons ORDER BY ordering ASC");
while($t=mysql_fetch_array($ardoise))
{
  $a=strtotime($t['derniere_positivite']);
  $b=time()-345600;
  $c=$a-$b;
  if($c>0 || $t['money']<=0)
  {
  if($i>=$maxi)
    {
      $text.='\end{tabular}
\clearpage
\begin{tabular}{|l|l|l|l|l|l|}\hline';
      $i=0;
    }
  if($t['money']>5)
    $positif='++';
  else if ($t['money']>0)
    $positif='+';
  else
    $positif='';

  if($_GET['solde'])
    $solde=$t['money'];
  else
    $solde='';

  
$text.=$solde.'&'.$positif.'&'.$t['login'].'&\hspace*{'.$size.'}&\hspace*{'.$size.'}&\hspace*{'.$size.'}\\\\\hline'."\n";
  $i++;
  }
}
echo $text.'
\end{tabular}
\end{document}'
?>

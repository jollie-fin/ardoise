<?php
include 'layout.php';
mysql_connect('localhost', 'foyer','XXXX');
mysql_select_db($mysql_db);
header("Content-disposition: attachment; filename=ardoise.tex"); 
header("Content-type:application/tex");
$size='70pt';
$maxi=60;
$text='\documentclass{article}
\usepackage[left=20pt,right=20pt,top=20pt,bottom=20pt]{geometry}
\usepackage{multicol}
\begin{document}
\begin{multicols}{3}
\begin{tabular}{|l|l|}
\hline
';

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
\begin{tabular}{|l|l|}\hline
';
      $i=0;
    }


  $solde=$t['money'];


  
  $text.=$t['login'].'& \\hspace{3cm} \\\\\\hline'."\n";
  $i++;
  }
}
echo $text.'
\end{tabular}
\end{multicols}
\end{document}'
?>

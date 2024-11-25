<?php
  $middle = '';
  $start = '<ul class="nav nav-pills nav-fill gap-2 p-1 small bg-ssrounded-3 shadow-sm" id="pillNav2" role="tablist" 
  style="">';
foreach($links as $row => $link)
{	
	foreach($link as $key => $value)
	{
		$middle .= '<li class="main-item" role="presentation">' . "\n" . $value . "\n". '</li>' ."\n";
        
	}	
}
$finish = '</ul>';

print $start.$middle.$finish;
?>

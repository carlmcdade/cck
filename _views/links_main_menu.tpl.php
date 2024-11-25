<?php
  $middle = '';
  $start = '<ul class="nav nav-pills nav-fill gap-2 p-1 small bg-ssrounded-3 shadow-sm" id="pillNav2" role="tablist" 
  style="--bs-nav-link-color: var(--bs-white); --bs-nav-pills-link-active-color: var(--bs-primary); --bs-nav-pills-link-active-bg: var(--bs-white);">';
foreach($links as $row => $link)
{	
	foreach($link as $key => $value)
	{
		$middle .= '<li class="nav-item" role="presentation">
    <button class="btn-primary btn nav-link nav-link-color-white active rounded-3" id="home-tab-'.
	 $key.'-'.$row.'" data-bs-toggle="tab" type="button" role="tab" aria-selected="true">' . "\n" . $value . "\n". '</button></li>' ."\n";
        
	}	
}
$finish = '</ul>';

print $start.$middle.$finish;
?>

<?php
print '<ul class="nav nav-pills nav-fill gap-2 p-1 small bg-primary rounded-3 shadow-sm" id="pillNav2" role="tablist" style="--bs-nav-link-color: var(--bs-white); --bs-nav-pills-link-active-color: var(--bs-primary); --bs-nav-pills-link-active-bg: var(--bs-white);">
 ';
foreach($links as $key => $link)
{	
	foreach($link as $key => $value)
	{
		print('<li class="nav-item" role="presentation">
    <button class="nav-link active rounded-3" id="home-tab2" data-bs-toggle="tab" type="button" role="tab" aria-selected="true">' . "\n" . $value . "\n". '</button>' ."\n");
        print("</li>\n");
	}	
}
print '</ul>';
?>

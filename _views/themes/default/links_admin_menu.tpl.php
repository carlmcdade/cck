<?php 

print '<div id="admin-menu" class="menus">';
foreach($links as $section => $link)
{
	$module_name = explode('_', $section);
	print '<div class="sections">';
	print '<h1 class="section-title">' . $module_name[0] . '</h1>';
	print '<ul class="' . $section . '">';
	
	foreach($link as $key => $value)
	{
		//
		
		print '<li id="' . $section . '-' . $key . '" class="' . $section . '">' . $value . '</li>' ."\n";
		
	}
	
	print '</ul>';
	print '</div>';
}

print '</div>';


?>
<?php 

print '<div id="admin-menu" class="menus">';
foreach($links as $section => $link)
{
	$module_name = explode('_', $section);
	print '<div class="sections">';
	print '<h1 class="section-title">' . $module_name[0] . '</h1>';
	print '<ul class="' . $section . '">';
	
	
		
		print '<li>' . $adminNavigation . '</li>' ."\n";
		
	
	
	print '</ul>';
	print '</div>';
}

print '</div>';


?>
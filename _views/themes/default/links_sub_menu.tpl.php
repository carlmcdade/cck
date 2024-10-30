<?php 
print '<ul id="sub-menu-' . $menu_index . '" class="menus">';
foreach($links as $section => $link)
{
	
	foreach($link as $key => $value)
	{
		//
		
		print '<li id="' . $section . '-' . $key . '" class="' . $section . '">' . $value . '</li>' ."\n";
		
	}
	
	
}
	

?>
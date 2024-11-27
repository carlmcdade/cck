<?php

if(!isset($rows)){
		
		print 'no posts to read';

}
else{
$output = '<div class="row">';


//$output .= '<tbody><tr>' . "\n";
//var_dump($topContent);
	// table rows
	$counter = 0;
	foreach ($rows as $tr => $row)
	{
		$more = '<a href="?content/content_view/id/'. $row['id'] . '">more</a>';
		$output .= '<div style="" class="">';
		
			if(isset($row) && !empty($row['content_title']))
			{

			    //$output .= '<h3 id="td-' . (isset($id) ? $id : '')  . $tr . '-' .  $tr . '" class="table-cells">' . $row['name'] . '</h3>' . "\n";
				$output .= '<div class="post-header" style="padding:1em;"><h1 style="" id="td-' . (isset($id) ? $id : '')  . $tr . '-' .  $tr . '" class="">' . (isset($row['content_title']) ? $row['content_title']:'') . ' </h1><br>by <span class="fs-5">' .$row['name'] ."</span></div>\n";
				$output .= '<div style="" class="border border-solid border-1 border-primary border-start-0 border-end-0 p-3 mt-0">' . (isset($row['content_body']) ? substr($row['content_body'],0,200):'') . $more .  '</div>' . "\n";
			}
			else
			{
				$output .= '<div id="" class="table-cells"></div>' . "\n";
			}
		
		$output .= '</div>' . "\n";
		$counter = $counter + 1;
		//if($counter > 3){ break;}
	}


$output .= '</div>';
print $output;
}
?>

<!-- table_blog_content --><?php

if(!isset($rows)){
		
		print 'no posts to read';

}
else{
$output = '<div>';


//$output .= '<tbody><tr>' . "\n";
//var_dump($topContent);
	// table rows
	$counter = 3;
	foreach ($rows as $tr => $row)
	{
		$output .= '<div style="" class="">';
		
			if(isset($row))
			{

			    //$output .= '<h3 id="td-' . (isset($id) ? $id : '')  . $tr . '-' .  $tr . '" class="table-cells">' . $row['name'] . '</h3>' . "\n";
				$output .= '<div class="post-header" style="padding:1em;"><h1 style="" id="td-' . (isset($id) ? $id : '')  . $tr . '-' .  $tr . '" class="">' . (isset($row['content_title']) ? $row['content_title']:'') . ' </h1><br>by <span class="fs-5">' .$row['name'] ."</span></div>\n";
				$output .= '<div style="" class="border border-solid border-1 border-primary border-start-0 border-end-0 p-3 mt-0">' . (isset($row['content_body']) ? substr($row['content_body'],0,200):'') . '</div>' . "\n";
			}
			else
			{
				$output .= '<div id="" class="table-cells">nothing</div>' . "\n";
			}
		
		$output .= '</div>' . "\n";
		$counter = $counter + 1;
		//if($counter > 3){ break;}
	}


$output .= '</div>';
print $output;
}
?>

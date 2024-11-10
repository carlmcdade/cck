<?php

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
				$output .= '<h2 id="td-' . (isset($id) ? $id : '')  . $tr . '-' .  $tr . '" class="">' . $row['content_title'] . '</h2> by <span class="fs-4">' .$row['name'] ."</span>\n";
				$output .= '<div style="" class="border border-solid border-1 border-primary border-start-0 border-end-0 p-3 mt-2">' . substr($row['content_body'],0,200) . '</div>' . "\n";
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

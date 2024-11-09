<?php

if(!isset($rows)){
		
		print 'no posts to read';

}
else{
$output = '<div>';


//$output .= '<tbody><tr>' . "\n";
//var_dump($topContent);
	// table rows
	foreach ($rows as $tr => $row)
	{
		$output .= '<div id="tr-'. (isset($id) ? $id : '') . '-' . $tr . '" class="table-cells">';
		
			if(isset($row))
			{

			    //$output .= '<h3 id="td-' . (isset($id) ? $id : '')  . $tr . '-' .  $tr . '" class="table-cells">' . $row['name'] . '</h3>' . "\n";
				$output .= '<h2 id="td-' . (isset($id) ? $id : '')  . $tr . '-' .  $tr . '" class="table-cells">' . $row['content_title'] . '</h2> by <span fs-4>' .$row['name'] ."</span>\n";
				$output .= '<p id="td-' . (isset($id) ? $id : '')  . $tr . '-' .  $tr . '" class="table-cells fs-5">' . substr($row['content_body'],0,100) . '</p>' . "\n";
			}
			else
			{
				$output .= '<div id="td-' . (isset($id) ? $id : '')  . $tr . '-' .  $tr . '" class="table-cells">nothing</div>' . "\n";
			}
		
		$output .= '</div>' . "\n";
	}


$output .= '</div>';
print $output;
}
?>

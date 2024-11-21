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
		$more = '<i><a style="text-decoration:none;" href="?users/user_profile/'. $row['id'] . '">about ... .. .</a></i>';
		$output .= '<div style="" class="">';
		
			if(isset($row))
			{

			    //$output .= '<h3 id="td-' . (isset($id) ? $id : '')  . $tr . '-' .  $tr . '" class="table-cells">' . $row['name'] . '</h3>' . "\n";
				$output .= '<div style="padding:1em;background-color:#dee5ff;"><h1 style="" id="td-' . (isset($id) ? $id : '')  . $tr . '-' .  $tr . '" class="">';
				$output .= '<img class="" style="float:left;width:60px;" src="images/user_profile/user_id_'. $row['id'] .'/'.$row['image'].'">';
				$output .= (isset($row['content_title']) ? $row['content_title']:'') . ' </h1><br> <span style="font-size:1rem;" class="">' .$row['name'] . ' ' . $row['middle']."</span></div>\n";
				$output .= '<div style="font-size:.7rem" class="border border-solid border-1 border-primary border-start-0 border-end-0 p-3 mt-0">' . (isset($row['bio']) ? substr($row['bio'],0,200):'') . 
				'   '. $more . '</div>' . "\n";
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

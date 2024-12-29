<!--table_categories--><?php 

$output  = '<div class="row">';
$output  .= '<div class="col"><h5>Treeview</h5>';
$output .= '';
//exit($output);
foreach($rows as $name => $item)
{
    $child_rows = $rows;
	if($item['parentId'] == 0){

		$output .= '<div style=""><a href="">'.$item['name'].'</a></div>';
		foreach($child_rows as $child_key => $child)
		{
			if($child['parentId'] == $item['id'])
			{ 
				$output .= '<div style="margin-left: 2rem;"><a href="">'.$child['name'].'</a></div>';
			}
		}

	}else{

		//$output .= '<div style="margin-left: 2rem;"><a href="">'.$item['name'].'</a></div>';
	} 
	

}


$output .= '</div>';
$output  .= '<div class="col"><h5>Table View</h5><table class="table">';

// table header

//$output .= '<tbody><tr>' . "\n";
if(!empty($rows))
{
	// table rows
	foreach ($rows as $tr => $row)
	{
		$output .= '<tr id="tr-'. (isset($id) ? $id : '') . '-' . $tr . '" class="table-cells">';
		// table cells per row
		foreach($header as $td => $cell)
		{
			
			if(isset($row[$td]))
			{
				if($td === 1 ||$td === 0 ){
					$row[$td] = '<a role="button" class="btn btn-primary" href="">' .$row[$td]. '</a>' ;

			    }
				$output .= '<td id="td-' . (isset($id) ? $id : '')  . $tr . '-' .  $td . '" class="table-cells">' . $row[$td] . '</td>' . "\n";
			}
			else
			{
				$output .= '<td id="td-' . (isset($id) ? $id : '')  . $tr . '-' .  $td . '" class="table-cells"></td>' . "\n";
			}
		}
		$output .= '</tr>' . "\n";
	}

}
$output .= '</table></div></div>';
print $output;
?>

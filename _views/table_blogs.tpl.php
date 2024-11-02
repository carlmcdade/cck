<?php 
$output = '<table class="table">';
$output .= '<thead><tr>';
// table header
foreach ($header as $th => $column)
{
	$output .= '<th scope ="col">' .  $column . '</th>' . "\n";	
}
$output .= '</tr></thead>' . "\n";
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
				
			    switch($td)
			    {
			    case "0":
			    	   $row[$td] = '<a role="button"  class="btn btn-primary" href="?user/admin_blog">' .$row[$td]. '</a>' ;
			    	break;
			    case "1":
			    	   $row[$td] = '<a role="button"  class="btn btn-primary" href="?user/users_blog">' .$row[$td]. '</a>' ;
			    	break;
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
$output .= '</table>';
print $output;
?>

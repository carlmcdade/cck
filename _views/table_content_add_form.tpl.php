<?php 
$output = '<form><table class="table">';
$output .= '<thead><tr>';
// table header
foreach ($header as $th => $column)
{
	//$output .= '<th scope ="col">' .  $column . '</th>' . "\n";
	$label = $column;

//$output .= '</tr></thead>' . "\n";
//$output .= '<tbody><tr>' . "\n";
if(!empty($rows))
{
	// table rows
	foreach ($rows as $tr => $row)
	{
		$output .= '<tr id="tr-'. (isset($id) ? $id : '') . '-' . $tr . '" class="table-cells">';
		// table cells per row
		
		
			
			
			if(isset($row[$tr]))
			{
				     $output .= '<tr><td id="td-' . (isset($id) ? $id : '')  . $tr . '-' .  $tr . 
				     '" class="table-cells"> <label>'.$label.'</label> <input type="'.$fieldType.'" class="form-control" id="" placeholder="'. $column.'"></td></tr>' . "\n";
			  
			}
			else
			{
				$output .= '<tr><td id="td-' . (isset($id) ? $id : '')  . $tr . '-' .  $tr. '" class="table-cells"></td></tr>' . "\n";
			}
		
		$output .= '' . "\n";
		break;
	}
}

}
$output .= '</table></form>';
print $output;
?>

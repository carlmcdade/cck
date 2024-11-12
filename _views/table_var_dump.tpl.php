<?php 
$output = '<table class="table table-striped">';
$output .= '<thead><tr>';
// table header
foreach ($header as $th => $column)
{
	$output .= '<th scope ="col">' .  $column . '</th>' . "\n";	
}
$output .= '</tr></thead>' . "\n";
var_dump($rows);
if(!empty($rows))
{
	// table rows
	//$counter = 0;
	//$output .= '<tr><td colspan="2">'. $firstRow[1].'something</td></tr>' . "\n";
	foreach ($rows as $tr => $row)
	{
		
		
		$output .= '<tr id="tr-'. (isset($id) ? $id : '') . '-' . $tr . '" class="table-cells">';
		// table cells per row
		foreach($header as $td => $cell)
		{
			if(isset($row['name']))
			{
				if(strlen($row[$td] > 40)){
				     $row[$td] = substr($row[$td],0,40);
				}
				$output .= '<td id="td-' . (isset($id) ? $id : '')  . $tr . '-' .  $td . '" class="table-cells"><a href="?admin/module_comments_view/'.$row[$td].'">' . $row[$td] . '</a></td>' . "\n";
			}
			else
			{
				$output .= '<td id="td-' . (isset($id) ? $id : '')  . $tr . '-' .  $td . '" class="table-cells">section</td>' . "\n";
			}
		}
		$output .= '</tr>' . "\n";
	}
    //$counter = $counter +1;
}
$output .= '</table>';
print $output;
?>

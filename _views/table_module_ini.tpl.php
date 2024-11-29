<?php 
$output = '<table class="table table-striped">';
$output .= '<tr class="table-cells">';
// table header
foreach ($header as $th => $column)
{
	$output .= '<td class="first-row">' .  $column . '</td>' . "\n";	
}
$output .= '</tr>' . "\n";
//var_dump($rows);
if(!empty($rows))
{
	// table rows
	//$counter = 0;
	//$output .= '<tr><td colspan="2">'. $section.'</td></tr>' . "\n";


	foreach ($rows as $tr => $row)
	{
		$output .= '<tr id="" class="table-cells">';	
	foreach($row as $key=> $value){
		// table cells per row
			if($key == 1)
			{

								//$output .= '<tr><td id="td-' . (isset($id) ? $id : '')  . $tr . '-' .  $tr . '" class="table-cells">'. $row[$key].'what</td></tr>' . "\n";
			}
			elseif($key == 0)
			{
				$output .= '<td id="td-' . (isset($id) ? $id : '')  . $tr . '-' .  $tr . '" class="table-cells"><a href="?admin/module_edit/'.$row[1].'">configure</a></td>'.
				'<td>'. $row[1]. '</td><td><a href="?admin/module_comments_view/' . $row[1].'">'.'view'.'</a></td>'. 
				'' . "\n";
			}
		}
	$output .= '</tr>' . "\n";	
	}
    
}
$output .= '</table>';

print $output;
//var_dump($row);
?>

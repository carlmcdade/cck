<?php 
$output = '<form method="POST" action="?users/edit_user_save" name="user_edit"><table class="table">';
$output .= '<thead><tr>';
// table header
// table header
//$header[] = array('action');
foreach ($header as $th => $column)
{
			
            if($th == 0) { 
                        //i mo
                 $column = 'action';
            }
            elseif($th == 1) { 
                        //i mo
                 $column = 'name';
            }


	
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
				

			    if($td == 0){
			         $id = $row['id'];
			    	 $output .= '<td id="td-' . (isset($id) ? $id : '')  . $tr . '-' .  $td . '" class="table-cells">
			    	 <input type="hidden" name="'.$cell.'" id="'.$cell.'" value="'.$row['id'].'">
			    	 <input type="submit" class="btn btn-primary" value="save" name="save_user" id="'. $id.'">
			    	 </td>' ;
			    }
			    else{	
				     $output .= '<td id="td-' . (isset($id) ? $id : '')  . $tr . '-' .  $td . '" class="table-cells">  <input  value="'. $row[$td].'" name="'.$cell.'" type="text" class="form-control" id="" placeholder="'. $row[$td].'"></td>' . "\n";
			    }
			
			}
			else
			{
			
			    $row[$td] = 'none';
				$output .= '<td id="td-' . (isset($id) ? $id : '')  . $tr . '-' .  $td . '" class="table-cells">  <input  value="'. $row[$td].'" name="'.$cell.'" type="text" class="form-control" id="" placeholder="none"></td>' . "\n";
			}
		}
		$output .= '</tr>' . "\n";
	}
	
	//$output .= '<tr><td><input type="submit" class="btn btn-primary" value="save" name="save_user" id="'. $id.'"></td></tr>';

}
$output .= '</table></form>';
print $output;
?>

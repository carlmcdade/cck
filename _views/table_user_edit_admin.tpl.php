<?php 
$output = '<div class="container">';
//$output .= '<div><div>';
// table header
// table header
//$header[] = array('action');
if(!empty($rows))
{
	// table rows
    $output .= '<div class="container">';
	$output .= '<div style="border:solid blue 1px" id="tr-'. (isset($id) ? $id : '') . '-'  . '" class="row"><div style=""border: solid red 1px; class="col">';
        
	foreach ($rows as $tr => $row)
	{
        $output .= '<form method="POST" action="?admin/edit_user_save/'. $row['id'].'" name="formdata-'.$tr.'" id="formdata-'.$tr.'">';

		// table cells per row
		
		foreach($header as $td => $cell)
		{  
			
			
			if(isset($row[$td]))
			{
				

			    if($td == 0){
			         $id = $row['id'];
			    	 $output .= '<div id="td-' . (isset($id) ? $id : '')  . $tr . '-' .  $td . '" class="table-cells">
			    	 <input type="hidden" name="'.$cell.'-'. $td .'" id="'.$cell.'-'. $td .'" value="'.$row['id'].'">
			    	 <input type="submit" class="btn btn-primary" value="save" name="save_user-'.$row['id'].'" id="save_user-'. $row[0].'">
			    	 </div>' ;
			    }
                elseif($td == 4){
                    
			    	$editor =  'editor<div class="" name="editor-'.$tr.'" id="editor-'.$tr.'">'.$row[4].'</div>' ."\n";
			    	//$output .= '<div id="td-' . (isset($id) ? $id : '')  . $tr . '-' .  $td . '" class="table-cells"> '.$editor. "</div>\n" .
					$output .= ' <textarea value="'.$row[$td].'" name="'.$cell.'-'. $tr. '"  class="form-control" id="'. (isset($cell) ? $cell.'-'.$tr : '') .
					'" placeholder="'. $row[$td].'">' . $row[4]. "</textarea>\n";
			    	
			    }
			    else{
					$id = $row['id'];
				    $editor =  '' ."\n";
					$output .= '<div id="td-' . (isset($cell) ? $cell : '')  . $tr . '-' .  $td . '" class="table-cells">  <input value="'.
					$row[$td].'" name="'.$cell.'"  type="text" class="form-control" id="'. (isset($cell) ? $cell : '') .'" placeholder="'. $row[$td].
					'"></div>' . "\n";
			    }			
			}
			else
			{
			
			    $row[$td] = 'none';
				$output .= '<div id="td-' . (isset($cell) ? $cell: '')  . $tr . '-' .  $td . '" class="table-cells">  
                <input  value="'. $row[$td].'" name="'.(isset($cell) ? $cell : '').'" type="text" class="form-control" id="'.
                (isset($cell) ? $cell : '').'" placeholder="none"></div>' . "\n";
			}
            
		}
		$output .= '</form>' . "\n";
	}
	
	$output .= '</div>';
	$output .= '<div style="" class="col">instructions</div>';

}
$output .= '</div></div>';
print $output;
?>


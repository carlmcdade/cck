<?php 
$output = '<form method="POST" action="?users/edit_user_save" name="form" id="form"><table class="table">';
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
                elseif($cell == 'bio'){
			    	
			    	$editor =  'editor<div name="editor" id="editor">'.$row[$td].'</div>';
			    	$output .= '<tr><td id="td-' . (isset($id) ? $id : '')  . $tr . '-' .  $td . '" class="table-cells"> '.$editor.' <input value="'.$row[$td].'" name="'.$cell.'"  type="hidden" class="form-control" id="'. (isset($cell) ? $cell : '') .'" placeholder="'. $row[$td].'"></td></tr>' . "\n";
			    	
			    }
			    else{	
				     $output .= '<tr><td id="td-' . (isset($cell) ? $cell : '')  . $tr . '-' .  $td . '" class="table-cells">  <input value="'.$row[$td].'" name="'.$cell.'"  type="text" class="form-control" id="'. (isset($cell) ? $cell : '') .'" placeholder="'. $row[$td].'"></td></tr>' . "\n";
			    }			
			}
			else
			{
			
			    $row[$td] = 'none';
				$output .= '<td id="td-' . (isset($cell) ? $cell: '')  . $tr . '-' .  $td . '" class="table-cells">  <input  value="'. $row[$td].'" name="'.(isset($cell) ? $cell : '').'" type="text" class="form-control" id="'.(isset($cell) ? $cell : '').'" placeholder="none"></td>' . "\n";
			}
		}
		$output .= '</tr>' . "\n";
	}
	
	//$output .= '<tr><td><input type="submit" class="btn btn-primary" value="save" name="save_user" id="'. $id.'"></td></tr>';

}
$output .= '</table></form>';
print $output;
?>
<script>
// javascript is loaded after the template has been rendered to prevent element not found errors
//const container = document.getElementByID('editor');
const quill = new Quill('#editor',{theme:'snow'});

//listen to quill editor and append to form element
form.addEventListener("formdata", (event) => {
          event.formData.append("bio", quill.root.innerHTML);
        });
    
</script>

<?php 
$output = '<form name="form" id="form" method="POST" action="?users/edit_profile_save"><table class="table">';
$output .= '<thead><tr>';

if(!empty($rows))
{
	// table rows
	
	foreach ($rows as $tr => $row)
	{
		// table cells per row
		
		foreach($header as $td => $cell)
		{  
			
			$output .= '<tr colspan="8" id="tr-'. (isset($id) ? $id : '') . '-' . $header[$tr] . '" class="table-danger"><td class="">'. $header[$td] ."\n</td></tr>";
		
			
			if(isset($row[$td]))
			{
				
			    switch($td)
			    {
			    case "0":
			    	   $id = $row[$td];

			    	  // $output .= '<td id="td-' . (isset($id) ? $id : '')  . $tr . '-' .  $td . '" class="table-cells">'.$row[$td].'</td>' . "\n";

			        
			    	default :
			    	    $placeholder = $row[$td];
			    	 break;
			    }
			
			    if($td == 0){
			         
			    	 $output .= '<tr><td id="td-' . (isset($id) ? $id : '')  . $tr . '-' .  $td . '" class="table-cell"> <input value="'.$row[$td].'" name="'.$cell.'"  type="text" class="form-control" id="'. (isset($id) ? $id : '') .'" placeholder="'. $row[$td].'">'. 
			    	 '</td></tr>' ;
			    }
			    elseif($td == 4){
			    	
			    	$editor =  'editor<div name="editor" id="editor">'.$row[$td].'</div>';
			    	$output .= '<tr><td id="td-' . (isset($id) ? $id : '')  . $tr . '-' .  $td . '" class="table-cell"> '.$editor.' <input value="'.$row[$td].'" name="'.$cell.'"  type="hidden" class="form-control" id="'. (isset($id) ? $id : '') .'" placeholder="'. $row[$td].'"></td></tr>' . "\n";
			    	
			    }
			    else{	
				     $output .= '<tr><td id="td-' . (isset($id) ? $id : '')  . $tr . '-' .  $td . '" class="table-cell">  <input value="'.$row[$td].'" name="'.$cell.'"  type="text" class="form-control" id="'. (isset($id) ? $id : '') .'" placeholder="'. $row[$td].'"></td></tr>' . "\n";
			    }
			
			}
			
			else
			{
				//$editor = ' wrong editor<div name="editor" id="editor"></div>';
				$output .= '<tr><td id="td-' . (isset($id) ? $id : '')  . $tr . '-' .  $td . '" class="table-cell">
				<input value="'.$row[$td].'" name="'.$cell.'" type="text" class="form-control" id="'. (isset($id) ? $id : '') .'" placeholder="none"></td></tr>' . "\n";
			}
		}
		$output .= '<tr><td><input type="submit" class="btn btn-primary" value="save" name="save_user" id="'. $id.'">'."\n".'</td></tr>';

	}

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

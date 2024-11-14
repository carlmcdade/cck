<?php 
$output = '<form name="form" id="form" method="POST" action="?users/edit_profile_save"><table class="table">';
$output .= '<thead><tr>';
// table header
// table header
/* foreach ($header as $th => $column)
{
			/**if($th == 2) { 
                       //thi
                 continue;
            } elseif($th == 3) { 
                        //i mo
                 continue;
            }
            elseif($th == 4) { 
                        //i mo
                 continue;
            }
             elseif($th == 5) { 
                        //i mo
                 continue;
            }
            if($th == 0) { 
                        //i mo
                 $column = 'profile';
            }
            elseif($th == 1) { 
                        //i mo
                 //$column = 'profile';
            }


	
	$output .= '<th scope ="col">' .  $column . '</th>' . "\n";	
}
$output .= '</tr></thead>' . "\n"; */
//$output .= '<tbody><tr>' . "\n";
if(!empty($rows))
{
	// table rows
	
	foreach ($rows as $tr => $row)
	{
		// table cells per row
		
		foreach($header as $td => $cell)
		{  
			
			$output .= '<tr colspan="8" id="tr-'. (isset($id) ? $id : '') . '-' . $header[$tr] . '" class="table-cells"><td style="background-color:#dee5ff;" class="table-cells">'. $header[$td] ."\n</td></tr>";
		
			
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
			         
			    	 $output .= '<tr><td id="td-' . (isset($id) ? $id : '')  . $tr . '-' .  $td . '" class="table-cells"> <input value="'.$row[$td].'" name="'.$cell.'"  type="text" class="form-control" id="'. (isset($id) ? $id : '') .'" placeholder="'. $row[$td].'">'. 
			    	 '</td></tr>' ;
			    }
			    elseif($td == 4){
			    	
			    	$editor =  'editor<div name="editor" id="editor">'.$row[$td].'</div>';
			    	$output .= '<tr><td id="td-' . (isset($id) ? $id : '')  . $tr . '-' .  $td . '" class="table-cells"> '.$editor.' <input value="'.$row[$td].'" name="'.$cell.'"  type="hidden" class="form-control" id="'. (isset($id) ? $id : '') .'" placeholder="'. $row[$td].'"></td></tr>' . "\n";
			    	
			    }
			    else{	
				     $output .= '<tr><td id="td-' . (isset($id) ? $id : '')  . $tr . '-' .  $td . '" class="table-cells">  <input value="'.$row[$td].'" name="'.$cell.'"  type="text" class="form-control" id="'. (isset($id) ? $id : '') .'" placeholder="'. $row[$td].'"></td></tr>' . "\n";
			    }
			
			}
			
			else
			{
				//$editor = ' wrong editor<div name="editor" id="editor"></div>';
				$output .= '<tr><td id="td-' . (isset($id) ? $id : '')  . $tr . '-' .  $td . '" class="table-cells"><input value="'.$row[$td].'" name="'.$cell.'" type="text" class="form-control" id="'. (isset($id) ? $id : '') .'" placeholder="none"></td></tr>' . "\n";
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

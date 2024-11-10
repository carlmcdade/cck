<?php 
$output = '<form method="POST" action="?users/edit_user_save" name="user_edit"><table class="table">';
$output .= '<thead><tr>';
// table header
// table header
foreach ($header as $th => $column)
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
            }*/
            if($th == 0) { 
                        //i mo
                 $column = 'account';
            }
            elseif($th == 1) { 
                        //i mo
                 $column = 'profile';
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
				
			    switch($td)
			    {
			    case "0":
			    	   $id = $row[$td];

			    	  // $output .= '<td id="td-' . (isset($id) ? $id : '')  . $tr . '-' .  $td . '" class="table-cells">'.$row[$td].'</td>' . "\n";


			    	break;
			    case "1":
			    	   
			    	   //$row[$td] = '<a role="button"  class="btn btn-primary" href="?admin/edit_profile/'. $id .'">' .$row[$td]. '</a>' ;
			    	break;
			    
			        case "4":
			    	   $row[$td] = substr($row[$td],0,40);
			    	break;
			    	default :
			    	    $placeholder = $row[$td];
			    	 break;
			    }
			
			    if($td == 0){
			         
			    	 $output .= '<td id="td-' . (isset($id) ? $id : '')  . $tr . '-' .  $td . '" class="table-cells">   <input type="submit" class="btn btn-primary" value="save" name="save_user"'. $id .'"></td>' ;
			    }
			    else{	
				     $output .= '<td id="td-' . (isset($id) ? $id : '')  . $tr . '-' .  $td . '" class="table-cells">  <input name="'.$cell.'" type="text" class="form-control" id="" placeholder="'. $row[$td].'"></td>' . "\n";
			    }
			
			}
			else
			{
				$output .= '<td id="td-' . (isset($id) ? $id : '')  . $tr . '-' .  $td . '" class="table-cells">  <input name="'.$cell.'" type="text" class="form-control" id="" placeholder="none"></td>' . "\n";
			}
		}
		$output .= '</tr>' . "\n";
	}

}
$output .= '</table></form>';
print $output;
?>

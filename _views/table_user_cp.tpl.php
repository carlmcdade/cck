<?php 
$output = '<table class="table fs-6">';
$output .= '<thead><tr>';

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
			if($td == 0){
			}
			else{
				
				
			}
			
			if(isset($row[$td]))
			{
				
			    switch($td)
			    {
			    case "0":
			    	   $id = $row[$td];

			    	   $row[$td] = '<a role="button"  class="btn btn-primary" href="?users/edit_user/'. $id .'">edit</a>' ;

			    	break;
			    case "1":
			    	   $row[$td] = '<a role="button"  class="btn btn-primary" href="?users/edit_profile/'. $id .'">' .$row[$td]. '</a>' ;
			    	break;
			    
			        case "4":
			    	   $row[$td] = substr($row[$td],0,40);
			    	break;
			    }
			
			    
				$output .= '<td id="td-' . (isset($id) ? $id : '')  . $tr . '-' .  $td . '" class="table-cells">' . $row[$td] . '</td>' . "\n";
			}
			else
			{
				$output .= '<td id="td-' . (isset($id) ? $id : '')  . $tr . '-' .  $td . '" class="table-cells">none</td>' . "\n";
			}
		}
		$output .= '</tr>' . "\n";
	}

}
$output .= '</table>';
print $output;
?>

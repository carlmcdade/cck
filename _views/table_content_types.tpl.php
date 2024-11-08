<?php 
$output = '<form><table class="table">';
$output .= '<thead><tr>';
// table header
$displayCol = array(1,2,6);
foreach ($header as $th => $column)
{
				if(in_array($th, $displayCol)){
						$output .= '<th scope ="col">' .  $column . '</th>' . "\n";	
				     //$output .= '<td id="td-' . (isset($id) ? $id : '')  . $tr . '-' .  $td . '" class="table-cells">'. $row[$td].'</td>' . "\n";
			    }else{
			    	$output .= '' . "\n";	
			    }
			    
	
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
			    if($td == 0 ){
			         
			    	 $output .= '<td id="td-' . (isset($id) ? $id : '')  . $tr . '-' .  $td . '" class="table-cells"> <a role="button" style="width:100%" class="btn btn-primary mw-100" href="?admin/content_type_edit/'. $id .'">edit</a></td>' ;
			    }
			
			    elseif($td == 1){
			         
			    	 $output .= '<td id="td-' . (isset($id) ? $id : '')  . $tr . '-' .  $td . '" class="table-cells"> <a role="button" style="width:100%" class="btn btn-primary mw-100" href="?admin/content_type_post/'. $id .'">' .$row[$td]. '</a></td>' ;
			    }
			    elseif($td == 6){	
				     $output .= '<td id="td-' . (isset($id) ? $id : '')  . $tr . '-' .  $td . '" class="table-cells">'. $row[$td].'</td>' . "\n";
			    }
			    else{
                   }
			}
			else
			{
				$output .= '<td id="td-' . (isset($id) ? $id : '')  . $tr . '-' .  $td . '" class="table-cells"></td>' . "\n";
			}
		}
		$output .= '</tr>' . "\n";
	}

}
$output .= '</table></form>';
print $output;
?>

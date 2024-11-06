<?php 
$output = '<form><table class="table">';
$output .= '<thead><tr>';
// table header
foreach ($header as $th => $column)
{
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
			
			    if($td == 0 || $td == 1){
			         
			    	 $output .= '<td id="td-' . (isset($id) ? $id : '')  . $tr . '-' .  $td . '" class="table-cells"> <a role="button" style="width:100%" class="btn btn-primary mw-100" href="?blog/add_content/'. $id .'">' .$row[$td]. '</a></td>' ;
			    }
			    else{	
				     $output .= '<td id="td-' . (isset($id) ? $id : '')  . $tr . '-' .  $td . '" class="table-cells">  <input type="text" class="form-control" id="" placeholder="'. $row[$td].'"></td>' . "\n";
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

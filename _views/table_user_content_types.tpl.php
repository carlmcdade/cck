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
		$id = $row['id'];
		foreach($header as $td => $cell)
		{  
			
           
			if(isset($row[$td]))
			{
				
			   
			    if($td == 0 ){
			         
			    	$newName = $row[($td + 1)]; 
			    	$output .= '<td id="td-' . (isset($id) ? $id : '')  . $tr . '-' .
			    	 $td . '" class="table-cells"> <a role="button" style="width:100%" class="btn btn-primary mw-100" href="?content/content_add_post/'. $id .'">'.$newName.'</a></td>' ;
			    }
			
			    elseif($td == 2){
			         
			    	 $output .= '<td id="td-' . (isset($id) ? $id : '')  . $tr . '-' .  $td . '" class="table-cells">' .$row[$td]. '</td>' ;
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

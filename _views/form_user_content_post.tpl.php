<?php 
$output = '<form action="'.$formAction.'" method="POST"><table class="table">';
$output .= '<thead><tr>';

  $element_types = array(
  	  
  	  'input' => 'input',
  	  'textarea' => 'textarea',
  	  'radio' => 'radio',
  	  'select' => 'select',
  	  'checkbox' => 'checkbox',
  	  'date' => 'date',
  	  'date-time' => 'datetime-local',
  	  'email' => 'email',
  	  'file' => 'file',
  	  'hidden' => 'hidden',
  	  'image' => 'image',
  	  'month' => 'month',
  	  'week' => 'week',
  	  'number' => 'number',
  	  'password' => 'password',
  	  'range' => 'range',
  	  'reset' => 'reset',
  	  'search' => 'search',
  	  'submit' => 'submit',
  	  'text' => 'text',
  	  'time' => 'time',
  	  'url' => 'url',
  	  'color' => 'color'
  	  );
  
if(!empty($rows))
{
	// table rows
	foreach ($rows as $tr => $row)
	{
		$output .= '<tr id="tr-'. (isset($id) ? $id : '') . '-' . $tr . '" class="table-cells">';
		// table cells per row
		$label = $row['label'];
		$type =  $row['field_type'];
		
			
			
			//if(isset($row[$tr]))
			//{
				     $output .= '<tr><td id="td-' . (isset($id) ? $id : '')  . $tr . '-' .  $tr . 
				     '" class="table-cells"> <label>'.$label.'</label> <input type="text" class="form-control" id="" name="'. $row['name'].'"></td></tr>' . "\n";
			  
			//}
			//else
			//{
				//$output .= '<tr><td id="td-' . (isset($id) ? $id : '')  . $tr . '-' .  $tr. '" class="table-cells"></td></tr>' . "\n";
			//}
		
		$output .= '' . "\n";
		//break;
	}
	$output .= '<tr><td id="td-' . (isset($id) ? $id : '')  . $row['name'] . '-' .  $row['name'] . 
				     '" class="table-cells"> <input name="save" value="save" type="submit" class=" primary"></td></tr>' . "\n";
		
}


      	  
$output .= '</table></form>';
print $output;
?>

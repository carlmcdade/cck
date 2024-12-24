<?php 
$element_types = array(

    'input' => 'input',
    'textarea' => 'textarea',
    'radio' => 'radio',
    'select' => 'select',
	'fieldset' => 'fieldset',
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
$html_tags = array(

    'textarea' => 'textarea',
	'fieldset' => 'fieldset',
    'select' => 'select'
);

$weights = array(1,2,3,4,5,6,7,8,9,0,-1,-2,-3,-4,-5,-6,-7,-8,-9);
$visibility = array(
	'readonly',
	'disabled',
	'required'

);

$field_attr = array(
	'html_tag' => $html_tags,
	'field_type' => $element_types,
	'weight' => $weights,
	'visibility' => $visibility
);
$output = '<div>';
$output .= '<div>';
// table header
foreach ($header as $th => $column)
{
	

		if(!empty($rows))
		{
			// table rows
			foreach ($rows as $tr => $row)
			{
				$output .= '<div id="" class="row">';
				// table cells per row
				
					
						$output .= '<div style="border-color: #dddddd;border-width:1px;border-style:solid;" class="col-3 ">'.$column.'</div>';
						if(array_key_exists($column,$field_attr)){

							$output .='<div id="td" class="col-3 border">';
							$output .= '<select>';
							$output .= '<option value="'.$row[$column]. '">'.$row[$column]. '</option>';
							foreach($field_attr[$column] as $list_name => $list_item){

								$output .= '<option value="">'.$list_item. '</option>';

							}
							$output .= '</select>';
							$output .= '</div>' . "\n";

						}else{

							$output .='<div id="td" class="col-3 border">' . $row[$column] . '</div>' . "\n";

						}
					    
				$output .= '</div>' . "\n";
			}

		}
}
$output .= '</div></div>';
print $output;
?>

<!--form_user_content_post--><?php

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
//var_dump($rows); exit;
if (!empty($rows)) {
    // table rows
    $output .= "\n". '<input value= "'.$contentId.'" type="hidden" class="form-control" id="content-id" name="content_id">' . "\n";
    $output .= '<input value= "'.$contentType.'" type="hidden" class="form-control" id="content-type" name="content_type">' . "\n";
    $output .= '<input value= "'.$contentTime.'" type="hidden" class="form-control" id="content-time" name="content_time">' . "\n";
    $output .= '<input value= "'.$contentUserId.'" type="hidden" class="form-control" id="content-user-id" name="content_user_id">' . "\n";
    $output .= '<input value= "'.$contentTypeId.'" type="hidden" class="form-control" id="content-type-id" name="content_type_id">' . "\n";
    $output .= '<input value= "'.print_r($contentTypeFields, TRUE).'" type="hidden" class="form-control" id="content-type-fields" name="content_type_fields">' . "\n";
    $output .= '<input value= "'.print_r($contentTypeCategories,TRUE).'" type="hidden" class="form-control" id="content-type-categories" name="content_type_categories">' . "\n";
    
    $output .= '<tr>
	<td style="text-align:center;border-style:solid; border: 1px 0 1px 0; border-color:#777777; background-color:#777777;color:#ffffff;"
	name="td_content_title" id="td-content-title" class="table-cells">Meta Name</td></tr>' . "\n";

    $output .= '<tr><td name="td_content_title" id="td-content-title" class="table-cells"><input value="'.$contentType.' - '.$contentTime.'" 
	type="text" class="form-control" placeholder="required!" id="content-title" name="content_title" REQUIRED></td></tr>' . "\n";
    $output .= '<tr>
	<td style="text-align:center;border-style:solid; border: 1px 0 1px 0; border-color:#777777; 
	background-color:#777777;color:#ffffff;"name="td_content_title" id="td-content-title" class="table-cells">Content Type Fields</td></tr>' . "\n";

    foreach ($rows as $tr => $row) {
        $output .= '<tr id="tr-'. (isset($id) ? $id : '') . '-' . $tr . '" class="table-cells">'."\n";
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
                     '" class="table-cells"> 
					 <button id="save" name="save" value="save" type="submit" class="btn btn-secondary"> Save</button>'."\n".'
					 <button title="Requires Site Administrator Permissions" class="btn btn-secondary" type="submit" formaction="?admin/content_type_edit/'.$contentTypeId.'">Add new field</button>'."\n".'
					 </td></tr>' . "\n";

}



$output .= '</table></form>';
print $output;

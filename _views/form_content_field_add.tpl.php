<!--form_content_field_add--><?php
function getElement($elementTypeList) {
	$element_list = array();
    foreach ($elementTypeList as $key => $type) {
		$name = $type;
        switch ($type) {


            case 'input': $element = '<input />'. "\n";
                break;
            case 'textarea': $element =  '<textarea></textarea>'. "\n";
                break;
            case 'radio': $element =  '<input type="radio"/>'. "\n";
                break;
            case 'select': $element =  '<select><option>option</option></select>'. "\n";
                break;
            case 'checkbox': $element =  '<input type="checkbox" />'. "\n";
                break;
            case 'date': $element =  'date'. "\n";
                break;
            case 'date-time': $element =  'datetime-local'. "\n";
                break;
            case 'email': $element =  'email'. "\n";
                break;
            case 'file': $element =  'file'. "\n";
                break;
            case 'hidden': $element =  'hidden'. "\n";
                break;
            case 'image': $element =  'image'. "\n";
                break;
            case 'month': $element =  'month'. "\n";
                break;
            case 'week': $element =  'week'. "\n";
                break;
            case 'number': $element =  'number'. "\n";
                break;
            case 'password': $element =  'password'. "\n";
                break;
            case 'range': $element =  'range'. "\n";
                break;
            case 'reset': echo 'reset'. "\n";
                break;
            case 'search': $element =  'search'. "\n";
                break;
            case 'submit': $element =  'submit'. "\n";
                break;
            case 'text':  $element =  'text'. "\n";
                break;
            case 'time':  $element =  'time'. "\n";
                break;
            case 'url':   $element =  'url'. "\n";
                break;
            case 'color': $element =  'color'. "\n";
                break;
            default: 'no type found' . "\n";
			
            
        }
		$type = $element;
		$element_list[$name] = $type."\n";
    }
	return $element_list;
}
$output = '<form action="'.$formAction.'" method="POST">
<div class="container">';
$output .= '<div class="row"><div class="col">';

$elementTypes = array(

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
;
if (!empty($rows)) {
    // table rows
    //$output .= "\n". '<input value= "'.$contentId.'" type="hidden" class="btn btn-secondary form-control" id="content-id" name="content_id">' . "\n";
   // $output .= '<input value= "'.$contentType.'" type="hidden" class="btn btn-secondary form-control" id="content-type" name="content_type">' . "\n";
    //$output .= '<input value= "'.$contentTime.'" type="hidden" class="btn btn-secondary form-control" id="content-time" name="content_time">' . "\n";
    //$output .= '<input value= "'.$contentUserId.'" type="hidden" class="btn btn-secondary form-control" id="content-user-id" name="content_user_id">' . "\n";
    //$output .= '<input value= "'.$contentTypeId.'" type="hidden" class="btn btn-secondary form-control" id="content-type-id" name="content_type_id">' . "\n";
    /* $output .= '<tr>
    <td style="text-align:center;border-style:solid; border: 1px 0 1px 0; border-color:#777777; background-color:#777777;color:#ffffff;"
    name="td_content_title" id="td-content-title" class="table-cells">Meta Name</td></tr>' . "\n";


    $output .= '<tr><td name="td_content_title" id="td-content-title" class="table-cells"><input value="'.$contentType.' - '.$contentTime.'"
    type="text" class="form-control" placeholder="required!" id="content-title" name="content_title" REQUIRED></td></tr>' . "\n";
    */
    $output .= '<div
	style="text-align:center;border-style:solid; border: 1px 0 1px 0; border-color:#777777; 
	background-color:#777777;color:#ffffff;"name="td_content_title" id="td-content-title" class="table-cells">Content Type Fields</div>' . "\n";

    foreach ($rows as $tr => $row) {
        // table cells per row
        $label = $row['label'];
        $type =  $row['field_type'];



        //if(isset($row[$tr]))
        //{
        $output .= ' <label>'.$label.'</label> <input type="text" class="bg-secondary form-control" id="" name="'. $row['name'].'">' . "\n";

        //}
        //else
        //{
        //$output .= '<tr><td id="td-' . (isset($id) ? $id : '')  . $tr . '-' .  $tr. '" class="table-cells"></td></tr>' . "\n";
        //}

        $output .= '' . "\n";
        //break;
    }
    $output .= '
					 <button id="save" name="save" value="save" type="submit" class="btn btn-secondary mt-1"> Save</button>'."\n".'
					 <button class="btn btn-secondary mt-1" type="submit" formaction="?content/content_add_field/'.$contentTypeId.'">Add new field</button>'."\n";
					 

}



$output .= '</form></div><div class="col">';
$output .= '<pre>'. print_r(getElement($elementTypes),1).'</pre></div></div>' . "\n";
print $output;
?>

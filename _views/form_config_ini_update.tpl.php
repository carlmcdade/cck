<!--form_content_field_add--><?php
//exit('<pre>'. print_r($form).'</pre>');
$output = '<div style="text-align:center;border-style:solid; border: 1px 0 1px 0; border-color:#777777; background-color:#777777;color:#ffffff;"
	name="td_content_title" id="td-content-title" class="table-cells">Section</div>' . "\n";


$output .= '<div name="td_content_title" id="td-content-title" class="first-row table-cells text-center"><h4>'.$section.'</h4></div>' . "\n";

$output .= '
	<div style="text-align:center;border-style:solid; border: 1px 0 1px 0; border-color:#777777; 
	background-color:#777777;color:#ffffff;"name="td_content_title" id="td-content-title" class="table-cells">Field Value</div>' . "\n";
$output .= '<form class="" action="'.$formAction.'" method="POST"><table style="width:100%"; class="table">';
$output .= '<tr>';

$form_element_types = array(

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

if (!empty($form)) {
    /* table rows
    $output .= "\n". '<input value= "'.$contentId.'" type="hidden" class="btn btn-secondary form-control" id="content-id" name="content_id">' . "\n";
    $output .= '<input value= "'.$contentType.'" type="hidden" class="btn btn-secondary form-control" id="content-type" name="content_type">' . "\n";
    $output .= '<input value= "'.$contentTime.'" type="hidden" class="btn btn-secondary form-control" id="content-time" name="content_time">' . "\n";
    $output .= '<input value= "'.$contentUserId.'" type="hidden" class="btn btn-secondary form-control" id="content-user-id" name="content_user_id">' . "\n";
    $output .= '<input value= "'.$contentTypeId.'" type="hidden" class="btn btn-secondary form-control" id="content-type-id" name="content_type_id">' . "\n";
     */

    //$output .= print_r($form,1);
    $count = 1;
    foreach ($line as $tr => $row) {
        if (is_array($row)) {
            $output .= '<tr id="tr-'. (isset($id) ? $id : '') . '-' . $tr . '" class="table-cells">'."\n";
        }

        if (!is_numeric($tr)) {
            foreach ($row as $item => $data) {
                $output .= '<tr><td id="td-'.
                    '" class="table-cells"> <label style="padding:.5rem;text-align:center;background-color:#e1e1e1;display:block;border-bottom: 1px #777 solid;">['.
                    (isset($tr) ? $tr : '').']['. (isset($row) ? print_r($item, 1) : 'no label') .
                    ']</label> <input value="'. (isset($line[$section][$tr]) ? print_r($line[$section][$tr], 1) : print_r((isset($data) ? $data : 'no data'), 1)).'" placeholder="'.
                    (isset($line[$section][$tr]) ? print_r($line[$section][$tr], 1) : print_r((isset($data) ? $data : 'no data'), 1)).
                    '" type="text" class=" form-control" id="'.$item.'" name="'. $item .'"></td></tr>' . "\n";
            }
        } else {

            $output .= '<tr><td id="td-'.
            '" class="table-cells"> <label style="padding:.5rem; text-align:center;background-color:#e1e1e1;display:block;border-bottom 1px #777 solid;">['.
            (isset($tr) ? $tr : '').']['. (isset($count) ? $count : 'no label') .
            ']</label> <input placeholder="'.
            (isset($line[$section][$tr]) ? print_r($line[$section][$tr], 1) : print_r((isset($row[$count]) ? $row[$count] : $tr), 1)).
            '" type="text" class=" form-control" id="'.$count.'-'.$item.'" name="'. $item .'"></td></tr>' . "\n";
        }


        $output .= '' . "\n";
        //break;
        $count = $count + 1;
    }
}



$output .= '</table>';


$output .= '<div id="td-' . (isset($id) ? $id : '')   . '-'  .
'" class="text-center table-cells"> 
<button id=save" name="save" value="save" type="submit" class="btn btn-secondary"> Save</button>'."\n".'
<button class="btn btn-secondary" type="reset" formaction="">Reset</button>'."\n".'
</div></form>' . "\n";
print $output;
?>

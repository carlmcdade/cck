<!--form_user_content_post--><?php
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
$rows = $_POST;
$output =  '<div class="container"><div style="" class="col"><div class="row">';
if (isset($_GET['event_date'])) {
    $output .= '<h3 style="border-top:solid #dedede 1px; border-bottom:solid #dedede 1px;"> Event Date - ' .$_GET['event_date'] . '</h3>';
}


if (isset($_POST['content_id'])) {
    $output .= '<div style="max-width:400px;max-height:600px;overflow-y:auto;border: solid blue 1px;" class="col"> form action event save <hr><pre style="">'.
    print_r($eventFields, 1) .'</pre><hr><pre>'. print_r($_POST, 1) . '</pre></div>';
}



$output .= '<div style="max-height:600px;max-width:400px;" class="col">';
//$output .= '<thead><tr>';
$output .= '<form action="'.$formAction.'" method="POST">';

//var_dump($rows); exit;
if (!empty($_POST)) {

    $type =  (isset($_POST['content_type']) ? $_POST['content_type'] : '');
    $type_fields =  (isset($_POST['content_type_fields']) ? $_POST['content_type_fields'] : '');
    // table rows

    $output .= '<div style="text-align:center;border-style:solid; border: 1px 0 1px 0; border-color:#777777; background-color:#777777;color:#ffffff;"
	 name="td_content_title" id="td-content-title" class="">'. $type .'</div>' . "\n";

    $output .= '<div name="td_content_title" id="td-content-title" class=""><input value="'.$_POST['content_id'].'" 
	type="text" class="form-control" placeholder="required!" id="content-title" name="content_title" DISABLED></div>' . "\n";
    $output .= '<div style="text-align:center;border-style:solid; border: 1px 0 1px 0; border-color:#777777; 
	background-color:#eaeaea;color:#666;" name="td_content_title" id="td-content-title" class="table-cells">fields</div>' . "\n";

    foreach ($_POST['content_type_'.$type]['fields'] as $label => $value) {
        //$output .= '<div id="tr-'. (isset($label) ? $label : '') . '-' . $label. '" class="table-cells">'."\n";
        // table cells per row


        $output .= ' <label>'.$label.'</label><input type="text" class="form-control" id="" name="content-type-field-'. $label.'" />' . "\n";
        $output .= '' . "\n";
                       
            
        
        
    }
    
    $output .= '<pre style="max-height:200px; overflow-y:scroll;">'. print_r($rows['Posted-'.$contentType],1).'</pre>';


    $output .= '<button style="" role="button" id="save" name="save" value="save" type="submit" class="btn btn-secondary">Save</button>';
    $output .= "  ".'<button role="button" title="Requires Logged in User Permissions" name="" id="" class="btn btn-secondary" type="submit" formaction="?users/user_calendar_event&action=add_event'. $contentTypeId .'">Add Event</button>';

    $output .= "\n". '<input value= "'.$contentId.'" type="hidden" class="form-control" id="content-id" name="content_id">' . "\n";
    $output .= '<input value= "'.(!empty($contentType) ? $contentType : $_POST['content_type']).'" type="hidden" class="form-control" id="content-type" name="content_type">' . "\n";
    $output .= '<input value= "'.$contentTime.'" type="hidden" class="form-control" id="content-time" name="content_time">' . "\n";
    $output .= '<input value= "'.$contentUserId.'" type="hidden" class="form-control" id="content-user-id" name="content_user_id">' . "\n";
    $output .= '<input value= "'.$contentTypeId.'" type="hidden" class="form-control" id="content-type-id" name="content_type_id">' . "\n";
    $output .= '<input value= "'.$formAction.'" type="hidden" class="form-control" id="form-action-save-event" name="form_action_save_event">' . "\n";
    $output .= '<input value= "'.print_r($contentTypeFields, true).'" type="hidden" class="form-control" id="content-type-fields" name="content_type_fields">' . "\n";
    $output .= '<input value= "'.print_r($contentTypeCategories, true).'" type="hidden" class="form-control" id="content-type-categories" name="content_type_categories">' . "\n";
    $output .= '<input value= "'.print_r($_POST, 1).'" type="hidden" class="form-control" id="create-calendar-event" name="create_calendar_event">' . "\n";
   

}

$output .= '</form>';
print $output .'</div></div>';
//exit('<pre>'.print_r($VAR).'<pre>');

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
$output =  '<div class="container"><div style="" class="col"><div class="row">';
if (isset($_GET['event_date'])) {
    $output .= '<h3 style="margin:.5rem 0 0 0; border-top:solid #cccccc 1px; border-bottom:solid #cccccc 1px;"> Event Date - ' .
    (!empty($_GET['event_date']) ? $_GET['event_date']: ' choose a date') . '</h3>';
}

/*
if (isset($_POST['content_id'])) {
    $output .= '<div style="max-width:400px;max-height:600px;overflow-y:auto;border-width:0px 1px 0px 1px;border-style:solid; border-color: #cccccc;" class="col"> form action event save <hr><pre style="">'.
    print_r($eventFields, 1) .'</pre><hr><pre>'. print_r($_POST, 1) . '</pre></div>';
}
*/


$output .= '<div style="border-top: solid #f1f1f1 0px; overflow-y:scroll;max-height:600px;max-width:400px;" class="col">';
//$output .= '<thead><tr>';
$output .= '<form action="'.$formAction.'" method="POST">';

//var_dump($rows); exit;
if (!empty($_POST)) {

    $type =  (isset($_POST['content_type']) ? $_POST['content_type'] : '');
    $type_fields =  (isset($_POST['content_type_fields']) ? $_POST['content_type_fields'] : '');
    // table rows

    $output .= '<div style="text-align:center;border-style:solid; border:0; border-color:#777777; background-color:#777777;color:#ffffff;"
	 name="td_content_title" id="td-content-title" class="">'. (isset($_POST['content_id']) ? $_POST['content_id']:$type) .'</div>' . "\n";
/******************** content id *******************/
    $output .= '<div name="td_content_title" id="td-content-title" class=""><input value="'.$_POST['content_id'].'" 
	type="hidden" class="form-control" placeholder="required!" id="content-title" name="content_title" DISABLED></div>' . "\n";
    $output .= '<h3 style="text-align:center;border-style:solid; border-width:1px; border-color:#777777; 
	background-color:#f1f1f1;color:#666;" name="td_content_title" id="td-content-title" class="table-cells">Content fields</h3>' . "\n";
    if(isset($_POST['Posted-'.$type])){
        foreach ($_POST['Posted-'.$type]['posted-fields'] as $label => $value) {
            //$output .= '<div id="tr-'. (isset($label) ? $label : '') . '-' . $label. '" class="table-cells">'."\n";
            // table cells per row
    //var_dump($value);
        // $post_name = 'Posted-'. $type;
            $output .= ' <label>'.$label.'</label><input value="'. $value.'" type="text" class="form-control with-value" id="" name="content_create['.$type.'][fields]['.$label.']" />' . "\n";
            
        }
        $output .= '<input value="'.$_POST['content_id'].'" type="hidden" class="form-control" name="content_create['.$type.'][fields][content_id]">' . "\n";
        $output .= '<br>' . "\n";

    }else{


        $output .= '<input style="border: solid red 2px;" value="No fields for this content type. Contact site administrator" type="text" class="form-control" id="" name="content-type-field-fields'.'"DISABLED/>' . "\n";
        $output .= '<br>' . "\n";

    }
    if (!empty($eventFields)) {
        //echo print_r($contentTypeFields,1);
        //exit();
        $count = 1;
        
        

            /********  bring fileds from database coloumns to POST array********/
            $output .= '</div> <div class="col">';
            $output .= '<div style="text-align:center;border-style:solid; border:0; border-color:#777777; background-color:#777777;color:#ffffff;"
	                    name="td_content_title" id="td-content-title" class="">Event</div>' . "\n";

            $output .= '<h3 style="border-style:solid; border-width:1px; border-color:#777777; text-align:center;background-color:#f1f1f1;">Event fields</h3>';
            $output .= '<input value="'.$contentType.'" type="hidden" class="form-control" id="" name="event_create[event][content_type]" />' . "\n";

            $output .= ' <input value="'.$eventFields['id'].'" type="hidden" class="form-control" id="" name="event_create[event][fields][id]" />' .
             "\n";
            $output .= ' <input value="'.$eventFields['event_id'].'" type="hidden" class="form-control" id="" name="event_create[event][fields][event_id]" />' . "\n";

            $output .= ' <input value="'.$_POST['content_id'].'" type="hidden" class="form-control" id="" name="event_create[event][fields][content_id]" />' . "\n";

            $output .= ' <input value="'.$eventFields['event_user_id'].'" type="hidden" class="form-control" id="" name="event_create[event][fields][event_user_id]" />' . "\n";

            $output .= '<label for="event-create[event][fields][event_start_date]">event start date</label>';
            $output .= ' <input value="" type="date" class="form-control" id="event-create[event][fields][event_start_date]" name="event_create[event][fields][event_start_date]" />' . "\n";
            //$output .= '<div class="input-group-addon"><span class="glyphicon glyphicon-th"></span></div></div>';


            $output .= ' <label for="event-create[event][fields][event_end_date]">event end date</label><input value="" type="date" class="form-control" id="event-create[event][fields][event_end_date]" name="event_create[event][fields][event_end_date]" />' . "\n";

            $output .= ' <label>weight</label><input value="" type="text" class="form-control" id="event-create[event][fields][event_end_date]" name="event_create[event][fields][weight]" />' . "\n";

            $output .= ' <label>posted date</label><input value="" type="text" class="form-control" id="" name="event_create[event][fields][event_posted_date]" />' . "\n";

            $output .= ' <label>status</label><input value="" type="text" class="form-control" id="" name="event_create[event][fields][event_status]" />' . "\n";


            $output .= ' <label>visibility</label><input value="" type="text" class="form-control" id="" name="event_create[event][fields][visibility]" />' . "\n";

            




            $count = $count + 1;
        


    }


    //$output .= '<pre style="max-height:200px; overflow-y:scroll;">'. print_r($_POST, 1).'<br>event fields:<br>'.print_r($eventFields, 1). '<br>rows:<br>'.'</pre>';


    $output .= '</div><div style="text-align: right;padding-right:170px;"><button style="" role="button" id="save" name="save" value="save" type="submit" class="btn btn-secondary">Save</button>';
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
    $output .= '<input value= "'.print_r($eventFields, 1).'" type="hidden" class="form-control" id="create-calendar-event" name="event_create[event][available_event_fields]">' . "\n";


}

$output .= '</form>';
print $output .'</div></div>';
//exit('<pre>'.print_r($VAR).'<pre>');

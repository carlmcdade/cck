<!--form_user_content_post-->
<?php
//echo 'form user event post';
$output = '<form action="'.$formAction.'" method="POST"><table class="table table-striped">';
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
    $output .= '<input value= "'.$formAction.'" type="hidden" class="form-control" id="form-action-save-event" name="form_action_save_event">' . "\n";
    $output .= '<input value= "'.(isset($_GET['event_date']) ? $_GET['event_date'] : '').'" type="hidden" class="form-control" id="event_date" name="event_date">' . "\n";
    if (!empty($contentTypeFields)) {
        //echo print_r($contentTypeFields,1);
        //exit();
        $count = 1;
        foreach ($rows as $field_row => $field_value ) {
            
                
                    //exit(print_r($field_key,1));
                    
                    /********  bring fileds from database coloumns to POST array********/
                        $output .= ' <input value="'.$contentTypeFields[$field_row]['label'].'" type="hidden" class="form-control" id="" name="content_type_'.$contentType .'[fields]['.$field_value['name'].']'. $field_value['name'].'" />' . "\n";
                        $output .= ' <input value="'.$contentTypeFields[$field_row]['label'].'" type="hidden" class="form-control" id="" name="content_type_'.
                        $contentType .'[fields]['.$field_value['name'].'][label]" />' . "\n";
                        
                        $output .= ' <input value="'.$contentTypeFields[$field_row]['name'].'" type="hidden" class="form-control" id="" name="content_type_'.                       
                        $contentType .'[fields]['.$field_value['name'].'][name]" />' . "\n";

                        $output .= ' <input value="'.$contentTypeFields[$field_row]['description'].'" type="hidden" class="form-control" id="" name="content_type_'.
                        $contentType .'[fields]['.$field_value['name'].'][description]" />' . "\n";
                        
                        
                        $output .= ' <input value="'.$contentTypeFields[$field_row]['user_id'].'" type="hidden" class="form-control" id="" name="content_type_'.     
                        $contentType .'[fields]['.$field_value['name'].'][user_id]" />' . "\n";
                        
                        $output .= ' <input value="'.$contentTypeFields[$field_row]['field_type'].'" type="hidden" class="form-control" id="" name="content_type_'.
                        $contentType .'[fields]['.$field_value['name'].'][field_type]" />' . "\n";
                        
                        $output .= ' <input value="'.$contentTypeFields[$field_row]['weight'].'" type="hidden" class="form-control" id="" name="content_type_'.
                        $contentType .'[fields]['.$field_value['name'].'][weight]" />' . "\n";

                        $output .= ' <input value="'.$contentTypeFields[$field_row]['html_tag'].'" type="hidden" class="form-control" id="" name="content_type_'.
                        $contentType .'[fields]['.$field_value['name'].'][html_tag]" />' . "\n";

                        $output .= ' <input value="'.$contentTypeFields[$field_row]['css_inline'].'" type="hidden" class="form-control" id="" name="content_type_'.
                        $contentType .'[fields]['.$field_value['name'].'][css_inline]" />' . "\n";
                        

                        $output .= ' <input value="'.$contentTypeFields[$field_row]['visibility'].'" type="hidden" class="form-control" id="" name="content_type_'.
                        $contentType .'[fields]['.$field_value['name'].'][visibility]" />' . "\n";
                        
                        

                        
                        
                        
                        
                
            

            $count = $count + 1;
        }


    }

    //foreach($contentTypeCategories as $catkey => $cat_name){
    $output .= '<input value= "'. $contentTypeCategories.'" type="hidden" class="form-control" id="content-type-categories" name="content_type_categories">' . "\n";
    //}
    $output .= '<tr>
	<td style="text-align:center;border-style:solid; border: 1px 0 1px 0; border-color:#777777; background-color:#777777;color:#ffffff;"
	name="td_content_title" id="td-content-title" class="table-cells">'. $contentType .'</td></tr>' . "\n";

    $output .= '<tr><td name="td_content_title" id="td-content-title" class="table-cells"><input value="'.$contentType.' - '.$contentTime.'" 
	type="text" class="form-control" placeholder="required!" id="content-title" name="content_title" REQUIRED></td></tr>' . "\n";
    $output .= '<tr>
	<td style="text-align:center;border-style:solid; border: 1px 0 1px 0; border-color:#777777; 
	background-color:#eaeaea;color:#666;" name="td_content_title" id="td-content-title" class="table-cells">fields</td></tr>' . "\n";

    foreach ($rows as $tr => $row) {
        $output .= '<tr id="tr-'. (isset($id) ? $id : '') . '-' . $tr . '" class="table-cells">'."\n";
        // table cells per row
        $label = $row['label'];
        $type =  $row['field_type'];



        //if(isset($row[$tr]))
        //{
        $output .= '<tr><td id="td-' . (isset($id) ? $id : '')  . $tr . '-' .  $tr .
        '" class="table-cells"> <label>'.$label.'</label> 
        <input type="text" class="form-control" id="" name="Posted-'.$contentType.'[posted-fields]['.$row['name'].']'.$row['name'].'" />
        <input type="hidden" value="'. $row['name'].'" class="form-control" id="" name="Posted-'.$contentType.'[available-fields]['.$row['name'].']'. $row['name'].'" />
        </td></tr>' . "\n";
        //$output .= '<input value= "-'. $row['name'].'-" type="hidden" class="form-control" id="content-type-fields" name="Posted-'.$contentType.'[posted-fields]['.$row['name'].']['.$tr.']">' . "\n";
        //$output .= '<input value= "-'. $row['label'].'-" type="hidden" class="form-control" id="content-type-fields" name="Posted-'.$contentType.'[posted-fields]['.$row['name'].']['.$tr.']" />' . "\n";
            

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
					 <button title="Requires Logged in User Permissions" class="btn btn-secondary" type="submit" formaction="?users/user_calendar&action=add_event&type='.
                     $contentType.'&event_date='.(isset($_GET['event_date']) ? $_GET['event_date'] : '').'">Add Event</button>'."\n".'
					 </td></tr>' . "\n";

} else {
    //$output .= '<pre>'.print_r($_POST).'</pre>';
    $output .= "\n". '<input value= "'.$contentId.'" type="hidden" class="form-control" id="content-id" name="content_id">' . "\n";
    $output .= '<input value= "'.$contentType.'" type="hidden" class="form-control" id="content-type" name="content_type">' . "\n";
    $output .= '<input value= "'.$contentTime.'" type="hidden" class="form-control" id="content-time" name="content_time">' . "\n";
    $output .= '<input value= "'.$contentUserId.'" type="hidden" class="form-control" id="content-user-id" name="content_user_id">' . "\n";
    $output .= '<input value= "'.$contentTypeId.'" type="hidden" class="form-control" id="content-type-id" name="content_type_id">' . "\n";
    foreach ($contentTypeFields as $field_key => $field_name) {
        if (isset($field_key)) {

            $output .= '<input value= "'. (isset($field_name) ? print_r($field_name,1) : '').'" type="hidden" class="form-control" id="content-type-fields" name="content_type_fields['.(isset($field_key) ? $field_key : 'none set').'][]">' . "\n";
            $output .= '<input value= "'. (isset($field_value) ? print_r($field_value,1) : '').'" type="hidden" class="form-control" id="content-type-fields" name="content_type_fields['.(isset($field_key) ? $field_key : 'none set').']['.(isset($field_key) ? $field_key : 'none set').'][label][]" />' . "\n";
                      
        }
    }

    $output .= '<input value= "'. $contentTypeCategories.'" type="hidden" class="form-control" id="content-type-category" name="content_type_category">' . "\n";

    $output .= '<tr>
	<td style="text-align:center;border-style:solid; border: 1px 0 1px 0; border-color:#777777; background-color:#777777;color:#ffffff;"
	name="td_content_title" id="td-content-title" class="table-cells">'. $contentType .'</td></tr>' . "\n";

    $output .= '<tr><td name="td_content_title" id="td-content-title" class="table-cells"><input value="'.$contentType.' - '.$contentTime.'" 
	type="text" class="form-control" placeholder="required!" id="content-title" name="content_title" REQUIRED></td></tr>' . "\n";
    $output .= '<tr>
	<td style="text-align:center;border-style:solid; border: 1px 0 1px 0; border-color:#777777; 
	background-color:#eaeaea;color:#666;"name="td_content_title" id="td-content-title" class="table-cells">fields</td></tr>' . "\n";


    $output .= '<tr><td id="td-' . (isset($enumerate) ? $enumerate : '').
                 '" class="table-cells"> 
					 <button id="save" name="save" value="save" type="submit" class="btn btn-secondary"> Save</button>'."\n".'
					 <button title="Requires Logged in User Permissions" class="btn btn-secondary" type="submit" formaction="?users/user_calendar&add='.
                 $contentTypeId.'&event_date='.(isset($_GET['event_date']) ? $_GET['event_date'] : '').'">Add Event</button>'."\n".'
					 </td></tr>' . "\n";



}



$output .= '</table></form>';
print $output;

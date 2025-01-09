<!--form_content_type_edit -->
<?php
//echo 'form user event post';
$output = '<form name="content_type" id="content-type" class="" action="'.$formAction.'" method="POST">';
$output .= '';

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
    //$output .= "\n". '<input value= "'.$contentId.'" type="hidden" class="form-control" id="content-id" name="content_id">' . "\n";
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
        foreach ($rows as $field_row => $field_value) {


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

    $output .= '<input value= "'. $contentTypeCategories.'" type="hidden" class="form-control" id="content-type-categories" name="content_type_categories">' . "\n";
    $output .= '<a id="" style="text-decoration: none;" class="" href="javascript:;">';
    $output .= '<h5 style="color: #852525; border-top: solid #852525  1px;border-bottom: solid #852525  1px;background-color: #fcdddd; padding: .5rem 0; text-align:center;">'. $contentType .'</h5>' . "\n";
    $output .= '</a>';
    $output .= '<div  class="">';
    $output .= '<input value="'.$contentType.' - '.$contentTime.'" 
	type="text" class="form-control" placeholder="required!" id="content-title" name="content_title">' . "\n";
    $output .= '<h5 style="text-align:center;border-top: solid #cccccc 1px;border-bottom: solid #cccccc 1px; background-color:#f1f1f1;padding: .3rem 0; ">Present fields</h5>' . "\n";

    foreach ($rows as $tr => $row) {
        $label = $row['label'];
        $type =  $row['field_type'];



        //if(isset($row[$tr]))
        //{
        $output .= '<label>'.$label.'</label> 
                    <input type="text" class="form-control" id="" name="Posted-'.$contentType.'[posted-fields]['.$row['name'].']'.$row['name'].'" />
                    <input type="hidden" value="'. $row['name'].'" class="form-control" id="" name="Posted-'.$contentType.'[available-fields]['.$row['name'].']'. $row['name'].'" />
                    ' . "\n";

        $output .= '' . "\n";
        //break;
    }
    $output .= '<div class="text-center" style="padding: .5rem 0 .5rem 0;"><button id="save" name="save" value="save" type="submit" class="btn btn-secondary"> Save content type</button>'."\n".'
					 <button id="'.$contentType.'-fields-control" formaction="?admin/content_type_post/'.$contentTypeId.'" title="show possible fields" class="btn btn-secondary" type="submit">New content</button></div>'."\n".'
				' . "\n";
    $output .= '</div>';

} else 
{
    //$output .= '<pre>'.print_r($_POST).'</pre>';
    //$output .= "\n". '<input value= "'.$contentId.'" type="hidden" class="form-control" id="content-id" name="content_id">' . "\n";
    $output .= '<input value= "'.$contentType.'" type="hidden" class="form-control" id="content-type" name="content_type">' . "\n";
    $output .= '<input value= "'.$contentTime.'" type="hidden" class="form-control" id="content-time" name="content_time">' . "\n";
    $output .= '<input value= "'.$contentUserId.'" type="hidden" class="form-control" id="content-user-id" name="content_user_id">' . "\n";
    $output .= '<input value= "'.$contentTypeId.'" type="hidden" class="form-control" id="content-type-id" name="content_type_id">' . "\n";
    if(isset($contentTypeFields) and count($contentTypeField) > 0 ){
        foreach ($contentTypeFields as $field_key => $field_name) {
            if (isset($field_key)) {

                $output .= '<input value= "'. (isset($field_name) ? print_r($field_name, 1) : '').'" type="hidden" class="form-control" id="content-type-fields" name="content_type_fields['.(isset($field_key) ? $field_key : 'none set').'][]">' . "\n";
                $output .= '<input value= "'. (isset($field_value) ? print_r($field_value, 1) : '').'" type="hidden" class="form-control" id="content-type-fields" name="content_type_fields['.(isset($field_key) ? $field_key : 'none set').']['.(isset($field_key) ? $field_key : 'none set').'][label][]" />' . "\n";

            }
        }
    }



    $output .= '<input value= "'. $contentTypeCategories.'" type="hidden" class="form-control" id="content-type-category" name="content_type_category">' . "\n";
    $output .= '<a class="" data-toggle="collapse" href="javascript:;'.$contentType.'-fields"';
    $output .= ' style="display:block;text-decoration: none;color: #852525; border-top: solid #852525  1px;border-bottom: solid #852525  1px;background-color: #fcdddd; padding: .5rem 0; text-align:center;">'. $contentType .'' . "\n";
    $output .= '</a>';
    $output .= '<div id="'.$contentType.'-fields" class="">';
    $output .= '<input value="'.$contentType.' - '.$contentTime.'" 
	type="text" class="form-control" placeholder="required!" id="content-title" name="content_title" REQUIRED />' . "\n";
    $output .= '<h5 style="text-align:center;border-top: solid #cccccc 1px;border-bottom: solid #cccccc 1px; background-color:#f1f1f1;padding: .3rem 0;">fields</h5>' . "\n";


    $output .= ' 
					 <div class="text-center" style="padding: .5rem 0 .5rem 0;"><button id="save" name="save" value="save" type="submit" class="btn btn-secondary"> Save content type</button>'."\n".'
					 <button id="'.$contentType.'-fields-control" href="javascript:;" title="show possible fields" class="btn btn-secondary" type="submit">Add field</button></div>'."\n".'
				' . "\n";
    $output .= '</div>';



}

$output .= '</form>';
print $output;


<!-- table_content_types_admin  ---><?php
$output = '';
$output .= '<h5 class="bg-secondary border" style="text-align: center; padding:.5rem">Types</h5>';
$output .= '' . "\n";
$output .= '<table class="table table-striped fs-6">';


foreach($contentTypeNames as $typeName){
   // $output .= '<tr><td colspan="2"><pre style="height:200px; overflow-y:scroll;">'.print_r($contentTypeInfo[$typeName],1). '</pre></td></tr>';

        if (!empty($rows)) {
            // table rows
            foreach ($rows as $tr => $row)
            {
                $output .= '<tr id="tr-'. (isset($id) ? $id : '') . '-' . $tr . '" class="table-cells">';
                // table cells per row

                
                    $keeper = '';
                        $button_0 ='';
                        $button_1 ='';
                        switch ($tr) {
                            case "1":
                                
                            
                                break;
                            case "2":
                                $button_0 = '<form name="create_new_'.$row['content_type_name'] .'" method="post">';
                                $button_0 .= "\n".'  <input type="hidden" name="Posted_'.$row['content_type_name'].'[posted_fields][content_type]" id="Posted-form-posted-content-type-'.$typeName.'" value="" />';
                                $button_0 .= "\n".'  <input type="hidden" name="Posted_'.$row['content_type_name'].'[posted_fields][content_type][name]" id="Posted-form-posted-content-type-name-'.$row['content_type_name'].'" value="'.$row['content_type_name'].'" />';
                                $button_0.= "\n".'  <input type="hidden" name="Posted_'.$row['content_type_name'].'[posted_fields][content_type][id]" id="Posted-form-posted-content-type-id-'.$row['content_type_id'].'" value="'.$row['content_type_id'].'" />';
                                $button_0.= '<button title="" type="submit" name="create_new_' . $row['content_type_name'] . '" id="post-button-id-'. $row['content_type_id'].'" role="button"  class="btn btn-primary" formaction="?admin/content_type_edit/'. $row['content_type_id'] .
                '&content_type_name='. $typeName.'">';
                                $button_0 .= 'edit';
                                $button_0 .= '</button>';
                                $button_0 .= '</form>';
                                //$button_1
                                $button_1 = '<form name="create_new_'.$row['content_type_name'] .'" method="post">';
                                $button_1 .= "\n".'  <input type="hidden" name="Posted_'.$row['content_type_name'].'[posted_fields][content_type]" id="Posted-form-posted-content-type-'.$typeName.'" value="" />';
                                $button_1 .= "\n".'  <input type="hidden" name="Posted_'.$row['content_type_name'].'[posted_fields][content_type][name]" id="Posted-form-posted-content-type-name-'.$row['content_type_name'].'" value="'.$row['content_type_name'].'" />';
                                $button_1.= "\n".'  <input type="hidden" name="Posted_'.$row['content_type_name'].'[posted_fields][content_type][id]" id="Posted-form-posted-content-type-id-'.$row['content_type_id'].'" value="'.$row['content_type_id'].'" />';
                                $button_1 .= '<a class="btn btn-primary target-type-attr" id="show-type-info-control" href="javascript:;" title="" name="show_field_type_info' . $row['content_type_name'] . '" role="button">';
                                $button_1 .= 'info';
                                $button_1 .= '</a>';
                        
                                $button_1 .= '</form>';
                                //$button_1 .= '<form name="form_type_post_with_'.$row['content_type_name'].'" id="form-type-post-with-'.$row['content_type_name'].'" class="" method="post">';
                                $button_2 = '<form name="create_new_'.$row['content_type_name'] .'" method="post">';
                                $button_2 .= "\n".'  <input type="hidden" name="Posted_'.$row['content_type_name'].'[posted_fields][content_type]" id="Posted-form-posted-content-type-'.$typeName.'" value="" />';
                                $button_2 .= "\n".'  <input type="hidden" name="Posted_'.$row['content_type_name'].'[posted_fields][content_type][name]" id="Posted-form-posted-content-type-name-'.$row['content_type_name'].'" value="'.$row['content_type_name'].'" />';
                                $button_2 .= "\n".'  <input type="hidden" name="Posted_'.$row['content_type_name'].'[posted_fields][content_type][id]" id="Posted-form-posted-content-type-id-'.$row['content_type_id'].'" value="'.$row['content_type_id'].'" />';
                                $button_2 .= '<button title="" type="submit" name="create_new_' . $row['content_type_name'] . '" id="post-button-id-'. $row['content_type_id'].'" role="button"  class="btn btn-primary" formaction="?admin/content_type_post/'. $row['content_type_id'] .
                '&content_type_name='.$typeName.'">';
                                $button_2 .= $typeName;
                                $button_2 .= '</button>';
                                $button_2 .= '</form>';



                                $output .= '<td colspan="2" id="" class="'.$keeper.' table-cells">'."\n" ."\n".'<h6 class="" 
                                style="background-color: #666666; min-width:380px;color: #ffffff;text-align: center; padding:.5rem">'.$typeName.'</h6><div id="show-type-info-'.$typeName.'" class="show-type-attr" style="min-width:380px;max-width:380px;height:200px; overflow-y: scroll;"><pre>'. 
                                '<h6 style="padding:.3rem" class="fs-5 bg-secondary border">content type info:</h6>'.print_r($contentTypeInfo[$typeName],1).
                                '<h6 style="padding:.3rem" class="fs-5 bg-secondary border">content type fields:</h6>'.(isset($contentTypeFields[$typeName]) ? print_r($contentTypeFields[$typeName],1): 'no fields').'</pre></div></td>' .
                                '<td rowspan="2"><div style="max-width:400px;max-height:400px;overflow-y:scroll;background-color: #fefefe;min-width:400px;" class="col">
                                <h5 class="" style="padding:.5rem;text-align:center;background-color: #eaeaea;"><i>'.$typeName.'</i> - field list </h5>';
                                $output .= '<pre><span class="fs-5">=====Content Type=======</span>'."\n". print_r($contentTypeInfo[$typeName],1);
                                /***************Content type container attributes*****************/
                                $type_attr ='';
                                foreach($contentTypeInfo[$typeName] as $attr_key => $attr_value){
                                    $type_attr .= '<div><form class="" style="" action="" method="post">';
                                    $type_attr .="\n".'    <label for="Posted-form-posted-content-type-id-'.$attr_key.'" >'.$attr_key.'</label>'."";
                                    $type_attr .= "\n".'   <input class="form-control-xs" type="text" name="Posted_'.$row['content_type_name'].'[content_type][attributes]['.$attr_key.']" id="Posted-form-posted-content-type-id-'.$attr_key.'" value="'.$attr_value.'" />';
                                    $type_attr .= '  <button style="padding:1px 2px;" class="btn" type="submit" role="button">'.'save'.'</button>';
                                    $type_attr .= '</form></div>'."\n";

                                }

                                $output .= '<h5 style="padding:2px 2px 2px 5px;" class="fs-5 bg-secondary border">Content type attributes:</h5>'."". $type_attr.'';

                                $f_type_attr ='';
                                      
                                if($contentTypePresentFields !== NULL and isset($contentTypePresentFields[$typeName])){
                                        foreach($contentTypePresentFields[$typeName] as $f_attr_key => $f_attr_value ){

                                            
                                                $f_type_attr .= "\n".'<span';
                                                $f_type_attr .= "\n".'  style="padding:.3rem 0.5rem .2rem .5rem;" class="f-6 bg-secondary border">'.$typeName.'-'. $f_attr_value['machine_id'].'-'.$f_attr_value['field_type'].'</span>'. "\n";
                                            foreach($f_attr_value as $input_key => $input_value){

                                                $f_type_attr .= '<div class="" style="margin:0.4rem 0 0.3rem 0"><form class="" style="" action="" method="post">';
                                                $f_type_attr .= "".'  <label>'.$input_key.'</label>'."\n";
                                                $f_type_attr .= "".'  <input class="form-control-xs" style="" type="text" name="Posted['.$typeName.'][attributes]['.$f_attr_value['machine_id'].'" id="Posted-form-posted-content-type-id-" value="'. $input_value.'" />'. "";
                                                $f_type_attr .= '  <button style="padding:1px 2px;" class="btn" type="submit" role="button">'.'save'.'</button>';
                                                $f_type_attr .= '</form></div>'."";


                                            }

                                        }
                                }   

                                $output .= '<h5 style="padding:2px 2px 2px 5px;" class="fs-5 bg-secondary border">Present Fields:</h5>'. $f_type_attr.'';


                                //$output .= '<span class="fs-5">=====Content Fields=======</span>'.
                                //"\n".print_r((isset($contentTypePresentFields[$typeName]) ? $contentTypePresentFields[$typeName]: 'de nada'),1).'</pre>'."\n".'</div></td>' ."\n";
                               
                                $output .= '<tr><td colspan="2" id="" class="'.$keeper.' table-cells">'."\n" .
                                '<div style="padding:0;margin:0;max-width:300px;" class="row"><div class="col">'.$button_2. '</div><div class="col">  '.
                                 $button_1 .'</div><div class="col"> '. $button_0 .
                                 '</div></div></div></td></tr>' . "\n";
                                
                                break;

                        
                     
                                
                
                                  
                        }

                        
                        //$output .= '<td id="" class="'.$keeper.' table-cells">' . $button_0 . '</td>' . "\n";
                    
                
                $output .= '' . "\n";
                
            }

        }
}
$output .= '</table>';
print $output;
?>
<!--end table_content_types_admin-->

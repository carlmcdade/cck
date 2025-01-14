<!----- table_content_types -------><?php
//var_dump($row);
//exit;



$output = '' . "\n";
if (!empty($row)) {
    // table rows
    $output = '<div style="margin-bottom:1rem; margin-top:1rem; background-color: #c3dfff" class="border container">';
    $output .= '<div style="padding-bottom: 0.75rem;" class="row border border-black">';
    $output .= '<div style="margin-bottom:1rem; background-color: #fccb45; border-bottom: solid #000000 1px;" class=" text-center fs-5">'.
    (isset($row['content_body']['link-text']) ? $row['content_body']['link-text']: '').' - '. (isset($row['content_type_name']) ? $row['content_type_name']: '')
    .'</div>';
    $output .= '<div style="" class="col">'.
                '<a class="fs-5" style="text-decoration:none;" href="http://'.(isset($row['content_body']['link-path']) ? $row['content_body']['link-path']: '').'" />'.
                (isset($row['content_body']['link-text']) ? $row['content_body']['link-text']: '').'</a></div>';
    //$output .= '<div class="col">'.(isset($row['content_body']['body']) ? $row['content_body']['body']: '').'</div>';
   // $output .= '<div class="">'.(isset($row['content_body']['date']) ? $row['content_body']['date']: '').'</div>';
    
    $output .= '<div class="">';
    $output .= '<form id="form-'.$row['content_machine_id'].'" name="form-'.$row['content_machine_id'].'" method="post">'; 
    $output .= '<button style="position:relative;top:4px;float:left;margin:0.5rem 0.5rem .5rem 0" class="btn btn-sm" type="submit" role="button" formaction="?content/content_edit&content_machine_id='.$row['content_machine_id'].'">edit</button>';
    
    
        
        if(is_array($row['content_body'])){
            foreach($row['content_body'] as $fieldName => $fieldValue){

                $output .= '<input id="'.$fieldName.'" type="hidden" name="content_body['.$fieldName.']" value="'.print_r($fieldValue,1).'" />';
        
            }
        }
        else{

            foreach($content_fields as $field => $fieldValue){

                $output .= '<input id="'.$fieldValue['machine_id'].'" type="hidden" name="content_body['.$fieldValue['link-name'].']" value="'.$fieldValue['link-name'].'" />';
        
            }
        }
    
   
    //$output .= '<input id="database_value" type="hidden" name="database_value" value="'. print_r($row['content_body'],1).'" />';

    //$output .= '<input id="content-machine-id" type="hidden" name="content_machine_id" value="'.$row['content_machine_id'].'" />';
    
    $output .= '</form></div>';
    
    $output .= '<details class=""><summary class="btn btn-sm">info</summary>';
    foreach ($row as $tr => $line) 
    {
        
        // table cells per row
    if(is_array($line)){ 
                $button_1 = '';
                $button_1 .= '<div style="margin:0;" class="col bg-secondary">'.$tr.'</div><div style="margin:0;" class="col btn-primary text-center">list</div>';
                $button_1 .= '<details style="" class="bg-warning p-1"><summary class="bg-warning p-1">fields</summary>';

                
                foreach($content_fields[$row['content_type_name']] as $line_key => $line_value){

                    $button_1 .= '<div style="#ffffff;border: solid #000000 1px;margin-bottom:0.5rem;">
                    <div style=" padding:0 0 0 0;background-color: #000000;color: #ffffff" class="col border-dark">'.$line_value['name'].
                    '</div><div style="background-color: #ffffff;padding:0 0 0 0; overflow-y: scroll;" class="col"><pre>'.$line_value['name'].'</pre></div></div>';
                    
                            
                 }
                $button_1 .= '</details>';
            }else{


                        $button_1 = '<div style="" class="col bg-secondary">'.$tr.'</div><div style="" class="col btn-primary">'.$line.'</div>';

            }
                        

            $output .= '<div style="margin-bottom: 0.5rem; margin-top: 0.5rem;" class="row">' . $button_1 . '</div>' . "\n";
            if(isset($row_attributes[$tr]))
            {
                $button_attr = '';
                foreach($row_attributes[$tr] as $line_key => $line_value){

                    if(empty($line_value))
                    {
                        $line_value = 'empty';
                    }
                    $button_attr .= '<div style="border: solid #000000 1px;margin:0">
                    <div style="border:solid #000000 1px;margin:0; padding:0 0 0 12px;background-color: #000000; color: #ffffff " class="">'.$line_key.
                    '</div><div style="background-color: #ffffff;padding:0 0 0 12px;margin:0; overflow-y: scroll;" class="">'.substr($line_value,0,40).'</div></div>';
                            
                 }
                $output .=  '<details class="p-1 border border-dark" style="background-color: #fcee76;">
                <summary style="" title="Information about this field column" class="p-1">field info</summary>'.$button_attr.'</details>';
            }
            
        
        
    }
    $output .= '</div>';
    $output .= '</details></div>' . "\n";
}

print $output;
?>
<!-----end table_content_types_ end ---->
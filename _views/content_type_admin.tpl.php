<!----- table_content_types -------><?php
//var_dump($row);
//exit;



$output = '' . "\n";
/**** show this line of content */

if (!empty($row)) {
    // table rows
    $output = '<div name=name_row_"'.$row['content_machine_id'].'" id=id-row-"'.$row['content_machine_id'].'" style="margin-bottom:1rem" class=" border container">';
    foreach ($row as $tr => $line) {
        
        // table cells per row
    if(is_array($line)){ 
            $button_1 = '';
            foreach($line as $line_key => $line_value){

                $button_1 .= '<div class="row" ><div style="margin:0;" class="col bg-warning">'.$line_key.'</div>';
                $button_1 .= '<div style="margin:0; overflow-y: scroll;" class="col">'.substr($line_value,0,40).'</div></div>';
                        
            }

            }else{


                        $button_1 = 'admin<div style="margin:0;" class="col bg-secondary">'.$tr.'</div><div style="margin:0;" class="col">'.$line.'</div>';
            }
                        

            $output .= '<div style="margin-bottom: 0.5rem; margin-top: 0.5rem;" class="row">' . $button_1 . '</div>' . "\n";     
        
    }
    $output .= '</div>' . "\n";
}



/**** admin this line of content */

if (!empty($row)) {
    // table rows
    $output = '<div class="btn-secondary fs-4 p-1 row"><div class="col">'.$row['content_title'].'</div><div style="left: 0px;margin-left: 3rem;" class="fs-6 col">['.$row['content_name'].']</div></div>';
    $output .= '<details><summary class="bg-warning p-1">edit</summary><form id="form-'.$row['content_machine_id'].'" name="name_'.$row['content_machine_id'].'" method="post"><div style="margin-bottom:1rem" class="border container">';
    foreach ($row as $tr => $line) {

        if(isset($tr) and $tr == 'id'){
           
            continue;
        }
        
        // table cells per row
    if(is_array($line)){ 

                $button_1 = '';
                $button_1  = '<div class="row"><div style="margin:0;" class="col bg-secondary">'.$tr.'</div><div class="col border">content type fields </div>';
                        
             foreach($line as $line_key => $line_value){
                $name_field = explode(":", $line_key);
                if(isset($contentTypeFields[$row['content_type_id']][$name_field[1]])){
                    $show_this = print_r($contentTypeFields[$row['content_type_id']][$name_field[1]],1);
                }else{
                    $show_this = print_r($contentTypeFields[$row['content_type_id']],1);
                }
                $button_1  .= '<div class="row" ><div style="margin:0;" class="col bg-warning">'.$line_key.'</div></div>';
                $button_1 .= '<div class="row"><div class="col border border-dark" style="max-height: 10rem; overflow-y:scroll">';
                $button_1  .= '<input name=content_body['.$line_key.'] id="" class="form-control-xs" style="" value="'.$line_value.'" />';
                $button_1 .= '</div>';
                $button_1 .= '<div style="max-height: 10rem; overflow-y:scroll" class="col border">';
                $button_1 .= '<pre>'.$show_this.'</pre>';
                $button_1  .= '</div></div>';
                        
             }
             $button_1 .= '</div>' ;

            }else{

                        
                        $button_1  = '<div class="row"><div style="margin:0;" class="col bg-secondary">'.$tr.'</div><div class="col border"> field attributes</div></<div>';
                        $button_1 .= '<div class="row"><div class="col"><input name="'.$tr.'" id="id-'.$tr.'" title="'.''.'" type="text" style="margin:0;" class="form-control-xs" value="'.$line.'" />';
                        
                        $button_1 .= '</div><div style="max-height:10rem; overflow-y:scroll;" class="col"><pre>'.print_r($fields_attr[$tr],1).'<hr>'.'</pre></div></div>' ;
                        
            }
                        
            $output .= '<button value="'.$row['content_machine_id'].'" class="btn btn-secondary" role="button" type="submit" formaction="?admin/content_save&content_machine_id='.$row['content_machine_id'].'">'.$row['content_name'].'</button>';
            $output .= '<div style="margin-bottom: 0.5rem; margin-top: 0.5rem;" class="row">' . $button_1 . '</div>' . "\n";
           
        
        
    }
    $output .= '</div></form></details>' . "\n";
}

print $output;
?>
<!-----end table_content_types_ end ---->
<!----- table_content_types -------><?php
//var_dump($row);
//exit;

$output = '' . "\n";
if (!empty($row)) {
    // table rows
    $output = '<div style="margin-bottom:1rem" class="border container">';
    foreach ($row as $tr => $line) {
        
        // table cells per row
    if(is_array($line)){ 
                $button_1 = '';
             foreach($line as $line_key => $line_value){

                $button_1 .= '<div class="row" ><div style="margin:0;" class="col bg-warning">'.$line_key.'</div><div style="margin:0; overflow-y: scroll;" class="col">'.substr($line_value,0,40).'</div></div>';
                        
             }

            }else{


                        $button_1 = '<div style="margin:0;" class="col bg-secondary">'.$tr.'</div><div style="margin:0;" class="col">'.$line.'</div>';
            }
                        

            $output .= '<div style="margin-bottom: 0.5rem; margin-top: 0.5rem;" class="row">' . $button_1 . '</div>' . "\n";
            if(isset($row_attributes[$tr]))
            {
                $output .=  '<details><summary>more</summary><pre>'.print_r($row_attributes[$tr],1).'</pre></details>';
            }
        
        
    }
    $output .= '</div>' . "\n";
}

print $output;
?>
<!-----end table_content_types_ end ---->
<!----- table_content_types -------><?php
//var_dump($rows);

$output = '<div class="container">';
$output .= '<div class="row">';

/*
foreach ($header as $th => $column) {

    $output .= '<div style="width:100px;" id="id-'.$th.'" name="'.$column.'" class="first-row table-cells">' .  $column . '</div>' . "\n";
}
*/
$output .= '</div>' . "\n";
//$output .= '<tbody>' . "\n";
if (!empty($rows)) {
    // table rows
    $output .= '<div style="" class="row">';
    foreach ($rows as $tr => $row) {
        
        // table cells per row

        
            

           
                        $button_1 = '<pre>'.print_r($row,1).'</pre><hr>';
                        $button_1 = '<form><a title="'.$row['content_type_machine_desc'].'" name="' . $row['content_type_name'] . '" id="" role="button" style="display: block; width: 11rem; height:11rem;padding-top:3.75rem;padding-bottom:auto;" class="btn btn-primary fs-3" href="?content/content_add_post/'. $row['content_type_id'] .'"><span>' .$row['content_type_name']. '</span></a>' ;
                        $button_1 .= '<input type="hidden" value="'.$row['content_type_id'].'" name="content_type_id" id="content-type-id" />';
                        $button_1 .= '<input type="hidden" value="'.$row['content_type_name'].'" name="content_type_name" id="content-type-name" />';
                        $button_1 .= '</form>' ;
                        

                $output .= '<div style="margin-bottom: 1.5rem;" class="col">' . $button_1 . '</div>' . "\n";
           
        
        
    }
    $output .= '</div>' . "\n";
}
$output .= '</div>';
print $output;
?>
<!-----end table_content_types_ end ---->
<!----- table_content_types -------><?php
//var_dump($rows);

$output = '<table class="table table-striped fs-6">';
$output .= '<tr class="table-cells">';


foreach ($header as $th => $column) {

    $output .= '<td style="width:100px;" id="id-'.$th.'" name="'.$column.'" class="first-row table-cells">' .  $column . '</td>' . "\n";
}

$output .= '</tr>' . "\n";
//$output .= '<tbody>' . "\n";
if (!empty($rows)) {
    // table rows
    foreach ($rows as $tr => $row) {
        $output .= '<tr id="tr-'. (isset($id) ? $id : '') . '-' . $tr . '" class="table-cells">';
        // table cells per row

        foreach ($header as $td => $cell) {
            if ($td == 0) {
            } else {


            }

            if (isset($row[$td])) {
                $keeper = '';
                switch ($td) {
                    case "0":
                        $id = $row[$td];

                        $button = '<form name="content_type_edit" id="content-type-edit" >' ;
                        $button .= '<input type="hidden" value="'.$row[1].'" name="content_type_name" id="content-type-name">' ;
                        foreach ($header as $th => $column) {

                            $button .= '<input type="hidden" value="'.$column.'" name="Posted-'.$row[1].'[posted-fields]['.$th.']" id="content-type-id" />' ;
                        }
                        $button .= '<input type="hidden" value="'.$id.'" name="content_type_id" id="content-type-id">' ;
                        $button .= '</form>';
                        $row[$td]= $button;

                        break;
                    case "1":
                        
                        $button_1 = '<form><a name="' . $td . '" id="'. $id .'" role="button"  class="btn btn-primary" href="?content/content_add_post/'. $id .'">' .$row[$td]. '</a>' ;
                        $button_1 .= '<input type="hidden" value="'.$id.'" name="content_type_id" id="content-type-id" /></form>' ;
                        $row[$td] = $button_1;
                        break;

                    case "4":
                        $row[$td] = substr($row[$td], 0, 40);
                        break;
                    default:
                        $keeper = 'keep-width';
                }


                $output .= '<td id="td-' . (isset($id) ? $id : '')  . $tr . '-' .  $td . '" class="'.$keeper.' table-cells">' . $row[$td] . '</td>' . "\n";
            } else {
                $output .= '<td id="td-' . (isset($id) ? $id : '')  . $tr . '-' .  $td . '" class="'.$keeper.'. table-cells">none</td>' . "\n";
            }
        }
        $output .= '</tr>' . "\n";
    }

}
$output .= '</table>';
print $output;
?>
<!-----end table_content_types_ end ---->
<!--table_user_cp --><?php

$output = '<table class="table table-striped fs-6">';
$output .= '<tr class="table-cells">';

$colspan = 1;
foreach ($header as $th => $column) {
   
    $show_cols = array(0,1,8); 
    $column = str_replace('_',' ', $column); 
    if (!in_array($th, $show_cols)) {
        $colspan = $colspan + 1;
        continue;
    } else {

        $output .= '<td colspan="'.$colspan.'" id="id-'.$th.'" name="'.$column.'" class="first-row table-cells">' .  $column . '</td>' . "\n";
    }
   
}

$output .= '</tr>' . "\n";
//$output .= '<tbody>' . "\n";
if (!empty($rows)) {
    // table rows
    foreach ($rows as $tr => $row) {
        $output .= '<tr id="tr-'. (isset($id) ? $id : '') . '-' . $tr . '" class="table-cells">';
        // table cells per row
        $colspan = 1;
        $show_cols = array(0,1,8); 
        foreach ($header as $td => $cell) {
            if (!in_array($td, $show_cols)) {
                $colspan = $colspan + 1;
                continue;
            } else {


            }

            if (isset($row[$td])) {
                $keeper = '';
                switch ($td) {
                    case "0":
                        $id = $row[$td];
                        $button_0 = '<form>';
                        foreach ($header as $td => $cell) {
                            $button_0 .= '<input value="'.$cell.'" type="hidden" name="posted-fields['.$cell.']" id="" class="form-control" style="" />';
                        }
                        //$button_0 = '<input value="" type="hidden" name="posted-fields['.$cell.']" id="" class="form-control" style="" />';
                        //$button_0 = '';
                        $button_0 = '<a name="'.$td .'" id="'. $id . '" role="button"  class="btn btn-primary" formaction="?users/edit_user/'. $id .'">edit</a></form>' ;
                        $row[$td] = $button_0;
                        break;
                    case "1":
                        $button_1 = '<form>';
                        $button_1 = '';
                        $button_1 = '';
                        $button_1 .= '<a title="'.$row[6].'" name="' . $td . '" id="'. $id .'" role="button"  class="btn btn-primary" formaction="?users/edit_profile/'. $id .'">'.
                        $row[3].' '.$row[4].'</a></form>' ;
                        $row[$td] = $button_1;
                        break;

                    case "6":
                        $row[$td] = '<a href="javascript:;" role="button" title="'.$row[$td]. '" />view</a>';
                        break;
                    default:
                        $keeper = 'keep-width';
                }


                $output .= '<td colspan="'.$colspan.'" id="td-' . (isset($id) ? $id : '')  . $tr . '-' .  $td . '" class="'.$keeper.' table-cells">' . $row[$td] . '</td>' . "\n";
            } else {
                $output .= '<td id="td-' . (isset($id) ? $id : '')  . $tr . '-' .  $td . '" class="'.$keeper.'. table-cells">none</td>' . "\n";
            }
        }
        $output .= '</tr>' . "\n";
    }

}
$output .= '</table>';
print $output;

<?php

$output = '<table class="table table-striped fs-6">';
$output .= '<tr class="table-cells">';


foreach ($header as $th => $column) {

    $output .= '<td id="id-'.$th.'" name="'.$column.'" class="first-row table-cells">' .  $column . '</td>' . "\n";
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

                        $row[$td] = '<form name="form_type_edit_'.$row[$td].'" id="id-'. $row[$td].'" class="" method="post">
                         <input type="hidden" name="edit_type_'.$row['name'].'" id="edit-id-'.$row['name'].'-'. $id. '" value="edit content type '.$row['name'].'" />
                         <input type="hidden" name="name" id="'.$cell.'-'. $td .'" value="'.$row['name'].'">
                        <button title="Edit the fields of this content type" type="submit" value="'.$row['id'].'" name="edit_type'.'" id="edit-button-id-'. $id . '" role="button"  class="btn btn-primary" formaction="?admin/content_type_edit/'. $id .'">edit</button></form>' ;
                        
                        break;
                    case "1":
                        $row[$td] = '<form name="form_type_create_post_'. $row[$td].'" id="'.$row[$td].'" class="" method="post">
                         <input type="hidden" name="post_type_'.$id.'" id="id-'.$row[$td].'-'. $id. '" value="post a new "'.$row['name'].' />
                         <input type="hidden" name="name" id="'.$cell.'-'. $td .'" value="'.$row['name'].'">
                        <button title="create new post using this contnet type" type="submit" name="create_new_' . $row['name'] . '" id="post-button-id-'. $id .'" role="button"  class="btn btn-primary" formaction="?admin/content_type_post/'. $id .'">' .$row[$td]. '</button></form>' ;
                        
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

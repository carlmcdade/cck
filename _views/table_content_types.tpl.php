<?php

$output = '<table class="table table-striped fs-6">';
$output .= '<tr class="table-cells">';


foreach ($header as $th => $column) {
/*====== table header name override =====  */
/*
    
    if($th == 2) {
               //thi
         continue;
    } elseif($th == 3) {
                //i mo
         continue;
    }
    elseif($th == 4) {
                //i mo
         continue;
    }
     elseif($th == 5) {
                //i mo
         continue;
    }
    if ($th == 0) {
        //i mo
        $column = 'account';
    } elseif ($th == 1) {
        //i mo
        $column = 'profile';
    }

*/

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

                        $row[$td] = '<a name="'.$td .'" id="'. $id . '" role="button"  class="btn btn-primary" href="?content/content_type_edit/'. $id .'">edit</a>' ;

                        break;
                    case "1":
                        $row[$td] = '<a name="' . $td . '" id="'. $id .'" role="button"  class="btn btn-primary" href="?content/content_add_post/'. $id .'">' .$row[$td]. '</a>' ;
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

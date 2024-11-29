<!--table_categories--><?php 
$output = '<table class="table table-striped">';
$output .= '<tr>';
// table header
foreach ($header as $th => $column)
{
	$output .= '<td class="first-row">' .  $column . '</td>' . "\n";	
}
$output .= '</tr>' . "\n";
//$output .= '<tbody><tr>' . "\n";
if(!empty($rows))
{
	// table rows
	foreach ($rows as $tr => $row)
	{
		$output .= '<tr id="tr-'. (isset($id) ? $id : '') . '-' . $tr . '" class="table-cells">';
		// table cells per row
		foreach($header as $td => $cell)
		{
			
			if(isset($row[$td]))
			{
				
                if(!empty($row[$td] && $td !== 1 )){
                    if(is_numeric($row[$td])){
                        $cell_check = $row[2];
                      }else{
                        $cell_check = $row[$td];  
                      }
                    if($row[$td] == $row[2]){
                        $name_check = '';
                    }else{
                        $name_check = '='.$row[$td];
                    }
					$row[$td] = '<a role="button" class="btn btn-primary" href="?admin/admin_config_edit&'.$row[2]. $name_check .'">' .$cell_check. '</a>' ;
                    $output .= '<td id="td-' . (isset($id) ? $id : '')  . $tr . '-' .  $td . '" class="table-cells">' . $row[$td] . '</td>' . "\n";
			    }else{
                    if(empty($row[$td])){
                      $cell_check = 'empty';
                    }elseif(is_array($row[$td])){
                        $cell_check = 'list';  
                      }
                    else{
                      $cell_check = $row[$td];  
                    }
                    
                    $row[$td] = '<a role="button" class="btn btn-primary" href="?admin/admin_config_edit&'.$row[2].'='.$cell_check.'">' .$cell_check. '</a>' ;
                    $output .= '<td id="td-' . (isset($id) ? $id : '')  . $tr . '-' .  $td . '" class="table-cells">' . $row[$td] . '</td>' . "\n";
                }
				
			}
			else
			{
				$output .= '<td id="td-' . (isset($id) ? $id : '')  . $tr . '-' .  $td . '" class="table-cells">empty</td>' . "\n";
			}
		}
		$output .= '</tr>' . "\n";
	}

}
$output .= '</table>';
print $output;
?>

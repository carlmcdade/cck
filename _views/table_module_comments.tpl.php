<!-- table_module_comments --><?php
//var_dump($moduleMethods);
$output = '<div class="container"';
$method_output = '';
$comment_titles = '';
/*  methods list */
 $method_output ='<div id="list-example" class="list-group">';
 $comment_titles = '<div data-spy="scroll" data-target="#list-example" data-offset="0" class="scrollspy-example">' ."\n";

    foreach($moduleMethods as $key => $name){
    /* ============ side bar naviagation ============ */
      $method_output .= '<a class="list-group-item list-group-item-action fs-6" href="#list-item-'.$key.'">'.str_replace('_' , ' ', $name)."</a><br>\n";
    /* ========= comments ====================== */
      $comment_titles .= '<h5 class="m-0" style="padding:.25em 0 .25em 0; border-bottom: 2px solid #777;background-color: #ffffff;" id="list-item-'.$key.'">'.$name.'</h5>';
      $comment_titles .= '<pre class="m-0" style="max-width:100%;overflow-x:auto; background-color: #fff999;">'. ($moduleComments[$key] != FALSE ? $moduleComments[$key]: 'no developer comments').'</pre>'."\n";
      $comment_titles .= '<a style="--bs-btn-padding-y: .15rem; --bs-btn-padding-x: .5rem; --bs-btn-font-size: 1rem;" class="btn btn-secondary btn-sm rounded-0" href="https://github.com/carlmcdade/cck/blob/main/_controllers/'.  $module .'/'. $module .'.class.inc">code</a>';
    }
$comment_titles .= '</div>';

    /* ======== modules list =================*/
    $method_output .= '<span class="fs-4">Other Modules</span>'; 
    foreach($otherModules as $key => $name){
    	$method_output .= '<a class="list-group-item list-group-item-action fs-6" href="?admin/module_comments_view/'.$name.'">'.$name."</a><br>\n";
    }
    
$method_output .= '</div>';

$output .= '</div>' . "\n";
$output .= '<div style="border-style:solid;border-width:1px 0 1px 0;border-color:#cccccc;" class="row">';
foreach ($header as $th => $column)
{
	$span = ($th == 0 ? 8 : 4);
	$output .= '<div class="fs-4 col-'.$span.'">' .  $column . '</div>' . "\n";	
}

$output .= '</div><div style="height:600px; overflow-y:scroll;" class="container">';

if(!empty($rows))
{
	// table rows
	//$counter = 0;
	//$output .= '<tr><td colspan="2">'. $section.'</td></tr>' . "\n";


	foreach ($rows as $tr => $row)
	{
		$output .= '<div class="row">';	
	foreach($row as $key=> $value){
		// table cells per row
			if($key == 1)
			{

								//$output .= '<tr><td id="td-' . (isset($id) ? $id : '')  . $tr . '-' .  $tr . '" class="table-cells">'. $row[$key].'what</td></tr>' . "\n";
			}
			elseif($key == 0)
			{
				//$output .= '<td id="td-' . (isset($id) ? $id : '')  . $tr . '-' .  $tr . '" class="table-cells"><a href="?admin/module_edit/'.$row[0].'">configure</a></td>';
				$output .= '<div style="overflow-y:scroll" class="col-8">'. $row[1]. $comment_titles . '</div>'."\n".'<div class="col-4" style=";text-align: center;color: #ffffff;background-color:#666"><br>'. 
				'' . "\n";
			}
			
	}	
	$output .= "". $method_output. "</div>\n";
	$output .= '</div>' . "\n";	
	}
    
}
$output .= '</div>';

print $output;
//var_dump($row);
?>

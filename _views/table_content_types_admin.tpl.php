
<!-- table_content_types_admin  --->
<?php
$output = '';
$output .= '<h5 class="bg-secondary border" style="text-align: center; padding:.5rem">Types</h5>';
$output .= '' . "\n";
$output .= '<div class="container fs-6"><div class="row">';


foreach($contentTypeNames as $typeName => $value){
    /* row start */
    $output .= '<div class="row"><div style="background-color: #999999;" class="col border border-1 border-dark border-bottom-0  text-light text-center p-3 fs-4">'.$typeName.'</div></div>';
    $output .= '<div class="row">';
    $output .= '<div class="col bg-white border border-dark" style="text-transform: capitalize;text-align: center; padding:.3rem" max-height:450px;overflow-y: scroll;width:420px; border: solid blue 1px;">'.
    $typeName .' attributes</div>';
    $output .= '<div class="col btn-secondary border" style="text-transform: capitalize;text-align: center; padding:.3rem" max-height:450px;overflow-y: scroll;width:420px; border: solid red 1px;">';
    $output .= ' present fields</div>';
    $output .= '</div>';
    $output .='<div class="row">';
    /***** Left column start ****/
    $output .= '<div style="max-height:450px;overflow-y: scroll;width:420px; border-right: #eaeaea solid  1px;" class="col">';
    //$output .= '<h5 class="bg-secondary border " style="text-align: center; padding:.3rem">'.$typeName.'</h5>';
        if (!empty($rows)){
            foreach ($contentTypeInfo[$typeName] as $f_name => $f_value){

                $output .= '<div style="margin-bottom:.5rem;" class="">  <label style="display:block;" for="'.$f_name.'"> ' . $f_name.'</label> '."\n".' <input name="" id="'.$f_name.'" class="form-control-xs" type="text" value="'.$f_value.'" /></div>'."\n";
            }

        }
            
            
            
    $output .= '</div>';
    /*** Left column end ****/
    /* row column break*/
    /********* Right Column ********/
    $output .= '<div style="max-height:450px;overflow-y: scroll;width:420px; border-left: solid #eaeaea 1px;" class="col">';
    //$output .= '<h5 class="btn-secondary" style="text-align: center; padding:.3rem">'.$typeName.' - fields</h5>';
    //$output .= 'right column<pre>'. print_r($contentTypePresentFields[$typeName],1).'</pre>';
    if(isset($contentTypePresentFields[$typeName]) and count($contentTypePresentFields[$typeName]) > 0){
        $form_build = '<form name="'.$typeName.'-edit" id="" style="" method="post">'. "\n";
        $field_count = 1;
       
        foreach($contentTypePresentFields[$typeName] as $f_key => $f_value){
            $field_total = count($contentTypePresentFields[$typeName]);
            $form_build .= '<div class="bg-secondary border p-2 text-center fs-6 sticky"><span style="color: #ffffff; font-size:12px;font-weight:500;" class="btn btn-secondary">fields : '.$field_count.' of '.$field_total.'</span> <br><span>  '."\n". $typeName.'-['.$f_key. ']-'.$f_value['field_type'].' </span></div>';
            foreach($f_value as $fld_name => $fld_value){
                $form_build .= "\n".'<div class=""><label class="form-label" for="'.$fld_name.'">'.$fld_name.'</label><input class="form-control" type="text" name="" id="'.$fld_name.'" value="'.$fld_value.'" /></div>'. "\n";
            }

            $field_count = $field_count + 1;

           

        }
        $form_build .= ''. "\n";
    }
    $output .= $form_build.'</div>';
    /** end right column **/
    /******** button station ************/
    

    /***end type row**/
    $output .= '</div>';

    $output .= '<div style="margin-bottom:1rem;" class="row">';
    $output .= '<div class="col bg-secondary border" style="text-transform: capitalize;text-align: center; padding:.3rem max-height:450px;overflow-y: scroll;width:420px; border: solid blue 1px;">';
    $output .= '<button class="btn btn-secondary" role="button" type="submit" formaction="?admin/content_type_edit/'.$contentTypeInfo[$typeName]['content_type_id'].
    '">Save '. $typeName.' attributes</button> ';

    $output .= '</div>';
    $output .= '<div class="col btn-secondary border" style="text-transform: capitalize;text-align: center; padding:.3rem max-height:450px;overflow-y: scroll;width:420px; border: solid red 1px;">';
    $output .= '<button class="btn btn-primary" role="button" type="submit" formaction="?admin/content_type_edit/'.$contentTypeInfo[$typeName]['content_type_id'].'">save all</button> ';
    $output .= '<button class="btn btn-primary" role="button" type="submit" formaction="?admin/content_type_edit/'.$contentTypeInfo[$typeName]['content_type_id'].'">add field</button> ';
    $output .= ' </div>';
    $output .= '</div></form>';
    
}       

$output = $output .'</div></div>';
print $output. 'end';
?>
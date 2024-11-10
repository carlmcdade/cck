<?php 
$output = '<table class="table table-responsive">';
$output .= '<thead><tr>';
// table header
$skip_over = array(2,3,4,5,6,);
foreach ($header as $th => $column)
{
			if(in_array( $th , $skip_over)) { 
                       //this value 
                 continue;
            } 

            elseif($th == 0) { 
                        //i mo
                 $column = 'blog';
            }
            elseif($th == 1) { 
                        //i mo
                 $column = 'profile';
            }
            


	
	$output .= '<th scope ="col">' .  $column . '</th>' . "\n";	
}
$output .= '</tr></thead>' . "\n";
//$output .= '<tbody><tr>' . "\n";
//var_dump($topContent);
if(!empty($rows))
{
	// table rows
	foreach ($rows as $tr => $row)
	{
		$output .= '<tr id="tr-'. (isset($id) ? $id : '') . '-' . $tr . '" class="table-cells">';
		// table cells per row
		$skip_over = array(2,3,4,5,6,);
		foreach($header as $td => $cell)
		{
			
			if(in_array( $td , $skip_over)) { 
                       //this value 
                 continue;
            } 
			if(isset($row[$td]))
			{
				
			    switch($td)
			    {
			    case "0":
			    	   $id = $row[$td];

			    	   $row[$td] = '<a style="width:100%;" role="button"  class="btn btn-primary" href="?blog/blog_user/'. $id .'">view</a>' ;

			    	break;
			    case "1":
			    	   $addOn = $td + 1;
			    	   $row[$td] = '<a style="width:100%" role="button"  class="text-nowrap btn btn-primary" href="?users/user_profile/'. $id .'">' .$row[$td]. ' ' .$row[$addOn]. '</a>' ;
			    	break;
			        	
			        	
			    
			        case "4":
			    	   $row[$td] = substr($row[$td],0,40);
			    	break;
			        case "7":
			        	  if(isset($userID)){
			        	  	  $profileImage = $row[$td];
			        	     $row[$td] ='<img  height="48px" width="48px" class="align-self-start mr-3 img-thumbnail" src="images/user_profile/user_id_'. $id . '/' . $profileImage . '" alt="'.$row[$td].'">';   
                          }
                          else{
                          	 
                          	  $profileImage = $row[$td];
                              $row[$td] ='<img  height="64px" width="64px" class="align-self-start mr-3 img-thumbnail" src="images/user_profile/user_id_'. $id . '/' . $profileImage . '" alt="'.$row[$td].'">';   

                          }
			        	  break;
			    }
			
			    
				$output .= '<td id="td-' . (isset($id) ? $id : '')  . $tr . '-' .  $td . '" class="table-cells">' . $row[$td] . '</td>' . "\n";
			}
			else
			{
				$output .= '<td id="td-' . (isset($id) ? $id : '')  . $tr . '-' .  $td . '" class="table-cells"></td>' . "\n";
			}
		}
		$output .= '</tr>' . "\n";
	}



}
$output .= '</table>';
print $output;
?>

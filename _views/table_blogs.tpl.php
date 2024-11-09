<?php 
$output = '<table class="table table-responsive">';
$output .= '<thead><tr>';
// table header
foreach ($header as $th => $column)
{
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
		foreach($header as $td => $cell)
		{
			
			if($td == 2) { 
                       //this value 
                 continue;
            } elseif($td == 3) { 
                        //i mostly 
                 continue;
            }
            elseif($td == 4) { 
                        //i mo
                 continue;
            }
             elseif($td == 5) { 
                        //i .
                 continue;
            }
			if(isset($row[$td]))
			{
				
			    switch($td)
			    {
			    case "0":
			    	   $id = $row[$td];

			    	   $row[$td] = '<a style="width:50%;" role="button"  class="btn btn-primary" href="?blog/blog_user/'. $id .'">view</a>' ;

			    	break;
			    case "1":
			    	   $addOn = $td + 1;
			    	   $row[$td] = '<a style="width:50%" role="button"  class="text-nowrap btn btn-primary" href="?users/user_profile/'. $id .'">' .$row[$td]. ' ' .$row[$addOn]. '</a>' ;
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

<?php

// Define a class
class blog_form {
  // Sets properties
  public $user_id;
  public $user_name_first;
  public $user_name_last;

  // Method of the class
  function blog_form_get_values() {
    // Returns a string with the properties value. Uppercase the first character of each word
    return ucwords($this->user_id. ' - '. $this->user_name_first . $this->user_name_last) . '<br />';
  }
  
  // Method of the class
  function blog_form_make_form($results)
  {
  	
  	$output = '';
  	
  	// Returns a string with the properties value. Uppercase the first character of each word
  	foreach($results as $item)
  	{
		$output .= $item;
	}
  	return $output;
  }
  
}


?>
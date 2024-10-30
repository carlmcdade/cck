<?php

/*
 * @author Carl McDade
 * @copyright Copyright (c) 2010, Carl McDade
 * @since 2010-02-19
 * @version 0.2
 * @license http://opensource.org/licenses/gpl-license.php GNU Public License
 * @link http://www.drupal.se Drupal Sweden
 *
 */

class example{
    
   // some object variables 
   public $id;
   public $first_name;
   public $last_name;
   
   // for the database connection
   public $dbc;
   
   function __construct()
   {
        // connect to the database
        $this->dbc = DbConn::connect();
   }
 
   public function info()
   {
   	   
   	   $output = '#'.$this->id.': '.$this->first_name.' '.$this->last_name ."<br />\n";
   	   
   	   return $output;
   }
   
   function get_select()
   {
   	   // PDO
   	   $query = "SELECT id, first_name, last_name FROM users";
   	   $result = $this->dbc->query($query);
   	   $result->setFetchMode(PDO::FETCH_CLASS, 'example');
   	   
   	   $output = '<p>This is some actual data from the user table called by the  example model class. The object is mapped to the info() method
which a nice thing since now you can easily extend the class and override the method then manipulate the user object
in another model or controller.'."</p>\n";
	   $output .= '<p>';
   	   
   	   while ($user = $result->fetch())
   	   {
   	   	   $output .=  $user->info()."\n";
   	   }
   	   
   	   $output .= '</p>';
   	   return $output;
    }
    
    function get_create() {
    	
    	$sql = "INSERT all FROM table_one WHERE state='cloning'";
        return $sql;
             
    }
    
    function get_delete() {
    	
    	$sql = "DELETE FROM table_one WHERE state='cloning'";
        return $sql;
             
    }
    
    function get_update() {
    	
    	$sql = "UPDATE all SET dna_checked='TRUE' WHERE state='meta-human'";
        return $sql;
             
    }

}

?>

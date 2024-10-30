<?php

/**
 * @author Carl McDade
 * @copyright Carl McDade
 * @since 2011
 * @version 1.0
 * @license MIT
 *
 * @link http://berlinto.com/berlinto
 * ==================================================================
 *
 *                        dbconn.class.inc
 *
 * ==================================================================
 *
 * @TODO make a template for this comment
 *
 */

 class dbconn{

 	 static private $_instance = null;
 	 public $db; 
 	 
     
     public static function connect()
     {
     	 
            //$db = new PDO("mysql:host=remote-mysql3.servage.net;dbname=carlmcdade1", 'carlmcdade1', 'ding_L');
            
            $connection = new PDO("mysql:localhost;dbname=berlinto", 'root', 'beer',array( PDO::ATTR_PERSISTENT => true));
             
            return $connection;
            
            /* 
            $connection = mysql_connect("remote-mysql3.servage.net",
            		"carlmcdade1",
            		"ding_L");
            
            $db = mysql_select_db("carlmcdade1", $connection);
            return $db;
          */
     }
     
     function db_operation()
    {
        
        $variables = array();
        $model = 'default';
        $mode = ber_pathpart(2);
        print $mode;
        
        switch($mode) 
        {
            // models return a view/model
            case 'create':
            	$variables['page_title'] = 'Create One';
                $variables['content'] = $this->common->ber_model('example','get_create');
                $model = 'default';
                break;
                
            case 'view':
            	
                $variables['page_title'] = 'View One';
            	$variables['content'] = $this->common->ber_model('example','get_retrieve');
                $model = 'default';
                break;
                
            case 'update':
            	
            	$variables['page_title'] = 'Update One';
            	$output = 'This is a plain string to show the use of the out parameter';
                
                // doing it a bit different and setting the form into a variable
                $variables['start'] = '<div style="border:1px solid #eaeaea">start</div>'.
                //mvc_access(__function__);
                $variables['myform'] = $this->common->ber_model('example','get_update');
                $variables['end'] = '<div style="border:1px solid #eaeaea">end</div>';
                $model = 'defualt';
                break;
                
            case 'delete':
            	$variables['page_title'] = 'Delete One';
                $this->common->ber_model('example','get_delete');
                $model = 'default';
                break;
        }        
            
        $variables['result'] = $model;
        $variables['content'] = $output;
        
        print $this->common->ber_view($view, $variables);
    }


}
?>

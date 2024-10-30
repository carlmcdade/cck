<?php

/*
 * @author Carl McDade
 * @copyright Copyright (c) 2010, Carl McDade
 * @since 2010-02-19
 * @version 0.2
 * @license
 * @link http:
 *
 */


class example_admin{
	
	private $common;
	public  $page_title = 'Examples Administration';
	public  $section;
	public  $module;
	public  $settings;
	
	
	function __construct()
	{
		//Test the Common settings
		$this->section = get_class($this);
		$parent = explode('_', $this->section);
		$this->module = $parent[0];
		
		// Get configuration settings
    	}
    	
    	function __destruct()
    	{
    		//
    	}
    	
    	function hook_admin_links()
    	{
    		$link = 'links';
    		$var[$link][1] = array(
        		'text' => 'Examples', 
        		'path' => 'admin/'. $this->module.'/example_list'
        		);
        	return $var;
        }
    
        /**
        *  Sub navigation is not a hook and displayed per call by section
        */
    
        function hook_sub_links($index = 0)
        {
        	$link = 'links';
        	$var = array();
        	$var[$link][2] = array(
        		'text' => 'Examples',
        		'path' => '?' . 'admin/' . $this->module . '/example_list'
        		);
        	return $var;
        }
        
        function hook_access()
        {
        	$authorize = array(
        		$this->module . '/example_add' => array('access foo'),
        		$this->module . '/example_edit' => array('access baz'),
        		$this->module . '/example_save' => array('access boo','access suisse'),
        		);
        	return $authorize;
        }
        	
	
	/**
	*    This is a user administration function where the main admin menu is not shown
	*    although the user is in the administration section they are not given the default
	*    admin menu
	*/
	
	function example_list()
	{
		
		global $cck;
		$main_menu = $cck->_hooks('hook_links');
		$sub_menu = $this->hook_sub_links();
		
		//  view template variables
		$variables['page_title'] = $this->page_title;
		$variables['content_title'] = 'Examples';   	
		$variables['main_navigation'] = $cck->_menu_links($main_menu, 'links_main_menu');
		
		// Get the content column values 
		$connect = $cck->_dbconnect();
		$query = 'SELECT * FROM content_types';
		
		// table header from database
		$result = $connect->prepare("SELECT * FROM content_types LIMIT 0");
		$result->execute();
		$table_fields = $result->fetchAll(PDO::FETCH_COLUMN);
		
		
		for ($i = 0; $i < $result->columnCount(); $i++) {
		    $col = $result->getColumnMeta($i);
		    $columns[] = $col['name'];
		}
		
		
		// table rows and field values
		$result = $connect->prepare("SELECT * FROM content_types");
		$result->execute();
		$table_rows = $result->fetchAll();
		
		// validate content
		if(!empty($table_rows))
    	{
    		$header = $columns;
    		$rows = $table_rows;
    		
    		// set table variables for view table template
			$table['header'] = $header;
			$table['rows'] = $rows;	
			$output = $cck->_view('table', $table);	
    	}
    	else
    	{
	    	$output = 'Query incomplete or not found!';
    	}
 	 
		
		
		// final output variables for view page template
		$variables['content'] = 'list of all users example' . $output;
		print $cck->_view('page_admin', $variables);
	}
	  
}
?>

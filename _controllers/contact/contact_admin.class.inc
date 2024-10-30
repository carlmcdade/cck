<?php

/*
 * @author Carl McDade
 * @copyright Copyright (c) 2010, Carl McDade
 * @since 2010-02-19
 * @version 0.2
 * @license Apache 2.0
 * @link http://www.fhqk.com/cck Berlin Germany
 *
 */


class contact_admin{
	
	private $common;
	public  $page_title = 'Contact Administration';
	public  $section;
	public  $module;
	public  $settings;



    function __construct()
    {
        //Test the Common settings
        $this->common = Common::get_instance();
        $this->section = get_class($this);
        $parent = explode('_', $this->section);
        $this->module = $parent[0];
        
    }
    
    /**
    *   Sub navigation is not a hook and displayed per call by section
    */
    
    function hook_sub_links($index = 0)
    {      
        $link = 'links';        
        $var = array();       
        $var[$link][2] = array(
        		'text' => 'Categories',
        		'path' => 'admin/' . $this->module . '/contact_list'
        );       
        $var[$link][1] = array(
        		'text' => 'Add Contact',
        		'path' => $this->section . '/contact_add'
        );        
        return $var;      
    }
    

    function hook_admin_links()
    {
        $link = 'links';
    	
    	$var[$link][1] = array(
        		'text' => 'Contacts lists', 
        		'path' => 'admin/' . $this->module . '/contacts'
        		);
        $var[$link][2] = array(
        		'text' => 'Categories', 
        		'path' => 'admin/' . $this->module . '/categories'
        		);

        return $var;
    }  
    
    function categories()
    {
    	global $cck, $ini_settings;
    	
    	// get all links from each class controller
        $main_menu = $cck->_hooks('hook_links');
    	$sub_menu = $this->hook_sub_links();
    	
    	$output = '';
    	
    	$variables['page_title'] = $this->page_title; 	
    	$variables['main_navigation'] = $cck->_menu_links($main_menu, 'links_main_menu');
		$variables['sub_navigation'] = $cck->_module_links($sub_menu,
			array(
				'template'=>'links_sub_menu',
				'index' => $this->module
    			));
        $variables['content_title'] = ucfirst( __FUNCTION__);
    	$variables['content'] = 'example text for ' . $variables['content_title'];
    	print $cck->_view('page_admin', $variables);
    }
    
    function contacts()
    {
    	global $cck, $ini_settings;
    	
    	// get all links from each class controller
        $main_menu = $cck->_hooks('hook_links');
    	$sub_menu = $this->hook_sub_links();
    	
    	$output = '';
    	
    	$variables['page_title'] = $this->page_title; 	
    	$variables['main_navigation'] = $cck->_menu_links($main_menu, 'links_main_menu');
		$variables['sub_navigation'] = $cck->_module_links($sub_menu,
			array(
				'template'=>'links_sub_menu',
				'index' => $this->module
    			));
        $variables['content_title'] = ucfirst( __FUNCTION__);
    	$variables['content'] = 'example text';
    	print $cck->_view('page_admin', $variables);
    }
    
 
    
}

?>

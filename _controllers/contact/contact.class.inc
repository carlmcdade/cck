<?php

/*
 * @author Carl McDade
 * @copyright Copyright (c) 2010, Carl McDade
 * @since 2010-02-19
 * @version 0.2
 * @license
 * @link http://www.berlinto.com Berlin Germany
 *
 */


namespace contact;
class contact {
	
	private $common;
	public  $menu;
	public  $section;
	public  $module;

	
	function __construct()
	{
		//Test the Common settings
		$this->module = __NAMESPACE__;
	}
	
	function hook_links()
	{
		$link = 'links';
		$var[$link][1] = array(
			'text' => 'Contact', 
        		'path' => 'contact/contact',
    			'alias' => 'contact_us',
    			'controller' => 'contact',
    			'action' => 'contact',
    			'css_class' => array($this->module, 'main_item'),
        		'css_id' => $this->module 
        		);
        	return $var;
        }
        
        /**
    *   Sub navigation is a hook and displayed per call by hook_links
    */
    
    function hook_module_links($index = 0)
    {
 
    	$link = 'links';
    	
    	$var = array();
    	
    	$var[$link][1] = array( 
					'text' => 'Support', 
					'path' => $this->module . '/contact_support'
					);
		$var[$link][2] = array(
					'text' => 'Site Admin', 
					'path' => $this->module . '/contact_siteadmin'
					);
				
		
        
        return $var;
    }
        
        function contact()
        {
        	global $cck;
        	/// get all links from each class controller
        	$menu = $cck->_hooks('hook_links');
        	$sub_menu = $cck->_hooks('hook_module_links');
        	$output = "";
    	
        	$form = array();
    	        $form[] = array("form" => "addContact");
    	        $form[] = array("First name:" => "name_first");               
                $form[] = array(
				   "action" => "myscript.php",
				   "method" => "post",		   
				   );
                foreach($form as $key => $value){
                    if(is_string($value)){
                      $output .= $key . ":" . $value ."";
                    }
                    else{
                        foreach($value as $low_key => $low_value){
                          $output .= $low_key . ":" .  $low_value . "<br>";
                        }
                       
                    }
                }
		
            $variables['seperators'] = array('|','-',';',':');
    	    $variables['pageTitle'] = 'Contact';
    	    $variables['menuTitle'] = 'Contact';
    	    $variables['contentTitle'] = 'How to Get in touch';
    	    $variables['dbTable'] = 'userlist';
        
            $variables['mainNavigation'] = $cck->_menu_links($menu, 'links_main_menu', $variables);	
            $variables['subNavigation'] = $cck->_module_links($sub_menu[$this->module], array('template'=>'links_sub_menu','index' => $this->module), $variables); 

		    $variables['content'] = $output;
		    
		    print $cck->_view('default', $variables);
	}
}

?>

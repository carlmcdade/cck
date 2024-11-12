<?php



namespace contact;

use SQLite3;
/**
 * @author Carl McDade 
 * @copyright Carl McDade
 * @since 2011
 * @version 1.0
 * @license MIT
 * 
 * @link http://hardcopy.free.nf
 * ==================================================================
 * 
 *                        contact.class.inc
 * 
 * ==================================================================
 * This CCK example site is built around this blogging module.
 * It handles the blog content type
 *  
 * 
 */
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
	
	
        
    function contact_support($is_secure=TRUE)
    {
        global $cck,$ini_settings;
        // get all links from each class controller
        $database = $ini_settings['databases']['user_db'];
    	$table = array();
    	$columns = array();
    	$rows = array();
    	$output ='';
    	
    	/// build admin navigation links that only are used by this module/method
   
        
             	//$link = 'links';

    	$link = 'links';
    	
    	$var = array();
    	
    	$var[$link][1] = array( 
					'text' => 'Your Profile', 
					'path' => 'users/user_profile'
					);
		$var[$link][2] = array(
					'text' => 'Your Account', 
					'path' => 'users/user_account'
					);
		$var[$link][3] = array(
					'text' => 'Your Content', 
					'path' => 'users/user_blog'
					);
		$var[$link][4] = array(
				'text' => 'User settings',
				'path' => 'users/user_settings'
		);
		$var[$link][5] = array(
				'text' => 'Your Inbox',
				'path' => 'users/user_messages'
		);
			
    	
    	
    	$menu = $cck->_hooks('hook_links');    	
    	$sub_menu = $cck->_hooks('hook_module_links');
    	$admin_menu = $var;

    	//var_dump($sub_menu); exit;
    	$variables['menuTitle'] = 'Contact';
    	$variables['adminMenuTitle'] = 'User Admin';
    	$variables['pageTitle'] = 'Site Admin';
    	$variables['mainNavigation'] = $cck->_menu_links($menu, 'links_main_menu',$variables);
    	$variables['subNavigation'] = $cck->_module_links($sub_menu[$this->module],
    		array(
    			'template'=>'links_sub_menu',
    			'index' => $this->module
    			) , $variables); 
    	
    	$variables['adminNavigation'] = $cck->_module_links($admin_menu , array(
    			'template'=>'links_user_menu',
    			'index' => $this->module
    			) , $variables); 
    	
    	
    	
    	
    	$variables['contentTitle'] = $cck->_path_segment(1);
    	
    	$variables['postUrl'] = '?' .$cck->_path_segment(0). '/' . 'login_user'; 
    	
    	$output .=  $cck->_view('forms', $variables);
               
        $variables['content'] = $output;
        print $cck->_view('page_admin', $variables);
    }
    
    
        
    function contact_siteadmin($is_secure=TRUE)
    {
        global $cck,$ini_settings;
        // get all links from each class controller
        $database = $ini_settings['databases']['user_db'];
    	$table = array();
    	$columns = array();
    	$rows = array();
    	$output ='';
    	
    	/// build admin navigation links that only are used by this module/method
   
        
             	//$link = 'links';

    	$link = 'links';
    	
    	$var = array();
    	
    	$var[$link][1] = array( 
					'text' => 'Your Profile', 
					'path' => 'users/user_profile'
					);
		$var[$link][2] = array(
					'text' => 'Your Account', 
					'path' => 'users/user_account'
					);
		$var[$link][3] = array(
					'text' => 'Your Content', 
					'path' => 'users/user_blog'
					);
		$var[$link][4] = array(
				'text' => 'User settings',
				'path' => 'users/user_settings'
		);
		$var[$link][5] = array(
				'text' => 'Your Inbox',
				'path' => 'users/user_messages'
		);
			
    	
    	
    	$menu = $cck->_hooks('hook_links');    	
    	$sub_menu = $cck->_hooks('hook_module_links');
    	$admin_menu = $var;

    	//var_dump($sub_menu); exit;
    	$variables['menuTitle'] = 'Site Admin';
    	$variables['adminMenuTitle'] = 'User Admin';
    	$variables['pageTitle'] = 'Site Admin';
    	$variables['mainNavigation'] = $cck->_menu_links($menu, 'links_main_menu',$variables);
    	$variables['subNavigation'] = $cck->_module_links($sub_menu[$this->module],
    		array(
    			'template'=>'links_sub_menu',
    			'index' => $this->module
    			) , $variables); 
    	
    	$variables['adminNavigation'] = $cck->_module_links($admin_menu , array(
    			'template'=>'links_user_menu',
    			'index' => $this->module
    			) , $variables); 
    	
    	
    	
    	
    	$variables['contentTitle'] = $cck->_path_segment(1);
    	
    		$variables['postUrl'] = '?' .$cck->_path_segment(0). '/' . 'login_user'; 
    	
    	
    	$output .=  $cck->_view('forms', $variables);
               
    	     $variables['content'] = $output;
        print $cck->_view('page_admin', $variables);
    }
    
}

?>

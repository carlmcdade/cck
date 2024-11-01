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
 *                        users.class.inc
 * 
 * ==================================================================
 *
 * @todo 
 * 
 */

namespace users;

use SQLite3;

class users{
	
	private $common;
	public  $menu;
	public  $section;
	public  $module;

    function __construct()
    {
    	//Test the Common settings
		$this->module = __NAMESPACE__;
        
    }
    
    /**
     *
     * @return multitype:multitype:string
     */
    
    function hook_access()
    {
    	$authorize = array(
    			$this->module . '/users_profile' => array('users profile'),
    			$this->module . '/users_settings' => array('users settings'),
    			$this->module . '/users_control_panel' => array('users control panel'),
    			$this->module . '/users_history' => array('users history'),
    	);   
    	return $authorize;
    }
    
    /**
    *   Navigation hook for all modules
    */

    function hook_links()
    {
    	$link = 'links';
    	
    	$var[$link][1] = array(
        		'text' => 'My Account', 
        		'path' => $this->module . '/users_control_panel',
        		'controller' => 'users',
        		'action' => 'users_control_panel',
        		'css_class' => array($this->module, 'main_item'),
        		'css_id' => $this->module 
        		);
        return $var;
    }
    
    /**
    *   Sub navigation is a hook and displayed per call by hook_links
    */
    
    function hook_module_links()
    {
    	$link = 'links';
    	
    	$var[$link][1] = array(
					'text' => 'control panel', 
					'path' => $this->module . '/users_control_panel'
					);
    	$var[$link][2] = array( 
					'text' => 'profile', 
					'path' => $this->module . '/users_profile',
					'alias' => 'index',
					'controller' => $this->module,
					'action' => 'users_profile',
					'css_class' => array($this->module, 'main_item'),
					'css_id' => $this->module 
						);
		$var[$link][3] = array(
					'text' => 'settings', 
					'path' => $this->module . '/users_settings'
					);
		$var[$link][4] = array(
				'text' => 'history',
				'path' => $this->module . '/users_history'
		);		
        
        return $var;
    }
    
    /**
     * 
     * 
     */

    function users_profile()
    {
    	global $cck, $ini_settings;
    	
    
    	
    	$database = $ini_settings['databases']['user_db'];
    	$table = array();
    	$columns = array();
    	$rows = array();
    	
    	//$connect = $cck->_dbconnect($ini_settings['databases']['user_db']);
    	
    	// get all links from each class controller
    	$menu = $cck->_hooks('hook_links');
    	$sub_menu = $cck->_hooks('hook_module_links');
    	$variables = array();
    	$variables['pageTitle'] = 'User';
    	$variables['contentTitle'] = 'User profile';
    	$variables['menuTitle'] = 'User Panel';
    	$variables['dbTable'] = 'userlist';
    	$variables['mainNavigation'] = $cck->_menu_links($menu, 'links_main_menu', $variables);
    	$variables['sub_navigation'] = $cck->_module_links($sub_menu[$this->module],
    		array(
    			'template'=>'links_sub_menu',
    			'index' => $this->module
    			)
    		, $variables);
    	$db = new SQLite3($database);

        $result = $db->query('SELECT * FROM userlist WHERE id=' . $cck->_path_segment(2). '');
        
    	 while ($row = $result->fetchArray()) {
               $rows[] = $row;
         }
          //SQLite3Result::numColumns();
        for ($i = 0; $i < $result->numColumns(); $i++) {
			    $col = $result->columnName($i);
			    $columns[] = $col;
			}
				$table['header'] = $columns;
				$table['rows'] = $rows; 
				$output = $cck->_view('table', $table);
       
    	
    	// Get the content column values
      
    	
    	$variables['content'] =  'User Id: ' .$cck->_path_segment(2) . '<br>' . $output;
        print $cck->_view('users', $variables);         
    }
    
    /**
     * 
     * 
     */
    
    function users_control_panel()
    {
    	// set links
    	global $cck,$ini_settings;
    	
    	
    	$database = $ini_settings['databases']['user_db'];
    	$table = array();
    	$columns = array();
    	$rows = array();
   
    	
    	// get all links from each class controller
    	$menu = $cck->_hooks('hook_links');
    	$sub_menu = $cck->_hooks('hook_module_links');
    	$user_menu = $cck->_hooks('hook_user_links');
    	$variables = array();
    	$variables['menuTitle'] = 'User'; 	
    	$variables['pageTitle'] = 'User Control Panel';
    	$variables['contentTitle'] = '';
    	$variables['mainNavigation'] = $cck->_menu_links($menu, 'links_main_menu' , $variables);
    	$variables['subNavigation'] = $cck->_module_links($sub_menu[$this->module],
    		array(
    			'template'=>'links_sub_menu',
    			'index' => $this->module
    			)
    		, $variables); 
    	
    	$variables['content'] = '';  
    	print $cck->_view('users', $variables);
    }
    
    /**
     * 
     * 
     */
    
    function users_settings()
    {
    	// get all links from each class controller
    	global $cck, $ini_settings; 
    	
    	
    	$database = $ini_settings['databases']['user_db'];
    	$table = array();
    	$columns = array();
    	$rows = array();
   
    	
    	$menu = $cck->_hooks('hook_links');
    	$sub_menu = $cck->_hooks('hook_module_links');
    	$user_menu = $cck->_hooks('hook_user_links');
    	$variables['pageTitle'] = 'User';
    	$variables['contentTitle'] = 'User settings';
        
        $variables['menuTitle'] = 'User Settings';
    	$variables['mainNavigation'] = $cck->_menu_links($menu, 'links_main_menu', $variables);
    	$variables['subNavigation'] = $cck->_module_links($sub_menu[$this->module],
    		array(
    			'template'=>'links_sub_menu',
    			'index' => $this->module
    			), $variables); 
 
    	$db = new SQLite3($database);
    	
        $userID = $cck->_path_segment(2);
        if(!empty($userID))
        {
            $result = $db->query('SELECT * FROM userlist WHERE id='.$userID.'');
        }
        else
        {
        	$result = $db->query('SELECT * FROM userlist');
        }
        
    	 while ($row = $result->fetchArray()) {
               $rows[] = $row;
         }
          //SQLite3Result::numColumns();
        for ($i = 0; $i < $result->numColumns(); $i++) {
			    $col = $result->columnName($i);
			    $columns[] = $col;
			}
				$table['header'] = $columns;
				$table['rows'] = $rows; 
				$output = $cck->_view('table', $table);
		
       
    	
    	$variables['content'] = $output;
        print $cck->_view('users', $variables);
    }
    
    /**
     *
     *
     */
    
    function users_history()
    {
    	// get all links from each class controller
    	global $cck, $ini_settings; 
    	
    	$database = $ini_settings['databases']['user_db'];
    	$table = array();
    	$columns = array();
    	$rows = array();
   
    	
    	$menu = $cck->_hooks('hook_links');
    	$sub_menu = $cck->_hooks('hook_module_links');
    	$variables = array();
    	$variables['pageTitle'] = 'User History';
    	$variables['contentTitle'] = 'User History';
        $variables['dbTable'] = 'userlist';
        $variables['menuTitle'] = 'User History';
    	$variables['mainNavigation'] = $cck->_menu_links($menu, 'links_main_menu', $variables);
    	$variables['subNavigation'] = $cck->_module_links($sub_menu[$this->module],
    		array(
    			'template'=>'links_sub_menu',
    			'index' => $this->module
    			), $variables); 
// get user id from url 
    	$db = new SQLite3($database);
    	
        $userID = $cck->_path_segment(2);
        if(!empty($userID))
        {
            $result = $db->query('SELECT * FROM userlist WHERE id='.$userID.'');
        }
        else
        {
        	$result = $db->query('SELECT * FROM userlist');
        }
        
    	 while ($row = $result->fetchArray()) {
               $rows[] = $row;
         }
          //SQLite3Result::numColumns();
        for ($i = 0; $i < $result->numColumns(); $i++) {
			    $col = $result->columnName($i);
			    $columns[] = $col;
			}
				$table['header'] = $columns;
				$table['rows'] = $rows; 
				$output = $cck->_view('table', $table);
       
        
    	
    	$variables['content'] = $output;
    	print $cck->_view('users', $variables);
    }
    
    /**
     * 
     * 
     */
    
    function users_login_submit()
    {
    	$variables['content'] = 'show users logged in and redirect';
    	print $this->common->ber_view('users', $variables);
    }
    
    /**
     * 
     * 
     */
    
    function users_login_form()
    {
    	$variables['content'] = 'show users login form';
    	print $this->common->ber_view('users', $variables);
    }
    
    /**
     * 
     * 
     */
    
    function users_logout_submit()
    {
    	$variables['content'] = 'show users logged out and redirect';
    	print $this->common->ber_view('users', $variables);
    }
    
    /**
     * 
     * 
     */
    
    function users_logout()
    {
    	$variables['content'] = 'show users logout confirmation';
    	print $this->common->ber_view('users', $variables);
    }
}

?>

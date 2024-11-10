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
    			$this->module . '/user_profile' => array('users profile'),
    			$this->module . '/user_settings' => array('users settings'),
    			$this->module . '/user_control_panel' => array('users control panel'),
    			$this->module . '/user_history' => array('users history'),
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
        		'text' => 'Your Account', 
        		'path' => $this->module . '/user_control_panel',
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
    	
    	$var = array();
    	
    	$var[$link][1] = array( 
					'text' => 'Profiles', 
					'path' => 'admin/admin_user_profiles'
					);
		$var[$link][2] = array(
					'text' => 'Accounts', 
					'path' => 'admin/admin_user_accounts'
					);
		$var[$link][3] = array(
					'text' => 'Content', 
					'path' => 'admin/admin_user_content'
					);
		$var[$link][4] = array(
				'text' => 'User Settings',
				'path' => 'admin/admin_user_settings'
		);
		$var[$link][5] = array(
				'text' => 'User Messages',
				'path' => 'admin/admin_user_messages'
		);
			
    	
        return $var;
    }
    
    /**
     * 
     * 
     */

    function user_profile()
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
				$output = $cck->_view('table_profile_edit', $table);
       
    	
    	// check for user id no id means site owner
        $variables['userID'] = $cck->_path_segment(2);
        if (empty($cck->_path_segment(2))) {
            $variables['profileImage'] = 'default_user.jpeg';
            $variables['userHandle'] = 'Site Members';
            $variables['userBio'] = $cck->_view('default_footer', $variables);
            
          }else{
          	  
          foreach($rows as $key => $value){
          
          	$variables['profileImage'] =  $value ['image'];
            $variables['userHandle'] =  $value ['name'];
            $variables['userBio'] = $value['bio'];
          }
        }
         
         
        
    	$variables['contentTitle'] = $variables['userHandle'].'\'s profile';
    	$variables['content'] =  '<h3><i>Quick Edit</i></h3>' . $output;
        print $cck->_view('page_profile', $variables);         
    }
    
    /**
     * 
     * 
     */
    
    function user_control_panel()
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
		$output = $cck->_view('table_user_cp', $table);
		
    	// Get the content column values
        $variables['userID'] = $cck->_path_segment(2);
        if (empty($cck->_path_segment(2)))
        {
            $variables['profileImage'] = 'default_user.jpeg';
            $variables['userHandle'] = 'Site Members';
            $variables['menuTitle'] = 'Site Members'; 	
            
            $link = 'links';
    	
    	$var = array();
    	
    	$var[$link][1] = array( 
					'text' => 'User Profiles', 
					'path' => 'users/user_profile'
					);
		$var[$link][2] = array(
					'text' => 'User Accounts', 
					'path' => 'users/user_account'
					);
		$var[$link][3] = array(
					'text' => 'User Content', 
					'path' => 'blog/blog_user'
					);
		$var[$link][4] = array(
				'text' => 'User Settings',
				'path' => 'users/user_settings'
		);
		
			
    	
        }else{
          	  
            foreach($rows as $key => $value)
            {
          
          	    $variables['profileImage'] =  $value ['image'];
                $variables['userHandle'] =  $value ['name'];
                $variables['userBio'] = $value['bio'];
                $variables['menuTitle'] = $value['name']; 	
            }
                        
            $link = 'links';
    	
    	$var = array();
    	
    	$var[$link][1] = array( 
					'text' => 'Profile', 
					'path' => 'users/user_profile/' . $userID
					);
		$var[$link][2] = array(
					'text' => 'Accounts', 
					'path' => 'users/user_account/' . $userID
					);
		$var[$link][3] = array(
					'text' => 'Content', 
					'path' => 'users/user_blog/' . $userID
					);
		$var[$link][4] = array(
				'text' => 'Settings',
				'path' => 'users/user_settings/' . $userID
		);
		
			
        }
         
		
    	$variables['pageTitle'] = 'User Control Panel';
    	$variables['contentTitle'] = '';
    	$variables['mainNavigation'] = $cck->_menu_links($menu, 'links_main_menu' , $variables);
    	$variables['subNavigation'] = $cck->_module_links($var,
    		array(
    			'template'=>'links_sub_menu',
    			'index' => $this->module
    			)
    		, $variables); 
    	
    	$variables['content'] = $output;  
    	print $cck->_view('users', $variables);
    }
    
    /**
     * 
     * 
     */
    
    function user_settings()
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
				$output = $cck->_view('table_user_cp', $table);
		
		
       
    	
    	$variables['content'] = $output;
        print $cck->_view('users', $variables);
    }
    
    /**
     *
     *
     */
    
    function user_history()
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
    	print $cck->_view('users', $variables);
    }
    
    /**
     * 
     * 
     */
    
    function users_login_form()
    {
    	$variables['content'] = 'show users login form';
    	print $cck->_view('users', $variables);
    }
    
    function user_account($userID = NULL)
    {
         // get all links from each class controller
    	global $cck, $ini_settings;
    	$database = $ini_settings['databases']['user_db'];
    	$table = array();
    	$columns = array();
    	$rows = array();
   
    	// get all links from each class controller
    	$menu = $cck->_hooks('hook_links');    	
    	$sub_menu = $cck->_hooks('hook_module_links');
    	//var_dump($sub_menu); exit;
    	$variables['menuTitle'] = 'Site Admin';
    	$variables['pageTitle'] = 'Site Admin';
    	$variables['contentTitle'] = $cck->_path_segment(1);
    	$variables['mainNavigation'] = $cck->_menu_links($menu, 'links_main_menu',$variables);
    	$variables['subNavigation'] = $cck->_module_links($sub_menu[$this->module],
    		array(
    			'template'=>'links_sub_menu',
    			'index' => $this->module
    			) , $variables); 
    	
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
				$output = $cck->_view('table_user_cp', $table);
		// Get the content column values
        $variables['userID'] = $cck->_path_segment(2);
        if (empty($cck->_path_segment(2)))
        {
            $variables['profileImage'] = 'default_user.jpeg';
            $variables['userHandle'] = 'Site Members';
            $variables['menuTitle'] = 'Site Members'; 	
            
            $link = 'links';
    	
    	$var = array();
    	
    	$var[$link][1] = array( 
					'text' => 'User Profiles', 
					'path' => 'users/user_profile'
					);
		$var[$link][2] = array(
					'text' => 'User Accounts', 
					'path' => 'users/user_account'
					);
		$var[$link][3] = array(
					'text' => 'User Content', 
					'path' => 'users/user_blog'
					);
		$var[$link][4] = array(
				'text' => 'User Settings',
				'path' => 'users/user_settings'
		);
		
			
    	
        }else{
          	  
            foreach($rows as $key => $value)
            {
          
          	    $variables['profileImage'] =  $value ['image'];
                $variables['userHandle'] =  $value ['name'];
                $variables['userBio'] = $value['bio'];
                $variables['menuTitle'] = $value['name']; 	
            }
        }
         
		
    	$variables['pageTitle'] = 'User Account';
    	$variables['contentTitle'] = '';
    	$variables['mainNavigation'] = $cck->_menu_links($menu, 'links_main_menu' , $variables);
    	$variables['subNavigation'] = $cck->_module_links($var,
    		array(
    			'template'=>'links_sub_menu',
    			'index' => $this->module
    			)
    		, $variables); 
    	
        $variables['content'] = $output;
    	
    	print $cck->_view('page_profile', $variables);
    	
    }
    
    function user_blog($userID = NULL)
    {
         // get all links from each class controller
    	global $cck, $ini_settings;
    	$database = $ini_settings['databases']['user_db'];
    	$table = array();
    	$columns = array();
    	$rows = array();
   
    	// get all links from each class controller
    	$menu = $cck->_hooks('hook_links');    	
    	$sub_menu = $cck->_hooks('hook_module_links');
    	//var_dump($sub_menu); exit;
    	$variables['menuTitle'] = 'Site Admin';
    	$variables['pageTitle'] = 'Site Admin';
    	$variables['contentTitle'] = $cck->_path_segment(1);
    	$variables['mainNavigation'] = $cck->_menu_links($menu, 'links_main_menu',$variables);
    	$variables['subNavigation'] = $cck->_module_links($sub_menu[$this->module],
    		array(
    			'template'=>'links_sub_menu',
    			'index' => $this->module
    			) , $variables); 
    	
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
		
        $variables['content'] = "User Acoount: ". $output;
    	
    	print $cck->_view('page_admin', $variables);
    	
    }
    
    function user_content($userID = NULL)
    {
         // get all links from each class controller
    	global $cck, $ini_settings;
    	$database = $ini_settings['databases']['user_db'];
    	$table = array();
    	$columns = array();
    	$rows = array();
   
    	// get all links from each class controller
    	$menu = $cck->_hooks('hook_links');    	
    	$sub_menu = $cck->_hooks('hook_module_links');
    	//var_dump($sub_menu); exit;
    	$variables['menuTitle'] = 'Site Admin';
    	$variables['pageTitle'] = 'Site Admin';
    	$variables['contentTitle'] = $cck->_path_segment(1);
    	$variables['mainNavigation'] = $cck->_menu_links($menu, 'links_main_menu',$variables);
    	$variables['subNavigation'] = $cck->_module_links($sub_menu[$this->module],
    		array(
    			'template'=>'links_sub_menu',
    			'index' => $this->module
    			) , $variables); 
    	
    	
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
		
		
       
        $variables['content'] = "User Blog: ". $output;
    	
    	print $cck->_view('page_admin', $variables);
    	
    }
    
    function user_messages($userID = NULL)
    {
         // get all links from each class controller
    	global $cck, $ini_settings;
    	$database = $ini_settings['databases']['user_db'];
    	$table = array();
    	$columns = array();
    	$rows = array();
   
    	// get all links from each class controller
    	$menu = $cck->_hooks('hook_links');    	
    	$sub_menu = $cck->_hooks('hook_module_links');
    	//var_dump($sub_menu); exit;
    	$variables['menuTitle'] = 'Site Admin';
    	$variables['pageTitle'] = 'Site Admin';
    	$variables['contentTitle'] = $cck->_path_segment(1);
    	$variables['mainNavigation'] = $cck->_menu_links($menu, 'links_main_menu',$variables);
    	$variables['subNavigation'] = $cck->_module_links($sub_menu[$this->module],
    		array(
    			'template'=>'links_sub_menu',
    			'index' => $this->module
    			) , $variables); 
    	$db = new SQLite3($database);
    	$userID = $cck->_path_segment(2);

        $result = $db->query('SELECT * FROM userlist WHERE id="' . $userID. '"');
        
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
       
        $variables['content'] = "User Messages: ". $output;
    	
    	print $cck->_view('page_admin', $variables);
    	
    }
    /**
     * 
     * 
     */
    
    function users_logout_submit()
    {
    	$variables['content'] = 'show users logged out and redirect';
    	print $cck->_view('users', $variables);
    }
    
    /**
     * 
     * 
     */
    
    function users_logout()
    {
    	$variables['content'] = 'show users logout confirmation';
    	print $cck->_view('users', $variables);
    }
    
    function edit_user($userID = NULL)
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
        $userID = $cck->_path_segment(2);
    	$link = 'links';
    	
    	$var = array();
    	
    	$var[$link][1] = array( 
					'text' => 'Profile', 
					'path' => 'user/user_profile/'.$userID
					);
		$var[$link][2] = array(
					'text' => 'Account', 
					'path' => 'user/user_settings/'.$userID
					);
		$var[$link][3] = array(
					'text' => 'Content', 
					'path' => 'user/user_content/'.$userID
					);
		$var[$link][4] = array(
				'text' => 'Inbox',
				'path' => 'user/user_messages/' .$userID
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
				$output = $cck->_view('table_user_edit', $table);
				
		foreach($rows as $key => $value)			
		{
			$variables['userBio'] =  $value['bio'];
			$variables['userName'] = $value['name'];
			$variables['profileImage'] = $value['image'];
			$variables['userID'] = $userID;
		}
				
		$variables['content'] = $output;
		
        print $cck->_view('page_profile', $variables);
        
    }
    function edit_profile($userID = NULL)
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
        $userID = $cck->_path_segment(2);
    	$link = 'links';
    	
    	$var = array();
    	
    	$var[$link][1] = array( 
					'text' => 'Profile', 
					'path' => 'user/edit_profile/'.$userID
					);
		$var[$link][2] = array(
					'text' => 'Account', 
					'path' => 'user/edit_user/'.$userID
					);
		$var[$link][3] = array(
					'text' => 'Content', 
					'path' => 'user/edit_post/'.$userID
					);
		$var[$link][4] = array(
				'text' => 'Settings',
				'path' => 'user/edit_user_settings/'.$userID
		);
		$var[$link][5] = array(
				'text' => 'Inbox',
				'path' => 'user/edit_messages/' .$userID
		);
			
    	
    	
    	$sub_menu = $cck->_hooks('hook_module_links');
    	$menu = $cck->_hooks('hook_links');    	
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
				$output = $cck->_view('table_user_edit', $table);
				
		foreach($rows as $key => $value)			
		{
			$variables['userBio'] =  $value['bio'];
			$variables['userName'] = $value['name'];
			$variables['profileImage'] = $value['image'];
			$variables['userID'] = $userID;
		}
				
		$variables['content'] = $output;
		
        print $cck->_view('page_profile', $variables);
        
    }
    
    function edit_user_save()
    {
   	$link = 'links';
    	
          
    	global $cck,$ini_settings;
        // get all links from each class controller
        $database = $ini_settings['databases']['user_db'];
    	$table = array();
    	$columns = array();
    	$rows = array();
    	$var = array();
    	$output ='';
    	
   
	    $var = array();
    	
    	$var[$link][1] = array( 
						'path' => 'users/user_profile'
					);
		$var[$link][2] = array(
					'text' => 'User Accounts', 
					'path' => 'users/user_account'
					);
		$var[$link][3] = array(
					'text' => 'User Content', 
					'path' => 'blog/blog_user'
					);
		$var[$link][4] = array(
				'text' => 'User Settings',
				'path' => 'users/user_settings'
		);
		
			
    	
    	$sub_menu = $cck->_hooks('hook_module_links');
    	$menu = $cck->_hooks('hook_links');    	
    	$admin_menu = $var;

    	
    	//var_dump($sub_menu); exit;
    	$variables['menuTitle'] = 'Site Admin';
    	$variables['adminMenuTitle'] = 'User Admin';
    	$variables['pageTitle'] = 'User account saved';
    	$variables['contentTitle'] = 'account saved';
    	$variables['userBio'] = 'thanks for the updated information';
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
    	$output = $cck->_target('form_post');
    	$variables['content'] =  $output;
		
        print $cck->_view('page_profile', $variables);
        
    }
    
        
    function edit_profile_save()
    {
        global $cck,$ini_settings;
        // get all links from each class controller
        $database = $ini_settings['databases']['user_db'];
    	$table = array();
    	$columns = array();
    	$rows = array();
    	$var = array();
    	$output ='';
    	
    	$link = 'links';
    	
    	 
		$var = array();
    	
    	$var[$link][1] = array( 
						'path' => 'users/user_profile'
					);
		$var[$link][2] = array(
					'text' => 'User Accounts', 
					'path' => 'users/user_account'
					);
		$var[$link][3] = array(
					'text' => 'User Content', 
					'path' => 'blog/blog_user'
					);
		$var[$link][4] = array(
				'text' => 'User Settings',
				'path' => 'users/user_settings'
		);
		
			
    	
    	$sub_menu = $cck->_hooks('hook_module_links');
    	$menu = $cck->_hooks('hook_links');    	
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
    	
    	$variables['content'] = $output;
		
        print $cck->_view('page_profile', $variables);
        
    }
}

?>

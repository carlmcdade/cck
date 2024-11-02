<?php

/*
 * @author Carl McDade
 * @copyright Copyright (c) 2010, Carl McDade
 * @since 2010-02-19
 * @version 0.2
 * @
 * @
 *
 */

namespace admin;

use SQLite3;

class admin extends SQLite3 {
	
	public  $common;
	public  $menu;
	public  $title = 'Administration';
	public  $module;
	public  $section;
	public  $database = '';
	
	
    function __construct()
    {
        //Test the Common settings
        $this->module = __NAMESPACE__;
        $this->section = __NAMESPACE__;        
    }
    
    /**
     *   Navigation hook for all modules
     */
    
    function hook_links()
    {
    	$link = 'links';
    	
    	$var[$link][1] = array(
        		'text' => 'Administration', 
        		'path' => $this->module . '/main',
    			'alias' => 'index',
    			'controller' => $this->module,
    			'action' => 'main',
    			'css_class' => array($this->module, 'main_item'),
        		'css_id' => $this->module 
        		);
        
        return $var;
    }
  
    function hook_access()
    {
        $authorize = array(
			$this->module . '/main' => array('access foo'),
			$this->module . '/blocks' => array('access baz'),
			$this->module . '/themes' => array('access boo'),
        );

        return $authorize;
    }

    /**
    *   Sub navigation is a hook and displayed per call by hook_links
    */
    
    function hook_module_links($index = 0)
    {
 
    	$link = 'links';
    	
    	$var = array();
    	
    	$var[$link][1] = array( 
					'text' => 'Users', 
					'path' => $this->module . '/admin_user'
					);
		$var[$link][2] = array(
					'text' => 'Categories', 
					'path' => $this->module . '/admin_categories'
					);
		$var[$link][3] = array(
					'text' => 'Blogs', 
					'path' => $this->module . '/admin_blog'
					);
		$var[$link][4] = array(
				'text' => 'Posts',
				'path' => $this->module . '/admin_posts'
		);
		$var[$link][4] = array(
				'text' => 'Database',
				'path' => $this->module . '/admin_database'
		);
				
		
        
        return $var;
    }
    

    function main($output = NULL)
    {
        // get all links from each class controller
    	global $cck, $ini_settings; 
    	// get all links from each class controller
    	$menu = $cck->_hooks('hook_links');    	
    	$sub_menu = $cck->_hooks('hook_module_links');
    	
    	$variables['menuTitle'] = 'Site Admin';
    	$variables['pageTitle'] = 'Site Admin';
    	$variables['contentTitle'] = 'Login to Site';
    	$variables['mainNavigation'] = $cck->_menu_links($menu, 'links_main_menu',$variables);
    	$variables['subNavigation'] = $cck->_module_links($sub_menu[$this->module],
    		array(
    			'template'=>'links_sub_menu',
    			'index' => $this->module
    			) , $variables);
    	
    	
    	
    		$variables['postUrl'] = '?' .$cck->_path_segment(0). '/' . 'login_user'; 
    	
    	
    	$output .=  $cck->_view('forms', $variables);
               
        $variables['content'] = "<div>". $output ."</div>";
    	
    	print $cck->_view('page_form', $variables);
    }
    function allblogs()
    {
// get all links from each class controller
    	global $cck, $ini_settings;
    	
    	$database = $ini_settings['databases']['user_db'];
    	// get all links from each class controller
    	$menu = $cck->_hooks('hook_links');    	
    	$sub_menu = $cck->_hooks('hook_module_links');
    	//var_dump($sub_menu); exit;
    	$variables['menuTitle'] = 'Site Admin';
    	$variables['pageTitle'] = 'Site Admin';
    	$variables['contentTitle'] = 'site admin';
    	$variables['mainNavigation'] = $cck->_menu_links($menu, 'links_main_menu',$variables);
    	$variables['subNavigation'] = $cck->_module_links($sub_menu[$this->module],
    		array(
    			'template'=>'links_sub_menu',
    			'index' => $this->module
    			) , $variables); 
    	
    	
    	
               
        $variables['content'] = 'all blogs list admin panel';
    	
    	print $cck->_view('page_admin', $variables);
    }
    
    function admin_blog($is_secure = NULL)
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

        $result = $db->query('SELECT * FROM blogs');
        
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
				$output = $cck->_view('table_blogs', $table);
       
    	
    	
               
        $variables['content'] = 'blog user admin panel' . $output;
    	
    	print $cck->_view('page_admin', $variables);
    }
    
    function admin_database($is_secure = NULL)
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

        $result = $db->query('SELECT * FROM userlist');
        
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
       
        $variables['content'] = "connect to sqlite database: ". $output;
    	
    	print $cck->_view('page_admin', $variables);
    }


    function blocks()
    {
        // get all links from each class controller
    	global $cck; 
    	// get all links from each class controller
    	$menu = $cck->_hooks('hook_links');    	
    	$sub_menu = $cck->_hooks('hook_module_links');
    	//var_dump($sub_menu); exit;
    	$variables['menuTitle'] = 'Site Admin';
    	$variables['pageTitle'] = 'Site Admin';
    	$variables['contentTitle'] = 'site admin';
    	$variables['mainNavigation'] = $cck->_menu_links($menu, 'links_main_menu',$variables);
    	$variables['subNavigation'] = $cck->_module_links($sub_menu[$this->module],
    		array(
    			'template'=>'links_sub_menu',
    			'index' => $this->module
    			) , $variables); 
    	
    	
    	
               
        $variables['content'] = 'main admin panel';
    	
    	print $cck->_view('page_admin', $variables);
    }
    
    function themes()
    {
        global $cck;
        // get all links from each class controller
    	
    	$menu = $cck->_hooks('hook_links');    	
    	$sub_menu = $cck->_hooks('hook_module_links');
    	//var_dump($sub_menu); exit;
    	$variables['menuTitle'] = 'Site Admin';
    	$variables['pageTitle'] = 'Site Admin';
    	$variables['contentTitle'] = 'site admin';
    	$variables['mainNavigation'] = $cck->_menu_links($menu, 'links_main_menu',$variables);
    	$variables['subNavigation'] = $cck->_module_links($sub_menu[$this->module],
    		array(
    			'template'=>'links_sub_menu',
    			'index' => $this->module
    			) , $variables); 
    	
    	
    	
    	$variables['pageTitle'] = $this->title;
    	$variables['mainNavigation'] = $cck->_menu_links($main_menu);
    	
    	$variables['content'] = 'admin form submit';
        print $cck->_view('page_admin', $variables);
    }
    
    function posts()
    {
         // get all links from each class controller
    	global $cck; 
    	// get all links from each class controller
    	$menu = $cck->_hooks('hook_links');    	
    	$sub_menu = $cck->_hooks('hook_module_links');
    	//var_dump($sub_menu); exit;
    	$variables['menuTitle'] = 'Site Admin';
    	$variables['pageTitle'] = 'Site Admin';
    	$variables['contentTitle'] = 'site admin';
    	$variables['mainNavigation'] = $cck->_menu_links($menu, 'links_main_menu',$variables);
    	$variables['subNavigation'] = $cck->_module_links($sub_menu[$this->module],
    		array(
    			'template'=>'links_sub_menu',
    			'index' => $this->module
    			) , $variables); 
    	
    	
    	
               
        $variables['content'] = 'post admin panel';
    	
    	print $cck->_view('page_admin', $variables);
    }
    
    function admin_categories()
    {
         // get all links from each class controller
    	global $cck,$ini_settings;
    	
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
    	$variables['contentTitle'] = 'site admin';
    	$variables['mainNavigation'] = $cck->_menu_links($menu, 'links_main_menu',$variables);
    	$variables['subNavigation'] = $cck->_module_links($sub_menu[$this->module],
    		array(
    			'template'=>'links_sub_menu',
    			'index' => $this->module
    			) , $variables); 
    	$db = new SQLite3($database);

        $result = $db->query('SELECT * FROM categories');
        
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
				$output = $cck->_view('table_categories', $table);
    	
    	
               
        $variables['content'] = 'categories admin panel' . $output;
    	
    	print $cck->_view('page_admin', $variables);
    }
    
    function admin_user($is_secure=TRUE)
    {
        global $cck,$ini_settings;
        // get all links from each class controller
        $database = $ini_settings['databases']['user_db'];
    	$table = array();
    	$columns = array();
    	$rows = array();
    	$output ='';
    	
    	$menu = $cck->_hooks('hook_links');    	
    	$sub_menu = $cck->_hooks('hook_module_links');
    	//var_dump($sub_menu); exit;
    	$variables['menuTitle'] = 'Site Admin';
    	$variables['pageTitle'] = 'Site Admin';
    	$variables['mainNavigation'] = $cck->_menu_links($menu, 'links_main_menu',$variables);
    	$variables['subNavigation'] = $cck->_module_links($sub_menu[$this->module],
    		array(
    			'template'=>'links_sub_menu',
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
				$output = $cck->_view('table', $table);
		$variables['content'] = $output;
        print $cck->_view('page_admin', $variables);
    }

        
    function login_user($is_secure=TRUE)
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
    	$db = new SQLite3($database);

        $result = $db->query('SELECT * FROM userlist');
        
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
				$output = $cck->_view('table_users', $table);
       
    	     $variables['content'] = $output;
        print $cck->_view('page_admin', $variables);
    }
    
    function admin_users_profile($userID = NULL)
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
					'path' => 'users/user_content'
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
		
        print $cck->_view('page_admin', $variables);
    
    }
}

?>

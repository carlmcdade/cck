<?php



namespace admin;

use SQLite3;
use \content\content;

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
 *                        admin.class.inc
 * 
 * ==================================================================
 * This CCK example site is built around this blogging module.
 * It handles the blog content type
 *  
 * 
 */
class admin {
	
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
    /**
    Permisssion and access hook for per [module]/[method]security check
    */
  
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
					'text' => 'Accounts', 
					'path' => $this->module . '/admin_user_accounts',
					'css_id' => $this->module,
					'css_class' => array($this->module)
					);
		
		$var[$link][2] = array(
					'text' => 'Profiles',
					'path' => $this->module . '/admin_user_profiles',
					'css_id' => $this->module,
					'css_class' => array($this->module)
		);
				
		$var[$link][3] = array(
					'text' => 'Categories', 
					'path' => $this->module . '/admin_categories',
					'css_id' => $this->module,
					'css_class' => array($this->module)
					);
		$var[$link][4] = array(
					'text' => 'Content', 
					'path' => $this->module . '/admin_content',
					'css_id' => $this->module,
					'css_class' => array($this->module)
					);
		$var[$link][5] = array(
					'text' => 'Security',
					'path' => $this->module . '/admin_permissions',
					'css_id' => $this->module,
					'css_class' => array($this->module)
		);
		$var[$link][6] = array(
					'text' => 'Databases',
					'path' => $this->module . '/admin_databases',
					'css_id' => $this->module,
					'css_class' => array($this->module)
		);
		$var[$link][7] = array(
					'text' => 'Modules',
					'path' => $this->module . '/admin_modules',
					'css_id' => $this->module,
					'css_class' => array($this->module)
		);
		$var[$link][8] = array(
				'text' => 'Configuration',
				'path' => $this->module . '/admin_config',
				'css_id' => $this->module,
				'css_class' => array($this->module)

		);
					
					
        
        return $var;
    }
    

    function main($output = NULL)
    {
        // get all links from each class controller
    	global $cck, $ini_settings; 
		$output = '';
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
    			'index' => $this->module,
				'css_id' => $this->module,
				'css_class' => array($this->module)
    			) , $variables);
    	
    	
    	$variables['formName'] = $cck->_path_segment(1);
		;
    	$variables['postUrl'] = '?' .$cck->_path_segment(0). '/' . 'login_user'; 
    	
    	
    	$output .=  $cck->_view('forms', $variables);
               
        $variables['content'] = $output ;
    	
    	print $cck->_view('page_admin_form', $variables);
    }


    function admin_profiles()
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
    			'index' => $this->module,
				'css_id' => $this->module,
				'css_class' => array($this->module)
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
				$output = $cck->_view('table_users_admin', $table);
		$variables['content'] = $output;
    	
    	print $cck->_view('page_admin', $variables);
    }
    
    function admin_blogs($is_secure = NULL)
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
    			'index' => $this->module,
				'css_id' => $this->module,
				'css_class' => array($this->module)
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
    
    function admin_databases($is_secure = NULL)
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
    			'index' => $this->module,
				'css_id' => $this->module,
				'css_class' => array($this->module)
    			) , $variables); 
    	$db = $ini_settings['databases'];

				$table['header'] = array('name', 'datasource');
		        foreach($db as $alias => $name){
				     $rows[]= array($alias,$name); 
		        }
		        $table['rows'] = $rows;
				$output = $cck->_view('table', $table);
       
        $variables['content'] = "Databases noted in config.ini file : ". $output;
    	
    	print $cck->_view('page_admin', $variables);
    }
    
    
    
    
    function admin_modules()
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
    	$variables['contentTitle'] = 'admin site modules';
    	$variables['mainNavigation'] = $cck->_menu_links($menu, 'links_main_menu',$variables);
    	$variables['subNavigation'] = $cck->_module_links($sub_menu[$this->module],
    		array(
    			'template'=>'links_sub_menu',
    			'index' => $this->module,
				'css_id' => $this->module,
				'css_class' => array($this->module)
    			) , $variables); 
        $counter= 0;
        $sections = $ini_settings['modules'];
        //var_dump($sections);
                
        
				
			//foreach($section as $name => $value){	
			
              
		        foreach($sections as $alias => $string){
		        	$names = array_keys($sections); 
				    $table['section'] = 'modules';
		        	$rows[] = array($alias,$string);

				     
		        }


		        		        

		       
		$table['header'] = array('Action', 'Module','Documentation');
        $table['rows'] = $rows;
		$table['module'] = $rows[1];
		$table['section'] = $sections[1];
		$output = $cck->_view('table_module_ini', $table);
        
        $variables['content'] = 'configure and admin modules [ <i>config.ini</i>  ]'. $output;
    	
    	print $cck->_view('page_admin', $variables);
    }
    
    /*
     Documentation function  to show developer comments that are to to used
     by end users and developers. Removing the need for documentation that is 
     seperate for the site. Future plan is to make it a module rather that a 
     group of functions in the admin module
    */
    function module_comments_view($module = NULL){
    	
    	/* ====================== variables ===============*/
            global $cck,$ini_settings;
            $variables = array();
            $table = array();
            $output = '';
        /* ====================== menus ===============*/    
            $menu = $cck->_hooks('hook_links');    	
    	    $sub_menu = $cck->_hooks('hook_module_links');
    	    $module = $cck->_path_segment(2);
    	
            
            $variables['menuTitle'] = 'Site Admin';
    	    $variables['pageTitle'] = 'Site Admin';
    	    $variables['contentTitle'] = $module . ' - documentation';
    	    $variables['mainNavigation'] = $cck->_menu_links($menu, 'links_main_menu',$variables);
    	    $variables['subNavigation'] = $cck->_module_links($sub_menu[$this->module],
    		array(
    			'template'=>'links_sub_menu',
    			'index' => $this->module,
				'css_id' => $this->module,
				'css_class' => array($this->module)
    			) , $variables); 
       
          

            if(is_numeric($module)){
                $module = $ini_settings['modules'][$module];
                $module_class = "\\" . $module."\\". $module;
                $rc = new \ReflectionClass($module_class);
                $table['rows'] = array(array($module, $rc->getDocComment()));
            }
            
            elseif(empty($module)){
            
            // list modules
            exit('nothing found');
            
            }
            else{
            	
            
            $module_class = "\\" . $module."\\". $module;
            $rc = new \ReflectionClass($module_class);
         
            //$class_methods = get_class_methods(new myclass());
            
            $class_methods = get_class_methods($module_class);
            //var_dump($class_methods);
            foreach($class_methods as $key => $name)
            {
            	    $method_comments[] =  $rc->getMethod($name)->getDocComment();
            }
            //exit(var_dump($method_comments));
            $table['otherModules'] = $ini_settings['modules'];
            $table['moduleMethods'] =  $class_methods;
            $table['moduleComments'] = $method_comments;
            $table['rows'] = array(array($module, '<p class="fs-6"><pre style="overflow-x: auto;" class="">'. $rc->getDocComment().'</pre></p>'));
            
            }

    	/* ====================== content ===============*/
          
            $table['header'] = array( ' Developer comments', 'Methods'); 
            
            $table['module'] = $module;
        /* ====================== content template ===============*/
            $output = $cck->_view('table_module_comments', $table);
            $variables['content'] = $output;
        /* ====================== page template ===============*/
            print $cck->_view('page_admin', $variables);
    
    }
    
     
    /*
     Documentation function  to show developer comments that are to to used
     by end users and developers. Removing the need for documentation that is 
     seperate for the site. Future plan is to make it a module rather that a 
     group of functions in the admin module
    */
    
    
    function module_comments($comments_class){
    	
             $get_comments = new ReflectionClass($comments_class);
             return $get_comments->getDocComment();
    }
    
    function admin_config()
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
    			'index' => $this->module,
				'css_id' => $this->module,
				'css_class' => array($this->module)
    			) , $variables); 
        $counter= 0;
        $sections = array_keys($ini_settings);
        //var_dump($sections);
                
        foreach ($sections as $section => $name){
				
			//foreach($section as $name => $value){	
			
                $table['section'] = $name;
		        foreach($ini_settings[$name] as $alias => $string){
				     $rows[] = array($alias,$string, $name);

				     
		        }


		        		        

		}       
		        $table['header'] = array('field', 'data','section');
                 $table['rows'] = $rows;
		
		$output = $cck->_view('table_config_ini', $table);
       
        $variables['content'] = "Config.ini file : ". $output;
    	
    
    	
    	print $cck->_view('page_admin', $variables);
    }
    


    function admin_blocks()
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
    			'index' => $this->module,
				'css_id' => $this->module,
				'css_class' => array($this->module)
    			) , $variables); 
    	
    	
    	
               
        $variables['content'] = 'main admin panel';
    	
    	print $cck->_view('page_admin', $variables);
    }
    
    function admin_themes()
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
    			'index' => $this->module,
				'css_id' => $this->module,
				'css_class' => array($this->module)
    			) , $variables); 
    	
    	
    	
    	$variables['pageTitle'] = $this->title;
    	$variables['mainNavigation'] = $cck->_menu_links($main_menu);
    	
    	$variables['content'] = 'admin form submit';
        print $cck->_view('page_admin', $variables);
    }
    
    function admin_content()
    {
        global $cck,$ini_settings;
        
    	$database = $ini_settings['databases']['user_db'];
    	$table = array();
    	$columns = array();
    	$rows = array();
    	
    	//some variables to load into the view will appear as $[variable name]
      	$output = '';
    	$menu = $cck->_hooks('hook_links');
    	$sub_menu = $cck->_hooks('hook_module_links');
    	$variables['seperators'] = array('|','-',';',':');
    	$variables['pageTitle'] = 'Content';
    	$variables['menuTitle'] = 'Site Admin';
    	$variables['adminMenuTitle'] = 'Content Admin';
    	$variables['contentTitle'] = 'Content Types';
    	$variables['dbTable'] = 'content_types';
        
    	       	//$link = 'links';

    	$link = 'links';
    	
    	$var = array();
    	
    	$var[$link][1] = array( 
					'text' => 'Content List', 
					'path' => 'admin/content_list',
					'css_id' => $this->module,
				    'css_class' => array($this->module)
					
					);
		$var[$link][2] = array(
					'text' => 'Content Add', 
					'path' => 'admin/content_add',
					'css_id' => $this->module,
					'css_class' => array($this->module)
					);
		$var[$link][3] = array(
					'text' => 'Content Permissions', 
					'path' => 'admin/content_permissions',
					'css_id' => $this->module,
					'css_class' => array($this->module)
					);
		$admin_menu = $var;    	
    	//$admin_menu = $cck->_hooks('hook_module_links');
    	
    	$db = new SQLite3($database);

    	    	
        $userID = $cck->_path_segment(2);
        if(!empty($typeID))
        {
            $result = $db->query('SELECT * FROM content_types WHERE id='.$typeID.'');
        }
        else
        {
        	$result = $db->query('SELECT * FROM content_types');
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
				$output = $cck->_view('table_content_types', $table);
				
		foreach($rows as $key => $value)			
		{
			$variables['userBio'] =  '';
			$variables['userName'] = '';
			$variables['profileImage'] = '';
			$variables['userID'] = '';
		}
		$variables['mainNavigation'] = $cck->_menu_links($menu, 'links_main_menu',$variables);
		$variables['subNavigation'] = $cck->_module_links($sub_menu[$this->module],
    		array(
    			'template'=>'links_sub_menu',
    			'index' => $this->module,
				'css_id' => $this->module,
				'css_class' => array($this->module)
    			) , $variables); 
    	
    	$variables['adminNavigation'] = $cck->_module_links($admin_menu , array(
    			'template'=>'links_user_menu',
    			'index' => $this->module,
				'css_id' => $this->module,
				'css_class' => array($this->module)
    			) , $variables); 
    	
               
        $variables['content'] = 'admin content types' . $output;
    	print $cck->_view('page_admin', $variables);
   
    }
    
	
	function admin_content_field_add()
    {

        global $cck,$ini_settings;

        $database = $ini_settings['databases']['user_db'];
        $form = array();
        $columns = array();
        $rows = array();

        // get all links from each class controller
        $menu = $cck->_hooks('hook_links');
        $sub_menu = $cck->_hooks('hook_module_links');
        //var_dump($sub_menu); exit;
        $variables['menuTitle'] = 'Site Admin';
        $variables['contentTitle'] = 'Add Field to - <i>'. $_POST['content_type'].'</i>';
        $variables['pageTitle'] = 'Admin - Content Types';
        $variables['mainNavigation'] = $cck->_menu_links($menu, 'links_main_menu', $variables);

        //$link = 'links';
        $userID = $cck->_path_segment(2);

        $variables['subNavigation'] = $cck->_module_links(
            $sub_menu[$this->module],
            array(
                'template' => 'links_sub_menu',
                'index' => $this->module,
                'css_class' => array($this->module, 'sub_item'),
                'css_id' => $this->module
                ),
            $variables
        );


        $db = new SQLite3($database);

        $typeID = $cck->_path_segment(2);

        $resultAdd = $db->query('SELECT * FROM content_types WHERE type_id ="'. $typeID.'";');
        $result = $db->query('SELECT * FROM content_type_fields WHERE content_type_id ="'. $typeID.'" ORDER BY weight asc;');

        while ($row = $result->fetchArray()) {
            $rows[] = $row;

        }


        while ($rowAdd = $resultAdd->fetchArray()) {
            $form['contentType'] = $rowAdd['name'];
			$form['contentTypeId'] = $rowAdd['id'];

            $r[] = $rowAdd;
        }
        //var_dump($rows);
        //SQLite3Result::numColumns();
        for ($i = 0; $i < $result->numColumns(); $i++) {
            $col = $result->columnName($i);
            $columns[$col] = $col;
        }
        $form['formAction'] = '?content/content_post_save/'. $form['contentType'];
        $form['mimeType'] = '';
        $form['header'] = $columns;
        $form['rows'] = $rows;
       
		$form['contentUserId'] = (isset($form['contentUserId']) ? $form['contentUserId'] : '1');
		$form['userName'] = (isset($form['userName']) ? $form['userName'] : 'owner');
		$form['contentType'] = (isset($form['contentType']) ? $form['contentType'] : '');
		$form['contentId'] = $form['contentType'].'-'.hash('crc32',$cck->_path_segment(1).time() . mt_rand()) .'-'. $form['userName'];
        $form['contentTime'] = date("Y-m-d H:i:s"); 
        $output = $cck->_view('form_content_field_add', $form);



        $variables['content'] = 'Add new field to - <h3><i>'.$form['contentType'].'</i></h3>' . $output;

        print $cck->_view('page_admin_form', $variables);

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
    			'index' => $this->module,
				'css_id' => $this->module,
				'css_class' => array($this->module)
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
    
    function admin_users($is_secure=TRUE)
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
    
    	
    	
             	//$link = 'links';
        $userID = $cck->_path_segment(2);
    	$link = 'links';
    	
    	$var = array();
    	
    	$var[$link][1] = array( 
					'text' => 'Profile', 
					'path' => 'admin/admin_user_profiles/'. $userID,
					'css_id' => $this->module,
					'css_class' => array($this->module)
					);
		$var[$link][2] = array(
					'text' => 'Account', 
					'path' => 'admin/admin_user_accounts/' . $userID,
					'css_id' => $this->module,
					'css_class' => array($this->module)
					);
		$var[$link][3] = array(
					'text' => 'Content', 
					'path' => 'admin/admin_user_content/'. $userID,
					'css_id' => $this->module,
					'css_class' => array($this->module)
					);
		$var[$link][4] = array(
					'text' => 'Settings',
					'path' => 'admin/admin_user_settings/'. $userID,
					'css_id' => $this->module,
					'css_class' => array($this->module)
		);
		$var[$link][5] = array(
					'text' => 'Inbox',
					'path' => 'admin/admin_user_messages/'. $userID,
					'css_id' => $this->module,
					'css_class' => array($this->module)
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
    			'index' => $this->module,
				'css_id' => $this->module,
				'css_class' => array($this->module)
    			) , $variables); 
    	
    	$variables['adminNavigation'] = $cck->_module_links($admin_menu , array(
    			'template'=>'links_user_menu',
    			'index' => $this->module,
				'css_id' => $this->module,
				'css_class' => array($this->module)
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
				$output = $cck->_view('table_users_admin', $table);
		$variables['content'] = $output;
        print $cck->_view('page_admin', $variables);
    }
    
    function admin_user_content($userID = NULL){
    	
    	     
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
    	$variables['contentTitle'] = 'admin user content';
    	$variables['mainNavigation'] = $cck->_menu_links($menu, 'links_main_menu',$variables);
    	
             	//$link = 'links';
        $userID = $cck->_path_segment(2);
    	$link = 'links';
    	
    	$var = array();
    	
    	$var[$link][1] = array( 
					'text' => 'Profile', 
					'path' => 'admin/admin_user_profiles/'. $userID,
					'css_id' => $this->module,
					'css_class' => array($this->module)
					);
		$var[$link][2] = array(
					'text' => 'Account', 
					'path' => 'admin/admin_user_accounts/' . $userID,
					'css_id' => $this->module,
					'css_class' => array($this->module)
					);
		$var[$link][3] = array(
					'text' => 'Content', 
					'path' => 'admin/admin_user_content/'. $userID,
					'css_id' => $this->module,
					'css_class' => array($this->module)
					);
		$var[$link][4] = array(
					'text' => 'Settings',
					'path' => 'admin/edit_user_settings/'. $userID,
					'css_id' => $this->module,
					'css_class' => array($this->module)
		);
		$var[$link][5] = array(
					'text' => 'Inbox',
					'path' => 'admin/admin_user_messages/'. $userID,
					'css_id' => $this->module,
					'css_class' => array($this->module)
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
    			'index' => $this->module,
				'css_id' => $this->module,
				'css_class' => array($this->module)
    			) , $variables); 
    	
    	$variables['adminNavigation'] = $cck->_module_links($admin_menu , array(
    			'template'=>'links_user_menu',
    			'index' => $this->module,
				'css_id' => $this->module,
				'css_class' => array($this->module)
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
    	
    	
               
        $variables['content'] = 'admin  user_error content panel' . $output;
    	
    	print $cck->_view('page_admin', $variables);
    }
    
    function admin_user_profiles($userID = NULL)
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
					'path' => 'users/user_profile/'.$userID,
					'css_id' => $this->module,
				'css_class' => array($this->module)
					);
		$var[$link][2] = array(
					'text' => 'Account', 
					'path' => 'users/user_settings/'.$userID,
					'css_id' => $this->module,
				'css_class' => array($this->module)
					);
		$var[$link][3] = array(
					'text' => 'Content', 
					'path' => 'users/user_content/'.$userID,
					'css_id' => $this->module,
				'css_class' => array($this->module)
					);
		$var[$link][4] = array(
				'text' => 'Inbox',
				'path' => 'users/user_messages/' .$userID,
				'css_id' => $this->module,
				'css_class' => array($this->module)
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
    			'index' => $this->module,
				'css_id' => $this->module,
				'css_class' => array($this->module)
    			) , $variables); 
    	
    	$variables['adminNavigation'] = $cck->_module_links($admin_menu , array(
    			'template'=>'links_user_menu',
    			'index' => $this->module,
				'css_id' => $this->module,
				'css_class' => array($this->module)
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
		
        print $cck->_view('page_admin', $variables);
        
    }
    
    function admin_user_accounts($userID = NULL){
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
					'path' => 'users/user_profile/'.$userID,
					'css_id' => $this->module,
				'css_class' => array($this->module)
					);
		$var[$link][2] = array(
					'text' => 'Account', 
					'path' => 'users/user_settings/'.$userID,
					'css_id' => $this->module,
				'css_class' => array($this->module)
					);
		$var[$link][3] = array(
					'text' => 'Content', 
					'path' => 'users/user_content/'.$userID,
					'css_id' => $this->module,
				'css_class' => array($this->module)
					);
		$var[$link][4] = array(
				'text' => 'Inbox',
				'path' => 'users/user_messages/' .$userID,'css_id' => $this->module,
				'css_class' => array($this->module)
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
    			'index' => $this->module,
				'css_id' => $this->module,
				'css_class' => array($this->module)
    			) , $variables); 
    	
    	$variables['adminNavigation'] = $cck->_module_links($admin_menu , array(
    			'template'=>'links_user_menu',
    			'index' => $this->module,
				'css_id' => $this->module,
				'css_class' => array($this->module)
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
		
        print $cck->_view('page_admin', $variables);
        
    }
    
    function admin_user_settings($userID= NULL){
    	    
    	
    	      
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
    	$variables['contentTitle'] = 'admin user settings';
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
    	
    	
               
        $variables['content'] = 'admin user settings panel' . $output;
    	
    	print $cck->_view('page_admin', $variables);
    }
    
    function admin_user_messages($uderID = NULL){
    	
    	       
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
    	$variables['contentTitle'] = 'admin user messages';
    	$variables['mainNavigation'] = $cck->_menu_links($menu, 'links_main_menu',$variables);
    	$variables['subNavigation'] = $cck->_module_links($sub_menu[$this->module],
    		array(
    			'template'=>'links_sub_menu',
    			'index' => $this->module,
				'css_id' => '-'. $this->module,
				'css_name' => array($this->module)
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
    	
    	
               
        $variables['content'] = 'user messages admin panel' . $output;
    	
    	print $cck->_view('page_admin', $variables);
    	
    	
    }
    
    function admin_permissions(){
    	
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
					'text' => 'Permissions', 
					'path' => 'admin/admin_permissions',
					'css_id' => $this->module,
					'css_class' => array($this->module)

					);
		/**$var[$link][2] = array(
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
		*/
			
    	
    	
    	$menu = $cck->_hooks('hook_links');    	
    	$sub_menu = $cck->_hooks('hook_module_links');
    	$admin_menu = $var;

    	//var_dump($sub_menu); exit;
    	$variables['menuTitle'] = 'Site Security';
    	$variables['adminMenuTitle'] = 'User Security';
    	$variables['pageTitle'] = 'admin permissions';
    	$variables['mainNavigation'] = $cck->_menu_links($menu, 'links_main_menu',$variables);
    	$variables['subNavigation'] = $cck->_module_links($sub_menu[$this->module],
    		array(
    			'template'=>'links_sub_menu',
    			'index' => $this->module,
				'css_id' => $this->module,
				'css_class' => array($this->module)
    			) , $variables); 
    	
    	$variables['adminNavigation'] = $cck->_module_links($admin_menu , array(
    			'template'=>'links_user_menu',
    			'index' => $this->module,
				'css_id' => $this->module,
				'css_class' => array($this->module)
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
        
    function login_user($is_secure=TRUE)
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
			        'text' => 'User Profile',
				    'path' => 'users/user_profile',
					'css_id' => $this->module,
					'css_class' => array($this->module)
					);
		$var[$link][2] = array(
					'text' => 'User Accounts', 
					'path' => 'users/user_account',
					'css_id' => $this->module,
					'css_class' => array($this->module)
					);
		$var[$link][3] = array(
					'text' => 'User Content', 
					'path' => 'blog/blog_user',
					'css_id' => $this->module,
					'css_class' => array($this->module)
					);
		$var[$link][4] = array(
				    'text' => 'User Settings',
				    'path' => 'users/user_settings',
					'css_id' => $this->module,
					'css_class' => array($this->module)
		);
		
			
    	
    	$sub_menu = $cck->_hooks('hook_module_links');
    	$menu = $cck->_hooks('hook_links');    	
    	$admin_menu = $var;

    	
    	//var_dump($sub_menu); exit;
    	$variables['menuTitle'] = 'Site Admin';
    	$variables['adminMenuTitle'] = 'User Admin';
    	$variables['pageTitle'] = 'User Login';
    	$variables['contentTitle'] = 'user logged in';
    	$variables['userBio'] = 'thanks for logging in.';
    	$variables['mainNavigation'] = $cck->_menu_links($menu, 'links_main_menu',$variables);
    	$variables['subNavigation'] = $cck->_module_links($sub_menu[$this->module],
    		array(
    			'template'=>'links_sub_menu',
    			'index' => $this->module,
				'css_id' => $this->module,
				'css_class' => array($this->module)
    			) , $variables); 
    	
    	$variables['adminNavigation'] = $cck->_module_links($admin_menu , array(
    			'template'=>'links_user_menu',
    			'index' => $this->module,
				'css_id' => $this->module,
				'css_class' => array($this->module)
    			) , $variables); 
    	$output = $cck->_target('form_post');
    	$variables['content'] =  $output;
		
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
					'path' => 'admin/edit_profile/'.$userID,
					'css_id' => $this->module,
					'css_class' => array($this->module)
					);
		$var[$link][2] = array(
					'text' => 'Account', 
					'path' => 'admin/edit_user/'.$userID,
					'css_id' => $this->module,
					'css_class' => array($this->module)
					);
		$var[$link][3] = array(
					'text' => 'Content', 
					'path' => 'admin/edit_post/'.$userID,
					'css_id' => $this->module,
					'css_class' => array($this->module)
					);
		$var[$link][4] = array(
					'text' => 'Settings',
					'path' => 'admin/edit_user_settings/'.$userID,
					'css_id' => $this->module,
					'css_class' => array($this->module)
		);
		$var[$link][5] = array(
					'text' => 'Inbox',
					'path' => 'admin/edit_messages/' .$userID,
					'css_id' => $this->module,
					'css_class' => array($this->module)
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
    			'index' => $this->module,
				'css_id' => $this->module,
				'css_class' => array($this->module)
    			) , $variables); 
    	
    	$variables['adminNavigation'] = $cck->_module_links($admin_menu , array(
    			'template'=>'links_user_menu',
    			'index' => $this->module,
				'css_id' => $this->module,
				'css_class' => array($this->module)
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
					'path' => 'admin/edit_profile/'. $userID,
					'css_id' => $this->module,
					'css_class' => array($this->module)
					);
		$var[$link][2] = array(
					'text' => 'Account', 
					'path' => 'admin/edit_user/' . $userID,
					'css_id' => $this->module,
					'css_class' => array($this->module)
					);
		$var[$link][3] = array(
					'text' => 'Your Content', 
					'path' => 'admin/edit_post/'. $userID,
					'css_id' => $this->module,
					'css_class' => array($this->module)
					);
		$var[$link][4] = array(
					'text' => 'Settings',
					'path' => 'admin/edit_user_settings/'. $userID,
					'css_id' => $this->module,
					'css_class' => array($this->module)
		);
		$var[$link][5] = array(
					'text' => 'Inbox',
					'path' => 'admin/edit_messages/'. $userID,
					'css_id' => $this->module,
				'css_class' => array($this->module)
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
    			'index' => $this->module,
				'css_id' => $this->module,
				'css_class' => array($this->module)
    			) , $variables); 
    	
    	$variables['adminNavigation'] = $cck->_module_links($admin_menu , array(
    			'template'=>'links_user_menu',
    			'index' => $this->module,
				'css_id' => $this->module,
				'css_class' => array($this->module)
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
					'text' => 'User Profile',
					'path' => 'users/user_profile',
					'css_id' => $this->module,
				'css_class' => array($this->module)
					);
		$var[$link][2] = array(
					'text' => 'User Accounts', 
					'path' => 'users/user_account',
					'css_id' => $this->module,
				'css_class' => array($this->module)
					);
		$var[$link][3] = array(
					'text' => 'User Content', 
					'path' => 'blog/blog_user',
					'css_id' => $this->module,
				'css_class' => array($this->module)
					);
		$var[$link][4] = array(
				'text' => 'User Settings',
				'path' => 'users/user_settings',
				'css_id' => $this->module,
				'css_class' => array($this->module)
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
    			'index' => $this->module,
				'css_id' => $this->module,
				'css_class' => array($this->module)
    			) , $variables); 
    	
    	$variables['adminNavigation'] = $cck->_module_links($admin_menu , array(
    			'template'=>'links_user_menu',
    			'index' => $this->module,
				'css_id' => $this->module,
				'css_class' => array($this->module)
    			) , $variables); 
    	$output = $cck->_target('form_post');
    	$variables['content'] =  $output;
		
        print $cck->_view('page_user_save', $variables);
        
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
                    'text' => 'User Profile',
					'path' => 'users/user_profile',
					'css_id' => $this->module,
				'css_class' => array($this->module)
					);
		$var[$link][2] = array(
					'text' => 'User Accounts', 
					'path' => 'users/user_account',
					'css_id' => $this->module,
				'css_class' => array($this->module)
					);
		$var[$link][3] = array(
					'text' => 'User Content', 
					'path' => 'blog/blog_user',
					'css_id' => $this->module,
				'css_class' => array($this->module)
					);
		$var[$link][4] = array(
				'text' => 'User Settings',
				'path' => 'users/user_settings',
				'css_id' => $this->module,
				'css_class' => array($this->module)
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
    			'index' => $this->module,
				'css_id' => $this->module,
				'css_class' => array($this->module)
    			) , $variables); 
    	
    	$variables['adminNavigation'] = $cck->_module_links($admin_menu , array(
    			'template'=>'links_user_menu',
    			'index' => $this->module,
				'css_id' => $this->module,
				'css_class' => array($this->module)
    			) , $variables); 
    	
    			
		$output .= $cck->_target('form_post');
    	$variables['content'] =  $output;
		
        print $cck->_view('page_user_save', $variables);
        
    }
    
    function edit_category($userID = NULL)
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
					'path' => 'users/user_profile',
					'css_id' => $this->module,
				'css_class' => array($this->module)
					);
		$var[$link][2] = array(
					'text' => 'Your Account', 
					'path' => 'users/user_account',
					'css_id' => $this->module,
				'css_class' => array($this->module)
					);
		$var[$link][3] = array(
					'text' => 'Your Content', 
					'path' => 'users/user_content',
					'css_id' => $this->module,
				'css_class' => array($this->module)
					);
		$var[$link][4] = array(
				'text' => 'User settings',
				'path' => 'users/user_settings',
				'css_id' => $this->module,
				'css_class' => array($this->module)
		);
		$var[$link][5] = array(
				'text' => 'Your Inbox',
				'path' => 'users/user_messages',
				'css_id' => $this->module,
				'css_class' => array($this->module)
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
    			'index' => $this->module,
				'css_id' => $this->module,
				'css_class' => array($this->module)
    			) , $variables); 
    	
    	$variables['adminNavigation'] = $cck->_module_links($admin_menu , array(
    			'template'=>'links_user_menu',
    			'index' => $this->module,
				'css_id' => $this->module,
				'css_class' => array($this->module)
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
    
    
    function edit_post($userID = NULL)
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
					'path' => 'users/user_profile',
					'css_id' => $this->module,
					'css_class' => array($this->module)
					);
		$var[$link][2] = array(
					'text' => 'Your Account', 
					'path' => 'users/user_account',
					'css_id' => $this->module,
					'css_class' => array($this->module)
					);
		$var[$link][3] = array(
					'text' => 'Your Content', 
					'path' => 'users/user_content',
					'css_id' => $this->module,
					'css_class' => array($this->module)
					);
		$var[$link][4] = array(
					'text' => 'User settings',
					'path' => 'users/user_settings',
					'css_id' => $this->module,
					'css_class' => array($this->module)
		);
		$var[$link][5] = array(
				'text' => 'Your Inbox',
				'path' => 'users/user_messages',
				'css_id' => $this->module,
				'css_class' => array($this->module)
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
    			'index' => $this->module,
				'css_id' => $this->module,
				'css_class' => array($this->module)
    			) , $variables); 
    	
    	$variables['adminNavigation'] = $cck->_module_links($admin_menu , array(
    			'template'=>'links_user_menu',
    			'index' => $this->module,
				'css_id' => $this->module,
				'css_class' => array($this->module)
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
    
    
    function edit_config($userID = NULL)
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
					'path' => 'users/user_profile',
					'css_id' => $this->module,
				'css_class' => array($this->module)
					);
		$var[$link][2] = array(
					'text' => 'Your Account', 
					'path' => 'users/user_account',
					'css_id' => $this->module,
				'css_class' => array($this->module)
					);
		$var[$link][3] = array(
					'text' => 'Your Content', 
					'path' => 'users/user_content',
					'css_id' => $this->module,
				'css_class' => array($this->module)
					);
		$var[$link][4] = array(
				'text' => 'User settings',
				'path' => 'users/user_settings',
				'css_id' => $this->module,
				'css_class' => array($this->module)
		);
		$var[$link][5] = array(
				'text' => 'Your Inbox',
				'path' => 'users/user_messages',
				'css_id' => $this->module,
				'css_class' => array($this->module)
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
    			'index' => $this->module,
				'css_id' => $this->module,
				'css_class' => array($this->module)
    			) , $variables); 
    	
    	$variables['adminNavigation'] = $cck->_module_links($admin_menu , array(
    			'template'=>'links_user_menu',
    			'index' => $this->module,
				'css_id' => $this->module,
				'css_class' => array($this->module)
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
    
        
    function user_profiles($userID = NULL)
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
					'path' => 'users/user_profile',
					'css_id' => $this->module,
				'css_class' => array($this->module)
					);
		$var[$link][2] = array(
					'text' => 'Your Account', 
					'path' => 'users/user_account',
					'css_id' => $this->module,
				'css_class' => array($this->module)
					);
		$var[$link][3] = array(
					'text' => 'Your Content', 
					'path' => 'users/user_content',
					'css_id' => $this->module,
				'css_class' => array($this->module)
					);
		$var[$link][4] = array(
				'text' => 'User settings',
				'path' => 'users/user_settings',
				'css_id' => $this->module,
				'css_class' => array($this->module)
		);
		$var[$link][5] = array(
				'text' => 'Your Inbox',
				'path' => 'users/user_messages',
				'css_id' => $this->module,
				'css_class' => array($this->module)
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
    			'index' => $this->module,
				'css_id' => $this->module,
				'css_class' => array($this->module)
    			) , $variables); 
    	
    	$variables['adminNavigation'] = $cck->_module_links($admin_menu , array(
    			'template'=>'links_user_menu',
    			'index' => $this->module,
				'css_id' => $this->module,
				'css_class' => array($this->module)
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
    
    function content_type_edit(){
    	
    	var_dump($_POST);
    }
    
    function content_type_save(){
    	
    	global $cck,$ini_settings;
    	// get all links from each class controller
        $database = $ini_settings['databases']['user_db'];
    	$table = array();
    	$columns = array();
    	$rows = array();
    	$output = '';
    	
    	
    	$userID = $cck->_path_segment(2);
    	$link = 'links';
    	
    	$var = array();
    	
    	$var[$link][1] = array( 
					'text' => 'Profile', 
					'path' => 'admin/admin_user_profiles/'. $userID,
					'css_id' => $this->module,
				'css_class' => array($this->module)
					);
		$var[$link][2] = array(
					'text' => 'Account', 
					'path' => 'admin/admin_user_accounts/',
					'css_id' => $this->module,
				'css_class' => array($this->module)
					);
		$var[$link][3] = array(
					'text' => 'Content', 
					'path' => 'admin/admin_user_content/'. $userID,
					'css_id' => $this->module,
				'css_class' => array($this->module)
					);
		$var[$link][4] = array(
				'text' => 'Settings',
				'path' => 'admin/edit_user_settings/'. $userID,
				'css_id' => $this->module,
				'css_class' => array($this->module)
		);
		$var[$link][5] = array(
				'text' => 'Inbox',
				'path' => 'admin/admin_user_messages/'. $userID,
				'css_id' => $this->module,
				'css_class' => array($this->module)
		);
			
    	
    	$menu = $cck->_hooks('hook_links');    	
    	$sub_menu = $cck->_hooks('hook_module_links');
    	$admin_menu = $var;

    	//var_dump($sub_menu); exit;
    	$variables['menuTitle'] = 'Site Admin';
    	$variables['adminMenuTitle'] = 'User Admin';
    	$variables['pageTitle'] = 'Site Admin';
    	$variables['contentTitle'] = 'Save content';
    	$variables['mainNavigation'] = $cck->_menu_links($menu, 'links_main_menu',$variables);
    	$variables['subNavigation'] = $cck->_module_links($sub_menu[$this->module],
    		array(
    			'template'=>'links_sub_menu',
    			'index' => $this->module,
				'css_id' => $this->module,
				'css_class' => array($this->module)
    			) , $variables); 
    	
    	$variables['adminNavigation'] = $cck->_module_links($admin_menu , array(
    			'template'=>'links_user_menu',
    			'index' => $this->module,
				'css_id' => $this->module,
				'css_class' => array($this->module)
    			) , $variables); 
    	foreach($_POST as $key=>$value)
    	{
    		$output .= 'key=' . $key . '   :   : value= ' . $value . "<br>\n"; 
    	}
    	$output = '<p class="fs-6">' .$output.'</p>'."\n"; 
    	
    	$variables['content'] = $output;
    	print $cck->_view('page_admin', $variables);
    	
    }
    
    function content_type_post(){
    	
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
    	$variables['contentTitle'] = 'admin content';
    	$variables['mainNavigation'] = $cck->_menu_links($menu, 'links_main_menu',$variables);
    	
             	//$link = 'links';
        $userID = $cck->_path_segment(2);
    	$link = 'links';
    	
    	$var = array();
    	
    	$var[$link][1] = array( 
					'text' => 'Profile', 
					'path' => 'admin/admin_user_profiles/'. $userID,
					'css_id' => $this->module,
				'css_class' => array($this->module)
					);
		$var[$link][2] = array(
					'text' => 'Account', 
					'path' => 'admin/admin_user_accounts/' . $userID,
					'css_id' => $this->module,
				'css_class' => array($this->module)
					);
		$var[$link][3] = array(
					'text' => 'Content', 
					'path' => 'admin/admin_user_content/'. $userID,
					'css_id' => $this->module,
				'css_class' => array($this->module)
					);
		$var[$link][4] = array(
				'text' => 'Settings',
				'path' => 'admin/edit_user_settings/'. $userID,
				'css_id' => $this->module,
				'css_class' => array($this->module)
		);
		$var[$link][5] = array(
				'text' => 'Inbox',
				'path' => 'admin/admin_user_messages/'. $userID,
				'css_id' => $this->module,
				'css_class' => array($this->module)
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
    			'index' => $this->module,
				'css_id' => $this->module,
				'css_class' => array($this->module)
    			) , $variables); 
    	
    	$variables['adminNavigation'] = $cck->_module_links($admin_menu , array(
    			'template'=>'links_user_menu',
    			'index' => $this->module,
				'css_id' => $this->module,
				'css_class' => array($this->module)
    			) , $variables); 
    	
    	 
    	$db = new SQLite3($database);
    	
    	$typeID = $cck->_path_segment(2);

        $resultAdd = $db->query('SELECT * FROM content_types WHERE type_id ="'. $typeID.'";');
        $result = $db->query('SELECT * FROM content_type_fields WHERE content_type_id ="'. $typeID.'" ORDER BY weight asc;');
        
    	 while ($row = $result->fetchArray()) {
               $rows[] = $row;

         }
                        
         
              while ($rowAdd = $resultAdd->fetchArray()) {
                  $table['contentType'] = $rowAdd['name'];
                  
                  $r[] = $rowAdd;
               }
         //var_dump($rows);
          //SQLite3Result::numColumns();
        for ($i = 0; $i < $result->numColumns(); $i++) {
			    $col = $result->columnName($i);
			    $columns[$col] = $col;
			}
				$table['header'] = $columns;
				$table['rows'] = $rows; 
				$table['fieldType'] = '';
				$table['contentType'] = (isset($table['contentType']) ? $table['contentType'] : '');
				$output = $cck->_view('table_content_add_form', $table);
    	
    	
               
        $variables['content'] = 'create new content using <h3><i>'.$table['contentType'].'</i></h3>' . $output;
    	
    	print $cck->_view('page_admin', $variables);
    	
    }
    
    function content_type_submit(){
    	
    	
    }
}

?>

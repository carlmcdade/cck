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
 *                        blog.class.inc
 * 
 * ==================================================================
 *
 * @todo 
 * 
 */
namespace blog;

use SQLite3;

// classes used // classes used by the global $cck object from the globalspace

class blog{
	
	private $common;
	public  $menu;
	public  $section;
	public  $module;
	
	const   DUMMY = 'DUMMY';

    function __construct()
    {
        //Test the Common settings
        $this->module = __NAMESPACE__;
    }
    
    /**
    *   Navigation hook for all modules
    *   the array keys appear as $variables in the template file for links
    *   link.tpl.php, spaces will be replaced by underscores.
    */
    
    function __destruct()
    {
    	   //
    }

    function hook_links()
    {       
        $link = 'links';
    	
    	$var[$link][1] = array(
        		'text' => 'Blogs', 
        		'path' => $this->module . '/blog_latest',
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
					'text' => 'Blogs', 
					'path' => $this->module . '/blog_list'
					);
		$var[$link][2] = array(
					'text' => 'Categories', 
					'path' => $this->module . '/blog_categories'
					);
		$var[$link][3] = array(
					'text' => 'My Blog ', 
					'path' => $this->module . '/blog_user'
					);
		$var[$link][4] = array(
				'text' => 'New post',
				'path' => $this->module . '/blog_post_add'
		);
				
		
        
        return $var;
    }
    
    function hook_access()
    {
    	    $authorize = array(
    	    	    $this->module . '/blog_post_add' => array('access foo'),
    	    	    $this->module . '/blog_post_edit' => array('access baz'),
    	    	    $this->module . '/blog_post_delete' => array('access boo'),
    	    	    );
    	    return $authorize;
    }

    function blog_list()
    {
    	    
    	global $cck, $ini_settings;
    	
    	$database = $ini_settings['databases']['user_db'];
    	$table = array();
    	$columns = array();
    	$rows = array();
   
    	// get all links from each class controller
    	$menu = $cck->_hooks('hook_links');    	
    	$sub_menu = $cck->_hooks('hook_module_links');
    	//var_dump($sub_menu); exit;
    	$variables['menuTitle'] = 'Blog Users List';
    	$variables['pageTitle'] = 'Blogs';
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

    function blog_categories()
    {
        global $cck;
        
    	
    	//some variables to load into the view will appear as $[variable name]
      	$output = '';
    	$menu = $cck->_hooks('hook_links');
    	$sub_menu = $cck->_hooks('hook_module_links');
    	$variables['seperators'] = array('|','-',';',':');
    	$variables['pageTitle'] = 'Categories';
    	$variables['menuTitle'] = 'Categories';
    	$variables['contentTitle'] = 'Recent blog posts';
    	$variables['dbTable'] = 'userlist';
        
    	
    	$variables['mainNavigation'] = $cck->_menu_links($menu, 'links_main_menu',$variables);
    	$variables['subNavigation'] = $cck->_module_links($sub_menu[$this->module],
    		array(
    			'template'=>'links_sub_menu',
    			'index' => $this->module
    			)
    		, $variables); 
        $output .= print_r($cck->_path_segment(0));
    	$variables['content'] = 'Categories and taxonomy'. $output;
    	print $cck->_view('default', $variables);
    }
    
    function blog_latest()
    {
    	global $cck, $ini_settings;
    	
    	$database = $ini_settings['databases']['user_db'];
    	$table = array();
    	$columns = array();
    	$rows = array();
   
    	// get all links from each class controller
    	$menu = $cck->_hooks('hook_links');    	
    	$sub_menu = $cck->_hooks('hook_module_links');
    	//var_dump($sub_menu); exit;
    	$variables['iniSettings'] = $ini_settings;
    	$variables['menuTitle'] = 'Blog Latest';
    	$variables['pageTitle'] = 'Recent posts';
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
       
        $variables['content'] = "connect to sqlite database: ". 
        $output .$database . '<br>::' . 
        $_SERVER['REQUEST_URI'] .' <br>::' . 
        $_SERVER['QUERY_STRING'] .' <br>::' .
        $_SERVER['SCRIPT_FILENAME'] .' <br>::' .
        $ini_settings['paths']['install_dir'] . '<br>::'.
         CCK_ROOT. '<br>::' .
         DOCROOT . '<br>::'.
         	 $ini_settings['paths']['dev_symlink'];
         
    	
    	print $cck->_view('page_admin', $variables);

    }
    
    function blog_post_view()
    {
    	print 'blog post view';
    }
    
    function blog_post_add()
    {    	
    	global $cck;
    	
    	// get all links from each class controller
    	$menu = $cck->_hooks('hook_links');    	
    	$sub_menu = $cck->_hooks('hook_module_links');
    	$variables['menuTitle'] = 'Post add';
    	$variables['pageTitle'] = 'Blog';
    	$variables['contentTitle'] = 'Post add';
    	$variables['navigation'] = $cck->_menu_links($menu, 'links_main_menu',$variables);
    	$variables['sub_navigation'] = $cck->_module_links($sub_menu[$this->module],
    		array(
    			'template'=>'links_sub_menu',
    			'index' => $this->module
    			) , $variables); 
    	
    	
    	// set content
    	$variables['content'] = 'blog post  - add the form for the contentype here';
    	
    	print $cck->_view('default', $variables);
    	
    }
    
    function blog_post_edit()
    {
    	
    	global $cck;
    	$output = 'blog post edit';
    	
    	// get all links from each class controller
    	$menu = $cck->_hooks('hook_links');  	
    	$sub_menu = $cck->_hooks('hook_module_links');
    	
    	$variables['navigation'] = $cck->_menu_links($menu, 'links_main_menu');
    	$variables['sub_navigation'] = $cck->_module_links($sub_menu[$this->module],
    		array(
    			'template'=>'links_sub_menu',
    			'index' => $this->module
    			)); 
    	$variables['page_title'] = 'Blog';
    	$variables['content_title'] = 'Post edit';
        $variables['content'] = $output;
        print $cck->_view('default', $variables);
    }
    
    function blog_post_delete()
    {
    	print 'blog post delete';
    }
}

?>

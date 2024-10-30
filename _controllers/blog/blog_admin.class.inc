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


class blog_admin{
	
	private $common;
	public  $page_title = 'Blog Administration';
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
        		'text' => 'Blogs', 
        		'path' => 'admin/'. $this->module.'/blog_list_all'
        		);
        	$var[$link][2] = array(
        		'text' => 'Blog add post',
        		'path' => 'admin/' . $this->module . '/blog_add'
        		);
        	return $var;
        }
    
        /**
        *  Sub navigation is not a hook and displayed per call by section
        */
    
        function hook_sub_links($index = 0)
        {
        	$link = 'links';
        	
        	$var[$link][2] = array(
        		'text' => 'Blogs',
        		'path' => 'admin/' . $this->module . '/blog_list_all'
        		);
        	$var[$link][1] = array(
        		'text' => 'Blog Add',
        		'path' => $this->section . '/blog_add'
        		);
        	return $var;
        }
        
        function hook_access()
        {
        	$authorize = array(
        		$this->module . '/blog_add' => array('access foo'),
        		$this->module . '/blog_edit' => array('access baz'),
        		$this->module . '/blog_save' => array('access boo','access suisse'),
        		);
        	return $authorize;
        }
        
        function blog_form($configure = array(), $values = array(), $sort = 'ASC')
        {
        	global $cck, $ini_settings;
			
			$cck_types = new content_admin();
			$types = $cck_types->content_types();
			
			$connect = $cck->_dbconnect();
        	$query = $connect->prepare("SELECT * FROM node");
			$query->execute();
        	$information = $query->fetchAll(PDO::FETCH_ASSOC);
        	$output = '';
        	
			// table header from database
			$result = $connect->prepare("SELECT * FROM node LIMIT 0");
			$result->execute();
			$table_fields = $result->fetchAll(PDO::FETCH_COLUMN);
			
			$form = new form("blogContent", 300); 
			
			for ($i = 0; $i < $result->columnCount(); $i++) {
			    $element = $result->getColumnMeta($i);
			    $columns[] = $element['name'];
				
				$value = '';
				switch($element['name'])
				{
					case 'type':
										
        			$form->addElement(new 
						Element_Select(
						"Content types:", 
						"modules_list", 
						$types
						)
					);
					
					break;
					
					default:
					$value = $element['name'];
					
					$form->addElement(new 
        			Element_Textbox(
        				$element['name'],
        				$element['name'],
        				array('value' => $value)
        				)
        			);
					
					break;
				}
				
				
				
			}
			
    
		/*
			$form->addElement(new Element_Hidden("form", "addContent"));
			$form->addElement(new Element_Textbox("Content title:", "content_title"));
			$form->addElement(new Element_TinyMCE("Content:", "content"));
			$form->addElement(new Element_Textarea("Notes:", "Textarea"));
			$form->addElement(new Element_Textbox("Content author:", "content_author"));
			$form->addElement(new Element_Button);
		*/
        
		$form->addElement(new Element_Button);       
		$form->configure(array(
				"action" => "?content/content_save/blog",
				"method" => "post",
				"resourcesPath" => "_helpers/Form/Resources"
					
		));
                
		//$output .= print_r($values, 1);
		$output .= $form->render(true);
		return $output;
	}
	
	function blog_add()
	{
		global $cck;
		// get all links from each class controller
		$main_menu = $cck->_hooks('hook_links');
		$sub_menu = $this->hook_sub_links();
    	
		$output = $this->blog_form();
		$variables['content'] = $output;
		$variables['page_title'] = $this->page_title;
		$variables['content_title'] = 'Add blog';	
		$variables['main_navigation'] = $cck->_menu_links($main_menu, 'links_main_menu');
		$variables['sub_navigation'] = $cck->_module_links($sub_menu,
			array(
				'template'=>'links_sub_menu',
				'index' => $this->module
    			)); 
			
		print $cck->_view('page_admin', $variables);
	}
	
	function blog_edit()
	{
		// get all links from each class controller
		$main_menu = $this->common->get_hooks('hook_links');
		$sub_menu = $this->sub_links();
		
		// Get the content for this id
		$content_id = ber_pathpart(3);
		
		// get the row values in an array with the column names ascii2ebcdic associative keys
		$query = 'SELECT * FROM content_blog WHERE id =' . $content_id;
		$result = $this->dbc->query($query);
		$values = $result->fetchAll(PDO::FETCH_ASSOC);
		
		// Editing configuration
		$form = array(
			"action" => "index.php?admin/blog/blog_save",
			"method" => "post",
			"resourcesPath" => "_helpers/PFBC/Resources"
			);
		
		// place the values in a form
		$output .= $this->blog_form($configure, $values);
		$variables['content'] = $content_id . $output;
		$variables['page_title'] = $this->page_title;
		$variables['content_title'] = 'Edit post';
		$variables['main_navigation'] = $this->common->ber_links_menu($main_menu, 'links_main_menu');
		$variables['sub_navigation'] = $this->common->ber_links_menu($sub_menu, 'links_sub_menu');
		print $this->common->ber_view('page_admin', $variables);
	}
	
	function blog_save()
	{
		// get all links from each class controller
		$main_menu = $this->common->get_hooks('hook_links');
		$admin_menu = $this->hook_admin_links();
		
		$variables['page_title'] = $this->page_title;
		$variables['content_title'] = 'Blog Save';
		$variables['main_navigation'] = $this->common->ber_links_menu($main_menu, 'links_main_menu');      
		$variables['content'] = print_r($_POST, 1);
		print $this->common->ber_view('page_admin', $variables);
	}
	
	/**
	*    This is a user administration function where the main admin menu is not shown
	*    although the user is in the administration section they are not given the default
	*    admin menu
	*/
	
	function blog_list_all()
	{
		global $cck, $ini_settings;
		$main_menu = $cck->_hooks('hook_links');
		$sub_menu = $this->hook_sub_links();
		
		$variables['page_title'] = $this->page_title;
		$variables['content_title'] = 'Blogs';   	
		$variables['main_navigation'] = $this->common->ber_links_menu($main_menu, 'links_main_menu',' | ');
		$variables['sub_navigation'] = $this->common->ber_module_menu($sub_menu,
			array(
				'template'=>'links_sub_menu',
				'index' => $this->module
				)
			); 
		// Get the content column values 
		$connect = $cck->_dbconnect();
		
		// table header from database
		$result = $connect->prepare("SELECT * FROM content_data LIMIT 0");
		$result->execute();
		$table_fields = $result->fetchAll(PDO::FETCH_COLUMN);
			
		for ($i = 0; $i < $result->columnCount(); $i++)
		{
			$col = $result->getColumnMeta($i);
			$columns[] = $col['name'];
		}
		
		$query = $connect->query("SELECT * FROM content_data");
		$query->execute();
		$table_rows = $query->fetchAll();
		// validate content
			
		if(!empty($table_rows)) 	
		{
	    	
	    	// set table variables for view table template
			$table['header'] = $columns; 			
			$table['rows'] = $table_rows;	
			$output = $cck->_view('table', $table);
	    }
	    else
	    {
		    $output = 'Query incomplete or nothing found!';
	    }
		$variables['content'] = $output;
		print $cck->_view('page_admin', $variables);
	}
	
	function blog_settings()
	{   
		global $cck, $ini_settings;
		$main_menu = $this->common->get_hooks('hook_links');
		$admin_menu = $this->hook_admin_links();
		
		$variables['page_title'] = $this->page_title;
		$variables['content_title'] = 'Blog posts';
		$variables['main_navigation'] = $this->common->ber_links_menu($main_menu, 'links_main_menu');
		$variables['admin_navigation'] = $this->common->ber_links_menu($admin_menu, 'links_admin_menu');
		$variables['content'] = 'list of all blog pages with admin links';
		print $this->common->ber_view('page_admin', $variables);
        }
        
     function blog_test() 
     {
	     print 'tested';
     }   
}
?>

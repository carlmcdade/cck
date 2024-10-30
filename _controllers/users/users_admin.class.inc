<?php

/*
 * @author Carl McDade
 * @copyright Copyright (c) 2010, Carl McDade
 * @since 2010-02-19
 * @version 0.2
 * @license
 * @link http://www.fhqk.com Berlin Germany
 *
 */


class users_admin{
	
	private $common;
	public  $page_title = 'Users Administration';
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
    	
    	function hook_admin_links()
    	{
    		$link = 'links';
    		$var[$link][1] = array(
        		'text' => 'Users', 
        		'path' => 'admin/'. $this->module.'/users_list_all'
        		);
        	$var[$link][2] = array(
        		'text' => 'User add',
        		'path' => 'admin/' . $this->module . '/users_add'
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
        		'text' => 'Users',
        		'path' => 'admin/' . $this->module . '/users_list_all'
        		);
        	$var[$link][1] = array(
        		'text' => 'Add user', 
        		'path' => $this->section . '/users_add'
        		);
        	return $var;
        }
        
        function hook_access()
        {
        	$authorize = array(
        		$this->module . '/users_add' => array('access foo'),
        		$this->module . '/users_edit' => array('access baz'),
        		$this->module . '/users_save' => array('access boo','access suisse'),
        		);
        	return $authorize;
        }
        
        function users_form($configure = array(), $values = array(), $sort = 'ASC')
        {
        	global $cck;
        	$connect = $cck->_dbconnect();
        	$query = $connect->prepare("SELECT * FROM cck_users");
        	$query->execute();
        	if($query)
        	{
        		$information = $query->fetchAll();     	
        	}
        	else
        	{
        		$output = 'Nothing found!';
        	}
        	
        	// get the XML mapper for the content type
        	
        	$form = new Form("usersContent", 300); 
        	foreach ($information as $element)
        	{
        		$form->addElement(new 
        			Element_Textbox(
        				$element['content_field_label'],
        				$element['content_column_name'],
        				array('value' => 'required')
        				)
        			);
        	}  	
    
		/*
			$form->addElement(new Element_Hidden("form", "form-elements"));
			$form->addElement(new Element_HTML('<legend>Standard</legend>'));
			$form->addElement(new Element_Textbox("Textbox:", "Textbox"));
			$form->addElement(new Element_Password("Password:", "Password"));
			$form->addElement(new Element_File("File:", "File"));
			$form->addElement(new Element_Textarea("Textarea:", "Textarea"));
			$form->addElement(new Element_Select("Select:", "Select", $options));
			$form->addElement(new Element_Radio("Radio Buttons:", "RadioButtons", $options));
			$form->addElement(new Element_Checkbox("Checkboxes:", "Checkboxes", $options));
			$form->addElement(new Element_HTML('<legend>HTML5</legend>'));
			$form->addElement(new Element_Phone("Phone:", "Phone"));
			$form->addElement(new Element_Search("Search:", "Search"));
			$form->addElement(new Element_Url("Url:", "Url"));
			$form->addElement(new Element_Email("Email:", "Email"));
			$form->addElement(new Element_Date("Date:", "Date"));
			$form->addElement(new Element_DateTime("DateTime:", "DateTime"));
			$form->addElement(new Element_DateTimeLocal("DateTime-Local:", "DateTimeLocal"));
			$form->addElement(new Element_Month("Month:", "Month"));
			$form->addElement(new Element_Week("Week:", "Week"));
			$form->addElement(new Element_Time("Time:", "Time"));
			$form->addElement(new Element_Number("Number:", "Number"));
			$form->addElement(new Element_Range("Range:", "Range"));
			$form->addElement(new Element_Color("Color:", "Color"));
			$form->addElement(new Element_HTML('<legend>jQuery UI</legend>'));
			$form->addElement(new Element_jQueryUIDate("Date:", "jQueryUIDate"));
			$form->addElement(new Element_Checksort("Checksort:", "Checksort", $options));
			$form->addElement(new Element_Sort("Sort:", "Sort", $options));
			$form->addElement(new Element_HTML('<legend>WYSIWYG Editor</legend>'));
			$form->addElement(new Element_TinyMCE("TinyMCE:", "TinyMCE"));
			$form->addElement(new Element_CKEditor("CKEditor:", "CKEditor"));
			$form->addElement(new Element_HTML('<legend>Custom/Other</legend>'));
			$form->addElement(new Element_State("State:", "State"));
			$form->addElement(new Element_Country("Country:", "Country"));
			$form->addElement(new Element_YesNo("Yes/No:", "YesNo"));
			$form->addElement(new Element_Captcha("Captcha:"));
			$form->addElement(new Element_Button);
			$form->addElement(new Element_Button("Cancel", "button", array( "onclick" => "history.go(-1);")));
		*/
        
		$form->addElement(new Element_Button);       
		$form->configure(array(
				"action" => "?content/content_save/users",
				"method" => "post",
				"resourcesPath" => "_helpers/Form/Resources"
					
		));
                
		//$output .= print_r($values, 1);
		$output = $form->render(true);
		return $output;
	}
	
	function users_add()
	{
		
		global $cck;
		
		// get all links from each class controller
		$main_menu = $cck->_hooks('hook_links');
		$sub_menu = $this->hook_sub_links();
    	
		$form = array(
			"action" => "index.php?admin/users/users_saveas",
			"method" => "post",
			"resourcesPath" => "_helpers/Form/Resources"
			);		
		$output = $this->users_form($form);
		$variables['content'] = $output;
		$variables['page_title'] = $this->page_title;
		$variables['content_title'] = 'Add users';	
		$variables['main_navigation'] = $this->common->ber_links_menu($main_menu, 'links_main_menu');
		$variables['sub_navigation'] = $this->common->ber_module_menu($sub_menu,
			array(
				'template'=>'links_sub_menu',
				'index' => $this->module
    			)); 
		print $this->common->ber_view('page_admin', $variables);
	}
	
	function users_edit()
	{
		// get all links from each class controller
		$main_menu = $this->common->get_hooks('hook_links');
		$sub_menu = $this->sub_links();
		
		// Get the content for this id
		$content_id = ber_pathpart(3);
		
		// get the row values in an array with the column names ascii2ebcdic associative keys
		$query = 'SELECT * FROM content_users WHERE id =' . $content_id;
		$result = $this->dbc->query($query);
		$values = $result->fetchAll(PDO::FETCH_ASSOC);
		
		// Editing configuration
		$form = array(
			"action" => "index.php?admin/users/users_save",
			"method" => "post",
			"resourcesPath" => "_helpers/PFBC/Resources"
			);
		
		// place the values in a form
		$output .= $this->users_form($configure, $values);
		$variables['content'] = $content_id . $output;
		$variables['page_title'] = $this->page_title;
		$variables['content_title'] = 'Edit post';
		$variables['main_navigation'] = $this->common->ber_links_menu($main_menu, 'links_main_menu');
		$variables['sub_navigation'] = $this->common->ber_links_menu($sub_menu, 'links_sub_menu');
		print $this->common->ber_view('page_admin', $variables);
	}
	
	function users_save()
	{
		// get all links from each class controller
		$main_menu = $this->common->get_hooks('hook_links');
		$admin_menu = $this->hook_admin_links();
		/*
		$sql = "INSERT INTO `databasename`.`wp_users` (`ID`, `user_login`, `user_pass`, `user_nicename`, `user_email`, `user_url`, `user_registered`, `user_activation_key`, `user_status`, `display_name`) VALUES ('4', 'demo', MD5('demo'), 'Syed Balkhi', 'test@yourdomain.com', 'http://www.wpbeginner.com/', '2011-06-07 00:00:00', '', '0', 'Syed Balkhi');
		INSERT INTO `databasename`.`wp_usermeta` (`umeta_id`, `user_id`, `meta_key`, `meta_value`) VALUES (NULL, '4', 'wp_capabilities', 'a:1:{s:13:\"administrator\";s:1:\"1\";}');
		INSERT INTO `databasename`.`wp_usermeta` (`umeta_id`, `user_id`, `meta_key`, `meta_value`) VALUES (NULL, '4', 'wp_user_level', '10');";
		*/
		$variables['page_title'] = $this->page_title;
		$variables['content_title'] = 'User Save';
		$variables['main_navigation'] = $this->common->ber_links_menu($main_menu, 'links_main_menu');      
		$variables['content'] = print_r($_POST, 1);
		print $this->common->ber_view('page_admin', $variables);
	}
	
	/**
	*    This is a user administration function where the main admin menu is not shown
	*    although the user is in the administration section they are not given the default
	*    admin menu
	*/
	
	function users_list_all()
	{
		global $cck, $ini_settings;
		
		$main_menu = $cck->_hooks('hook_links');
		$sub_menu = $this->hook_sub_links();
		
		$variables['page_title'] = $this->page_title;
		$variables['content_title'] = 'Users';   	
		$variables['main_navigation'] = $cck->_menu_links($main_menu, 'links_main_menu');
		$variables['sub_navigation'] = $this->common->ber_module_menu($sub_menu,
			array(
				'template'=>'links_sub_menu',
				'index' => $this->module
				)
			); 
		// Get the content column values 
		$connect = ber_db_connect();
		$query = $connect->query("SELECT * FROM users");
		$rows = $query->fetchAll();
		
		$table['header'] = array('id','name');
		$table['rows'] = $rows;
		$table['id'] = __function__;
		$output = $this->common->ber_view('table', $table);
		$variables['content'] = 'list of all users pages with admin links' . $output;
		print $this->common->ber_view('page_admin', $variables);
	}
	
	function users_settings()
	{   
		$main_menu = $this->common->get_hooks('hook_links');
		$admin_menu = $this->hook_admin_links();
		
		$variables['page_title'] = $this->page_title;
		$variables['content_title'] = 'Blog posts';
		$variables['main_navigation'] = $this->common->ber_links_menu($main_menu, 'links_main_menu');
		$variables['admin_navigation'] = $this->common->ber_links_menu($admin_menu, 'links_admin_menu');
		$variables['content'] = 'list of all users pages with admin links';
		print $this->common->ber_view('page_admin', $variables);
        }    
}
?>

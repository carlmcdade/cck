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


class install_admin{
	
	private $common;
	public  $page_title = "Installation Administration";
	public  $section;
	public  $module;
	


    function __construct()
    {
        //Test the Common settings
        $this->section = get_class($this);
        $parent = explode('_', $this->section);
        $this->module = $parent[0];
        
    }

    function hook_admin_links()
    {
        $link = 'links';
        
    	$var[$link][1] = array(
        		"text" => "Module add", 
        		"path" => 'admin/'.$this->module . '/install_add'
        		);
        $var[$link][2] = array(
        		"text" => "Module remove", 
        		"path" => 'admin/'.$this->module . '/install_remove'
        		);
        $var[$link][3] = array(
        		"text" => "Module file list", 
        		"path" => 'admin/'.$this->module . '/install_list_all'
        		);

        return $var;
    }
    
    
    /**
    *   Sub navigation is not a hook and displayed per call by section
    */
    
    function hook_sub_links($index = 0)
    {
        $link = 'links';
    	
    	$var[$link][1] = array( 
					"text" => "Available modules", 
					"path" => "admin/install/install_list_all"
					);
		$var[$link][2] = array(
					"text" => "Uninstall modules", 
					"path" => "admin/install/install_remove"
					);
		$var[$link][3] = array(
					"text" => "Install modules", 
					"path" => "admin/install/install_add"
					);		
        
        return $var;
    }
    

    function install_add()
    {
        global $cck;
		// get all links from each class controller
        $main_menu = $cck->_hooks("hook_links");
    	$sub_menu = $this->hook_sub_links();
    	
    	$variables["page_title"] = $this->page_title;
    	$variables["content_title"] = "Install module";
    	$variables["main_navigation"] = $cck->_menu_links($main_menu, "links_main_menu");
    	$variables['sub_navigation'] = $cck->_module_links($sub_menu,
			array(
				'template'=>'links_sub_menu',
				'index' => $this->module
    			)); 
	$output = 'This adds the module name to the database for use';
    	$modules = $cck->_modules_list;
    	$form = new form("addContent", 300);
    	        $form->addElement(new Element_Hidden("form", "addContent"));
                $form->addElement(new Element_Select("Modules:", "modules_list", $modules));
                $form->addElement(new Element_TinyMCE("Description:", "content"));
                $form->addElement(new Element_Textarea("Notes:", "Textarea"));
                $form->addElement(new Element_Textbox("Module author:", "module_author"));
                $form->addElement(new Element_Button);
                
                $form->configure(array(
				   "action" => "index.php?admin/install/install_save",
				   "method" => "post",
				   "resourcesPath" => "_helpers/PFBC/Resources"
				   
				));
                

                $output .= $form->render(true);
               
        $variables["content"] = $output;
    	
    	print $cck->_view("page_admin", $variables);
    }

    function install_edit()
    {
        // get all links from each class controller
        $main_menu = $this->common->get_hooks("hook_links");
    	$admin_menu = $this->hook_admin_links();
    	
    	$variables["page_title"] = $this->page_title;
    	$variables["content_title"] = "Installation Settings";
    	
    	$variables["main_navigation"] = $this->common->ber_links_menu($main_menu, "links_main_menu",$separater = " | ");
    	$variables["admin_navigation"] = $this->common->ber_links_menu($admin_menu, "links_admin_menu", $separater = " | ");
    	
        $form = new Form("addContent", 300);
    	        $form->addElement(new Element_Hidden("form", "addContent"));
                $form->addElement(new Element_Textbox("Content title:", "content_title"));
                $form->addElement(new Element_TinyMCE("Content:", "content"));
                $form->addElement(new Element_Textarea("Notes:", "Textarea"));
                $form->addElement(new Element_Textbox("Content author:", "content_author"));
                $form->addElement(new Element_Button);
                
                $form->configure(array(
				   "action" => "index.php?admin/blog/install_save",
				   "method" => "post",
				   "resourcesPath" => "_helpers/PFBC/Resources"
				   
				));
                

                $output .= $form->render(true);
               
        $variables["content"] = $output;
    	
    	print $this->common->ber_view("page_admin", $variables);
    }
    
    function install_save($file)
    {
        $fp = file($file, FILE_IGNORE_NEW_LINES | FILE_SKIP_EMPTY_LINES);
		$query = '';
		foreach ($fp as $line) {
			if ($line != '' && strpos($line, '--') === false) {
				$query .= $line;
				if (substr($query, -1) == ';') {
					mysql_query($query);
					$query = '';
				}
			}
		}
		
		
		// Select MySQL DB
		mysql_select_db($database_name, $link) or die("Wrong MySQL Database");
		
		// Function For Run Multiple Query From .SQL File
		function MultiQuery($sqlfile, $sqldelimiter = ';') {
		set_time_limit(0);
		
		if (is_file($sqlfile) === true) {
		$sqlfile = fopen($sqlfile, 'r');
		
		if (is_resource($sqlfile) === true) {
		$query = array();
		echo "<table cellspacing='3' cellpadding='3' border='0'>";
		
		while (feof($sqlfile) === false) {
		$query[] = fgets($sqlfile);
		
		if (preg_match('~' . preg_quote($sqldelimiter, '~') . '\s*$~iS', end($query)) === 1) {
		$query = trim(implode('', $query));
		
		if (mysql_query($query) === false) {
		echo '<tr><td>ERROR:</td><td> ' . $query . '</td></tr>';
		} else {
		echo '<tr><td>SUCCESS:</td><td>' . $query . '</td></tr>';
		}
		
		while (ob_get_level() > 0) {
		ob_end_flush();
		}
		
		flush();
		}
		
		if (is_string($query) === true) {
		$query = array();
		}
		}
		echo "</table>";
		
		return fclose($sqlfile);
		}
		}
		
		return false;
		}
		
		/* * * Use Function Like This: ** */
		
		//MultiQuery($SQLFile);


    }
    
    /**
    *    This is a user administration function where the main admin menu is not shown
    *    although the user is in the administration section they are not given the default
    *    admin menu
    */
    
    function install_list_all()
    {
        global $cck;
		$main_menu = $cck->_hooks("hook_links");
    	$sub_menu = $this->hook_sub_links();
    	       
        $variables["page_title"] = $this->page_title;
        $variables["content_title"] = "Installed modules";   	
    	$variables["main_navigation"] = $cck->_menu_links($main_menu, "links_main_menu"," | ");
    	$variables['sub_navigation'] = $cck->_module_links($sub_menu,
			array(
				'template'=>'links_sub_menu',
				'index' => $this->module
    			)); 
    	$variables["content"] = "list of all available modules with admin links from the configuration file config.ini". '<br />' . implode('<br />',$cck->_modules_list);
        print $cck->_view("page_admin", $variables);
    }
    
    function install_settings()
    {
    
    	$main_menu = $this->common->get_hooks("hook_links");
    	$admin_menu = $this->hook_admin_links();
    	
        
        $variables["page_title"] = $this->page_title;
        $variables["content_title"] = "Installation settings";
    	
    	$variables["main_navigation"] = $this->common->ber_links_menu($main_menu, "links_main_menu",$separater = " | ");
    	$variables["admin_navigation"] = $this->common->ber_links_menu($admin_menu, "links_admin_menu", $separater = " | ");
    	
    	
    	
    	$form = new Form("addContent", 300);
    	
    	
    	//install_content_types
    	$available_tyoes = array();
    	
    	$comtent = new Content();
    	$available_tyoes = $content->content_types("form","checkboxes");
    	
    	foreach($available_tyoes as $value)
    	{
    		//
    	}
    	
    	
    	        $form->addElement(new Element_Hidden("form", "addContent"));
                $form->addElement(new Element_Textbox("Content title:", "content_title"));
                $form->addElement(new Element_TinyMCE("Content:", "content"));
                $form->addElement(new Element_Textarea("Notes:", "Textarea"));
                $form->addElement(new Element_Textbox("Content author:", "content_author"));
                $form->addElement(new Element_Button);
                
                $form->configure(array(
				   "action" => "index.php?admin/blog/install_save",
				   "method" => "post",
				   "resourcesPath" => "_helpers/PFBC/Resources"
				   
				));
                

                $output .= $form->render(true);
    	
    	$variables["content"] = "list of all blog pages with admin links";
        print $this->common->ber_view("page_admin", $variables);
    }
    
    
    function install_remove()
    {
        global $cck;
		// get all links from each class controller
        $main_menu = $cck->_hooks("hook_links");
    	$sub_menu = $this->hook_sub_links();
    	
    	$variables["page_title"] = $this->page_title;
    	$variables["content_title"] = "Install module";
    	$variables["main_navigation"] = $cck->_menu_links($main_menu, "links_main_menu");
    	$variables['sub_navigation'] = $cck->_module_links($sub_menu,
			array(
				'template'=>'links_sub_menu',
				'index' => $this->module
    			)); 
		$output = 'This adds the module name to the database for use';
    	$modules = $cck->_modules_list;
    	$form = new \form("addContent", 300);
    	        $form->addElement(new \Element_Hidden("form", "addContent"));
                $form->addElement(new \Element_Select("Modules:", "modules_list", $modules));
                $form->addElement(new \Element_TinyMCE("Description:", "content"));
                $form->addElement(new \Element_Textarea("Notes:", "Textarea"));
                $form->addElement(new \Element_Textbox("Module author:", "module_author"));
                $form->addElement(new \Element_Button);
                
                $form->configure(array(
				   "action" => "index.php?admin/install/install_save",
				   "method" => "post",
				   "resourcesPath" => "_helpers/PFBC/Resources"
				   
				));       

        $output .= $form->render(true);
               
        $variables["content"] = $output;
    	
    	print $cck->_view("page_admin", $variables);
    }
    
}

?>

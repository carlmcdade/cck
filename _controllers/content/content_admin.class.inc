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


class content_admin{
	
	private $common;
	public  $menu;
	public  $page_title = 'Content Administration';
	public  $section;
	public  $module;

    function __construct()
    {
        //Test the Common settings
        $this->common = Common::get_instance();
        $this->section = get_class($this);
		$parent = explode('_', $this->section);
		$this->module = $parent[0];
        
    }
    
    function __toString()
    {
    	return $this->section;
    }
    
    function hook_links()
    {
    	    $link = 'links';
    	     
    	    $var[$link][1] = array(
    	    	    'text' => 'Content connections',
    	    	    'path' => 'admin/'.$this->module.'/content_type_connection'
    	    	    );
            $var[$link][2] = array(
            	    'text' => 'Content fields', 
            	    'path' => 'admin/'.$this->module.'/content_type_fields'
        		);
            return $var;
    	    
    }

    function hook_admin_links()
    {
        $link = 'links';      
           	
    	$var[$link][1] = array(
        		'text' => 'Content types', 
        		'path' => 'admin/'. $this->module . '/content_type_list'
        		);
        $var[$link][2] = array(
        		'text' => 'Content add type', 
        		'path' => 'admin/'. $this->module . '/content_type_add'
        		);

        return $var;
    }
        

    /**
    *   Sub navigation is not a hook and displayed per call by section
    */
    
    function hook_sub_links($index = 0)
    {      
        $link = 'links';        
        $var = array();       
        $var[$link][2] = array(
        		'text' => 'Content types',
        		'path' => 'admin/' . $this->module . '/content_type_list'
        );       
        $var[$link][1] = array(
        		'text' => 'Add content type',
        		'path' => $this->section . '/content_type_add'
        );        
        return $var;      
    }

    function content_type_field_add()
    {
        $output = '';
    	// get all links from each class controller
        $main_menu = $this->common->get_hooks('hook_links');
    	$admin_menu = $this->hook_admin_links();
    	
    	$variables['page_title'] = $this->page_title;
    	$variables['content_title'] = 'Content list';
    	
    	$variables['main_navigation'] = $this->common->ber_links_menu($main_menu, 'links_main_menu',$separater = ' | ');
    	$variables['admin_navigation'] = $this->common->ber_links_menu($admin_menu, 'links_admin_menu', $separater = ' | ');
    	
    	
    	// XML file
    	
    	// get form data

    	// convert form data

    	// Add form data to XML file 
    	
    	// save and close XML file
    	
    	// get XML file again
    	
    	// Build new form
    	
    	// Show the form
    	
    	$options = array("Option #1", "Option #2", "Option #3");
    	
    	$form = new Form("GettingStarted", 300);
                $form->addElement(new Element_Checkbox("Checkbox:", "Checkbox", $options));
                $form->addElement(new Element_Button);
                $output .= $form->render(true);
               
        $variables['content'] = $output;
    	
    	print $this->common->ber_view('page_admin', $variables);
    }
    
    function content_type_fields()
    {
    	    // get all links from each class controller
    	    $main_menu = $this->common->get_hooks('hook_links');
    	    $sub_menu = $this->hook_sub_links();
    	    $output = '';
    	    
    	    $query = ber_url_query('type');
    	    $variables['page_title'] = $this->page_title;
    	    $variables['content_title'] = 'Content type | ' . $query . ' | fields';
    	    $variables['page_title'] = $this->page_title;
    	    $variables['main_navigation'] = $this->common->ber_links_menu($main_menu, 'links_main_menu');
    	    $variables['sub_navigation'] = $this->common->ber_module_menu($sub_menu,
    	    	array(
    	    		'template'=>'links_sub_menu',
    	    		'index' => $this->module
    	    		)
    	    	); 
    	    
    	    // load a model
    	    $type = $this->content_type_load($query);
    	    $output .= '<pre>';
    	    $output .=  print_r($type, 1);
    	    $output .= '</pre>';
    	    
    	    //
    	    $variables['content'] = $output;
    	    
    	    //
    	    print $this->common->ber_view('page_admin', $variables);
    }

    function content_type_field_edit()
    {
        // get all links from each class controller
        $main_menu = $this->common->get_hooks('hook_links');
    	$admin_menu = $this->hook_admin_links();
    	
    	$variables['page_title'] = $this->page_title;
    	$variables['content_title'] = 'Content types';
    	
    	$variables['main_navigation'] = $this->common->ber_links_menu($main_menu, 'links_main_menu',$separater = ' | ');
    	$variables['admin_navigation'] = $this->common->ber_links_menu($admin_menu, 'links_admin_menu', $separater = ' | ');
    	
    	$form = new Form("GettingStarted", 300);
    	
    			
    			$options = array("Option #1", "Option #2", "Option #3");
    	
    			$form->configure(array(
				   "action" => "admin/Content/action_two",
				   "method" => "post"
				   ));
                $form->addElement(new Element_Hidden("form", "elements"));
				$form->addElement(new Element_Textbox("Textbox:", "Textbox"));
				$form->addElement(new Element_Textarea("Textarea:", "Textarea"));
				$form->addElement(new Element_Select("Select:", "Select", $options));
				$form->addElement(new Element_Radio("Radio:", "Radio", $options));
				$form->addElement(new Element_File("File:", "File"));
				$form->addElement(new Element_Password("Password:", "Password"));
				$form->addElement(new Element_Checkbox("Checkbox:", "Checkbox", $options));
				$form->addElement(new Element_YesNo("Yes / No:", "YesNo"));
				$form->addElement(new Element_Checksort("Checksort:", "Checksort", $options));
				$form->addElement(new Element_Sort("Sort:", "Sort", $options));
				$form->addElement(new Element_State("State:", "State"));
				$form->addElement(new Element_Country("Country:", "Country"));
				$form->addElement(new Element_Email("Email:", "Email"));
				$form->addElement(new Element_Color("Color:", "Color"));
				$form->addElement(new Element_Date("Date:", "Date"));
				$form->addElement(new Element_Captcha("Captcha:"));
                $form->addElement(new Element_Button);
                $output .= $form->render(true);
               
        $variables['content'] = $output;
    	
    	print $this->common->ber_view('page_admin', $variables);
    }
    
    function content_type_view()
    {
        global $cck, $ini_settings; 	
    	
    	// get all links from each class controller
        $main_menu = $cck->_hooks('hook_links');
    	$sub_menu = $this->hook_sub_links();
    	
    	$output = '';
    	
    	// get the XML document for the content type
    	$query = ber_url_query('type');
    	
    	$type_xml = $this->content_type_load($query);
    	$type_name = $query;
    	
    	
    	
    	if($type_xml)
    	{
			//$output .= '<pre>' . print_r($type, 1) . '</pre>';
    	 				
			$type_name = $type_xml->DisplayName;
			$form = new Form("ContentType", 300);
			$lists = array('Element_Select');
    		
			if($type_xml->Fields->Field)
			{
				foreach ($type_xml->Fields->Field as $element)
				{
					$attributes = $element->attributes();
					
					$field = (string)$attributes['type'];
					$label = (string)$element->DisplayName;
					$name  = (string)$attributes['name'];
					$options = array();
							
					if($field)
					{
						$form->addElement(new $field($label, $name, $options));
						if(in_array($field, $lists))
						{
							foreach($element->Configuration->Options->Option as $value)
							{
								if(!is_array($value))
								{
									$options[] =  $value ;
								}
							}			
						}
					}
				}
				
				$form->addElement(new Element_Button);       
				$output .= $form->render(true);
			}
			else
			{
				//
				$type_name = $query;
				$output = 'Could not build form for : ';			
				$output .= $query . '. Check the content type\'s xml configuration.';
			}
		}
		else
		{
			$type_name = $query;
			$output = 'Could not build form for : ';
			$output .= $query . '. Check the content type\'s xml configuration.';
		}
        
		$variables['page_title'] = $this->page_title; 	
    	$variables['main_navigation'] = $this->common->ber_links_menu($main_menu, 'links_main_menu');
    	$variables['sub_navigation'] = $this->common->ber_module_menu($sub_menu,
			array(
				'template'=>'links_sub_menu',
				'index' => $this->module
    			)); 
    	
        $variables['content_title'] = 'Content type | ' . $type_name . ' | form';
    	$variables['content'] = $output;
        print $cck->_view('page_admin', $variables);
    }
    
    /**
    *   Content types list available
    */
    
    function content_type_list($dir = NULL, $exclude = array())
    {
    	global $cck, $ini_settings;
    	
    	// get all links from each class controller
        $main_menu = $cck->_hooks('hook_links');
    	$sub_menu = $this->hook_sub_links();
    	
    	$variables['main_navigation'] = $cck->_menu_links($main_menu, 'links_main_menu');
    	$variables['sub_navigation'] = $cck->_module_links($sub_menu,
			array(
				'template'=>'links_sub_menu',
				'index' => $this->module
				)
			); 
    	
    	$variables['page_title'] = $this->page_title;
    	$variables['content_title'] = 'Content types';	
    	
    	// Get the content column values
    	$connect = $cck->_dbconnect();
    	    
    	// table header from database
		
    	// table rows and field values
		$result = $connect->prepare("SELECT * FROM content_types");
			
		$result->execute();
			
		$table_rows = $result->fetchAll();
			
		// validate content
			
		if(!empty($table_rows))
	    	{
	    		$columns = array();
	    		$user_columns = array();
	    		$user_columns = array('manage', 'edit');
	    		
	    		// table header
	    		foreach ($table_rows[0] as $key => $value)
	    		{
	    			if(!is_numeric($key))
	    			{
		    			$columns[] = $key;
	    			}
	    				    			
	    		}
	    		
	    		foreach($user_columns as $extra)
				{
					array_push($columns, $extra);
				}
	    		
	    		// table rows
	    		$user_links = array(
	    			'manage'=> $this->section . '/content_type_view', 
					'edit'=> $this->section . '/content_type_edit'
	    		);			
				foreach($table_rows as $key => $value)
				{				
					foreach($user_links as $text => $path)
					{					
						$links['text'] = $text;
						$links['path'] = $path;
						$links['host'] = $ini_settings['url']['base'];
						$links['directory'] = $ini_settings['url']['dir'];

						array_push($table_rows[$key], $cck->_view('links',$links));
					}					
				}
	    		    		
	    		// set table variables for view table template
				$table['header'] = $columns; 			
				$table['rows'] = $table_rows;	
				$output = $cck->_view('table', $table);
	    	}
	    	else
	    	{
		    	$output = 'Query incomplete or nothing found!';
	    	}
	 	 
    	
    	$dir = (__dir__) . '/' . $ini_settings['system']['content_types'];
    	$exclude = $ini_settings['exclude'];
    	
    	
    	$types = '';
    	$rows = array(); // empty array variable
    	$ffs = scandir($dir);
    	
    	foreach($ffs as $ff)
    	{
    		if(is_array($exclude) and !in_array($ff,$exclude))
    		{
    			if($ff != '.' && $ff != '..')
    			{
    				if(!is_dir($dir . '/' . $ff))
    				{
    					$type_name = explode('.', $ff);
    					
    					$rows[] = array('<span>'. '<a href="?admin/content/content_type_view&type=' . ltrim($type_name[0]).'">'.$ff.'</a>'.
    								'</span>',
    								'<a href="?admin/content/content_type_fields&type=' . ltrim($type_name[0]).'">' . 'manage</a>',
    								'<a href="?admin/content/content_type_connection&type=' . ltrim($type_name[0]).'">'. 'connect</a>',
    								'<a href="?admin/content/content_type_datamapper&type=' . ltrim($type_name[0]).'">'. 'edit</a>',
    								'<a href="?admin/content/content_type_api&type=' . ltrim($type_name[0]).'">'. 'administration</a>',
    								'<a href="?admin/content/content_type_remove&type=' . ltrim($type_name[0]).'">'. 'delete</a>'
    								);
    				}
    			}
    		}
    	}
    	
    	$table['header'] = array('title','fields', 'datasource', 'data mapper', 'api', 'delete');
	$table['rows'] = $rows;
	$table['id'] = __function__;
	$output .= $this->common->ber_view('table', $table);
    	$variables['content'] = $output;
        print $this->common->ber_view('page_admin', $variables); 		
    }
    
    /**
    *
    *
    */
    
    function content_type_get($type)
    {
    	    // get the content type file
    	    global $ini_settings;
    	    $file = (__dir__) . '/' . $ini_settings['system']['content_types'] . '/' . $type . '.xml';
    	    include($file);
    	    
    	    // return the XML
    	    return $xmlstr;
    }
    
    /**
    *   Content types add form
    */
    
    function content_type_add()
    {
    	global $cck;
    	// get all links from each class controller
    	$menu = $cck->_hooks('hook_links');
    	    
    	// get sublinks just for this module
    	$sub_menu = $this->hook_sub_links();
    	    
    	$variables['main_navigation'] = $cck->_menu_links($menu, 'links_main_menu');
    	$variables['sub_navigation'] = $cck->_module_links($sub_menu,
    	array(
    		'template'=>'links_sub_menu',
    		'index' => $this->module
    		)); 
    	$variables['page_title'] = $this->page_title;
    	$variables['content_title'] = 'Content add type ';
    	
    	//
    	$form = new Form("ContentTypeAdd", 300);
    	
    			$form->configure(array(
				   "action" => "../cck/index.php?content_admin/content_type_save",
				   "method" => "post"
				   ));
				$form->addElement(new \Element_HTMLExternal('<fieldset><legend>My Fieldset</legend>'));
                $form->addElement(new Element_Hidden("form", "elements"));
				$form->addElement(new Element_Textbox("Name:", "type_name"));
				$form->addElement(new Element_Textarea("Descripion:", "type_description"));
				
				$form->addElement(new Element_HTMLExternal('</fieldset>'));
				$form->addElement(new Element_HTMLExternal(new content_admin()));
				$form->addElement(new Element_Button);
				
                $output = $form->render(true);
                
                $variables['content'] = $output;
    	
                print $this->common->ber_view('page_admin', $variables);
    
    	
    }
    
    /**
    *   Content types edit fields and settings
    */
    
    function content_type_edit($type = NULL)
    {
    	global $cck, $ini_settings;
    	// get the XML document for the content type
    	
    	$query = ber_url_query('type');
    	$path = __dir__ . '/content_types/' . $query . '.xml';
    	
    	if(file_exists($path))
    	{
	    	// load the the xml document for editing
	    	$xml = new DOMDocument();
	    	$xml->load($path);
	    	$nodes = $xml->getElementsByTagName('content_type') ;
	    	if ($nodes->length > 0) {
	    		//insert some stuff using appendChild()
	    	}
	    	
	    	//re-save
	    	//$xml->save($path);
    	}
    	
    	$output = '';
    	 
    	// get all links from each class controller
    	$main_menu = $cck->_hooks('hook_links');
    	$sub_menu = $this->hook_sub_links();
    	 
    	$variables['main_navigation'] = $cck->_menu_links($main_menu, 'links_main_menu');
		$variables['sub_navigation'] = $cck->_module_links($sub_menu,
			array(
				'template'=>'links_sub_menu',
				'index' => $this->module
    			));
    	$variables['page_title'] = $this->page_title;
    	$variables['content_title'] = 'Content add type ';
    	 
    	//
    	$form = new Form("ContentTypeAdd", 300);
    	 
    	$form->configure(array(
    			"action" => "admin/content/content_type_save",
    			"method" => "post"
    	));
    	$form->addElement(new Element_Hidden("form", "elements"));
    	$form->addElement(new Element_Textbox("Name:", "type_name"));
    	$form->addElement(new Element_Textarea("Descripion:", "type_description"));
    	
    	$output .= $form->render(true);
    	$variables['content'] = $output; 
    	print $this->common->ber_view('page_admin', $variables);
    }
    
    /**
    *   Content types save to database
    */
    
    function content_type_save()
    {
    	
    	exit('done');
    	
    	// Request post variables
    	$submitted = $_POST;
    	$new_content_type = $_POST['type_name'];
    	
    	// clean and format string
    	$new_content_type = $this->content_type_name($new_content_type);
    	$new_content_fields = array();
    	//create document root
    	$xml = new DOMDocument('1.0', 'UTF-8');
    	$xml->formatOutput = true;
    	
    	/* create the root element of the xml tree */
    	$xml_root = $xml->createElement( "content_type" );
    	$xml_fields = $xml->createElement( "Fields" );
    	$xml_field = $xml->createElement( "Field" );
    	$xml_attributes = $xml->createElement( "attributes" );
    	
    	$xml_root->setAttribute( "name", $new_content_type );
    	$xml_root->setAttribute( "status", "public" );
    	
    	$xml_field->setAttribute( "name", "" );
    	$xml_field->setAttribute( "type", "" );
    	
    	$xml->appendChild( $xml_root );
    	$xml_root->appendChild( $xml_fields );
    	$xml_fields->appendChild( $xml_field );
    	$xml_field->appendChild( $xml_attributes );   	
    	
    	$output = $xml->save( __dir__ . "/content_types/" . $new_content_type . ".xml" );
    	
    	return $output;
    	
    
    }
    
    function content_type_connection()
    {
    	      // get all links from each class controller
    	      $main_menu = $this->common->get_hooks('hook_links');
    	      $sub_menu = $this->hook_sub_links();
    	
    	      $query = ber_url_query('type');
    	
    	      $variables['page_title'] = $this->page_title;
    	      $variables['content_title'] = 'Content type | ' . $query . ' | connection';
    	      $variables['page_title'] = $this->page_title;
    	      $variables['main_navigation'] = $this->common->ber_links_menu($main_menu, 'links_main_menu');
    	      $variables['sub_navigation'] = $this->common->ber_module_menu($sub_menu,
    	      	  array(
    	      	  	  'template'=>'links_sub_menu',
    	      	  	  'index' => $this->module
    	      	  	  )
    	      	  ); 
    	    
    	      //
    	      $output = 'content type connections extract store';
    	    
    	      //
    	      $variables['content'] = $output;
    	    
    	      //
    	      print $this->common->ber_view('page_admin', $variables);
    }
    
    
    function content_type_load($type = NULL)
    {
    	global $ini_settings;
    	
    	if(empty($type))
    	{
    		exit('content type not found');
    	}
    	
    	$dir = (__dir__) . '/' . $ini_settings['system']['content_types'];
    	$exclude = $ini_settings['exclude'];
    	 
    	$ffs = scandir($dir);
    	
    	
    	foreach($ffs as $ff)
    	{
    		$handle = explode(".", $ff);
    		$name = $handle[0];
    		$file_type = $handle[1];
    		
    		if($name == $type && $file_type == 'xml')
    		{
				if(is_array($exclude) and !in_array($ff,$exclude))
				{
					if($ff != '.' && $ff != '..')
					{
						$ff = $dir . '/' . $ff;
						
						
						if (file_exists($ff)) 
						{
							libxml_use_internal_errors(true);
							
							$xml = simplexml_load_file($ff, 'SimpleXMLElement', LIBXML_NOCDATA);
							
							
							if (empty($xml))
							{
								$errors = libxml_get_errors();
								$error_count = 0;
							
								foreach ($errors as $error) {
									$output = $this->content_type_error($error, $xml);
									$error_count++;
								}
							
								libxml_clear_errors();
								if($error_count > 0)
								{
									return $output . ' Could not open ' . $handle[0]. ' check with the site owner.';
								}
							}					
							else
							{
								return $xml;
							}
							
						} 
						else
						{
							exit('Failed to open ' . $handle . $ff);
						}			
						
					}
					
				}
				
    		}
    		else
    		{
    			continue;
			}
    	}
    	
    	
    }
    
    function content_type_error($error, $xml)
	{
		$return  = $xml[$error->line - 1] . "\n";
		$return .= str_repeat('-', $error->column) . "^\n";
	
		switch ($error->level) {
			case LIBXML_ERR_WARNING:
				$return .= "Warning $error->code: ";
				break;
			 case LIBXML_ERR_ERROR:
				$return .= "Error $error->code: ";
				break;
			case LIBXML_ERR_FATAL:
				$return .= "Fatal Error $error->code: ";
				break;
		}
	
		$return .= trim($error->message) .
				   "\n  Line: $error->line" .
				   "\n  Column: $error->column";
	
		if ($error->file) {
			$return .= "\n  File: $error->file";
		}
	
		return "$return\n\n--------------------------------------------\n\n";
	}
	
	function content_types()
	{
		global $cck, $ini_settings;
		
		$dir = (__dir__) . '/' . $ini_settings['system']['content_types'];
		$exclude = $ini_settings['exclude'];
		$ffs = scandir($dir);
			
		foreach($ffs as $ff)
		{
			if(is_array($exclude) and !in_array($ff,$exclude))
			{
				if($ff != '.' && $ff != '..')
				{
					if(!is_dir($dir . '/' . $ff))
					{
						$type_name = explode('.', $ff);
						$name = ltrim($type_name[0]);
						if($name != '')
						{
							$content_types[] = $name;
						}
										
					}
				}
			}
		}
		return $content_types;
	}
	
	function content_type_merge($file1, $file2, $new_content_type)
	{
		
		$new_content_type = '.xml';		
		$xml1 = simplexml_load_file( $file1 );
		$xml2 = simplexml_load_file( $file2 );	// loop through the FOO and add them and their attributes to xml1
		
		foreach( $xml2->FOO as $foo ) {
			$new = $xml1->addChild( 'FOO' , $foo );
			foreach( $foo->attributes() as $key => $value ) {
				$new->addAttribute( $key, $value );
			}
		}	
		
		$fh = fopen( 'content_types/' . $new_content_type, 'w') or die ( "can't open file $fileout" );
		fwrite( $fh, $xml1->asXML() );
		fclose( $fh );
	}
	
	function content_type_split($datasource)
	{
		$filein = 'filein.xml';
		$xml = simplexml_load_file( $datasource );	
		foreach( $xml->FOO as $foo )
		{
			$foo_id = (string) $foo['Id'];
			$fileout = $foo_id . '.xml';
			$fh = fopen( $fileout, 'w') or die ( "can't open file $fileout" );
			fwrite( $fh, $foo->asXML() );
			fclose( $fh );
		}
	}
	
	function content_type_readall($document)
	{
		$out = '';
		$file = 'content_types/'.$document;
		$doc = new DOMDocument;
		$doc->preserveWhiteSpace = false;
		
		if(!file_exists($file))
		{
			//
			return $out;
		}
		else
		{
			$doc->load($file);				
			$xpath = new DOMXPath($doc);
			$results = $xpath->query('//comment()');
			
			foreach ($results as $comment)
			{
				$out .= print_r($comment,1);
			}
			
			return $out;
		}
	}
}


?>

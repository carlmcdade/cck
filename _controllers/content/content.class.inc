<?php

/*
 * @author Carl McDade
 * 
 * @since 2012-06-11
 * @version 0.2
 *
 */


namespace content;

// classes used by the global $cck object from the globalspace

use \Common;
use SQLite3;

class content{
	
	public  $common;
	public  $menu;
	public  $section;
	public  $module;


    function __construct()
    {
    	// Common settings
    	$this->common = Common::get_instance();
    	$this->module = __NAMESPACE__;
    }
    
    function hook_module_links($index = NULL)
    {
    	    $link = 'links';
    	    
            $var[$link][1] = array(
    	    	    'text' => 'Content',
    	    	    'path' => $this->module . '/content_user_list'
    	    	    );  	    
    	    $var[$link][2] = array(
    	    	    'text' => 'Content Add',
    	    	    'path' => $this->module . '/content_add'
    	    	    );
    	    return $var;
    }
    
    function hook_user_links($index = NULL)
    {
    	    $link = 'links';
    	    
            $var[$link][1] = array(
    	    	    'text' => 'User Content',
    	    	    'path' => $this->module . '/content_user_list'
    	    	    );  	    
    	    $var[$link][2] = array(
    	    	    'text' => 'Add User Content',
    	    	    'path' => $this->module . '/content_add'
    	    	    );
    	    return $var;
    }

    function content_user_list()
    {
    	   
    	global $cck;
    	$output = 'A list of this users content';
    	   
    	   // get all links from each class controller
    	$menu = $cck->_hooks('hook_links');    	
    	$sub_menu = $cck->_hooks('hook_module_links');
    	$variables['seperators'] = array('|','-',';',':');
    	$variables['pageTitle'] = 'Content';
    	$variables['menuTitle'] = 'Content';
    	$variables['contentTitle'] = 'Content Types';
    	$variables['dbTable'] = 'content_types';

    	
    	$variables['navigation'] = $cck->_menu_links($menu, 'links_main_menu',$variables);
    	$variables['sub_navigation'] = $cck->_module_links($sub_menu[$this->module],
    		array(
    			'template'=>'links_sub_menu',
    			'index' => $this->module
    			) , $variables); 
    	   $variables['page_title'] = 'Content';
    	   $variables['content_title'] = 'Content list';
    	   $variables['content'] = $output;
    	   print $this->common->ber_view('default', $variables);      
    }
    
    function content_add()
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
    	$variables['menuTitle'] = 'Content';
    	$variables['contentTitle'] = 'Content Types';
    	$variables['dbTable'] = 'content_types';
        
    	
    	$variables['mainNavigation'] = $cck->_menu_links($menu, 'links_main_menu',$variables);
    	$variables['subNavigation'] = $cck->_module_links($sub_menu[$this->module],
    		array(
    			'template'=>'links_sub_menu',
    			'index' => $this->module
    			)
    		, $variables); 
         
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
				$output = $cck->_view('table_content_add', $table);
				
		foreach($rows as $key => $value)			
		{
			$variables['userBio'] =  '';
			$variables['userName'] = $value['name'];
			$variables['profileImage'] = '';
			$variables['userID'] = '';
		}
               
        $variables['content'] = 'Content types' . $output;
    	
    	print $cck->_view('default', $variables);
    }
    
    function content_crud()
    {
        
        $variables = array();
        $view = 'default';
        $mode = ber_pathpart(2);
        print $mode;
        
        switch($mode) 
        {
            // models return a view/model
            case 'create':
            	$variables['page_title'] = 'Create One';
                $variables['content'] = $this->common->ber_model('example','get_create');
                $view = 'movico';
                break;
                
            case 'view':
            	
                $variables['page_title'] = 'View One';
            	$variables['content'] = $this->common->ber_model('example','get_retrieve');
                $view = 'movico';
                break;
                
            case 'update':
            	
            	$variables['page_title'] = 'Update One';
            	$output = 'This is a plain string to show the use of the out parameter';
                
                // doing it a bit different and setting the form into a variable
                $variables['start'] = '<div style="border:1px solid #eaeaea">start</div>'.
                //mvc_access(__function__);
                $variables['myform'] = $this->common->ber_model('example','get_update');
                $variables['end'] = '<div style="border:1px solid #eaeaea">end</div>';
                $view = 'movico';
                break;
                
            case 'delete':
            	$variables['page_title'] = 'Delete One';
                $this->common->ber_model('example','get_delete');
                $view = 'movico';
                break;
        }        
            print $this->common->ber_view($view, $variables);
    }
    
    function view()
    {
	    global $cck, $ini_settings;
	    $menu = $cck->_hooks('hook_links'); 
	    $variables['page_title'] = 'View One';
	    $variables['navigation'] = $cck->_menu_links($menu, 'links_main_menu');
	    
	    $output ='';
	    
	    $connect = $cck->_dbconnect();
		$id = $connect->prepare("SELECT c.*, ci.table FROM content c JOIN content_type_info ci ON c.content_type = ci.id WHERE c.id=:id");
		$id->bindValue(':id', ber_pathpart(2));
		$id->execute();
		$id_result = $id->fetch(PDO::FETCH_ASSOC);
		$id_content = $id_result['ccid'];		
		
		if(!empty($id_content))
	    {
	    	// get content type info
			$content_type = $connect->prepare("SELECT * FROM " . $id_result['table']);
			$content_type->execute();
			$content_type_table = $content_type->fetchAll(PDO::FETCH_COLUMN);
			
			for ($i = 0; $i < $content_type->columnCount(); $i++) {
			    $col = $content_type->getColumnMeta($i);
			    $columns[] = $col['name'];
			}
			
			$field_order = $columns;
			unset($field_order[0]);
			$field_order = array_values($field_order);
			$field_order = array_flip($field_order);
	    	
			
	    	
	    	$content = $connect->prepare("SELECT cd.data, cc.* FROM content_collection cc JOIN content_data cd ON cc.data_id = cd.data_id WHERE cc.ccid=:ccid");
			$content->bindValue(':ccid', $id_content);
			$content->execute();
			$content_data = $content->fetchAll(PDO::FETCH_ASSOC);
			
			foreach($content_data as $result)
			{
				$data[] = array_merge($result, $id_result);			
			}
			
			$output .= $id_content . '= view content: <pre>' .  print_r($data,1);
			
			foreach($field_order as $f => $index)
			{
				$with_data[$f] = $data[$index];
			}
					
			$user_field_order = array('f1' => 1, 'f2' => 0);
			unset($with_data);
			foreach($user_field_order as $uf => $uindex)
			{
				if(isset($data[$uindex]))
				{
					$with_data[$uf] = $data[$uindex];
				}
			}
			
			foreach($columns as $key => $field)
			{
				
				$fields = $connect->prepare("SELECT $field FROM " . $id_result['table']);
				$fields->execute();
				$field_complete = $fields->fetchAll(PDO::FETCH_ASSOC);
				
				if($field == 'meta')
				{
					foreach($field_complete as $value)
					{
						//
						$meta[] = $value[$field];
					}
				}
				else
				{
					//
					foreach($field_complete as $value)
					{
						//
						$elements[$field][] = $value[$field];
					}
					
				}
				
			}
			
			foreach($elements as $name => $element)
			{
				
				foreach($element as $key => $value)
				{
						//
						$items[$name][$meta[$key]] = $value;
				}
				$items[$name]['field'] = $with_data[$name];
			}
			
			
			$output .= print_r($field_order,1);
			$output .= print_r($with_data,1);
			
			$output .= print_r($items,1);
	    	
	    }
	    else
	    {
	    	$output = 'Query incomplete or nothing found!';
	    }
	    
	    $variables['content_title'] = $id_content;			
    	$variables['content'] =  $output. '</pre>';
    	print $cck->_view('default', $variables);
    }   
    
    function edit()
    {
	    global $cck, $ini_settings;
	    $menu = $cck->_hooks('hook_links'); 
	    $variables['page_title'] = 'View One';
	    $variables['navigation'] = $cck->_menu_links($menu, 'links_main_menu');
	    
	    $output ='';
	    
	    print_r($this->_form_field('select', 'string'));
	    
	    $connect = $cck->_dbconnect();
		$id = $connect->prepare("SELECT * FROM content_type ");
		$id->bindValue(':id', ber_pathpart(2));
		$id->execute();
		$id_result = $id->fetch(PDO::FETCH_ASSOC);
		$id_content = $id_result['ccid'];		
		
		if(!empty($id_content))
	    {
	    	// get content type info
			$content_type = $connect->prepare("SELECT * FROM " . $id_result['table']);
			$content_type->execute();
			$content_type_table = $content_type->fetchAll(PDO::FETCH_COLUMN);
			
			for ($i = 0; $i < $content_type->columnCount(); $i++) {
			    $col = $content_type->getColumnMeta($i);
			    $columns[] = $col['name'];
			}
			
			$field_order = $columns;
			unset($field_order[0]);
			$field_order = array_values($field_order);
			$field_order = array_flip($field_order);
	    	
			
	    	
	    	$content = $connect->prepare("SELECT cd.data, cc.* FROM content_collection cc JOIN content_data cd ON cc.data_id = cd.data_id WHERE cc.ccid=:ccid");
			$content->bindValue(':ccid', $id_content);
			$content->execute();
			$content_data = $content->fetchAll(PDO::FETCH_ASSOC);
			
			foreach($content_data as $result)
			{
				$data[] = array_merge($result, $id_result);			
			}
			
			$output .= $id_content . '= view content: <pre>' .  print_r($data,1);
			
			foreach($field_order as $f => $index)
			{
				$with_data[$f] = $data[$index];
			}
					
			$user_field_order = array('f1' => 1, 'f2' => 0);
			unset($with_data);
			foreach($user_field_order as $uf => $uindex)
			{
				if(isset($data[$uindex]))
				{
					$with_data[$uf] = $data[$uindex];
				}
			}
			
			foreach($columns as $key => $field)
			{
				
				$fields = $connect->prepare("SELECT $field FROM " . $id_result['table']);
				$fields->execute();
				$field_complete = $fields->fetchAll(PDO::FETCH_ASSOC);
				
				if($field == 'meta')
				{
					foreach($field_complete as $value)
					{
						//
						$meta[] = $value[$field];
					}
				}
				else
				{
					//
					foreach($field_complete as $value)
					{
						//
						$elements[$field][] = $value[$field];
					}
					
				}
				
			}
			
			foreach($elements as $name => $element)
			{
				
				foreach($element as $key => $value)
				{
						//
						$items[$name][$meta[$key]] = $value;
				}
				$items[$name]['field'] = $with_data[$name];
			}
			
			
			$output .= print_r($field_order,1);
			$output .= print_r($with_data,1);
			
			$output .= print_r($items,1);
	    	
	    }
	    else
	    {
	    	$output = 'Query incomplete or nothing found!';
	    }
	    
	    $variables['content_title'] = $id_content;			
    	$variables['content'] =  $output. '</pre>';
    	print $cck->_view('default', $variables);
    }
    
    function _form_field($name, $type = 'object')
    {
    	//
    	switch($type)
    	{
			case 'object':
				
				$list = array(
					'html' => new Element_HTML('<legend>Standard</legend>'),
					'textbox' => new Element_Textbox("Textbox:", "Textbox"),
					'password' => new Element_Password("Password:", "Password"),
					'file' => new Element_File("File:", "File"),
					'textarea' => new Element_Textarea("Textarea:", "Textarea"),
					'select' => new Element_Select("Select:", "Select", $options),
					'radio' => new Element_Radio("Radio Buttons:", "RadioButtons", $options),
					'checkbox' => new Element_Checkbox("Checkboxes:", "Checkboxes", $options),
					'phone' => new Element_Phone("Phone:", "Phone"),
					'search' => new Element_Search("Search:", "Search"),
					'url' => new Element_Url("Url:", "Url"),
					'email' => new Element_Email("Email:", "Email"),
					'date' => new Element_Date("Date:", "Date"),
					'datetime' => new Element_DateTime("DateTime:", "DateTime"),
					'datetimelocal' => new Element_DateTimeLocal("DateTime-Local:", "DateTimeLocal"),
					'month' => new Element_Month("Month:", "Month"),
					'week' => new Element_Week("Week:", "Week"),
					'time' => new Element_Time("Time:", "Time"),
					'number' => new Element_Number("Number:", "Number"),
					'range' => new Element_Range("Range:", "Range"),
					'color' => new Element_Color("Color:", "Color"),
					'jqueryuidate' => new Element_jQueryUIDate("Date:", "jQueryUIDate"),
					'checksort' => new Element_Checksort("Checksort:", "Checksort", $options),
					'sort' => new Element_Sort("Sort:", "Sort", $options),
					'tinymce' => new Element_TinyMCE("TinyMCE:", "TinyMCE"),
					'ckeditor' => new Element_CKEditor("CKEditor:", "CKEditor"),
					'state' => new Element_State("State:", "State"),
					'country' => new Element_Country("Country:", "Country"),
					'yesno' => new Element_YesNo("Yes/No:", "YesNo"),
					'captcha' => new Element_Captcha("Captcha:"),
					'button' => new Element_Button("Cancel", "button", array(
			"onclick" => "history.go(-1);"
			)),
			);
						


				break;
			case 'string':
				
				$list = array(
					'html' => 'Element_HTML',
					'textbox' => 'Element_Textbox',
					'password' => 'Element_Password',
					'file' => 'Element_File',
					'textarea' => 'Element_Textarea',
					'select' => 'Element_Select',
					'radio' => 'Element_Radio',
					'checkbox' => 'Element_Checkbox',
					'phone' => 'Element_Phone',
					'search' => 'Element_Search',
					'url' => 'Element_Url',
					'email' => 'Element_Email',
					'date' => 'Element_Date',
					'datetime' => 'Element_DateTime',
					'datetimelocal' => 'Element_DateTimeLocal',
					'month' => 'Element_Month',
					'week' => 'Element_Week',
					'time' => 'Element_Time',
					'number' => 'Element_Number',
					'range' => 'Element_Range',
					'color' => 'Element_Color',
					'jqueryuidate' => 'Element_jQueryUIDate',
					'checksort' => 'Element_Checksort',
					'sort' => 'Element_Sort',
					'tinymce' => 'Element_TinyMCE',
					'ckeditor' => 'Element_CKEditor',
					'state' => 'Element_State',
					'country' => 'Element_Country',
					'yesno' => 'Element_YesNo',
					'captcha' => 'Element_Captcha',
					'button' => 'Element_Button',
					);

				break;			
		}  		
    		
    	$form_data = $list[$name];
    	return $form_data;
    }
    
}

?>

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


class admin_admin{
	
	private $common;
	public  $menu;
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
        		'text' => 'admin', 
        		'path' => 'admin/' . $this->module . '/site'
        		);
        $var[$link][2] = array(
        		'text' => 'admin settings', 
        		'path' => 'admin/' . $this->module . '/configuration'
        		);

        return $var;
    }
    
    function hook_sub_links($index = 0)
    {
    	$var = array();
    	
    	$var[$this->section][$this->section . '_3'] = array(
    			'text' => 'Email add',
    			'path' => 'admin/contact/email_add'
    	);
    
    	$var[$this->section][$this->section .'_5'] = array(
    			'text' => 'Email Settings',
    			'path' => 'admin/contact/email_settings_all'
    	);
    
    
    
    	return $var;
    }
    
    
    function hook_access()
    {
        $authorize = array(
			'ConClass1/action_one' => array('access foo'),
			'ConClass1/action_two' => array('access baz'),
			'ConClass1/action_three' => array('access boo','access suisse'),
        );

        return $authorize;
    }

    

    function categories()
    {
        global $cck;
        
        $variables['content'] = 'admin categories';
    	
    	print $cck->_view('page_admin', $variables);
    }

    function email_contact_categories()
    {
        //some variables to load into the view will appear as $[variable name]      	
    	$main_menu = $this->common->get_hooks('hook_links');
    	$sub_menu = $this->sub_links();
    	
    	$variables['main_navigation'] = $this->common->ber_links_menu($main_menu, 'links_main_menu',' | ');
    	$variables['sub_navigation'] = $this->common->ber_links_menu($sub_menu, 'links_sub_menu', ' | ');
    	
    	
    	$form = new Form("GettingStarted", 300);
                $form->addElement(new Element_Textbox("My Textbox:", "MyTextbox"));
                $form->addElement(new Element_Button);
                $output = $form->render(true);
               
        $variables['content'] = $output;
    	
    	print $this->common->ber_view('page_admin', $variables);
    }
    
    function admin_response()
    {
        global $cck;
    	$menu = $cck->_hooks('hook_links');
    	$variables['main_navigation'] = $cck->_menu_links($menu,'links_main_menu');
    	
    	$variables['content'] = 'admin response';
        print $cck->_view('page_admin', $variables);
    }
}

?>

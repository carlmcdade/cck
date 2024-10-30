<?php

/*
 * @author Carl McDade
 * @copyright Copyright (c) 2010, Carl McDade
 * @since 2010-02-19
 * @version 0.2
 * @license http://opensource.org/licenses/gpl-license.php GNU Public License
 * @link http://www.drupal.se Drupal Solution Exchange
 *
 */


class common_admin{
	
	public $common;
	public  $menu;
	public  $title = 'Administration Index';
	


    function __construct()
    {
        //Test the Common settings
        
        
    }

    
    function hook_admin_links()
    {
        $link = 'links';      
           	
    	$var[$link][1] = array(
        		'text' => 'Commonstuff', 
        		'path' => '?admin/'.$this->module.'/common_list'
        		);
        $var[$link][2] = array(
        		'text' => 'more ', 
        		'path' => '?admin/'.$this->module.'/common_add'
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

    

    function index()
    {
        $output = '';
    	
    	// get all links from each class controller
        $main_menu = $this->common->get_hooks('hook_links');
    	$admin_menu = $this->common->get_hooks('hook_admin_links', 'Admin');
    	
    	$variables['page_title'] = $this->title;
    	$variables['main_navigation'] = $this->common->ber_links_menu($main_menu, 'links_main_menu',' | ');
    	$variables['admin_navigation'] = $this->common->ber_links_menu($admin_menu, 'links_admin_index_menu', ' | ');
    	
    	
        $output .= 'Administration links to all active controller modules.';
               
        $variables['content'] = $output;
    	
    	print $this->common->ber_view('page_admin_index', $variables);
    }

    function blocks()
    {
        $output = '';
    	// get all links from each class controller
        $main_menu = $this->common->get_hooks('hook_links');
    	$admin_menu = $this->common->get_hooks('hook_admin_links', 'Admin');
    	
    	$variables['title'] = $this->title;
    	$variables['main_navigation'] = $this->common->ber_links_menu($main_menu, 'links_main_menu', ' | ');
    	$variables['admin_navigation'] = $this->common->ber_links_menu($admin_menu, 'links_admin_menu',' | ');
    	
    	$form = new Form("GettingStarted", 300);
                $form->addElement(new Element_Textbox("My Textbox:", "MyTextbox"));
                $form->addElement(new Element_Button);
                $output .= $form->render(true);
               
        $variables['content'] = $output;
    	
    	print $this->common->ber_view('page_admin', $variables);
    }
    
    function themes()
    {
        // get all links from each class controller
        $main_menu = $this->common->get_hooks('hook_links');
    	$admin_menu = $this->common->get_hooks('hook_admin_links', 'Admin');
    	
    	$variables['title'] = $this->title;
    	$variables['main_navigation'] = $this->common->ber_links_menu($main_menu, $separater = ' | ');
    	$variables['admin_navigation'] = $this->common->ber_links_menu($admin_menu, $separater = ' | ');
    	
    	$variables['content'] = 'admin form submit';
        print $this->common->ber_view('page_admin', $variables);
    }
}

?>

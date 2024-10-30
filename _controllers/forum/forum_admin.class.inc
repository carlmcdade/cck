<?php

/*
 * @author Carl McDade
 * @copyright Copyright (c) 2010, Carl McDade
 * @since 2010-02-19
 * @version 0.2
 * @license 
 * @link http://www.berlinto.com Berlinto Germany
 *
 */


class ConClass4_Admin{
	
	private $common;
	public  $menu;
	


    function __construct()
    {
        //Test the Common settings
        $this->common = Common::get_instance();
        
    }

    function hook_admin_links()
    {
        $var['C4_1'] = array(
        		'text' => 'C4 Admin one', 
        		'path' => '?admin/ConClass4/action_one'
        		);
        $var['C4_2'] = array(
        		'text' => 'C4 Admin two', 
        		'path' => '?admin/ConClass4/action_two'
        		);     
        
        $var['C4_3'] = array(
        		'text' => 'C4 Admin three', 
        		'path' => '?admin/ConClass4/action_three'
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

    

    function action_one()
    {
        // get all links from each class controller
    	// get all links from each class controller
        $main_menu = $this->common->get_hooks('hook_links');
    	$admin_menu = $this->common->get_hooks('hook_admin_links', 'Admin');
    	
    	$variables['title'] = $this->title;
    	$variables['main_navigation'] = $this->common->ber_links_menu($main_menu, $separater = ' | ');
    	$variables['admin_navigation'] = $this->common->ber_links_menu($admin_menu, $separater = ' | ');
    	
    	$form = new Form("GettingStarted", 300);
                $form->addElement(new Element_Textbox("My Textbox:", "MyTextbox"));
                $form->addElement(new Element_Button);
                $output .= $form->render(true);
               
        $variables['content'] = $output;
    	
    	print $this->common->ber_view('page_admin', $variables);
    }

    function action_two()
    {
        // get all links from each class controller
        $main_menu = $this->common->get_hooks('hook_links');
    	$admin_menu = $this->common->get_hooks('hook_admin_links', 'Admin');
    	
    	$variables['title'] = $this->title;
    	$variables['main_navigation'] = $this->common->ber_links_menu($main_menu, $separater = ' | ');
    	$variables['admin_navigation'] = $this->common->ber_links_menu($admin_menu, $separater = ' | ');
    	
    	$form = new Form("GettingStarted", 300);
                $form->addElement(new Element_Textbox("My Textbox:", "MyTextbox"));
                $form->addElement(new Element_Button);
                $output .= $form->render(true);
               
        $variables['content'] = $output;
    	
    	print $this->common->ber_view('page_admin', $variables);
    }
    
    function action_three()
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

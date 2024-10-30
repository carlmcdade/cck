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


class category_admin{
	
	private $common;
	public  $menu;
	public  $title = 'Page Adminstration';
	


    function __construct()
    {
        //Test the Common settings
        $this->common = Common::get_instance();
        
    }

    function hook_admin_links()
    {
        $var['c5_1'] = array(
        		'text' => 'C5 Admin one', 
        		'path' => '?admin/ConClass5/action_one'
        		);
        $var['c5_2'] = array(
        		'text' => 'C5 Admin two', 
        		'path' => '?admin/ConClass5/action_two'
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
    	$menu = $this->common->get_hooks('hook_admin_links', 'Admin');
    	
    	$variables['title'] = $this->title;
    	$variables['navigation'] = $this->common->ber_links_menu($menu, 'links_admin_menu', $separater = ' | ');
    	
    	$form = new Form("GettingStarted", 300);
                $form->addElement(new Element_Textbox("My Textbox:", "MyTextbox"));
                $form->addElement(new Element_Button);
                $output .= $form->render(true);
               
        $variables['content'] = $output;
    	
    	print $this->common->ber_view('page_admin', $variables);
    }

    function action_two()
    {
        //some variables to load into the view will appear as $[variable name]      	
    	$menu = $this->common->get_hooks('hook_admin_links', 'Admin');
    	
    	$variables['title'] = $this->title;
    	$variables['navigation'] = $this->common->ber_links_menu($menu, 'links_admin_menu',$separater = ' = ');
    	
    	$form = new Form("GettingStarted", 300);
                $form->addElement(new Element_Textbox("My Textbox:", "MyTextbox"));
                $form->addElement(new Element_Button);
                $output .= $form->render(true);
               
        $variables['content'] = $output;
    	
    	print $this->common->ber_view('page_admin', $variables);
    }
    
    function action_three()
    {
        $menu = $this->common->get_hooks('hook_admin_links', 'Admin');
        
        $variables['title'] = $this->title;
    	$variables['navigation'] = $this->common->ber_links_menu($menu, 'links_admin_menu',$separater = ' - ');
    	
    	$variables['content'] = 'admin form submit';
        print $this->common->ber_view('page_admin', $variables);
    }
}

?>

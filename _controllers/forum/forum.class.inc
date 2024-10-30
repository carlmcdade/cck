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

/*
 * Normally the Classes would be in individual files and loaded via an iterator
 *
 */



class forum{

    private $common;
    public  $menu;


    function __construct()
    {
        //Test the Common settings
        $this->common = Common::get_instance();
    }


    function hook_links()
    {
        $var['c4_1'] = array(
        		'text' => 'C4 link', 
        		'path' => '?ConClass4/index'
        		);

        return $var;
    }

    function hook_forms()
    {
        
        $var = array();

        return $var;

    }

    function index()
    {             

        // get all links from each class controller
    	$menu = $this->common->get_hooks('hook_links');
    	$variables['page_title'] = 'Index';
    	$output = $this->common->ber_links_menu($menu, 'links_main_menu', $separater = ' ** ');
        $output .= '<div> a presentation of the different hooks available to the sytem. They are set via the configuration file.</div>';
        $output .= '<pre>' . print_r($this->common->get_all_hooks(), 1) . '</pre>';
        $output .= '<pre>' . print_r($this->common->get_all_hooks('Admin'), 1) . '</pre>';

        
        
        $variables['content'] = $output;
        
        print $this->common->ber_view('default', $variables, $output);
        
    }
}

?>
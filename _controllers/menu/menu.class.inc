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

namespace menu;

use \Common;

class menu{
	
	private $common;
	public  $menu;
	public  $section;
	public  $dbc;
	public  $module;


    function __construct()
    {
        //Test the Common settings
        $this->common = Common::get_instance();
        $this->section = get_class($this);
        $this->module = __NAMESPACE__;
        
    }
    
    /**
    *   Navigation hook for all modules
    */
    
    
    /**
    *   Sub navigation is not a hook and displayed per call by section
    */
    
    function hook_sub_links($index = 0)
    {
        $var = array();
    	
        $var[$this->section][$this->section . '_1'] = array(
        		'text' => 'archive',
        		'path' => '?' . $this->section . '/view'
        );
        
    	$var[$this->section][$this->section . '_2'] = array( 
					'text' => 'archive', 
					'path' => '?' . $this->section . '/view_all'
					);
		$var[$this->section][$this->section . '_3'] = array(
					'text' => 'by category', 
					'path' => '?' . $this->section . '/add'
					);
		$var[$this->section][$this->section .'_4'] = array(
					'text' => 'latest', 
					'path' => '?' . $this->section . '/remove'
					);
				
		
        
        return $var;
    }
    

}

?>
<?php
namespace menu;
/**
 * @author Carl McDade 
 * @copyright Carl McDade
 * @since 2011
 * @version 1.0
 * @license MIT
 * 
 * @link http://hardcopy.free.nf
 * ==================================================================
 * 
 *                        menu.class.inc
 * 
 * ==================================================================
 * This CCK example site is built around this blogging module.
 * It handles the blog content type
 *  
 * 
 */

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
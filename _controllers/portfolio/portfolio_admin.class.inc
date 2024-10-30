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


class portfolio_admin{
	
	private $common;
	public  $menu;
	public  $page_title = "Portfolio Administration";
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
        		'text' => 'Portfolio', 
        		'path' => 'admin/'. $this->module.'/list_all'
        		);
        	$var[$link][2] = array(
        		'text' => 'Portfolio add',
        		'path' => 'admin/' . $this->module . '/add'
        		);
        	return $var;
    }
}

?>

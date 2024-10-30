<?php	

	
/**
 *
 *
 * @author carl
 */
class menu_admin {

private $common;
	public  $page_title = 'Menu Administration';
	public  $dbc;
	public  $module;
	public  $section;
	


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
    	    	    'text' => 'Menu add',
    	    	    'path' =>  'admin/'. $this->module . '/view'
    	    	    );
    	    $var[$link][2] = array(
    	    	    'text' => 'Menus',
    	    	    'path' => 'admin/'. $this->module . '/view_all'
    	    	    );
    	    return $var;
    }
    
    /**
    *   Sub navigation is not a hook and displayed per call by section
    */
    
    function hook_sub_links($index = 0)
    {
    	    $link = 'links';
    	    $var[$link][1] = array(
    	    	    'text' => 'Menu add item', 
    	    	    'path' => 'admin/'. $this->module . '?admin/menu/menu_add_item'
    	    	    );
    	    $var[$link][2] = array(
    	    	    'text' => 'Menu remove item',
    	    	    'path' => 'admin/'. $this->module . '/menu_add_item'
    	    	    );
    	    $var[$link][3] = array(
    	    	    'text' => 'Menu list items',
    	    	    'path' => 'admin/menu/menu_list_items'
    	    	    );
    	    return $var;
    }
	
}
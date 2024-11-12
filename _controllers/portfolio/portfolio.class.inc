<?php
namespace portfolio;
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
 *                        portfolio.class.inc
 * 
 * ==================================================================
 * This CCK example site is built around this blogging module.
 * It handles the blog content type
 *  
 * 
 */
class portfolio {
	
	private $common;
	public  $menu;
	public  $module;
	
	function __construct()
	{
		//Test the Common settings
		$this->module = __NAMESPACE__;
	}
	
	function __destruct()
	{
		//
	}
	
	/**
	 * Main menu hook
	 * @return multitype:string
	 */

    function hook_links()
    {
        
        $link = 'links';
    	
    	$var[$link][1] = array(
        		'text' => 'Portfolio', 
        		'path' => $this->module . '/list_all',
        		'css_class' => array($this->module, 'main_item'),
        		'css_id' => $this->module 
        		);
        return $var;
        
    }
    
    /**
     *   Sub navigation is a hook and displayed per call by hook_links
     */
    
    function hook_module_links($index = 0)
    {
    
    	$link = 'links';
    	 
    	$var = array();
    	 
    	$var[$link][1] = array(
    			'text' => 'Projects',
    			'path' => $this->module . '/list_all'
    	);
    	$var[$link][2] = array(
    			'text' => 'Featured',
    			'path' => $this->module . '/featured'
    	);

    	return $var;
    }
    
    function hook_admin_links()
    	{
    		$link = 'links';
    		$var[$link][1] = array(
        		'text' => 'Portfolios', 
        		'path' => 'admin/'. $this->module.'/blog_list_all'
        		);
        	$var[$link][2] = array(
        		'text' => 'Add portfolio',
        		'path' => 'admin/' . $this->module . '/blog_add'
        		);
        	return $var;
        }

    
    function list_all()
    {
        global $cck,$ini_settings;
    	
    	// get all links from each class controller
    	$menu = $cck->_hooks('hook_links');
    	$sub_menu = $cck->_hooks('hook_module_links');
    	$variables['pageTitle'] = 'Portfolio';
    	$variables['contentTitle'] = 'Our projects';
    	$variables['content'] = ' <p class="fs-4">portfolio is a list of content aggregated with the [Project] category</p>';
    	$variables['menuTitle'] = 'List of Portfolio';
    	$variables['mainNavigation'] = $cck->_menu_links($menu, 'links_main_menu', $variables);
    	$variables['subNavigation'] = $cck->_module_links($sub_menu[$this->module],
    		array(
    			'template'=>'links_sub_menu',
    			'index' => $this->module
    			)
    		, $variables);
    	
    	print $cck->_view('default', $variables);
    }
    
    function featured()
    {
        global $cck;
    	
    	// get all links from each class controller
    	$menu = $cck->_hooks('hook_links');
    	$sub_menu = $cck->_hooks('hook_module_links');
    	$variables['pageTitle'] = 'Portfolio';
    	$variables['contentTitle'] = 'Featured projects';
    	$variables['menuTitle'] = 'Featured';
    	$variables['content'] = 'featured project';
    	
    	
    	$variables['mainNavigation'] = $cck->_menu_links($menu, 'links_main_menu',$variables);
    	$variables['subNavigation'] = $cck->_module_links($sub_menu[$this->module],
    		array(
    			'template'=>'links_sub_menu',
    			'index' => $this->module
    			), $variables);
    	
    	print $cck->_view('default', $variables);
    }
    
}

?>

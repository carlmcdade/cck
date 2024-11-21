<?php
namespace install;
/**
 * @author Carl McDade 
 * @copyright Carl McDade
 * @since 2011
 * @version 1.0
 * @license MIT
 * 
 * @link http://hardcopy.free.nf Content Connection Kit
 * ==================================================================
 * 
 *                        install.class.inc
 * 
 * ==================================================================
 *
 * @todo 
 *
 */
class install{
	
	private $common;
	public  $menu;
	public  $section;
	public  $module;

    function __construct()
    {
        //Test the Common settings
        $this->module = __NAMESPACE__;
        $this->section = __NAMESPACE__;
    }
    
    /**
    *   Navigation hook for all modules
    *   the array keys appear as $variables in the template file for links
    *   link.tpl.php, spaces will be replaced by underscores.
    */
    
    function __destruct()
    {
    	   //
    }
    
    /**
    Check the installation environment for required PHP modules and install
    directory location. Pull settings from _configuration/config.ini and
    compare to read server host information.
    */
    function install_env_check()
    {
    	
    	global $cck,$ini_settings;
    	$user_settings = array();
    	$install_settings = $ini_settings['install'];
    	
    	
    }

    
}

?>

<?php

/**
 * @author Carl McDade 
 * @copyright Carl McDade
 * @since 2011
 * @version 1.0
 * @license MIT
 * 
 * @link http://fhqk.com Content Connection Kit
 * ==================================================================
 * 
 *                        install.class.inc
 * 
 * ==================================================================
 *
 * @todo 
 * 
 */
namespace install;

// classes used by the global $cck object from the globalspace
use \PDO;
use \PDOException;

// classes used by this module controller class

use \form;
use \Element_Textbox;
use \Element_Textarea;
use \Element_Hidden;
use \Element_Button;

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

    
}

?>

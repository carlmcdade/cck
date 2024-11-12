<?php
namespace category;
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
 *                        blog.class.inc
 * 
 * ==================================================================
 * This CCK example site is built around this blogging module.
 * It handles the blog content type
 *  
 * 
 */

class category{
	
	private $common;

    function __construct()
    {
        //Test the Common settings
        $this->common = Common::get_instance();
    }

    
    
}

?>

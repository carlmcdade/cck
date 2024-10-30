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

namespace example;

use Common;

class example{
	
	private $common;
	public  $menu;
	public  $section;


    function __construct()
    {
        $this->common = \Common::get_instance();
        
        
    }
}

?>
<?php

/**
 * @author Carl McDade 
 * @copyright Carl McDade
 * @since 2011
 * @version 1.0
 * @license MIT
 * 
 * @link http://berlinto.com/berlinto
 * ==================================================================
 * 
 *                        index.php
 * 
 * ==================================================================
 *
 * @todo make a template for this comment
 * 
 */



     global $cck;

// Set tsession_starthe front page by redirectionif(!$_SERVER['QUERY_STRING'])

	$variables = array();
	
	$variables['content'] = "site owner and a list of users";
	
	print $cck->_view('default', $variables);




?>
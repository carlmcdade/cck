<?php


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
 *                        index.php
 * 
 * ==================================================================
 *
 * @todo make a template for this comment
 * 
 */



     global $cck, $ini_settings, $_SESSION;

// Set tsession_starthe front page by redirectionif(!$_SERVER['QUERY_STRING'])

	$variables = array();
	
	$variables['content'] = "site owner and a list of users";
	$variables['INI'] = $ini_settings;
	$variables['CCK'] = $cck;
	$variables['VAR'] = $variables;
	print $cck->_view('default', $variables);




?>
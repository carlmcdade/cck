<?php
ob_start();

/**
 * @author Carl McDade
 * @copyright Carl McDade
 * @since 2011
 * @version 1.0
 * @license Apache 1.0
 *
 * @link http://berlinto.com
 * ==================================================================
 *
 *                        index.php
 *
 * ==================================================================
 *
 * @todo make a template for this comment
 *
 */

define('CCK_ROOT', __DIR__);
require_once('cck.php');
if (file_exists(INI_FILENAME))
{
    $ini_settings = parse_ini_file(INI_FILENAME, true);

}


// Set the front page by redirection
if (!$_SERVER['QUERY_STRING']) header('location:' . $ini_settings['url']['frontpage']);

// Start system and respond to calls
$cck = new CCK();
$cck->_bootstrap();


?>
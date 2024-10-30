<?php

/**
* Full page template file
*/

?>
<!DOCTYPE html>
<html>
<head>
<meta http-equiv="Content-Language" content="en">
<meta http-equiv="Content-Type" content="text/html; charset=windows-1252">
<title>Berlinto Web Architecture</title>
<meta name="description" content="Berlinto a PHP framework for web developers to build on.">
<meta name="keywords" content=" berlinto, drupal, wordpress, framework, cms, hosting, webhosting, server, php, servage">

<title><?php echo (isset($title) ? $title : ''); ?></title>

<link rel="stylesheet" href="css/default.css" type="text/css" />
 
<!--[if IE]>
	<script src="http://html5shiv.googlecode.com/svn/trunk/html5.js"></script><![endif]-->
<!--[if lte IE 7]>
	<script src="js/IE8.js" type="text/javascript"></script><![endif]-->
<!--[if lt IE 7]>
	<link rel="stylesheet" type="text/css" media="all" href="css/ie6.css"/>
<![endif]-->

</head>

<body id="index" class="home">

<header id="banner" class="body">

<section id="page-title" class="body">
<h1><?php echo (isset($page_title) ? $page_title : ''); ?></h1>
</section>

<nav>
<?php echo (isset($main_navigation) ? $main_navigation : ''); ?>
</nav>

<section id="admin-section">
 <?php echo (isset($admin_navigation) ? $admin_navigation : ''); ?>
</section>

</header><!-- /#banner -->


<footer id="post-info" class="body">
<span> The Berlinto project is owned and operated by FHQK Enterprises</span>
<span>FHQK Enterprises © 2012 - Carl McDade - All rights reserved.</span>
<span>No content on this site may be copied without express written consent from Carl McDade.</span>
</footer>

</body>

</html> 


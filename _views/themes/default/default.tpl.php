<!DOCTYPE html>
<html lang="en">
<head>
<meta charset="utf-8" />
<title>Berlinto Web Architecture | <?php echo (isset($page_title) ? $page_title : ''); ?></title>
<meta name="description" content="Berlinto a PHP framework for web developers to build on.">
<meta name="keywords" content=" berlinto, drupal, wordpress, framework, cms, hosting, webhosting, server, php, servage">

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
	<?php echo (isset($navigation) ? $navigation : ''); ?>
</nav>

<?php if(isset($sub_navigation)): ?>
	<div id="sub-menu">
		<?php echo $sub_navigation; ?>
	</div>
<?php endif; ?> 

</header><!-- /#banner -->

<section id="content-title" class="body">
	<h1><?php echo (isset($content_title) ? $content_title : ''); ?></h1>
</section>

<section id="content" class="body">
	<?php echo (isset($content) ? $content : ''); ?>
</section><!-- /#content -->

<footer id="post-info" class="body">
<span> The Berlinto project is owned and operated by FHQK Enterprises</span>
<span>FHQK Enterprises © 2012 - Carl McDade - All rights reserved.</span>
<span>No content on this site may be copied without express written consent from Carl McDade.</span>
</footer>

</body>

</html> 


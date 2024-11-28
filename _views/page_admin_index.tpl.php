<!--page_admin_index --><!DOCTYPE html>
<html>
<head>
<meta http-equiv="Content-Language" content="en">
<meta http-equiv="Content-Type" content="text/html; charset=windows-1252">
<title><?php echo(isset($title) ? $title : 'CCK Administration'); ?></title>
<meta name="description" content="Berlinto a PHP framework for web developers to build on.">
<meta name="keywords" content=" berlinto, drupal, wordpress, framework, cms, hosting, webhosting, server, php, servage">

</head>

<body id="index" class="home">

<header id="banner" class="body">

<section id="page-title" class="page-title">
<span><?php echo(isset($page_title) ? $page_title : ''); ?></span>
</section>

<nav>
<?php echo(isset($main_navigation) ? $main_navigation : ''); ?>
</nav>

<section id="admin-section">
 <?php echo(isset($admin_navigation) ? $admin_navigation : ''); ?>
  <div style="clear:both"></div>
</section>

</header><!-- /#banner -->


<footer id="post-info" class="body">
<span> The Content Connection Kit project is owned and operated by &copy;2010 - Carl McDade - All rights reserved.</span>
<span>No content on this site may be copied without written consent from Carl McDade.</span>
</footer>
<style><?php require('css/admin.css'); ?></style>

</body>

</html> 


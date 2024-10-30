<?php 
if((require 'default_header.tpl.php') == TRUE)
{
    //echo 'default_header.tpl.php'; 
    //exit;
}
else
{
print('<!DOCTYPE html>
<html lang="en">
<head>
<meta charset="utf-8" />
<title>CCK | ' . $pageTitle . '</title>
<meta name="description" content="CCK is a PHP framework for web developers to build on.">
<meta name="keywords" content=" cck, drupal, wordpress, framework, cms, hosting, webhosting, server, php, servage">
<meta name="viewport" content="width=device-width, initial-scale=1">
<link href="https://cdn.jsdelivr.net/npm/bootstrap@5.3.2/dist/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-T3c6CoIi6uLrA9TneNEoa7RxnatzjcDSCmG1MXxSR1GAsXEV/Dwwykc2MPK8M2HN" crossorigin="anonymous">    

<link rel="stylesheet" href="default.css" type="text/css" />
 
</head>

<body>
<script src="https://cdn.jsdelivr.net/npm/bootstrap@5.3.3/dist/js/bootstrap.bundle.min.js" integrity="sha384-YvpcrYf0tY3lHB60NNkmXc5s9fDVZLESaAA55NDzOxhy9GkcIdslK1eN7N6jIeHz" crossorigin="anonymous"></script>
<div class="container my-5">
 <div class="col-lg-8 px-0">
<h1>'.$pageTitle. '</h1></div></div>');
}
?>
<div class="container my-5">

      <div class="col-lg-8 px-0">
              
	      <p class="fs-5">
<?php if(isset($mainNavigation)){
		  echo $mainNavigation;
		}
?>

<?php if(isset($subNavigation)){
		  echo $subNavigation;
		}
?>
</p></div></div>
<!-- /#banner -->
<div class="container my-5">
	<div class="col-lg-8 px-0"><?php echo (isset($contentTitle) ? $contentTitle : ''); ?></div>
	</div>

<div class="container my-5">

      <div class="col-lg-8 px-0">
              
	      <p class="fs-5">
	<?php echo (isset($content) ? $content : ''); ?></p>
</div></div><!-- /#content -->
<?php

if((require 'default_footer.tpl.php') == TRUE)
{
    //echo 'default_header.tpl.php'; 
    //exit;
}
?>
</body>

</html> 
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
 *                             users.tpl.php
 *
 * ==================================================================
 *
 * @todo make a template for this comment
 *
 */
?>

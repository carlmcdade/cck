<!-- template page_blog_view --><!DOCTYPE html>
<html lang="en">
<head>
<meta charset="utf-8" />
<title>CCK | <?php echo(isset($pageTitle) ? $pageTitle : ''); ?></title>
<meta name="description" content="CCK is a PHP framework for web developers to build on.">
<meta name="keywords" content=" cck, drupal, wordpress, framework, cms, hosting, webhosting, server, php, servage">
<meta name="viewport" content="width=device-width, initial-scale=1">
<link rel="apple-touch-icon" sizes="180x180" href="images/favicon/apple-touch-icon.png">
<link rel="icon" type="image/png" sizes="32x32" href="images/favicon/favicon-32x32.png">
<link rel="icon" type="image/png" sizes="16x16" href="images/favicon/favicon-16x16.png">
<link rel="manifest" href="/site.webmanifest">

<link href="https://cdn.jsdelivr.net/npm/bootstrap@5.3.2/dist/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-T3c6CoIi6uLrA9TneNEoa7RxnatzjcDSCmG1MXxSR1GAsXEV/Dwwykc2MPK8M2HN" crossorigin="anonymous">    
<link href="https://vjs.zencdn.net/8.16.1/video-js.css" rel="stylesheet" />

</head>

<body>
<script src="https://cdn.jsdelivr.net/npm/bootstrap@5.3.3/dist/js/bootstrap.bundle.min.js" integrity="sha384-YvpcrYf0tY3lHB60NNkmXc5s9fDVZLESaAA55NDzOxhy9GkcIdslK1eN7N6jIeHz" crossorigin="anonymous"></script>
<script src="https://cdn.jsdelivr.net/npm/quill@2.0.2/dist/quill.js"></script>
<div class="container my-5">

<div class="col-lg-8 px-0">
<h1><?php echo(isset($pageTitle) ? $pageTitle : ''); ?></h1>


     
       
<?php if (isset($mainNavigation)) {
    echo $mainNavigation;
}
?>
    
<!-- /#banner -->
 
<div style="text-align:right;">
<div class="btn-group">        
<?php if (isset($subNavigation)) {
            echo $subNavigation;
        }
?>
	      
        <?php if (isset($adminNavigation)) {
            echo $adminNavigation;
        }
?>
</div></div>
<div style="text-align:center; border-color:#777777; border-style:solid; border-width: 1px 0 1px 0;" class ="fs-4">
<?php
$clearSpace = array("_", "-");
$contentTitle = str_replace($clearSpace, " ", $contentTitle);
$frontCheck = '?'. $_SERVER['QUERY_STRING'];
if ($frontPage == $frontCheck || $urlSection == 'admin' || $urlSection == 'users') {
    echo '<h1>' .(isset($contentTitle) ? $contentTitle : '') .'</h1>';
} else {
    echo '<h1>' .(isset($contentTitle) ? $contentTitle : '') .'</h1>';
    ?>
</div>
<?php  } ?>

    <?php echo(isset($content) ? $content : ''); ?>

        
    <!-- /#content -->
  
<?php require('default_footer.tpl.php'); ?>
   </div>    
</div> 
<style><?php require('css/default.css'); ?></style>
</body>
</html>
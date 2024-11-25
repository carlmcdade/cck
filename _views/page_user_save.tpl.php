<!-- <?php //print_r ($_SERVER); ?>--><!DOCTYPE html>
<html lang="en">
<head>
<meta charset="utf-8" />
<title>CCK | <?php echo (isset($pageTitle) ? $pageTitle : ''); ?></title>
<meta name="description" content="CCK is a PHP framework for web developers to build on.">
<meta name="keywords" content=" cck, drupal, wordpress, framework, cms, hosting, webhosting, server, php, servage">
<meta name="viewport" content="width=device-width, initial-scale=1">
<link href="https://cdn.jsdelivr.net/npm/bootstrap@5.3.2/dist/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-T3c6CoIi6uLrA9TneNEoa7RxnatzjcDSCmG1MXxSR1GAsXEV/Dwwykc2MPK8M2HN" crossorigin="anonymous">    
<link href="https://vjs.zencdn.net/8.16.1/video-js.css" rel="stylesheet" />
<link href="https://cdn.jsdelivr.net/npm/quill@2.0.2/dist/quill.snow.css" rel="stylesheet">

 
</head>

<body>
<script src="https://cdn.jsdelivr.net/npm/bootstrap@5.3.3/dist/js/bootstrap.bundle.min.js" integrity="sha384-YvpcrYf0tY3lHB60NNkmXc5s9fDVZLESaAA55NDzOxhy9GkcIdslK1eN7N6jIeHz" crossorigin="anonymous"></script>
<script src="https://cdn.jsdelivr.net/npm/quill@2.0.2/dist/quill.js"></script>

<!-- Initialize Quill editor -->

<div class="container my-5">

<div class="col-lg-8 px-0">
<h1><?php echo (isset($pageTitle) ? $pageTitle : ''); ?></h1>
</div></div>

<div class="container my-5">

      <div class="col-lg-8 px-0">
              
<?php if(isset($mainNavigation)){
		  echo $mainNavigation;
		}
?>
<div class="btn-group">
<?php if(isset($subNavigation)){
		  echo $subNavigation;
		}
?>

<?php if(isset($adminNavigation)){
		  echo $adminNavigation;
		}
?>
</div>
    
      </div>
    </div>
<!-- /#banner -->

<div class="container my-5">
      <div class="col-lg-8 px-0">
       
         <h1>
         <?php 

             $clearSpace = array("_", "-");
             $contentTitle = str_replace($clearSpace, " ", $contentTitle);
             echo (isset($contentTitle) ? $contentTitle : ''); 
             if (empty($userID))
             	 {
             	 	 $userID = 'shared';
             	 	 $profileImage = 'default_user.jpeg';
             	 	 $userBio = '<p class="fs-5">Cras sit amet nibh libero, in gravida nulla. Nulla vel metus scelerisque ante sollicitudin. Cras purus odio, vestibulum in vulputate at, tempus viverra turpis. Fusce condimentum nunc ac nisi vulputate fringilla. Donec lacinia congue felis in faucibus.</p>
';
             	 }
             	 
             	 

         ?>
         </h1>
       
      
 

   
    <div class="col border border-danger rounded ml-2 mr-2">
    <img style="float:left; width:150px; height:150px;" class="align-self-start m-3 img-fluid" src="images/user_profile/user_id_<?php echo $userID . '/' .$profileImage. ''; ?>" alt="Generic placeholder image">   
    <p  style="margin-right:.75em;margin-left:1em;min-height: 150px;" class="fs-6 mt-2 ml-2 mr-2"><?php echo $userBio; ?></p>
    </div>

          
          <h4><?php echo (isset($userName) ? $userName : $userHandle); ?></h4> 
	      
	      <?php echo (isset($content) ? $content : ''); ?>
         <!-- /#content -->

<?php

if((require 'default_footer.tpl.php') == TRUE)
{
    //echo 'default_header.tpl.php'; 
    //exit;
}
?>
</div></div>
<style>
    @import "css/admin.css";
  </style>
</body>

</html> 
<?php
 
/**
 * @author Carl McDade
 * @copyright Carl McDade
 * @since 2012
 * @version 1.0
 * @license MIT
 *
 * @link http://hardcopy.free.nf
 * ==================================================================
 *
 *                        default.tpl.php
 *
 * ==================================================================
 *
 * @todo make a template for this comment
 *
 */
?>

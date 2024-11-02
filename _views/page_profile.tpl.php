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
<link rel="stylesheet" href="default.css" type="text/css" />
 
</head>

<body>
<script src="https://cdn.jsdelivr.net/npm/bootstrap@5.3.3/dist/js/bootstrap.bundle.min.js" integrity="sha384-YvpcrYf0tY3lHB60NNkmXc5s9fDVZLESaAA55NDzOxhy9GkcIdslK1eN7N6jIeHz" crossorigin="anonymous"></script>
<div class="container my-5">

<div class="col-lg-8 px-0">
<h1><?php echo (isset($pageTitle) ? $pageTitle : ''); ?></h1>
</div></div>

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

<?php if(isset($adminNavigation)){
		  echo $adminNavigation;
		}
?>
</p>
    
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
             	 }
             	 
             	 

         ?>
         </h1>
        </div>
      
</div>
<div class="media container my-5">
  <img  height="200px" width="200px" class="align-self-start mr-3 img-thumbnail" src="images/user_profile/user_id_<?php echo $userID . '/' .$profileImage. ''; ?>" alt="Generic placeholder image">
  <div class="media-body col-lg-8 px-0">
    <h5 class="mt-0"><?php echo $userHandle; ?></h5>
    <p class="fs-5">Cras sit amet nibh libero, in gravida nulla. Nulla vel metus scelerisque ante sollicitudin. Cras purus odio, vestibulum in vulputate at, tempus viverra turpis. Fusce condimentum nunc ac nisi vulputate fringilla. Donec lacinia congue felis in faucibus.</p>
    <p class="fs-5">Donec sed odio dui. Nullam quis risus eget urna mollis ornare vel eu leo. Cum sociis natoque penatibus et magnis dis parturient montes, nascetur ridiculus mus.</p>
  </div>
</div>
<div class="container my-5">
      <div class="col-lg-8 px-0">             
	      <p class="fs-5">
	      <?php echo (isset($content) ? $content : ''); ?></p>
        </div>
    <!-- /#content -->
<div class="container my-5">
      <div class="col-lg-8 px-0">    
        <p class="fs-5">You've successfully loaded up the Content Connection Kit example. It includes <a href="https://getbootstrap.com/">Bootstrap 5</a> via the <a href="https://www.jsdelivr.com/package/npm/bootstrap">jsDelivr CDN</a> 
        <a href"https://github.com/carlmcdade/cck">the code</a> can be downloaded from <a href="https://github.com/carlmcdade/cck">GitHub</a> for your own website.
        </p>   
      </div>
    </div>
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
 * @since 2012
 * @version 1.0
 * @license MIT
 *
 * @link http://berlinto.com/berlinto
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

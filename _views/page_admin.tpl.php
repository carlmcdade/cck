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
</p>

    
      </div>
    </div>
<!-- /#banner -->

<div class="container my-5">
      <div class="col-lg-8 px-0">
       
         
         <?php 

             $clearSpace = array("_", "-");
             $contentTitle = str_replace($clearSpace, " ", $contentTitle);
             $frontCheck = '?'. $_SERVER['QUERY_STRING'];
                     if($frontPage == $frontCheck || $urlSection == 'admin'){
                     	 echo '<h1>' .(isset($contentTitle) ? $contentTitle : '') .'</h1>';
                     }else{
                        echo '<h1>' .(isset($contentTitle) ? $contentTitle : '') .'</h1>';
                        
                        ?>
                            <div class="col text-start border border-primary rounded-3">
     
      <img style="float:left; width:150px; height:relative;margin:1.5em;" class="align-self-start mr-3 img-fluid" src="images/user_profile/user_id_<?php echo $userID . '/' .$profileImage. ''; ?>" alt="Generic placeholder image">     
    <p class="fs-6"><?php echo $userBio; ?></p>
    

      </div>
          
                   <?php  } ?>
         
      
    

          <h4><?php echo (isset($userName) ? $userName : 'test'); ?></h4> 
	      <p class="fs-5">
	      <?php echo (isset($content) ? $content : ''); ?></p>
        
    <!-- /#content -->
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

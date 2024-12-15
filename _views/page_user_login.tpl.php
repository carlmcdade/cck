<?php
if (isset($_SESSION['UserData']) and $_SESSION['UserData']['UserName'] !== 'no name given') {
    
    $content = 'logged in as : '."\n<br>".'<pre>'. print_r($_SESSION['UserData']['UserName'],1).'</pre>
    <form method="POST" name="form_log_out"><button name="user_logout" class="btn btn-secondary" type="submit" formaction="?admin/logout_user">log out</button></form>'. $content;
}else{

    $content = $CCK->_view('forms_admin_login', $VAR);
    ;
}
?>
<?php 



?><!-- page_user_login--><!DOCTYPE html>
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
<script src="js/jquery-3.7.1.min.js"></script>
<script src="js/cck.js"></script>


 
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

<!-- /#banner -->

<div class="container my-5">
      <div class="col-lg-8 px-0">
       
         <h1 class="first-row">
         <?php 
            
             $clearSpace = array("_", "-");
             $contentTitle = str_replace($clearSpace, " ", $contentTitle);
             //echo $messages;
             //echo (isset($loggedInUser) ? $loggedInUser : ' credentials not found in this template'); 
             	 

         ?>
         </h1>
       
	      <?php echo (isset($content) ? $content : 'no content found'); ?>
         <!-- /#content -->

<?php require ('default_footer.tpl.php');?>
</div></div>
<style><?php require('css/users.css'); ?></style>
</body>
</html> 

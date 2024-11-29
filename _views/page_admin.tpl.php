<!-- template page_admin-->
<?php
if (isset($_SESSION['UserData']) and $_SESSION['UserData']['UserName'] !== 'no name given') {
    
    $content = 'logged in as : '."\n<br>".'<pre>'. print_r($_SESSION['UserData']['UserName'],1).'</pre>
    <form method="POST" name="form_log_out"><button name="user_logout" class="btn btn-secondary" type="submit" formaction="?admin/logout_user">log out</button></form>'. $content;
}else{

    //$content = 'Log in as Adminstrator: <form method="POST" name="form_login"><button name="user_login" class="btn btn-secondary" type="submit" formaction="?admin/login_user">log in</button></form>'. $content;
}
?>

<!DOCTYPE html>
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
<link href="css/default.css" rel="stylesheet" />
<script src="https://ajax.googleapis.com/ajax/libs/jquery/3.7.1/jquery.min.js"></script>
<script>

$(document).ready(function() {
  $("#message-alert").hide();

  $("#myWish").click(function showAlert() {
    $("#message-alert").fadeTo(15000, 500).slideUp(500, function() {
      $("#message-alert").slideUp(500);
    });
  });
  

  $("#close-form").click(function(){
    $("#message-alert").hide();
  });
});

</script>
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
<?php

$clearSpace = array("_", "-");
$contentTitle = str_replace($clearSpace, " ", $contentTitle);
$frontCheck = '?'. $_SERVER['QUERY_STRING'];
if ($frontPage == $frontCheck || $urlSection == 'admin' || $urlSection == 'users') {
    echo '<h1>' .(isset($contentTitle) ? $contentTitle : '') .'</h1>';
} else {
    echo '<h1>' .(isset($contentTitle) ? $contentTitle : '') .'</h1>';
}
?>
<div style="text-align:right;">
<div class="btn-group">
<!-- sub navigation  -->
<?php if (isset($subNavigation)) {
    echo $subNavigation;
}
?>


<?php if (isset($adminNavigation)) {
    echo $adminNavigation;
}
?>
</div></div>
<div class="alert-boxes">
  <a title="click here for log in" id="myWish" href="javascript:;" class="btn btn-mini">Login as Administrator</a>
  
</div>
<div class="alert alert-secondary" id="message-alert">

  <?php 
       echo $CCK->_view('forms_admin_login', $VAR);
  ?>
<br>
  <button title="click here to close this form" name="close_form" id="close-form" type="button" class="btn btn-secondary" data-dismiss="alert"> close form </button>

</div>
<?php echo(isset($content) ? $content : ''); ?>
        
    <!-- /#content -->
<!-- footer -->
    <?php

       if ((require 'default_footer.tpl.php') == true) {
           echo '<!-- default_footer -->';
           //exit;
       }
?>

          </div>
</div> 
<style>
  <?php require("css/admin.css"); ?>
</style>
<?php //require("js/default.js"); ?>
</body>
</html> 

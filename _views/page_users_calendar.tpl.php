<!-- template page_users_calendar -->

<?php echo '<!-- <pre>'.print_r($_SESSION, 1).'</pre>-->';


if (isset($_SESSION['UserData'])) {
    $content = '<div style="" class="alert-boxes">
<div>
  <a title="click here for log in" id="myWish" href="javascript:;" class="btn btn-secondary">Logged in as :  '. $loggedInUser .'</a>
</div>
<div class="alert alert-secondary" id="message-alert"><pre>'. print_r($_SESSION, 1).
'</pre><form method="POST" name="form_log_out"><button name="user_logout" class="btn btn-secondary" type="submit" formaction="?admin/logout_user">log out</button>
    <input type="hidden" name="redirect_back" id="redirect-back" value= "'.
      (isset($POST['redirect_back']) ? $_POST['redirect_back'] : 'http://' . $_SERVER['HTTP_HOST'] . $INI['url']['frontpage']).'" />
    </form>
<div style="text-align: right;">
<button title="click here to close this form" name="close_form" id="close-form" type="button" class="btn btn-secondary " data-dismiss="alert"> close form </button>
</div>
</div></div><hr>'. $content;

} else {

    $content = '<div style="" class="alert-boxes">
<div>
    <a title="click here for log in" id="myWish" href="javascript:;" class="btn btn-secondary ">Login here:</a>
</div>
<div class="alert alert-secondary" id="message-alert">'. $CCK->_view('forms_admin_login', $VAR).'<br>
  <div style="text-align: right;">
      <button title="click here to close this form" name="close_form" id="close-form" type="button" class="btn btn-secondary " data-dismiss="alert"> close form </button>
  </div>
</div></div>'. $content;


}


?><!DOCTYPE html>
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
<link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/bootstrap-datepicker/1.10.0/css/bootstrap-datepicker.min.css" integrity="sha512-34s5cpvaNG3BknEWSuOncX28vz97bRI59UnVtEEpFX536A7BtZSJHsDyFoCl8S7Dt2TPzcrCEoHBGeM4SUBDBw==" crossorigin="anonymous" referrerpolicy="no-referrer" />
<script src="js/jquery-3.7.1.min.js"></script>
<script src="https://cdn.jsdelivr.net/npm/bootstrap@5.3.3/dist/js/bootstrap.bundle.min.js" integrity="sha384-YvpcrYf0tY3lHB60NNkmXc5s9fDVZLESaAA55NDzOxhy9GkcIdslK1eN7N6jIeHz" crossorigin="anonymous"></script>
<script src="https://cdnjs.cloudflare.com/ajax/libs/bootstrap-datepicker/1.10.0/js/bootstrap-datepicker.min.js" integrity="sha512-LsnSViqQyaXpD4mBBdRYeP6sRwJiJveh2ZIbW41EBrNmKxgr/LFZIiWT6yr+nycvhvauz8c2nYMhrP80YhG7Cw==" crossorigin="anonymous" referrerpolicy="no-referrer"></script>
<script src="https://cdn.jsdelivr.net/npm/quill@2.0.2/dist/quill.js"></script>
<script src="js/cck.js"></script>
</head>

<body>
<div class="container my-5">

<div class="row">
<h1><?php echo(isset($pageTitle) ? $pageTitle : ''); ?></h1>


     
       
<?php if (isset($mainNavigation)) {
    echo $mainNavigation;
}
?>
    
<!-- /#banner -->
 
<div style="text-align:right;">
<div class="btn-group">        
<?php if (isset($subNavigation) && !empty($subNavigation)) {
    echo $subNavigation;
}
?>
	      
        <?php if (isset($adminNavigation) && !empty($adminNavigation)) {
            echo $adminNavigation;
        }
?>
</div></div>
<?php

$clearSpace = array("_", "-");
$contentTitle = str_replace($clearSpace, " ", $contentTitle);
$frontCheck = '?'. $_SERVER['QUERY_STRING'];
if ($frontPage == $frontCheck || $urlSection == 'admin') {
    $content .=  '<h1 class=" mt-2 text-center border border-secondary border-start-0 border-end-0" style="">' .(isset($contentTitle) ? $contentTitle : '') .'</h1>';
} else {
    $content .=  '<h1 class=" mt-2 text-center border border-secondary border-start-0 border-end-0" style="">' .(isset($contentTitle) ? $contentTitle : '') .'</h1>';
}

?>

    <?php echo $content; ?>
    <div class="row">
        <div class="col" style="vertical-align:top;" class=""><div style="max-width:400px;"><h5 style="text-align: center;padding:.5rem 0" class="sticky">Dates</h5>
            <?php echo(isset($userCalendar) ? $userCalendar : ''); ?></div></div>
    
    
        <div class="col"><div style="max-height:450px;overflow-y:scroll;"><h5 style="text-align: center;padding: .5rem 0" class="sticky">Event types</h5>
             <?php echo(isset($contentTypes) ? $contentTypes : 'content types list'); ?></div></div>
    </div>
    
 
      
    <!-- /#content -->
  
<?php require('default_footer.tpl.php'); ?>

   </div>    
</div> 
<style><?php require('css/users.css'); ?></style>
</body>
</html>
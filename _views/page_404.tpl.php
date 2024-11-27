<meta name="keywords" content=" cck, drupal, wordpress, framework, cms, hosting, webhosting, server, php, servage">
<meta name="viewport" content="width=device-width, initial-scale=1">
<link href="https://cdn.jsdelivr.net/npm/bootstrap@5.3.2/dist/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-T3c6CoIi6uLrA9TneNEoa7RxnatzjcDSCmG1MXxSR1GAsXEV/Dwwykc2MPK8M2HN" crossorigin="anonymous">    

 
</head>

<body>
<script src="https://cdn.jsdelivr.net/npm/bootstrap@5.3.3/dist/js/bootstrap.bundle.min.js" integrity="sha384-YvpcrYf0tY3lHB60NNkmXc5s9fDVZLESaAA55NDzOxhy9GkcIdslK1eN7N6jIeHz" crossorigin="anonymous"></script>
<div class="container my-5">

<div class="col-lg-8 px-0">
<h1><?php echo (isset($pageTitle) ? $pageTitle : ''); ?></h1>
</div>

<?php if(isset($mainNavigation)){
		  echo $mainNavigation;
		}
?>

<?php if(isset($subNavigation)){
		  echo $subNavigation;
		}
?> 
<!-- /#banner -->

<div class="container my-5">
      <div class="col-lg-8 px-0">
       
         
         <h1>
         <?php 

             $clearSpace = array("_", "-");
             $contentTitle = str_replace($clearSpace, " ", $contentTitle);
             echo (isset($contentTitle) ? $contentTitle : ''); 

         ?>
         </h1>
        </div>
      
</div>
<div class="container my-5">

      <div class="col-lg-8 px-0">
              
	      <p class="fs-5"><?php echo (isset($content) ? $content : ''); ?></p>
        </div><!-- /#banner -->

<div id="content-title" class="content-title">
	<span><?php echo (isset($contentTitle) ? $contentTitle : 'Error'); ?></span>
  </div>

<div id="content">
 <?php echo (isset($content) ? $content : ''); ?>
 
  </div>

  require 'default_footer.tpl.php';  //echo 'default_header.tpl.php'; 
    //exit;

?>
        </div>
        </div>
    <!-- /#content -->

    
<style>
  <?php require('css/default.css'); ?>
</style>
</body>

</html> 


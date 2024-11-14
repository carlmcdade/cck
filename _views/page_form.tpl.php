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
<script src="https://cdn.jsdelivr.net/npm/quill@2.0.2/dist/quill.js"></script>

<!-- Initialize Quill editor -->
<script>
  const quill = new Quill(\'#editor\', {
    theme: \'snow\'
  });
</script><div class="container my-5">
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
?></p>
<!-- /#banner -->


              
	      <p class="fs-5"><?php if(isset($content))
	      	                    { 
	      	                    	echo $content;
	      	                    } ?>
	      </p>
	      <?php require 'default_footer.tpl.php'; ?>
        </div>
    <!-- /#content -->
    </div>


</body>
</html>

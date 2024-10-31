
<div class="container my-5">

      <div class="col-lg-8 px-0">
              
	      <p class="fs-5">
<?php 
		  //echo ' form $formMainLinks put tabs here for multiple forms on the same page';
		
?>

<?php 
		  //echo 'form $formSubLinks';
		
?></p></div></div>
<!-- /#banner -->

<div class="container my-5">
      <div class="col-lg-8 px-0">
       <h1> Login </h1>
        </div>
      
</div>
<div class="container my-5">

      <div class="col-lg-8 px-0">
              
	      <p class="fs-5">
              <form action="<?php echo $postUrl; ?>" method="post">
  <div class="mb-3">
    <label for="exampleInputEmail1" class="form-label">Email address</label>
    <input type="email" class="form-control" id="exampleInputEmail1" aria-describedby="emailHelp">
    <div id="emailHelp" class="form-text">email address used to register.</div>
  </div>
  <div class="mb-3">
    <label for="exampleInputPassword1" class="form-label">Password</label>
    <input type="password" class="form-control" id="exampleInputPassword1">
  </div>
  <div class="mb-3 form-check">
    <input type="checkbox" class="form-check-input" id="exampleCheck1">
    <label class="form-check-label" for="exampleCheck1">Keep me logged in</label>
  </div>
  <button type="submit" class="btn btn-primary">Submit</button>
</form>
	      </p>
        </div>
    <!-- /#content -->
<div class="container my-5">
      <h1>Hello, world!</h1>
      <div class="col-lg-8 px-0">
        <p class="fs-5">You've successfully loaded up the Content Connection Kit example. It includes <a href="https://getbootstrap.com/">Bootstrap 5</a> via the <a href="https://www.jsdelivr.com/package/npm/bootstrap">jsDelivr CDN</a>.</p>
    <!-- this paragraph in defaut.tpl.php -->
      </div>
    </div>
<?php

require 'default_footer.tpl.php';  //echo 'default_header.tpl.php'; 
    //exit;

?>

</body>
</html>

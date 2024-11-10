
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
    <input name="username" type="email" class="form-control" id="exampleInputEmail1" aria-describedby="emailHelp">
    <div id="emailHelp" class="form-text">email address used to register.</div>
  </div>
  <div class="mb-3">
    <label for="exampleInputPassword1" class="form-label">Password</label>
    <input name="password" type="password" class="form-control" id="exampleInputPassword1">
  </div>
  <div class="mb-3 form-check">
    <input type="checkbox"  value="continuous_login" name="open_session" class="form-check-input" id="exampleCheck1">
    <label class="form-check-label" for="exampleCheck1">Keep me logged in</label>
  </div>
  <button name="login_send" value="user_credentials" type="submit" class="btn btn-primary">Submit</button>
</form>
	      </p>
        </div>
    <!-- /#content -->


</body>
</html>

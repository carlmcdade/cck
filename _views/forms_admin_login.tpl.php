<!-- start login form-<?php echo $formName; ?>-->
  <h1> Credentials </h1>             
<form name="<?php echo $formName; ?>" id="login-user-<?php echo $formName; ?>" action="<?php echo $postUrl; ?>" method="post">
  
    <label for="exampleInputEmail1" class="form-label">Email address</label>
    <input value="donald@disney.com" title="Use: donald@disney.com for testing" name="Username" type="email" class="form-control" id="exampleInputEmail1" aria-describedby="emailHelp">
    email address used to register.
  
  
    <label for="exampleInputPassword1" class="form-label">Password</label>
    <input value="123456" title="Use :123456" name="Password" type="password" class="form-control" id="exampleInputPassword1">
  
  
    <input type="checkbox"  value="continuous_login" name="open_session" class="form-check-input" id="exampleCheck1">
    <label class="form-check-label" for="exampleCheck1">Keep me logged in</label>
  
  <button name="login_send" value="user_credentials" type="submit" class="btn btn-primary">Submit</button>
  
  <input type="hidden" name="redirect_back" id="redirect-back" value= "<?php echo 'http://' . $_SERVER['HTTP_HOST'] . $_SERVER['REQUEST_URI']; ?>" /> 
</form>
<!-- form end -->
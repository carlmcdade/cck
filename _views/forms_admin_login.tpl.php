<!-- start login form-<?php echo $formName; ?>-->
  <h1> Credentials </h1>             
<form name="<?php echo $formName; ?>" id="login-user-<?php echo $formName; ?>" action="<?php echo $postUrl; ?>" method="post">
  <div class="mb-3">
    <label for="exampleInputEmail1" class="form-label">Email address</label>
    <input name="Username" type="email" class="form-control" id="exampleInputEmail1" aria-describedby="emailHelp">
    <div id="emailHelp" class="form-text">email address used to register.</div>
  </div>
  <div class="mb-3">
    <label for="exampleInputPassword1" class="form-label">Password</label>
    <input name="Password" type="password" class="form-control" id="exampleInputPassword1">
  </div>
  <div class="mb-3 form-check">
    <input type="checkbox"  value="continuous_login" name="open_session" class="form-check-input" id="exampleCheck1">
    <label class="form-check-label" for="exampleCheck1">Keep me logged in</label>
  </div>
  <button name="login_send" value="user_credentials" type="submit" class="btn btn-primary">Submit</button>
</form>
<!-- form end -->
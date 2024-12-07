$(document).ready(function() {
  $("#message-alert").hide();

  $("#myWish").click(function showAlert() {
    $("#message-alert").slideToggle(500);
    });
    
  $("#close-form").click(function(){
    $("#message-alert").slideToggle(500);
  });

  $(document).ready(function() {
    var f = document.getElementById('user-warning-0');
    setInterval(function() {
        f.style.display = (f.style.display == 'none' ? '' : 'none');
    }, 500);

  });
});

$(document).ready(function() {
  $("#message-alert").hide();

  $("#myWish").click(function showAlert() {
    $("#message-alert").slideToggle(500);
    });
    
  $("#close-form").click(function(){
    $("#message-alert").slideToggle(500);
  });

  $("#blog-fields").hide();

  $("#blog-fields-control").click(function showAlert() {
    $("#blog-fields").slideToggle(500);
    });

    $("#comment-fields").hide();

    $("#comment-fields-control").click(function showAlert() {
      $("#comment-fields").slideToggle(500);
      });

    $("#link-fields").hide();

    $("#link-fields-control").click(function showAlert() {
        $("#link-fields").slideToggle(500);
        });

    $("#image-fields").hide();

        $("#image-fields-control").click(function showAlert() {
          $("#image-fields").slideToggle(500);
          });
    $("#block-fields").hide();

          $("#block-fields-control").click(function showAlert() {
            $("#block-fields").slideToggle(500);
            });
          
    
  

  $(document).ready(function() {
    var f = document.getElementById('user-warning-0');
    setInterval(function() {
        f.style.display = (f.style.display == 'none' ? '' : 'none');
    }, 500);

  });

  
});

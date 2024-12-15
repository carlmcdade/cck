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

    $("div.show-attr").hide();
    $("div.show-type-attr").hide();
    
    $("a.target-attr").on('click', function (){
            $("div.show-attr").slideToggle(500);
            $('a.target-attr').toggleText('edit attributes: show', 'edit attributes: hide');
            
            $("a.attr-close").toggle(); //Toggles from hide to show
    });

    $("a.target-type-attr").on('click', function (){
      $("div.show-type-attr").slideToggle(500);
      $('a.target-type-attr').toggleText('info', 'hide');
      $("a.type-attr-close").toggle(); //Toggles from hide to show
    });
        
    $("a.attr-close").on('click', function (event){
            event.stopPropagation();  // do not forget this
            $("div.show-attr").slideToggle(500);
            $('a.target-attr').toggleText('edit attributes: show', 'edit attributes: hide'); 
            $("a.attr-close").hide();//Toggles from hide to show
    });
          
   
  $(document).ready(function() {
    var f = document.getElementById('user-warning-0');
    setInterval(function() {
        f.style.display = (f.style.display == 'none' ? '' : 'none');
    }, 500);

  });

  jQuery.fn.extend({
    toggleText: function(stateOne, stateTwo) {
        return this.each(function() {
            stateTwo = stateTwo || '';
            $(this).text() !== stateTwo && stateOne ? $(this).text(stateTwo) : $(this).text(stateOne);
        });  
    }
  });

  
});

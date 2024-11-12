<div style="text-align:right">
<!--<div style="width:.25em"></div>-->
<div style="" class="dropdown mt-1">
  <button class="btn btn-secondary dropdown-toggle" type="button" data-bs-toggle="dropdown" aria-expanded="false">
    <?php print_r($adminMenuTitle); ?>
  </button>

  <ul class="dropdown-menu">
  <?php foreach($links as $key => $link )
  { 
      print("<li>" . $link . "</li>" . "\n"); 
  } ?>
  </ul>
</div>
</div>

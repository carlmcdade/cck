
<div style="text-align:right">
<div style="margin-left: 1rem;" class="dropdown mt-1">
  <button name="name_sub_menu_<?php echo $elementName; ?>" id="id-sub-menu-<?php echo $elementId; ?>" class="btn btn-secondary dropdown-toggle" type="button" 
  data-bs-toggle="dropdown" aria-expanded="false">
    <?php print($menuTitle); ?>
  </button>

  <ul class="dropdown-menu">
  <?php foreach ($links as $key => $link) {
      print("<li>" . $link . "</li>" . "\n");
  } ?>
  </ul>
</div>
</div>


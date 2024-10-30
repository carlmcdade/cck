<a class="dropdown-item" href="<?php echo (isset($host) ? $host : '..') . '/'; ?>
<?php 
   ?>
<?php echo (isset($ini_settings['url']['install_dir']) ? $directory . '/?': $installDir . '/?'); ?>
<?php echo (isset($path) ? $path : ''); ?>">
<?php echo (isset($text) ? $text : 'link'); ?></a>
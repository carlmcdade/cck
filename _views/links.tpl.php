<a class="dropdown-item" href="<?php echo (isset($host) ? $host : '..') . '/'; ?>
<?php 
   ?>
<?php 
// check to see if cck is in a sub directory of http:// [website]/[directory]
if (isset($ini_settings['url']['install_dir']))
	{
		 echo $ini_settings['url']['install_dir'];
	} else{
		 echo '?'; 
	}
   ?>
<?php echo (isset($path) ? $path : ''); ?>">
<?php echo (isset($text) ? $text : 'link'); ?></a>
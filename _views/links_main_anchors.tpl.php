<a class="btn btn-primary" role="button" href="<?php echo (isset($host) ? $host : '..') . '/'; ?>

<?php 
// check to see if cck is in a sub directory of http:// [website]/[directory]
//$getLocation = explode($installDir, $_SERVER['QUERY_STRING']);


if ($installDir == CCK_ROOT)
{
		 $href = $installDir . '/?';
		 
        if(!empty($devSymlink))
        {
	       $href = $devSymlink .'/?';
        }
	} else{
		 $href = '?'; 
}  
	echo $href;
   ?>
<?php echo (isset($path) ? $path : ''); ?>">
<?php echo (isset($text) ? $text : 'link'); ?></a>
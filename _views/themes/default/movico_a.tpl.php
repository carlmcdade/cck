<?php echo (isset($links) ? $links . '<br />' : ''); ?>
<?php echo (isset($title) ? $title . '<br />' : ''); ?>
<?php echo (isset($name) ? $name . '<br />' : ''); ?>
<?php echo (isset($date) ? $date . '<br />' : ''); ?>
<?php echo (isset($more) ? $more . '<br />' : ''); ?>
<p><?php echo (isset($content) ? $content : ''); ?></p>
<span id="source">Source code:</span>

	<?php
	
	require_once GESHI_PATH;
	
	$source = file_get_contents(CONTROLLERS_PATH .'/'. arg(1) . '.class.inc');
	$geshi = new GeSHi($source, 'php');
	$geshi->set_header_type(GESHI_HEADER_DIV); 
	$geshi->enable_line_numbers(GESHI_FANCY_LINE_NUMBERS);
	echo $geshi->parse_code();
	
	?>
<a href="https://github.com/carlmcdade/Movico-D7">Fork this at Github</a>

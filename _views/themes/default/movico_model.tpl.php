<?php echo (isset($links) ? $links : ''); ?><br />
<p><?php echo (isset($content) ? $content : ''); ?></p>


<?php
    
drupal_set_message('Since we are still in a module many things not available by the Default Drupal
	 system are available automatically to Movico. This message is set in the movico.tpl.php file');
	
?>
<span id="source">Source code:</span>

	<?php
	
	require_once GESHI_PATH;
	
	$source = file_get_contents(MODELS_PATH .'/example.model.inc');
	$geshi = new GeSHi($source, 'php');
	$geshi->set_header_type(GESHI_HEADER_DIV); 
	$geshi->enable_line_numbers(GESHI_FANCY_LINE_NUMBERS);
	echo $geshi->parse_code();
?>
<span id="source">Source code:</span>
<?php
	$source = file_get_contents(CONTROLLERS_PATH .'/'. arg(1) . '.class.inc');
	$geshi = new GeSHi($source, 'php');
	$geshi->set_header_type(GESHI_HEADER_DIV); 
	$geshi->enable_line_numbers(GESHI_FANCY_LINE_NUMBERS);
	echo $geshi->parse_code();
	
	?>
<a href="https://github.com/carlmcdade/Movico-D7">Fork this at Github</a>


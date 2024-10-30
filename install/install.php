


<?php
$path_parts = pathinfo($_SERVER['DOCUMENT_ROOT']."/cck/databases");
$path_partr = pathinfo(__FILE__);

?>

<?php 
$db_location = $_SERVER['DOCUMENT_ROOT']."/cck/databases/".'administration.db';

if(file_exists($db_location)==TRUE)
{ echo "file already found";
}else{
	$db = new SQLite3($db_location);
$db->exec('CREATE TABLE content_types (id INT)(name TEXT)');
$db->exec("INSERT INTO content_types (name) VALUES ('this is a content type')");
$result = $db->query('SELECT * FROM content_types');
var_dump($result->fetchArray());
};



var_dump($path_parts);
var_dump($path_partr);

?>


<p style="text-align:center;font-size:.75rem;clear:both; border-style:solid;border-width:1px 0 0 0;border-color:#cccccc;" class="">The Content Connection Kit project is owned and operated by &copy;2010 - Carl McDade - All rights reserved.</p>
<?php
function convert($size)
{
   $unit=array('b','kb','mb','gb','tb','pb');
   return @round($size/pow(1024,($i=floor(log($size,1024)))),2).' '.$unit[$i];
}

echo '<div style="font-size: .75rem;">'.'This page is using '.convert(memory_get_usage(false)). ' of '. ini_get('memory_limit').' of available memory '."\n"; // 123 kb
$array = [];

for ($i = 1; $i < 10000; $i++) {
    $array[] = substr(sha1((string) $i), 0, 15);

    if ($i % 1000 === 0) {
        //echo 'Usage: ' . convert(memory_get_usage(false)).' -> '."\n";
    }
}

echo 'Peak usage: ' . convert(memory_get_peak_usage(false)).' -> '."\n";
echo '</div>';



?>
<!-- The Content Connection Kit project is owned and operated by &copy;2010 - Carl McDade - All rights reserved.
No content on this site may be copied without express written consent from Carl McDade -->

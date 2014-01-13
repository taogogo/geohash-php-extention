<?php
error_reporting(E_ALL);
echo "version:".GEOHASH_VERSION."\n";
echo(microtime(true)."\n");
$geohash="wm3yr31d2524";
$coord = Geohash::decode($geohash);
print_r($coord);
var_dump($geohash,$coord);

$geohash = Geohash::encode($coord['latitude'],$coord['longitude']);
print_r(Geohash::encode(30.635780068114,104.03160111979,12));
var_dump($geohash);
echo(microtime(true)."\n");

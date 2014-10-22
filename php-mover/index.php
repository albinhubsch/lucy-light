<?php

date_default_timezone_set('Asia/Singapore');

if($_GET['update']){
	echo 'update';
	file_put_contents('./db2.txt', '');
	file_put_contents('./db2.txt', date('Y-m-d H:i:s'));
}else{
	$string = file_get_contents("./db2.txt");
	echo $string;
}
<?php
	$controlvalue = $_GET["control"];
	$cmd = "./IPC ".$controlvalue;
	shell_exec($cmd);
?>
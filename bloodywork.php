<?php
	$controlvalue = escapeshellarg($_GET["control"]);
	$cmd = "./IPC ".$controlvalue;
	shell_exec($cmd);
?>

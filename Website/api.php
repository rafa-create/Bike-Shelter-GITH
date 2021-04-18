<?php
$token="jadorelevelo";
var_dump($_GET);
var_dump($_SERVER);
 


if(!isset($_SERVER["HTTP_AUTHORIZATION"]) || $_SERVER["HTTP_AUTHORIZATION"] === ''){
    echo "Il n'y a pas de Token";
    exit;
}

if($_SERVER["HTTP_AUTHORIZATION"] !== "Bearer ".$token){
    echo $_SERVER["HTTP_AUTHORIZATION"];
    exit;

}
if(!isset($_GET["Aplaces"]) || $_GET["Aplaces"] === ''){
    echo "Veuillez renseigner Aplaces";
    exit;
}

file_put_contents(__DIR__.DIRECTORY_SEPARATOR."places.txt",$_GET["Aplaces"]);

echo "C'est tout bon !";

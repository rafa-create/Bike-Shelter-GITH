<?php
$token="jadorelevelo";

if(!isset($_SERVER["HTTP_AUTHORIZATION"]) || $_SERVER["HTTP_AUTHORIZATION"] === ''){
    echo "Unauthorized"; //car Il n'y a pas de Token
    exit;
}

if($_SERVER["HTTP_AUTHORIZATION"] !== "Bearer ".$token){
    echo "Unauthorized"; //car Il n'y a pas le bon Token
    exit;

}
if(!isset($_GET["Aplaces"]) || $_GET["Aplaces"] === ''){
    echo "Pas de paramètre";//car il faut renseigner Aplaces
    exit;
}

echo "Nombre de places actualisé";
file_put_contents(__DIR__.DIRECTORY_SEPARATOR."places.txt",$_GET["Aplaces"]);
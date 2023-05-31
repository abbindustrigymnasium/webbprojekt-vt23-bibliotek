<!-- Licensed under the MIT license: http://www.opensource.org/licenses/mit-license.php -->

<?php
$config = include("./config.php");

$params = array(
    "barcode" => $_POST["barcode"],
    "borrower" => $_POST["borrower"],
    "branch" => "SPETS",
);

$opts = array(
    CURLOPT_URL => "https://koha-staff.solsiden.xyz/cgi-bin/koha/circ/circulation.pl",
    CURLOPT_POST => true,
    CURLOPT_POSTFIELDS => $params,
    CURLOPT_COOKIE => "CGISESSID=" . $config["auth"],
);

$ch = curl_init();
curl_setopt_array($ch, $opts);
curl_exec($ch);
curl_close($ch);
?>

<html>
    <body>
        <p>Successfully lent out <?php echo $_POST["barcode"]; ?> to <?php echo $_POST["borrower"]; ?></p>
    </body>
</html>

<!doctype html>
<html>
<head>
<meta charset="utf-8">
<title>Bootloader</title>

<link rel="stylesheet" href='https://stackpath.bootstrapcdn.com/bootstrap/4.4.1/css/bootstrap.min.css'>
<script src='https://stackpath.bootstrapcdn.com/bootstrap/4.4.1/js/bootstrap.bundle.min.js'></script>
<link rel="stylesheet" href='https://use.fontawesome.com/releases/v5.7.2/css/all.css'>
<script src='https://cdnjs.cloudflare.com/ajax/libs/jquery/3.2.1/jquery.min.js'></script>

<style>
body {
    background-color: #EBEAEF
}

.container {
    flex-wrap: wrap
}

.card {
    border: none;
    border-radius: 10px;
    background-color: #4270C8;
    width: 350px;
    margin-top: -60px
}

p.mb-1 {
    font-size: 25px;
    color: #9FB7FD
}

.btn-primary {
    border: none;
    background: #5777DE;
    margin-bottom: 60px
}

.btn-primary small {
    color: #9FB7FD
}

.btn-primary span {
    font-size: 13px
}

.card.two {
    border-top-right-radius: 60px;
    border-top-left-radius: 0
}

.form-group {
    position: relative;
    margin-bottom: 2rem
}

.form-control {
    border: none;
    border-radius: 0;
    outline: 0;
    border-bottom: 1.5px solid #E6EBEE
}

.form-control:focus {
    box-shadow: none;
    border-radius: 0;
    border-bottom: 2px solid #8A97A8
}

.form-control-placeholder {
    position: absolute;
    top: 15px;
    left: 10px;
    transition: all 200ms;
    opacity: 0.5;
    font-size: 80%
}

.form-control:focus+.form-control-placeholder,
.form-control:valid+.form-control-placeholder {
    font-size: 80%;
    transform: translate3d(0, -90%, 0);
    opacity: 1;
    top: 10px;
    color: #8B92AC
}

.btn-block {
    border: none;
    border-radius: 8px;
    background-color: #506CCF;
    padding: 10px 0 12px
}

.btn-block:focus {
    box-shadow: none
}

.btn-block span {
    font-size: 15px;
    color: #D0E6FF
}
 
</style>

</head>

<body>
<?php
if($_POST["username"]== "bootloader" && $_POST["password"]== "mkhfh"){

}
else{
echo '<script>alert("Welcome to Geeks for Geeks")</script>'; 
  header ("Location: index.html");
}

?>


  <div class="container d-flex justify-content-center">
    <div class="d-flex flex-column justify-content-between">
        <div class="card mt-3 p-5">
            <div class="logo mb-3"><img src="https://imgur.com/zydrQCr.png"></div>
            <div>
                <p class="mb-1">Start controlling your</p>
                <h4 class="mb-5 text-white">MCU Over The Air!</h4>
				</div> <button class="btn btn-primary btn-lg"><small>Shall we start?</small><span>&nbsp;</span> </button>
        </div>
	<form method="post" action="script.php" enctype="multipart/form-data">		
        <div class="card two bg-white px-5 py-4 mb-3">
            <div class="form-group"><input type="file" class="form-control" id="file" name="file" required></div>
			<button type="submit" class="btn btn-primary btn-block btn-lg mt-1 mb-2" value="Upload" name ="upload" id="upload"><span>Upload!<i class="fas fa-long-arrow-alt-right ml-2"></i></span></button>
        </div>
	</form>	
    </div>
</div>


</body>
</html>
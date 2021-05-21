<?php 

$file_result = "";

//timeout
//calculate difference between two dates

function DateTimDiff($date1 , $date2){
	$dif=array();
	$first = strtotime($date1);
	$second = strtotime($date2);
	$datediff = abs($first - $second); //absolute value
	$dif['s'] = floor($datediff); //seconds
	$dif['m'] = floor($datediff/(60)); //minutes
	$dif['h'] = floor($datediff/(60*60)); // hours
	$dif['d'] = floor($datediff/(60*60*24)); //days
	return $dif;
	}
	
$time = time(); // current time
$file_time = filemtime('download.txt'); // last modifying time for download.txt file
$current_time = date('m/d/Y g:ia' , $time); // convert to a readable formate
$update_time = date('m/d/Y g:ia' , $file_time);
$diff = DateTimDiff($current_time , $update_time)['m'];//difference with minutes

//return download flag to 0 after 5 minutes automatically
if ($diff > 4){
	$myFile=fopen("download.txt", "w") or die("unable to open");
    file_put_contents("download.txt", 0 );
	}


//checking for the uploaded file
if ( (isset($_POST["upload"])) && ($_FILES["file"]["error"] > 0 ) )
{
	//if there was an error while uploading the file
    $file_result .= "No File Uploaded or Invalid File". "<br>" ;
    $file_result .= "Error Code: " . $_FILES["file"]["error"] . "<br>";
} 

elseif ( (isset($_POST["upload"])) && ($_FILES["file"]["error"] == 0) )
{
//if there was no error
//check for download value
    $mydownloadFile=fopen("download.txt", "r") or die("unable to open");
    $isDownloading = file_get_contents("download.txt");

    if($isDownloading == "0")
    {
		//if STM  is not downloading any thing from the server
		$file_name = $_FILES["file"]["name"];
		//save uploaded file name to use it later
		$my_file = fopen("file_name.txt", "w+") or die("unable to open");
		file_put_contents("file_name.txt", $file_name);
		fclose($my_file);
		//allowed extensions
		$file_extension = explode(".",$file_name);
		$file_ext = strtolower(end($file_extension));
		$allowed = array("txt" , "hex");
		
		if(in_array($file_ext , $allowed )){
			$file_result .=
			"Upload: " . $_FILES["file"]["name"] . "<br>" .
			"Type: "  . $_FILES["file"]["type"]. "<br>".
			"Size: "  . ($_FILES["file"]["size"] / 1024) . " Kb<br>" .
			"Temp file:  " . $_FILES["file"]["tmp_name"] . "<br>";
			//save the uploaded file to this specific path
			move_uploaded_file($_FILES["file"]["tmp_name"],
			"/home/vhosts/fota.freevar.com/New directory/" . $_FILES["file"]["name"]);

			$file_result .= "File Upload Successful!"; 
			//update application version
			$metadata=fopen("MetaData.txt", "r") or die("unable to open");
			$metadata_arr = file("MetaData.txt");
			$version_num = $metadata_arr[1][1].$metadata_arr[1][2].$metadata_arr[1][3]; // V001
			$version_num = intval($version_num);
			$version_num = $version_num + 1 ;

			// calculate code size of the hex file
			$file_name = "New directory/" . $file_name;
			$myFile=fopen( $file_name , "r") or die("unable to open");
			$file_array = file($file_name); // save file content in rray
			$array_length = count($file_array); // calculate number of lines

			$total_pages = ceil($array_length/30); // number of pages
			$last_page_size = $array_length%30;  //number of lines in last page
        
			$data = "";
			$code_size=0;
			for($i=0 ; $i < $array_length; $i++)
			{
				$data=$file_array[$i];
				////check the record type if it is 00 then it is a data record
				if($data[7]=="0" && $data[8] == "0")
				{
					//get character count to calculate size
					$temp=$data[1].$data[2];
					//convert to hexadeciemal
					$temp2=hexdec($temp);
					$code_size += $temp2;
				}
			}
			//to make version number in this shape V001
			$str1=sprintf("%03d", $version_num);
			
			//save code size and application version in metadata.txt file
			$Size=fopen("MetaData.txt", "w+") or die("unable to open");
			//file_put_contents("MetaData.txt", $code_size."\r\n".$total_pages."\r\n");
			file_put_contents("MetaData.txt", $code_size."\r\n"."V".$str1."\r\n");
		}
		
		else
		{
			//if file extension is not allowed
			echo " You cannot upload files with this type! ";
		}
		
    }
	
    else
    {
		//if STM is still downloading a previous version
		echo " busy downloading a file, please upload later ";
		
		//timeout 
		/*$mm_file=fopen("timeout.txt", "r") or die("unable to open");
        $file_arr = file("timeout.txt");
        $tries_num = $file_arr[0][0]; 
        $tries_num = intval($tries_num);
        $tries_num = $tries_num + 1 ;
		
		$plus=fopen("timeout.txt", "w+") or die("unable to open");
        file_put_contents("timeout.txt", $tries_num."\r\n");
		
		if ($tries_num == 5){
			$mmFile=fopen("download.txt", "w") or die("unable to open");
            file_put_contents("download.txt", 0);
			file_put_contents("timeout.txt", 0);
		}
		*/  
    }
}
    


if(isset($_GET["download"]) && is_numeric($_GET["download"]))
{
	//recieve download flag value from STM
    $file_result="";
    $myFile=fopen("download.txt", "w") or die("unable to open");
    file_put_contents("download.txt", $_GET["download"]);
}

if(isset($_GET["page"]) && is_numeric($_GET["page"]))
{
	//recieve page number from STM
	$get_content=fopen("file_name.txt", "r") or die("unable to open");
	$content = file_get_contents("file_name.txt");
	$content = "New directory/" . $content;
	
    $file_result="";
    $myFile=fopen($content, "r") or die("unable to open");

    $file_array = file($content);//save hex file in array
    $data="";
    $data2 = "";
    for($i=0; $i < 30 ; $i++)
    {
		//get the desired page line by line
        $line = $file_array[$_GET["page"]*30+$i];
        $line_length = strlen($line);
        $encrypted_line = "";
        // $encrypted_line2 = "";
        $temp1 = "";
        for($j=0; $j<$line_length; $j++)
        {
			//encrypt data
            $temp1 = 122 ^ ord($line[$j]);
			//cast data to character
            $encrypted_line .= chr($temp1);
			
            // $encrypted_line2 .= 122 ^ $temp1;
            // echo $temp1 ;
            // echo "\n";
        }
        
        //concatenate all lines
        $data .= $encrypted_line;
		
		// echo $encrypted_line;
        // $data2 .= $encrypted_line2;
		
		//check for the end of the file
        if($_GET["page"]==($total_pages-1) && $i==($last_page_size-1))
        {
            break;
        }
    }
	
    echo $data;
	
    // echo "\n\n\n";
    // echo $data2;
	//file_put_contents("page.txt", $data);

    fclose($myFile);
	fclose($get_content);
}

echo $file_result;

	?>





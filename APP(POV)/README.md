# ITI-Graduation-Project-FOTA-
Project main purpose is to flash a new software over the air.

## Why:
- Remote Management.
- Allow Updates.
- Fix Bugs.
- Security Enhancement.

## Project Overview:
- Login to the system.
- Upload the hex file to the server.
- STM start checking for updates.
- Bootloader start flashing the app.

![image](https://user-images.githubusercontent.com/32434683/112478577-d55c7700-8d7c-11eb-96ed-ee29a7a11d16.png)


## Demo
![ezgif com-gif-maker](https://user-images.githubusercontent.com/32434683/111859358-07b74000-8949-11eb-8e22-2e9aa7e413d1.gif)

## How it works
### Server Side
- User enters a username and a password.
- If it matches the saved ones, the site redirects him to the upload page.
- If not it will redirect him to login panel again.
- User chooses a hex file and hit upload button.
- Allowed file extensions is .txt, .hex.
- If he tried to upload a file with a different extensions it will return error.
- If STM still downloading other version server will return busy error.
- Open hex file in read mode waiting for STM to send number of desired page.
- Once server gets the number it will start to encrypt the data and send to STM.
- After 5 minutes from starting download, if the STM didn’t receive the pages then there is something wrong and the server will allow uploading updates to fix bugs.
### STM Side
- First we check if there is an application code burnt on the flash memory or not.
- If there wasn’t, we send a command to the server to forbid any modifying to the hex file on the server.
- second we read num. of version and we also read size of file to make sure it doesn’t exceed the maximum range.
- If all was clear, we send a command to the server to receive the hex file page by page.
- We receive the data encrypted so we decrypt and start flashing.
- We check also on the check sum and if there was something wrong, we go to server and get this page again.
- But if there was an application already burnt on flash memory, we check the version number.
- If it matches the one saved on memory we do nothing but if not, we do the previous steps all over again.
### Application(POV)
### Circuit
![image](https://user-images.githubusercontent.com/32434683/112479574-da6df600-8d7d-11eb-86a8-4fc204a73be1.png)
- The hall sensor detects the magnet and generates a falling edge.
- We loop on the array, so every falling edge we display 64 pattern, every 5 elements make a character.



